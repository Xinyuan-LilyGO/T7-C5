# T7-C5 开发板

T7-C5 是一款基于 ESP32-C5-MINI 的开发板，适用于 Wi-Fi 6、蓝牙、USB、锂电池和低功耗应用。

## 硬件参数

| 项目 | 参数 |
| --- | --- |
| MCU | ESP32-C5-MINI-1-N4 |
| CPU | ESP32-C5，240 MHz |
| 无线 | 2.4/5 GHz Wi-Fi 6、蓝牙 |
| Flash | 4 MB，QIO，80 MHz |
| PSRAM | 无 |
| 逻辑电平 | 3.3 V |
| USB 输入 | 5 V |

USB 接口用于供电、下载和串口调试。不要把 5 V 直接接到 GPIO 或 3.3 V 电源轨。

## 引脚定义

下表中的编号均为 GPIO 编号，不是 ESP32-C5-MINI 模组物理引脚编号。例如 UART0 的 TX/RX 是 GPIO11/GPIO12，对应模组物理引脚 39/40。

| 功能 | GPIO | 说明 |
| --- | ---: | --- |
| BOOT 按键 | 28 | 低电平有效；下载失败时可在复位时按住 |
| I2C SDA | 2 | 与电池电压分压采样复用 |
| I2C SCL | 3 | CNC1/CNC2 接口引出 |
| 电池 ADC | 2 | VBAT 通过 100 kOhm / 100 kOhm 分压接入 |
| UART0 TX | 11 | USB/串口调试输出；模组物理脚 39 |
| UART0 RX | 12 | USB/串口调试输入；模组物理脚 40 |
| USB D- | 13 | 原生 USB 数据线 |
| USB D+ | 14 | 原生 USB 数据线 |
| 通用 GPIO | 0、1、4、5、6、7、8、10、15、23-27 | 分配外设前请参考原理图 |

### I2C 注意事项

开发板在 CNC1/CNC2 接口引出了 GPIO2（SDA）、GPIO3（SCL）、3.3 V 和 GND。原理图中没有板载 I2C 外设，使用扫描例程时需要外接 I2C 设备。

SDA 和 SCL 需要外接上拉电阻到 3.3 V，常用值为 2.2 kOhm 到 4.7 kOhm。禁止把 I2C 上拉到 5 V。GPIO2 同时连接电池分压电路，测量电池电压时不要让外部设备主动驱动该引脚。

如果第一次扫描能找到地址、第二次却显示没有设备，应先确认 SDA 为 GPIO2、SCL 为 GPIO3，检查上拉电阻和共地，并确认外设没有掉电。引脚接错或总线悬空时，首轮扫描可能出现假地址。

## PlatformIO

项目根目录的 `platformio.ini` 已配置 `esp32-c5-devkitc-1` 环境，使用 pioarduino ESP32 平台和 Arduino 框架，参数为 4 MB Flash、无 PSRAM、QIO、80 MHz，以及 `NO OTA（2 MB APP / 2 MB SPIFFS）` 分区表。

可用环境如下：

| 环境 | 例程 |
| --- | --- |
| `battery_voltage` | GPIO2 电池电压测量 |
| `deep_sleep_timer` | 定时器深度睡眠唤醒 |
| `factory` | Wi-Fi、蓝牙、按键和 I2C 工厂测试 |
| `i2c_test` | I2C 总线扫描 |
| `light_sleep_timer` | 定时器浅睡眠唤醒 |
| `scan` | BLE 扫描 |
| `wifi_access_point` | Wi-Fi AP 和 HTTP 服务 |
| `wifi_bluetooth_switch` | 使用 BOOT 按键切换 Wi-Fi/蓝牙模式 |

在项目根目录执行：

```text
pio run -e i2c_test
pio run -e factory -t upload --upload-port COMx
pio device monitor -e factory
```

首次编译时 PlatformIO 会下载 ESP32-C5 Arduino 框架和工具链。`Arduino/lib/libraries` 下的本地库会由 PlatformIO 自动加入。

## Arduino IDE

1. 安装 ESP32 Arduino Core，并选择 **ESP32C5 Dev Module**。
2. 打开 `Arduino/examples` 下的例程。
3. 如果例程使用本地库，将 `Arduino/lib/libraries` 下的库复制到 Arduino 的 libraries 目录。
4. 使用以下开发板设置：

| 设置项 | 值 |
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

ESP32-C5 不是双核 ESP32，不要照搬其他 ESP32 型号文档中的 Core1 配置。

## 目录结构

```text
Arduino/examples/       Arduino 例程
Arduino/lib/libraries/  Button 和 NTPClient 本地库
platformio.ini          PlatformIO 环境配置
partitions_no_ota_2mb.csv
```

## 参考资料

- [T7-C5 原理图](Hardware/T7-C5.pdf)
- [ESP32-C5-MINI-1 数据手册](Doc/esp32-c5-mini-1_datasheet_cn_v0.1_0620.pdf)
- [ESP32-C5 官方资料](https://www.espressif.com/en/products/socs/esp32-c5)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [PlatformIO](https://platformio.org/)
