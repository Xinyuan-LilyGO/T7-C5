#include <Arduino.h>
#include <Button.h>
#include "config.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// 配置5GHz WiFi信息（根据你的网络修改）
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 8 * 3600, 60000);

int scanTime = 5;  //In seconds
BLEScan* pBLEScan;

WiFiUDP Udp;

Button button1(PIN_BOOT);  // Connect your button between pin 2 and GND
uint32_t chipId = 0;
static bool board_test_is_over = true;

void ScanWiFi();
void button_callck(void);

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    // Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    // 获取设备名称（可能为空）
    // const char* name = advertisedDevice.getName().c_str();

    // // 获取MAC地址（强制转换格式）
    // String addr = advertisedDevice.getAddress().toString();

    // // 获取信号强度
    // int rssi = advertisedDevice.getRSSI();
    // 完整打印设备信息
    // Serial.printf("[BLE] %s | %s | RSSI: %ddBm\n",
    //               name ? name : "UNKNOWN",  // 处理空名称情况
    //               addr.c_str(),
    //               rssi);
  }
};

void setup(void) {
  Serial.begin(115200);
  button1.begin();
  WiFi.STA.begin();
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();  //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);  //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  delay(1000);
  Serial.println("-------------------------------------");
  Serial.println("Board:T7-C5");
  Serial.println("Factory examples!!!");
  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  Serial.print("Chip ID: ");
  Serial.println(chipId);
  Serial.printf("CPU freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("available RAM: %d KB\n", ESP.getFreeHeap() / 1024);
}

void loop() {
  if (button1.pressed()) {
    Serial.println("[success] boot btn pressed!!!");
    if (board_test_is_over) {
      button_callck();
    }
  }
  delay(100);
}

void button_callck(void) {
  board_test_is_over = false;
  Serial.println("-------------------------------------");

  Serial.println("2.4 Ghz wifi band mode scan:");
  WiFi.setBandMode(WIFI_BAND_MODE_2G_ONLY);
  ScanWiFi();

  Serial.println("5 Ghz wifi band mode scan:");
  WiFi.setBandMode(WIFI_BAND_MODE_5G_ONLY);
  ScanWiFi();

  BLEScanResults* foundDevices;
  Serial.println("BLE Devices scan:");
  foundDevices = pBLEScan->start(scanTime, false);
  int ble_scan_count = foundDevices->getCount();
  if (ble_scan_count > 0) {
    Serial.print("[success] BLE Scan success, count:");
    Serial.println(ble_scan_count);
  } else {
    Serial.print("[error] There is no bluetooth nearby. Please check!!!");
  }
  pBLEScan->clearResults();  // delete results fromBLEScan buffer to release memory
  Serial.println("-------------------------------------");
  Serial.println("Get Current Time:");
  WiFi.begin(ssid, password);
  int time_count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    time_count++;
    if (time_count > 20) {
      Serial.println("[error] WIFI connect timeout!!!");
      return;
    }
  }
  Serial.printf("%s is connect", ssid);

  timeClient.begin();
  timeClient.update();
  Serial.print("[success] get time success!!!,current time:");
  Serial.println(timeClient.getFormattedTime());
  board_test_is_over = true;
}

void ScanWiFi() {
  Serial.println("Scan start");
  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("[error] no networks found");
    Serial.println("[error] There is no Wi-Fi nearby. Please check!!!");
  } else {
    // Serial.print(n);
    // Serial.println(" networks found");
    // Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
    // for (int i = 0; i < n; ++i) {
    //   // Print SSID and RSSI for each network found
    //   Serial.printf("%2d", i + 1);
    //   Serial.print(" | ");
    //   Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
    //   Serial.print(" | ");
    //   Serial.printf("%4ld", WiFi.RSSI(i));
    //   Serial.print(" | ");
    //   Serial.printf("%2ld", WiFi.channel(i));
    //   Serial.print(" | ");
    //   switch (WiFi.encryptionType(i)) {
    //     case WIFI_AUTH_OPEN: Serial.print("open"); break;
    //     case WIFI_AUTH_WEP: Serial.print("WEP"); break;
    //     case WIFI_AUTH_WPA_PSK: Serial.print("WPA"); break;
    //     case WIFI_AUTH_WPA2_PSK: Serial.print("WPA2"); break;
    //     case WIFI_AUTH_WPA_WPA2_PSK: Serial.print("WPA+WPA2"); break;
    //     case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-EAP"); break;
    //     case WIFI_AUTH_WPA3_PSK: Serial.print("WPA3"); break;
    //     case WIFI_AUTH_WPA2_WPA3_PSK: Serial.print("WPA2+WPA3"); break;
    //     case WIFI_AUTH_WAPI_PSK: Serial.print("WAPI"); break;
    //     default: Serial.print("unknown");
    //   }
    //   Serial.println();
    //   delay(10);
    // }
    Serial.printf("[success] WiFi scan count:");
    Serial.println(n);
  }

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();
  Serial.println("-------------------------------------");
}