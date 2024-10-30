#include <stdio.h>
#include "nvs_flash.h"
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"





void app_main(void)
{
    nvs_flash_init();
    wifi_connect_init();
    esp_err_t err = wifi_connect_sta("mreza2", "internet2", 10000);
    //wifi_connect_ap("myESP32AP", "password");
    vTaskDelay(pdMS_TO_TICKS(20000));
    wifi_disconnect();
}