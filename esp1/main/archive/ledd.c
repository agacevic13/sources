#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>


#define PIN 2
#define PIN2 5

void app_main() {
  gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
  gpio_set_direction(PIN2, GPIO_MODE_OUTPUT);
  uint32_t isOn = 0;
  while (true) {
    isOn = !isOn;
    gpio_set_level(PIN2, !isOn);
    gpio_set_level(PIN, isOn);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}