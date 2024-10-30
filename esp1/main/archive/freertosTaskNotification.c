#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void * params)
{
    while(true)
    {
        xTaskNotify(receiverHandler, (1<<0), eSetBits);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler,(1<<1), eSetBits);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler,(1<<2), eSetBits);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler,(1<<3),eSetBits);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}


void receiver(void * params)
{
    uint16_t state;
    while(true)
    {
        xTaskNotifyWait(0xffffffff, 0, &state, portMAX_DELAY);
        printf("received state %d times\n", state);
    }
}

void app_main(void)
{
    xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender, "receiver", 2048, NULL, 2, NULL);
}























// void task1(void * params)
// {
//     while (true)
//     {
//         printf("reading temperature from %s\n", (char *) params);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
    
// }

// void task2(void * params)
// {
//     while (true)
//     {
//         printf("reading humidity from %s\n", (char *) params);
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//     }
    
// }

// void app_main(void)
// {
//     xTaskCreate(&task1, "temperature reading", 2048, "task 1", 2, NULL); 
//     xTaskCreatePinnedToCore(&task2, "humidity reading", 2048, "task 2", 2, NULL, 0);

// }