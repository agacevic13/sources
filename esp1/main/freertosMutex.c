#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t mutexBus;

void writeToBus(char* message)
{
    printf(message);
}

void task1(void * params)
{
    while (true)
    {
        printf("reading temperature \n");
        if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
        {
            writeToBus("temperature is 25C\n");
            //xSemaphoreGive(mutexBus);
        }
        else
        {
            printf("writing temperature timed out\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}

void task2(void * params)
{
    while(true)
    {
        printf("reading humidity \n");
        if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
        {
            writeToBus("humidity is 50\n");
            xSemaphoreGive(mutexBus);
        }
        else
        {
            printf("writing humidity timed out\n");
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex();
    xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
    xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
}

