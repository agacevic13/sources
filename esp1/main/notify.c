#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static TaskHandle_t receiverHandler= NULL;

void sender(void * params){
    while(true){
         //xTaskNotifyGive(...)
        //eSetBits je dobar ako hocemo da zadrzimo status kada se nesto dogodi
        xTaskNotify(receiverHandler, (1<<0), eSetBits);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);

        xTaskNotify(receiverHandler, (1<<1), eSetBits);
       // vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<2), eSetBits);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<3), eSetBits);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<4), eSetBits);
         vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}


void receiver(void * params){
    uint16_t state;
    while(true){
       //int count = ultaskNotifyTake(pdFALSE, portMAX_DELAY);
      xTaskNotifyWait(0xffffffff,0, &state, portMAX_DELAY);
      printf("received state %d times\n", state);
    }
}


void app_main(void){
    xTaskCreate(&receiver, "sender", 2048, "task 1", 2, &receiverHandler);
    xTaskCreate(&sender, "receiver", 2048, "task 2", 2, NULL);
}