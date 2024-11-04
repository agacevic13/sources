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
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG             "BLE"
#define DEVICE_NAME     "Anica BLE"

#define WIFI_SERVICE    0x3E, 0x4A, 0x92, 0xB6, 0xD7, 0xF1, 0xC8, 0x94, 0xE1, 0x0F, 0x3A, 0x2B, 0x4C, 0x8D, 0x57, 0x9A
#define SSID_CHAR       0x1A, 0x9F, 0x8E, 0xB3, 0x72, 0xCC, 0x41, 0x5A, 0x8D, 0xD7, 0x1E, 0x36, 0x4F, 0xAB, 0xCD, 0xE1
#define PASS_CHAR       0x6B, 0x21, 0x4C, 0xFA, 0x98, 0x33, 0x7E, 0xAD, 0x0B, 0x52, 0xD6, 0xE2, 0x45, 0xAA, 0xBC, 0x11

#define WIFI_SSID_RECEIVED_BIT  BIT0
#define WIFI_PASS_RECEIVED_BIT  BIT1
#define WIFI_CONNECTED_BIT      BIT2


uint8_t ble_addr_type;
uint8_t conn_handler;
EventGroupHandle_t wifi_events;

static char wifi_ssid[32] = {0};
static char wifi_pass[64] = {0};

void ble_app_advertise(void);

int ble_gap_event (struct ble_gap_event *event, void *arg)
{
    switch(event->type)
    {
    case BLE_GAP_EVENT_CONNECT:
        ESP_LOGI("GAP", "BLE_GAP_EVENT_CONNECT %s", event->connect.status == 0 ? "OK" : "Failed");
        if(event->connect.status != 0)
        {
            ble_app_advertise();
        }
        conn_handler = event->connect.conn_handle;
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGI("GAP", "BLE_GAP_EVENT_DISCONNECT");
        ble_app_advertise();
        break;
    case BLE_GAP_EVENT_ADV_COMPLETE:
        ESP_LOGI("GAP", "BLE_GAP_EVENT_ADV_COMPLETE");
        ble_app_advertise();
        break;
    case BLE_GAP_EVENT_SUBSCRIBE:
        ESP_LOGI("GAP", "BLE_GAP_EVENT_SUBSCRIBE");
        break;
    default:
        break;
    }
    return 0;
};
void ble_app_on_sync(void)
{
    ble_hs_id_infer_auto(0, &ble_addr_type);
    ble_app_advertise();
   
}
void host_task(void *params)
{
    nimble_port_run();
}

static int ssid_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{   
    if(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR)
    {
        os_mbuf_append(ctxt->om, "Enter SSID:", strlen("Enter SSID:"));
    }
    else if(ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
        size_t len = ctxt->om->om_len;
        if(len < sizeof(wifi_ssid))
        {
            memcpy(wifi_ssid, ctxt->om->om_data, len);
            wifi_ssid[len]= '\0';
            ESP_LOGI(TAG, "Received SSID: %s\n", wifi_ssid);
            xEventGroupSetBits(wifi_events, WIFI_SSID_RECEIVED_BIT);

        }
    }
    else{
        ESP_LOGE("TAG", "Invalid request.\n");
    }
    return 0;
}

static int pass_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    if(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR)
    {
        os_mbuf_append(ctxt->om, "Enter PASSWORD:", strlen("Enter PASSWORD:"));
    }
    else if(ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
        size_t len = ctxt->om->om_len;
        if(len < sizeof(wifi_pass))
        {
            memcpy(wifi_pass, ctxt->om->om_data, len);
            wifi_pass[len] = '\0';
            ESP_LOGI(TAG, "Received PASSWORD: %s\n", wifi_pass);
            xEventGroupSetBits(wifi_events, WIFI_PASS_RECEIVED_BIT);
        }
    }
    else{
        ESP_LOGE("TAG", "Invalid request.\n");
    }
    return 0;
}

static const struct ble_gatt_svc_def gat_svcs[] = 
{
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID128_DECLARE(WIFI_SERVICE),
        .characteristics = (struct ble_gatt_chr_def[])
        {
            {
                .uuid = BLE_UUID128_DECLARE(SSID_CHAR),
                .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE,
                .access_cb = ssid_write
                
            },
            {
                .uuid = BLE_UUID128_DECLARE(PASS_CHAR),
                .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE,
                .access_cb = pass_write
            },
            {
                0
            }
        },
    },
    {
        0
    }   
};


void ble_app_advertise(void)
{
    struct ble_hs_adv_fields fields;
    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_DISC_LTD;
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;
    fields.name = (uint8_t *)ble_svc_gap_device_name();
    fields.name_len = strlen(ble_svc_gap_device_name());
    fields.name_is_complete = 1;

    ble_gap_adv_set_fields(&fields);


    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));

    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER, &adv_params, ble_gap_event, NULL);
}

void event_handler(void* event_handler_arg, esp_event_base_t event_base, 
                    int32_t event_id, void *event_data)
{
    switch(event_id)
    {
    case WIFI_EVENT_STA_START:
        ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
        esp_wifi_connect();
        break;
    case WIFI_EVENT_STA_CONNECTED:
        ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
        break;
    default:
        break;
    }
}

void wifi_connect()
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_init_config);
    esp_event_loop_create_default();

    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t wifi_config = {};

    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, event_handler, NULL);

    strncpy((char *)wifi_config.sta.ssid, wifi_ssid, sizeof(wifi_config.sta.ssid)-1);
    strncpy((char *)wifi_config.sta.password, wifi_pass, sizeof(wifi_config.sta.password)-1);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    esp_err_t err = esp_wifi_connect();
    if (err == ESP_OK) {
        ESP_LOGI("WIFI", "Connecting to WiFi...");
    } else {
        ESP_LOGE("WIFI", "Failed to connect to WiFi: %s", esp_err_to_name(err));
    }
    
}

void wifi_connect_task(void *params)
{
   
    EventBits_t bits = xEventGroupWaitBits(wifi_events, WIFI_SSID_RECEIVED_BIT | WIFI_PASS_RECEIVED_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

    if((bits & (WIFI_SSID_RECEIVED_BIT | WIFI_PASS_RECEIVED_BIT)) == (WIFI_SSID_RECEIVED_BIT | WIFI_PASS_RECEIVED_BIT))
    {
        ESP_LOGI("WIFI", "Both SSID and PASSWORD received, connecting to WiFi...\n");
        wifi_connect();
        xEventGroupSetBits(wifi_events, WIFI_CONNECTED_BIT);
    }

    for (;;) {
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void app_main(void)
{
    nvs_flash_init();
    nimble_port_init();

    wifi_events = xEventGroupCreate();

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

    //wifi
    xTaskCreate(wifi_connect_task, "connect to wifi", 4096, NULL, 2, NULL);

}