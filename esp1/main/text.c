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

#define BUFFER_SIZE     500
#define HTTP_TAG "HTTP"

// char *song_buffer; //[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
// int buffer_len = 0;
typedef struct song_buffer_t
{
    uint8_t *buffer[2];
    //uint8_t *buffer1;
    int buffer_index;
    //int buffer_index1;
} song_buffer_t;

uint8_t currentBuffer = 0;

esp_err_t http_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id)
    {
    case HTTP_EVENT_ON_CONNECTED:
    {
        ESP_LOGI(HTTP_TAG, "HTTP client connected\n");
        break;
    }
    case HTTP_EVENT_ON_DATA:
    {
        ESP_LOGW(HTTP_TAG, "Lenght: %d", evt->data_len);
        song_buffer_t *song_buffer = evt->user_data;

        uint32_t data_written = 0;

        while(data_written < evt->data_len)
        {
            int remaining_space = BUFFER_SIZE - song_buffer->buffer_index;
            ESP_LOGI(HTTP_TAG, "remaining: %d, data_len: %d, data_written: %lu, currentBuffer: %d",
                                remaining_space, evt->data_len, data_written, currentBuffer);
            
            //calculate how many bytes to write to fill current buffer
            int bytes_to_write = (evt->data_len - data_written < remaining_space) ? evt->data_len - data_written : remaining_space;

            //write data to current buffer
            memcpy(&song_buffer->buffer[currentBuffer][song_buffer->buffer_index], (char *)evt->data, bytes_to_write);

            //update buffer index 
            song_buffer->buffer_index += bytes_to_write;
            data_written += bytes_to_write;
            ESP_LOGW(HTTP_TAG, "data_written: %lu, bytes_to_write: %d",
                                data_written, bytes_to_write);

            //switch between buffers
            if(song_buffer->buffer_index == BUFFER_SIZE)
            {
                song_buffer->buffer_index = 0;
                currentBuffer = (currentBuffer + 1) % 2;
            }
            //vTaskDelay(1000 /portTICK_PERIOD_MS);
        }
#if 0
        if (currentBuffer == 0) 
        {
            memcpy(&song_buffer->buffer0[song_buffer->buffer_index0], (char *)evt->data, evt->data_len);
            song_buffer->buffer_index0 = song_buffer->buffer_index0 + evt->data_len;
            song_buffer->buffer0[song_buffer->buffer_index0] = 0;
            if (song_buffer->buffer_index0 + evt->data_len > BUFFER_SIZE) 
            {
                currentBuffer = 1;
                song_buffer->buffer_index0 = 0;
            }
        }
        else if (currentBuffer == 1) 
        {
            memcpy(&song_buffer->buffer1[song_buffer->buffer_index1], (char *)evt->data, evt->data_len);
            song_buffer->buffer_index1 = song_buffer->buffer_index1 + evt->data_len;
            song_buffer->buffer1[song_buffer->buffer_index1] = 0;
            if (song_buffer->buffer_index1 + evt->data_len > BUFFER_SIZE) 
            {
                currentBuffer = 0;
                song_buffer->buffer_index1 = 0
            }
        }
#endif
        //printf("Message: %s\n", song_buffer->buffer0);
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
song_buffer_t song_buffer = {0};
void get_song()
{
    esp_http_client_config_t esp_http_client_config = {
        .url = "http://radio-esp32.000.pe/CMakeLists.txt",
        .method = HTTP_METHOD_GET,
        .event_handler = http_handler,
        .user_data = &song_buffer,
        .timeout_ms = 1000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);
    esp_err_t err = esp_http_client_perform(client);
    


    if(err == ESP_OK)
    {
        ESP_LOGI(HTTP_TAG, "GET status = %d, result = %s\n",esp_http_client_get_status_code(client), song_buffer.buffer[0]);
        ESP_LOGI(HTTP_TAG, "GET status = %d, result = %s\n",esp_http_client_get_status_code(client), song_buffer.buffer[1]);
    }
    else{
        ESP_LOGI(HTTP_TAG, "GET request failed: %s\n", esp_err_to_name(err));
    }
#if 0
    if(song_buffer.buffer[0] != NULL)
    {
        free(song_buffer.buffer[0]);
    }
    if(song_buffer.buffer[1] != NULL)
    {
        free(song_buffer.buffer[1]);
    }
#endif
    esp_http_client_cleanup(client);
}

void get_song_task(void *pvParameters) 
{
    get_song();
    while(1) 
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    nvs_flash_init();
    wifi_connect_init();
    wifi_connect_sta("Sources", "internet21", 1000);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    song_buffer.buffer[0] = calloc(BUFFER_SIZE, 1);
    song_buffer.buffer[1] = calloc(BUFFER_SIZE, 1);
    xTaskCreate(get_song_task, "get_song_task", 4096, NULL, 5, NULL);
}