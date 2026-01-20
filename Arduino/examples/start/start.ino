#include "driver/rtc_cntl.h"
#include "esp_sleep.h"

#define uS_TO_S_FACTOR 1000000  // 微秒到秒的转换系数
#define SLEEP_DURATION 10       // 睡眠时长（秒）

void setup() {
  Serial.begin(115200);
  
  // 配置唤醒源（这里使用定时器唤醒）
  esp_sleep_enable_timer_wakeup(SLEEP_DURATION * uS_TO_S_FACTOR);

  // // 关闭未使用的外设
  // esp_bluedroid_disable();
  // esp_bt_controller_disable();
  
  // 配置所有GPIO为下拉（避免悬空引脚耗电）
  for(int i = 0; i < GPIO_PIN_COUNT; i++) {
    if(ESP_OK != gpio_pulldown_dis(i)) {
      gpio_pulldown_en(i);
    }
    gpio_set_direction((gpio_num_t)i, GPIO_MODE_INPUT);
  }

  Serial.printf("进入深度睡眠，睡眠时长 %d 秒\n", SLEEP_DURATION);
  delay(100);  // 等待串口发送完成
  
  // 进入深度睡眠模式
  esp_deep_sleep_start();
}

void loop() {} // 深度睡眠后会自动重启
