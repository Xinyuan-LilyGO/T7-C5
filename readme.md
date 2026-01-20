<h1 align = "center">🏍 T7-C5 💦</h1>

## Introduction
The T7-C5 is a development board based on the ESP32C5-MINI module, featuring the high-performance ESP32C5 dual-mode Wi-Fi 6 and Bluetooth 5.0 chip, suitable for IoT applications. This development board integrates rich peripheral interfaces for rapid development and debugging.

## Pin Definition
| Pin Number | Name     | PIN  |
| ---------- | -------- | ---- |
| 1          | BOOT_PIN | IO28 |
| 2          | USB D+   | IO14 |
| 3          | USB D-   | IO13 |
| 4          | TXD      | IO39 |
| 5          | RXD      | IO40 |
| 6          | GPIO     | IO8  |
| 7          | GPIO     | IO15 |
| 8          | GPIO     | IO23 |
| 9          | GPIO     | IO24 |
| 10         | GPIO     | IO25 |
| 11         | GPIO     | IO26 |
| 12         | GPIO     | IO27 |
| 13         | GPIO     | IO10 |
| 14         | GPIO     | IO7  |
| 15         | GPIO     | IO1  |
| 16         | GPIO     | IO0  |
| 17         | GPIO     | IO6  |
| 18         | GPIO     | IO5  |
| 19         | GPIO     | IO4  |
| 20         | GPIO     | IO3  |
| 21         | GPIO     | IO2  |

## USB Interface
The board is equipped with a USB interface for:
- Downloading programs to the ESP32-C5 chip
- Debugging programs via serial port

## Precautions
- Please ensure the power supply voltage is 5V through the USB interface

## Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/software)

2. Copy all files under `Arduino/lib/` and paste them into the Arduion library path (generally `C:\Users\YourName\Documents\Arduino\libraries`);

3. Open the Arduion IDE and click `File->Open` in the upper left corner to open an example in `Arduino/example/xxx.ino` under this item;

4. Then configure Arduion. After the configuration is completed in the following way, you can click the button in the upper left corner of Arduion to compile and download;

| Arduino IDE Setting                  | Value                          |
| ------------------------------------ | ------------------------------ |
| Board                                | **ESP32C5 Dev Module**         |
| Port                                 | Your port                      |
| USB CDC On Boot                      | Enable                         |
| CPU Frequency                        | 240MHZ(WiFi)                   |
| Core Debug Level                     | None                           |
| USB DFU On Boot                      | Disable                        |
| Erase All Flash Before Sketch Upload | Disable                        |
| Events Run On                        | Core1                          |
| Flash Frequency                      | 80Mhz                          |
| Flash Mode                           | QIO                            |
| Flash Size                           | **4MB(32Mb)**                  |
| Arduino Runs On                      | Core1                          |
| USB Firmware MSC On Boot             | Disable                        |
| Partition Scheme                     | **NO OTA(2MB APP/2MB SPIFFS)** |
| PSRAM                                | Disable                        |
| Upload Mode                          | **UART0/Hardware CDC**         |
| Upload Speed                         | 921600                         |
| Zigbee Mode                          | Disable                        |

## References
- [ESP32-C5 Official Documentation](https://www.espressif.com/)
