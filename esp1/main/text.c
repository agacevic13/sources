#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "wifi_connect.h"

#define HTTP_TAG "HTTP"

// char *song_buffer; //[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
// int buffer_len = 0;
typedef struct song_buffer_t
{
    uint8_t *buffer0;
    uint8_t *buffer1;
    int buffer_index;
} song_buffer_t;

uint8_t currentBuffer = 0;

esp_err_t http_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id)
    {
    case HTTP_EVENT_ON_CONNECTED:
    {
        ESP_LOGI(HTTP_TAG, "HTTP client connected\n");
    }
    case HTTP_EVENT_ON_DATA:
    {
        ESP_LOGW(HTTP_TAG, "Lenght: %d", evt->data_len);
        song_buffer_t *song_buffer = evt->user_data;
        if (currentBuffer == 0) {
            memcpy(&song_buffer->buffer0[song_buffer->buffer_index], (char *)evt->data, evt->data_len);
            song_buffer->buffer_index = song_buffer->buffer_index + evt->data_len;
            song_buffer->buffer0[song_buffer->buffer_index] = 0;
            if (song_buffer->buffer_index + evt->data_len > 1000000) {
                currentBuffer = 1;
                song_buffer->buffer_index = 0
            }
        }
        else if (currentBuffer == 1) {
            memcpy(&song_buffer->buffer1[song_buffer->buffer_index], (char *)evt->data, evt->data_len);
            song_buffer->buffer_index = song_buffer->buffer_index + evt->data_len;
            song_buffer->buffer1[song_buffer->buffer_index] = 0;
|            if (song_buffer->buffer_index + evt->data_len > 1000000) {
                currentBuffer = 0;
                song_buffer->buffer_index = 0
            }
        }

        printf("Message: %s\n", song_buffer->buffer0);
    }
    break;
    default:
    {
        ESP_LOGW(HTTP_TAG, "eventId: %d", evt->event_id);
        break;
    }
    }
    return ESP_OK;
}

void get_song()
{
    song_buffer_t song_buffer = {0};
    song_buffer.buffer0 = calloc(100000, 1);
    song_buffer.buffer1 = calloc(100000, 1);
    esp_http_client_config_t esp_http_client_config = {
        .url = "http://radio-esp32.000.pe/CMakeLists.txt",
        .method = HTTP_METHOD_GET,
        .event_handler = http_handler,
        .user_data = &song_buffer,
        //.timeout_ms = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);
    esp_err_t err = esp_http_client_perform(client);
    


    if(err == ESP_OK)
    {
        ESP_LOGI(HTTP_TAG, "GET status = %d, result = %s\n",esp_http_client_get_status_code(client), song_buffer.buffer);
    }
    else{
        ESP_LOGI(HTTP_TAG, "GET request failed: %s\n", esp_err_to_name(err));
    }
    if(song_buffer.buffer != NULL)
    {
        free(song_buffer.buffer);
    }
    esp_http_client_cleanup(client);


}

void app_main(void)
{
    nvs_flash_init();
    wifi_connect_init();
    wifi_connect_sta("Sources", "internet21", 1000);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    get_song();
}