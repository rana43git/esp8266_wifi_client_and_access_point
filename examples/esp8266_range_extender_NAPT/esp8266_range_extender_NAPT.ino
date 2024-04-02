/*
 * This Arduino sketch configures an ESP8266 microcontroller to function as both a WiFi client and an Access Point (AP).
 * 
 * The device attempts to connect to an existing WiFi network using provided credentials and sets up its own AP with specified credentials.
 * Once connected to WiFi, it prints both IP address of WiFi client and Access Point to the serial monitor for reference.
 * 
 * This module can deliver internet access from station to the access point.
 * But void loop is not calling.
*/

// NAPT example released to public domain

#if LWIP_FEATURES && !LWIP_IPV6

#define HAVE_NETDUMP 0

#ifndef STASSID
#define STASSID "Hi"
#define STAPSK "12345678#"

#define NEWSSID "ESP8266_Repeater"
#define NEWPSK "qwertyui"

#endif

#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>

#define NAPT 1000
#define NAPT_PORT 10

#if HAVE_NETDUMP

#include <NetDump.h>

void dump(int netif_idx, const char* data, size_t len, int out, int success) {
  (void)success;
  Serial.print(out ? F("out ") : F(" in "));
  Serial.printf("%d ", netif_idx);

  // optional filter example: if (netDump_is_ARP(data))
  {
    netDump(Serial, data, len);
    // netDumpHex(Serial, data, len);
  }
}
#endif

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("\n=====================================================\nNAPT Range extender\n");
  Serial.printf("Heap on Start: %d\n", ESP.getFreeHeap());
  Serial.printf("Connecting ");

#if HAVE_NETDUMP
  phy_capture = dump;
#endif

  // first, connect to STA so we can get a proper local DNS server
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.printf("\n\nSTA IP: %s (dns: %s / %s)\n", WiFi.localIP().toString().c_str(), WiFi.dnsIP(0).toString().c_str(), WiFi.dnsIP(1).toString().c_str());

  // By default, DNS option will point to the interface IP
  // Instead, point it to the real DNS server.
  // Notice that:
  // - DhcpServer class only supports IPv4
  // - Only a single IP can be set
  auto& server = WiFi.softAPDhcpServer();
  server.setDns(WiFi.dnsIP(0));

  WiFi.softAPConfig(  // enable AP, with android-compatible google domain
    IPAddress(172, 217, 28, 254), IPAddress(172, 217, 28, 254), IPAddress(255, 255, 255, 0));
  WiFi.softAP(NEWSSID, NEWPSK);
  Serial.printf("AP IP: %s\n\n", WiFi.softAPIP().toString().c_str());

  Serial.printf("Heap Before: %d\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK) {
      Serial.printf("\nWiFi Network '%s' with '%s' password is now NATed behind '%s'\n\n", NEWSSID, NEWPSK, STASSID);
    }
  }
  Serial.printf("Heap After NAPT Initialization: %d\n", ESP.getFreeHeap());
  if (ret != ERR_OK) {
    Serial.printf("NAPT Initialization Failed!\n");
  }
}

#else

void setup() {
  Serial.begin(115200);
  Serial.printf("\n\nNAPT not supported in this configuration\n");
}

#endif

void loop() {}
