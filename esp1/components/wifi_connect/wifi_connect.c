#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include <stdio.h>
#include <string.h>

static char *TAG = "WIFI CONNECT";
static esp_netif_t *esp_netif;
static EventGroupHandle_t wifi_events;
static int CONNECTED = BIT0;
static int DISCONNECTED = BIT1;
char *get_wifi_disconnection_string(wifi_err_reason_t wifi_err_reason);
int disconnection_err_count = 0;
void event_handler(void *event_handler_arg, esp_event_base_t event_base,
                   int32_t event_id, void *event_data) {
  switch (event_id) {
  case WIFI_EVENT_STA_START:
    ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
    esp_wifi_connect();
    break;
  case WIFI_EVENT_STA_CONNECTED:
    ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
    disconnection_err_count = 0;
    break;
  case WIFI_EVENT_STA_DISCONNECTED: {
    wifi_event_sta_disconnected_t *wifi_event_sta_disconnected = event_data;

    ESP_LOGW(
        TAG, "DISCONNECTED %d: %s", wifi_event_sta_disconnected->reason,
        get_wifi_disconnection_string(wifi_event_sta_disconnected->reason));
    if (wifi_event_sta_disconnected->reason == WIFI_REASON_NO_AP_FOUND ||
        wifi_event_sta_disconnected->reason == WIFI_REASON_ASSOC_LEAVE ||
       wifi_event_sta_disconnected->reason == WIFI_REASON_AUTH_EXPIRE ) {
      if (disconnection_err_count++ < 5) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        esp_wifi_connect();
        break;
      }
    }
    xEventGroupSetBits(wifi_events, DISCONNECTED);
    break;
  }
  case IP_EVENT_STA_GOT_IP:
    ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");
    xEventGroupSetBits(wifi_events, CONNECTED);
    break;
  default:
    break;
  }
}

void wifi_connect_init(void) {
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                             event_handler, NULL));
  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                             event_handler, NULL));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
}

esp_err_t wifi_connect_sta(char *ssid, char *pass, int timeout) {
  wifi_events = xEventGroupCreate();
  esp_netif = esp_netif_create_default_wifi_sta();
  esp_wifi_set_mode(WIFI_MODE_STA);
  wifi_config_t wifi_config = {};
  strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
  strncpy((char *)wifi_config.sta.password, pass,
          sizeof(wifi_config.sta.password) - 1);
  esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
  esp_wifi_start();
  EventBits_t result =
      xEventGroupWaitBits(wifi_events, CONNECTED | DISCONNECTED, true, false,
                          pdMS_TO_TICKS(timeout));
  if (result == CONNECTED)
    return ESP_OK;
  return ESP_FAIL;
}