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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"




void ble_app_advertise();
void ble_app_on_sync();
void host_task(void *params);
//extern const struct ble_gatt_svc_def gat_svcs[];
int ble_gap_event (struct ble_gap_event *event, void *arg);
int ssid_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
int pass_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
void wifi_connect();
void wifi_connect_task(void *params);
