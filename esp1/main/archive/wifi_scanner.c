#include "esp_wifi.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <esp_log.h>

const char * TAG = "WIFI_SCANNER";

#define MAX_APs 20

char *getAuthModeName(wifi_auth_mode_t wifi_auth_mode) {
  switch (wifi_auth_mode) {
  case WIFI_AUTH_OPEN:
    return "WIFI_AUTH_OPEN";
  case WIFI_AUTH_WEP:
    return "WIFI_AUTH_WEP";
  case WIFI_AUTH_WPA_PSK:
    return "WIFI_AUTH_WPA_PSK";
  case WIFI_AUTH_WPA2_PSK:
    return "WIFI_AUTH_WPA2_PSK";
  case WIFI_AUTH_WPA_WPA2_PSK:
    return "WIFI_AUTH_WPA_WPA2_PSK";
  case WIFI_AUTH_WPA2_ENTERPRISE:
    return "WIFI_AUTH_ENTERPRISE";
  case WIFI_AUTH_WPA3_PSK:
    return "WIFI_AUTH_WPA3_PSK";
  case WIFI_AUTH_WPA2_WPA3_PSK:
    return "WIFI_AUTH_WPA2_WPA3_PSK";

  case WIFI_AUTH_WAPI_PSK:
    return "WIFI_AUTH_WAPI_PSK";
  case WIFI_AUTH_OWE:
    return "WIFI_AUTH_OWE";
  case WIFI_AUTH_WPA3_ENT_192:
    return "WIFI_AUTH_WPA3_ENT_192";
  case WIFI_AUTH_WPA3_EXT_PSK:
    return "WIFI_AUTH_WPA3_EXT_PSK";
  case WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE:
    return "WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE";
  case WIFI_AUTH_DPP:
    return "WIFI_AUTH_DPP";
  case WIFI_AUTH_MAX:
    return "WIFI_AUTH_MAX";
  }
  return "UNKNOWN";
}

void app_main(void) {
    nvs_flash_init();
#if 0
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);
#endif
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_err_t err = ESP_OK;
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_init error: %d", err);
        return;
    }
    esp_wifi_set_mode(WIFI_MODE_STA);
    err = esp_wifi_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_start error: %d", err);
        return;
    }

    wifi_scan_config_t wifi_scan_config = {.show_hidden = true};
    err = esp_wifi_scan_start(&wifi_scan_config, true);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_scan_start error: %d", err);
        return;
    }

  wifi_ap_record_t wifi_records[MAX_APs];
  uint16_t max_record = MAX_APs;

  err = esp_wifi_scan_get_ap_records(&max_record, wifi_records);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_wifi_scan_start error: %d", err);
    return;
  }

  ESP_LOGI(TAG, "all good, no error...");

  printf("Found %d access points:\n", max_record);
  printf("\n");
  printf("               SSID              | Channel | RSSI |   Auth Mode \n");
  printf("----------------------------------------------------------------\n");
  for (int i = 0; i < max_record; i++) {
    printf("%32s | %7d | %4d | %12s\n", (char *)wifi_records[i].ssid,
           wifi_records[i].primary, wifi_records[i].rssi,
           getAuthModeName(wifi_records[i].authmode));
  }
  printf("----------------------------------------------------------------\n");
}