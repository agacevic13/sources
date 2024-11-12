#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"



void app_main(void)
{
    nvs_flash_init(); 
    wifi_connect_init();
    wifi_connect_sta("", "", 10000);
    //wifi_disconnect();
}
