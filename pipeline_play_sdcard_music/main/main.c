#include <stdio.h>
#include <stdlib.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "wifi_connect.h"




    void app_main(){
    
    nvs_flash_init();
    wifi_connect_init();
    wifi_connect_sta("Sources", "internet21", 1000);
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    

}