# ESP8266 Wi-Fi Client and Access Point Mode

This project demonstrates how to configure an ESP8266 to operate simultaneously as both a **Wi-Fi station (client)** and an **Access Point (AP)**. Devices can connect to your ESP device as an AP while it also connects to another Wi-Fi network.

## 🔍 Overview

The ESP8266 is configured in `WIFI_AP_STA` mode:
- **AP mode**: Host its own network so other devices can connect.
- **Station mode**: Connect to an external Wi-Fi network (router or hotspot).

## ⚙️ Features

- Operates in dual mode: Client + Access Point  
- Soft AP with custom SSID and password  
- Automatically connects to external Wi-Fi on startup  
- Serial output of both AP IP and Station IP  
- Lightweight Arduino sketch for seamless integration  

## 📂 Repository Structure

```
/ (root)
├── sketch.ino             # Main Arduino sketch
├── README.md
└── LICENSE (optional)
```

## 📥 Prerequisites

- **Arduino IDE** or **PlatformIO** with ESP8266 support  
- ESP8266 development board (NodeMCU, Wemos D1 mini, etc.)  
- Include libraries:
  - `ESP8266WiFi.h`

## 🚀 Setup & Upload

1. Clone the repository:
   ```bash
   git clone https://github.com/rana43git/esp8266_wifi_client_and_access_point.git
   cd esp8266_wifi_client_and_access_point
   ```
2. Open the `.ino` file in Arduino IDE or PlatformIO.
3. Customize the following parameters in the sketch:
   ```cpp
   const char* wifi_ssid     = "YourHomeSSID";
   const char* wifi_password = "YourHomePassword";
   const char* ap_ssid       = "ESP_AP";
   const char* ap_password   = "apPassword";
   ```
4. Select your ESP8266 board and upload.

## 🌐 How It Works

- **Setup**:
  ```cpp
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
  WiFi.begin(wifi_ssid, wifi_password);
  ```
- **AP Mode**: Start a local network for client devices (e.g., phones, laptops).
- **Client Mode**: Connect to an existing Wi-Fi network as a client.
- **Serial Output**:
  - AP IP (e.g., `192.168.4.1`)
  - Station IP from your home router

## 🛠️ Code Behavior Summary

1. ESP boots up and starts in dual-mode (AP + Station).
2. Hosts an AP where other devices can connect.
3. Attempts to join your specified Wi-Fi network.
4. Prints both IP addresses in Serial Monitor.
5. No extra control logic is implemented in this example (loop is empty).

## ⚡ Usage Example

- After upload and reboot:
  1. Use the Serial Monitor (baud 115200) to see IP addresses.
  2. Connect your client device to the ESP AP using given SSID/password.
  3. ESP also connects to your home network if credentials are correct.

## 🌟 Customization Ideas

| Feature                        | Customization Guide                                           |
|-------------------------------|---------------------------------------------------------------|
| Wi-Fi credentials             | Change `wifi_ssid` and `wifi_password` in the sketch         |
| AP SSID/password              | Modify `ap_ssid` and `ap_password` variables                  |
| Additional functionality      | Use `WiFiClient` or `ESP8266WebServer` for HTTP APIs         |
| Logic in loop()               | Add communication between devices or servers in `loop()`     |

## 📜 License

Add your preferred open-source license here (e.g. MIT, Apache 2.0).

## 👨‍💻 Author

**Md. Shohel Rana (rana43git)**  
GitHub: [rana43git](https://github.com/rana43git)