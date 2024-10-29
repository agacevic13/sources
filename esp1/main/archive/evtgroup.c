#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/event_groups.h"


EventGroupHandle_t evtGrpup;
const int gotHttp =  BIT0;
const int gotBLE = BIT1;

void listenForHTTP(void *params) {
 
  while (true) {
    xEventGroupSetBits(evtGrpup, gotHttp);
    printf("got http\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void listenForBluetooth(void *params) {
  while (true) {
    xEventGroupSetBits(evtGrpup, gotBLE);
    printf("got BLU\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void * params){
    while(true){
        xEventGroupWaitBits(evtGrpup, gotHttp | gotBLE, true, true, portMAX_DELAY);
        printf("received http and BLU\n");
    }
}

void app_main(void) {
  evtGrpup = xEventGroupCreate();
  xTaskCreate(&listenForHTTP, "get http ", 2048, NULL, 1, NULL);
  xTaskCreate(&listenForBluetooth, "get BLU", 2048, NULL, 1, NULL);
  xTaskCreate(&task1,"do something with http", 2048, NULL, 1, NULL );
}