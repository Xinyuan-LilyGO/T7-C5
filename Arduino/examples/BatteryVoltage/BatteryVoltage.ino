/*
  Read the T7-C5 battery voltage through GPIO2.

  On the T7-C5 board, VBAT is connected to GPIO2 through a voltage divider:

      VBAT --- 100 kOhm --- GPIO2 --- 100 kOhm --- GND

  The voltage at GPIO2 is half of the battery voltage.
*/

#include <Arduino.h>

constexpr uint8_t BATTERY_ADC_PIN = 2;
constexpr float DIVIDER_R1_OHMS = 100000.0f;
constexpr float DIVIDER_R2_OHMS = 100000.0f;
constexpr float VOLTAGE_CALIBRATION = 1.0f;
constexpr uint8_t SAMPLE_COUNT = 32;
constexpr uint32_t SAMPLE_INTERVAL_MS = 2;

uint32_t readAveragedMilliVolts() {
  uint32_t sum = 0;

  // Discard the first conversion after the ADC has been idle.
  analogReadMilliVolts(BATTERY_ADC_PIN);

  for (uint8_t i = 0; i < SAMPLE_COUNT; ++i) {
    sum += analogReadMilliVolts(BATTERY_ADC_PIN);
    delay(SAMPLE_INTERVAL_MS);
  }

  return sum / SAMPLE_COUNT;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);
  analogSetPinAttenuation(BATTERY_ADC_PIN, ADC_11db);

  Serial.println("T7-C5 GPIO2 battery voltage example");
}

void loop() {
  const uint32_t adcMilliVolts = readAveragedMilliVolts();
  const float dividerRatio = (DIVIDER_R1_OHMS + DIVIDER_R2_OHMS) / DIVIDER_R2_OHMS;
  const float batteryVoltage = adcMilliVolts * dividerRatio * VOLTAGE_CALIBRATION / 1000.0f;

  Serial.printf("GPIO2: %lu mV, Battery: %.3f V\n",
                static_cast<unsigned long>(adcMilliVolts), batteryVoltage);

  delay(1000);
}
