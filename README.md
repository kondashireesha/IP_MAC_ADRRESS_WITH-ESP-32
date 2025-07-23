# 📡 ESP32 Wi-Fi IP & MAC Address Printer

This project demonstrates how to connect an **ESP32** to a Wi-Fi network and print its **IP address** and **MAC address** to the serial monitor using the **ESP-IDF framework**.

##  What This Project Does

- Connects ESP32 to your Wi-Fi network.
- Prints the IP address assigned by your router (via DHCP).
- Prints the device’s unique 6-byte MAC address.
- Logs everything via the serial terminal using `ESP_LOGI()`.

## 🛠️ Tools & Requirements

- ESP32 Dev Board (e.g., ESP32-WROOM)
- ESP-IDF (version 5.x recommended)
- USB Cable for flashing
- Serial terminal (built into ESP-IDF monitor)
- A working 2.4 GHz Wi-Fi network
📁 Project Structure

IP_MAC_Printer_ESP32/
├── CMakeLists.txt
├── main/
│ ├── CMakeLists.txt
│ └── main.c ← Your source code
└── sdkconfig (auto-generated) 
## 🔌 Hardware Setup

No extra components needed.  
Just connect your ESP32 board to your PC via USB. 

Add Your Wi-Fi Credentials
Open main/main.c and replace these lines with your network name and password:

//Add Your Wi-Fi Credentials
#define WIFI_SSID "Your_SSID"        // Replace with your Wi-Fi name
#define WIFI_PASS "Your_PASSWORD"
Make sure ESP-IDF is already set up in your system.

//Make sure ESP-IDF is already set up in your system.
idf.py menuconfig      # Optional (only if you need to configure)
idf.py build
idf.py -p COMx flash   # Replace COMx with your port (e.g., COM3 or /dev/ttyUSB0)
idf.py -p COMx monitor  
//Expected Output on Serial Monitor
bash

I (1234) WiFi_Info: Connecting to Wi-Fi...
I (4567) WiFi_Info: IP Address: 192.168.1.104
I (4567) WiFi_Info: Connected to SSID: Home_Network
I (4567) WiFi_Info: MAC Address: 24:6F:28:A1:B2:C3
