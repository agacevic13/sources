#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define PIN 35
#define SWITCH 15

void app_main(void)
{
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SWITCH, GPIO_MODE_INPUT);
    
    gpio_pulldown_en(SWITCH);
    gpio_pullup_dis(SWITCH);
    
    while(true)
    {
       int level = gpio_get_level(SWITCH);

        gpio_set_level(PIN, level);
        vTaskDelay(1);
    }

} 