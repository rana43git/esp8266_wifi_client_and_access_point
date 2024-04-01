/*
  This Arduino sketch configures an ESP8266 microcontroller to function as both a WiFi client and an Access Point (AP).
  It creates an HTTP server using the ESP8266WebServer library, responding with a "Hello from ESP8266!" message at the root path ("/").
  The device attempts to connect to an existing WiFi network using provided credentials and sets up its own AP with specified credentials.
  Once connected to WiFi, it prints both IP address of WiFi client and Access Point to the serial monitor for reference.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Define credentials for connecting to existing WiFi network
const char* ssid = "Hi";
const char* password = "12345678#";

// Define credentials for the Access Point (AP) mode
const char* apSSID = "ESP8266_Repeater";
const char* apPassword = "qwertyui";

// Create an instance of ESP8266WebServer on port 80
ESP8266WebServer server(80);

// Function to handle requests to the root path ("/")
void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP8266!</h1>");
}

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Connect to existing WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Print connection status to serial monitor
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wait for connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print IP address when connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  // Set up ESP8266 in AP mode
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(apSSID, apPassword);

  // Print AP IP address to serial monitor
  Serial.println("");
  Serial.println("Access Point Mode Enabled!");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Register the handleRoot function to handle requests to the root path ("/")
  server.on("/", handleRoot);

  // Start the HTTP server
  server.begin();
  Serial.println("");
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
