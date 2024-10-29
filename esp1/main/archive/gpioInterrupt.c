#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define SWITCH 15
QueueHandle_t interputQueue;

int pinNumber;
static void IRAM_ATTR gpio_isr_handler(void *args)
{
    //return;
    pinNumber = (int) args; 
    xQueueSendFromISR(interputQueue, &pinNumber, NULL);
}

void buttonPushedTask(void *params)
{   int pinNumber, count = 0;
    
    while(true)
    {

        if(xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            gpio_isr_handler_remove(pinNumber);

            do
            {
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            while(gpio_get_level(pinNumber) == 1);

          
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(SWITCH));
            gpio_isr_handler_add(SWITCH,gpio_isr_handler, (void *) SWITCH);
        }
    }
}

void app_main(void)
{
    gpio_set_direction(SWITCH, GPIO_MODE_INPUT);
    gpio_pulldown_en(SWITCH);
    gpio_pullup_dis(SWITCH);
    gpio_set_intr_type(SWITCH, GPIO_INTR_POSEDGE);

    interputQueue = xQueueCreate(1000, sizeof(int));
    xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(SWITCH,gpio_isr_handler, (void *) SWITCH);
}

