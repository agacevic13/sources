#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "driver/gpio.h"



//freertos high resolution timer example
//cale
int LED1_PIN = 13;
int LED2_PIN = 15;
int LED3_PIN = 17;

void timer_callback(void * args)
{
    // int pin = *((int *)args);
    static bool on;
    on = !on;
    gpio_set_level(pin, on);
}

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    
        const esp_timer_create_args_t esp_timer_create_args = 
        {
            .callback = timer_callback,
            .name = "my timer",
            .arg = &LED1_PIN
        };
        esp_timer_handle_t esp_timer_handle;
        esp_timer_create(&esp_timer_create_args, &esp_timer_handle);
        esp_timer_start_periodic(esp_timer_handle, 50);

        const esp_timer_create_args_t esp_timer_create_args = 
        {
            .callback = timer_callback,
            .name = "my timer",
            .arg = &LED2_PIN
        };

        int x = 0;
        while(true)
        {
            esp_timer_dump(stdout);
            vTaskDelay( 1000 / portTICK_PERIOD_MS);
            if(x++ == 5)
            {
                esp_timer_stop(esp_timer_handle);
                esp_timer_delete(esp_timer_handle);
            }
        }
}







//freertos timer example
#if 0
void on_timer(TimerHandle_t xTimer)
{
    printf("time hit %lld\n", esp_timer_get_time()/ 1000);
}

void app_main(void)
{
    printf("app started %lld\n", esp_timer_get_time() / 1000);
    TimerHandle_t xTimer = xTimerCreate("my timer", pdMS_TO_TICKS(1000), true, NULL, on_timer);
    xTimerStart(xTimer, 0);
}

#endif