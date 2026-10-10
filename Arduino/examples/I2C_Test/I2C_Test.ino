#include <Arduino.h>
#include <Wire.h>

#include "config.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println("T7-C5 I2C scanner");
}

void loop() {
  uint8_t devices = 0;

  Serial.println("Scanning I2C bus...");
  for (uint8_t address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Found device at 0x%02X\n", address);
      ++devices;
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found");
  }
  Serial.println("Scan complete");
  delay(2000);
}
