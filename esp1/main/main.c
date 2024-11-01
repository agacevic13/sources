#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "services/ans/ble_svc_ans.h"
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ble_wifi.h"

void app_main(void)
{
    nvs_flash_init();
    nimble_port_init();

    //set name
    ble_svc_gap_device_name_set(DEVICE_NAME);
    // gap and gatt init
    ble_svc_gap_init();
    ble_svc_gatt_init();
    //add serivces
    ble_gatts_count_cfg(gat_svcs);
    ble_gatts_add_svcs(gat_svcs);

    ble_hs_cfg.sync_cb = ble_app_on_sync;
    nimble_port_freertos_init(host_task);

    //init wifi
    wifi_connect_init();
    wifi_connect_sta(&user, &password, 10000);
    wifi_disconnect();
}