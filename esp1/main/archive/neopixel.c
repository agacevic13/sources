#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define RED_PIN     GPIO_NUM_14
#define BLUE_PIN    GPIO_NUM_21
#define GREEN_PIN   GPIO_NUM_9

// LED state tracking
static int current_led = 0;

// Timer callback function
void timer_callback(void* arg)
{
    // Turn off all LEDs
    gpio_set_level(RED_PIN, 0);
    gpio_set_level(BLUE_PIN, 0);
    gpio_set_level(GREEN_PIN, 0);
    
    // Turn on the current LED
    switch (current_led)
    {
        case 0:
            gpio_set_level(RED_PIN, 1);
            current_led = 1;
            break;
        case 1:
            gpio_set_level(BLUE_PIN, 1);
            current_led = 2;
            break;
        case 2:
            gpio_set_level(GREEN_PIN, 1);
            current_led = 0;
            break;
    }
}

void app_main(void)
{
    // Configure GPIO pins as outputs
    gpio_set_direction(RED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLUE_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_PIN, GPIO_MODE_OUTPUT);
    
    // Create a high-resolution timer
    const int timer_interval_ms = 500; // 500 ms for each LED
    esp_timer_handle_t timer;
    esp_timer_create_args_t timer_args = {
        .callback = timer_callback,
        .name = "led_timer"
    };
    
    // Create the timer
    esp_timer_create(&timer_args, &timer);
    
    // Start the timer
    esp_timer_start_periodic(timer, timer_interval_ms * 1000); // Convert ms to us

    // Main loop can be empty or used for other tasks
    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
