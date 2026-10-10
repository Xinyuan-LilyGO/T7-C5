# T7-C5

T7-C5 is an ESP32-C5-MINI development board for Wi-Fi 6, Bluetooth, USB, battery-powered and low-power applications.

## Hardware

| Item | Value |
| --- | --- |
| MCU | ESP32-C5-MINI-1-N4 |
| CPU | ESP32-C5, 240 MHz |
| Wireless | 2.4/5 GHz Wi-Fi 6, Bluetooth |
| Flash | 4 MB, QIO, 80 MHz |
| PSRAM | None |
| Logic voltage | 3.3 V |
| USB power input | 5 V |

The USB connector is used for power, programming and serial debug. Do not apply 5 V directly to a GPIO or to the 3.3 V rail.

## Pinout

The numbers below are GPIO numbers. ESP32-C5-MINI module pin numbers are different; for example, UART0 TX/RX are GPIO11/GPIO12 on module pins 39/40.

| Function | GPIO | Notes |
| --- | ---: | --- |
| BOOT button | 28 | Active low; hold while resetting to enter download mode if needed |
| I2C SDA | 2 | Shared with the battery-voltage divider |
| I2C SCL | 3 | Exposed on the CNC1/CNC2 connectors |
| Battery ADC | 2 | VBAT through a 100 kOhm / 100 kOhm divider |
| UART0 TX | 11 | USB/serial debug output; module pin 39 |
| UART0 RX | 12 | USB/serial debug input; module pin 40 |
| USB D- | 13 | Native USB data line |
| USB D+ | 14 | Native USB data line |
| General purpose | 0, 1, 4, 5, 6, 7, 8, 10, 15, 23-27 | Check the schematic before assigning peripherals |

### I2C notes

The board exposes I2C as GPIO2 (SDA) and GPIO3 (SCL), together with 3.3 V and GND on CNC1/CNC2. The board schematic does not add an I2C peripheral, so an external device is required for the scanner to report an address.

Use external pull-up resistors from SDA and SCL to 3.3 V, typically 2.2 kOhm to 4.7 kOhm. Never pull an I2C line up to 5 V. GPIO2 is also connected to the battery divider; avoid driving it while measuring VBAT.

If a scan reports devices once and then reports none, first check that SDA is GPIO2 and SCL is GPIO3, that the external pull-ups and GND are present, and that the target device has not been powered down. Incorrect or floating pins can produce a false first scan.

## PlatformIO

PlatformIO is configured in `platformio.ini` for the `esp32-c5-devkitc-1` board definition. It uses the pioarduino ESP32 platform, Arduino framework, 4 MB flash, no PSRAM, QIO flash mode, and the `NO OTA (2MB APP/2MB SPIFFS)` partition table.

Available environments:

| Environment | Example |
| --- | --- |
| `battery_voltage` | Battery voltage measurement on GPIO2 |
| `deep_sleep_timer` | Timer wake-up from deep sleep |
| `factory` | Wi-Fi, Bluetooth, button and I2C factory test |
| `i2c_test` | I2C bus scanner |
| `light_sleep_timer` | Timer wake-up from light sleep |
| `scan` | Bluetooth LE scan |
| `wifi_access_point` | Wi-Fi access point and HTTP server |
| `wifi_bluetooth_switch` | Switch Wi-Fi and Bluetooth modes with the BOOT button |

Build or upload one environment from the project directory:

```text
pio run -e i2c_test
pio run -e factory -t upload --upload-port COMx
pio device monitor -e factory
```

The first build downloads the ESP32-C5 Arduino framework and toolchain. The local libraries under `Arduino/lib/libraries` are automatically included by PlatformIO.

## Arduino IDE

1. Install the ESP32 Arduino core and select **ESP32C5 Dev Module**.
2. Open a sketch under `Arduino/examples`.
3. Copy the libraries under `Arduino/lib/libraries` to the Arduino libraries directory if the sketch uses them.
4. Use these board settings:

| Setting | Value |
| --- | --- |
| USB CDC On Boot | Enabled |
| CPU Frequency | 240 MHz (Wi-Fi) |
| Flash Frequency | 80 MHz |
| Flash Mode | QIO |
| Flash Size | 4 MB (32 Mb) |
| Partition Scheme | NO OTA (2 MB APP / 2 MB SPIFFS) |
| PSRAM | Disabled |
| Upload Mode | UART0 / Hardware CDC |
| Upload Speed | 921600 |
| USB DFU On Boot | Disabled |
| USB Firmware MSC On Boot | Disabled |
| Zigbee Mode | Disabled |

The ESP32-C5 is not a dual-core ESP32 target; do not select a Core1-only option from documentation for other ESP32 variants.

## Repository layout

```text
Arduino/examples/       Arduino sketches
Arduino/lib/libraries/  Local Button and NTPClient libraries
platformio.ini          PlatformIO environments
partitions_no_ota_2mb.csv
```

## References

- [T7-C5 schematic](Hardware/T7-C5.pdf)
- [ESP32-C5-MINI-1 datasheet](Doc/esp32-c5-mini-1_datasheet_cn_v0.1_0620.pdf)
- [ESP32-C5 documentation](https://www.espressif.com/en/products/socs/esp32-c5)
- [ESP32 Arduino core](https://github.com/espressif/arduino-esp32)
- [PlatformIO](https://platformio.org/)
