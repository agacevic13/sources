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

#define BATTER_SERVICE 0x180F
#define BATTERY_LEVEL 0x2A19
#define DEVICE_NAME "MY BLE DEVICE Anica"
#define DEVICE_INFO_SERVICE 0x180A
//#define GATT_SVR_SVC_ALERT_UUID     0x1811
#define MANUFACTORER_NAME           0x2A29

uint8_t ble_addr_type;
void ble_app_advertise();
void ble_svc_ans_init(void);

static int battery_read(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    uint8_t battery_level = 85;
    os_mbuf_append(ctxt->om, &battery_level, sizeof(battery_level));
    return 0;
}
static int device_info(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    os_mbuf_append(ctxt->om, "manufactorer name", strlen("manufactorer name"));
    return 0;
}

static int device_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{   
    printf("incoming message: %.*s\n", ctxt->om->om_len, ctxt->om->om_data);
    return 0;
}

static const struct ble_gatt_svc_def gat_svcs[] = 
{
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(DEVICE_INFO_SERVICE),
        .characteristics =(struct ble_gatt_chr_def[])
        {
            {
                .uuid = BLE_UUID16_DECLARE(MANUFACTORER_NAME),
                .flags = BLE_GATT_CHR_F_READ,
                .access_cb = device_info
            },
            {
                .uuid = BLE_UUID128_DECLARE(0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
                                        0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff),
                .flags = BLE_GATT_CHR_F_WRITE,
                .access_cb = device_write
            },
            {
                0
            }
        },
    },
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(BATTER_SERVICE),
        .characteristics =(struct ble_gatt_chr_def[])
        {
            {
                .uuid = BLE_UUID16_DECLARE(BATTERY_LEVEL),
                .flags = BLE_GATT_CHR_F_READ,
                .access_cb = battery_read
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

static int ble_gap_event (struct ble_gap_event *event, void *arg)
{
    switch(event->type)
    {
    case BLE_GAP_EVENT_CONNECT:
        ESP_LOGI("GAP", "BLE_GAP_EVENT_CONNECT %s", event->connect.status == 0 ? "OK" : "Failed");
        if(event->connect.status != 0)
        {
            ble_app_advertise();
        }
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
}

void ble_app_advertise(void)
{
    struct ble_hs_adv_fields fields;
    memset(&fields, 0, sizeof(fields));
    
    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    fields.name = (uint8_t *)ble_svc_gap_device_name();
    fields.name_len = strlen(ble_svc_gap_device_name());
    fields.name_is_complete = 1;
    fields.uuids16 = (ble_uuid16_t[]) {
        BLE_UUID16_INIT(DEVICE_INFO_SERVICE)
    };
    fields.num_uuids16 = 1;
    fields.uuids16_is_complete = 1;


    ble_gap_adv_set_fields(&fields);


    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER, &adv_params, ble_gap_event, NULL);
    
}

void ble_app_on_sync(void)
{
    ble_hs_id_infer_auto(0, &ble_addr_type);
    //ble_addr_type = BLE_OWN_ADDR_PUBLIC;
    ble_app_advertise();
   
}

void host_task(void *params)
{
    nimble_port_run();
}


void app_main(void)
{
    nvs_flash_init();

    //esp_nimble_hci_init();
    nimble_port_init();

    ble_svc_gap_device_name_set(DEVICE_NAME);
    ble_svc_gap_init();
    ble_svc_gatt_init();
    //ble_svc_ans_init();  //za blecent example from esp-idf
    ble_gatts_count_cfg(gat_svcs);
    ble_gatts_add_svcs(gat_svcs);
    

    ble_hs_cfg.sync_cb = ble_app_on_sync;
    nimble_port_freertos_init(host_task);
}