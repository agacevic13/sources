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

#define BUFFER_SIZE     100
#define HTTP_TAG "HTTP"

// char *song_buffer; //[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
// int buffer_len = 0;
typedef struct song_buffer_t
{
    uint8_t *buffer[2];
    //uint8_t *buffer1;
    int buffer_index[2];
    //int buffer_index1;
} song_buffer_t;

uint8_t currentBuffer = 0;
song_buffer_t song_buffer = {0};
SemaphoreHandle_t buffer_ready[2];
TaskHandle_t processing_buffer_handle;

void processing_buffer(void * params)
{
    while(1) 
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        int processBuffer = (currentBuffer + 1) % 2;
        ESP_LOGI(HTTP_TAG, "Processing buffer %d...", processBuffer);
        // funct here
        //pisiNaSd("tekstfajl.txt", range);

        //ESP_LOGW("Processing data: %s\n", song_buffer.buffer[processBuffer]);

        ESP_LOGW(HTTP_TAG, "Giving sem: %d", processBuffer);
        xSemaphoreGive(buffer_ready[processBuffer]);
    }
}

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
        // if (evt->user_data) 
        // {
        //     song_buffer_t *song_buffer = evt->user_data;
        // } 
        // else 
        // {
        //     ESP_LOGW(HTTP_TAG, "user_data is NULL");
        // }
        song_buffer_t *song_buffer = evt->user_data;

        uint32_t data_written = 0;
        while(data_written < evt->data_len)
        {

            {
                int remaining_space = BUFFER_SIZE - song_buffer->buffer_index[currentBuffer];
                ESP_LOGI(HTTP_TAG, "remaining: %d, data_len: %d, data_written: %lu, currentBuffer: %d",
                                    remaining_space, evt->data_len, data_written, currentBuffer);
                
                //calculate how many bytes to write to fill current buffer
                int bytes_to_write = (evt->data_len - data_written < remaining_space) ? evt->data_len - data_written : remaining_space;

                //write data to current buffer
                memcpy(&song_buffer->buffer[currentBuffer][song_buffer->buffer_index[currentBuffer]], (char *)evt->data, bytes_to_write);

                //update buffer index 
                song_buffer->buffer_index[currentBuffer] += bytes_to_write;
                data_written += bytes_to_write;
                ESP_LOGW(HTTP_TAG, "data_written: %lu, bytes_to_write: %d",
                                    data_written, bytes_to_write);
                ESP_LOGI(HTTP_TAG, "Buffer 0: %s", song_buffer->buffer[0]);
                ESP_LOGI(HTTP_TAG, "Buffer 1: %s", song_buffer->buffer[1]);

                //switch between buffers
                // if(song_buffer->buffer_index[currentBuffer] == BUFFER_SIZE || data_written == evt->data_len)
                if(song_buffer->buffer_index[currentBuffer] == BUFFER_SIZE)
                {
                    song_buffer->buffer_index[currentBuffer] = 0;

                    if(processing_buffer_handle != NULL)
                    {
                        ESP_LOGI(HTTP_TAG, "Notifying processing_buffer task.");
                        xTaskNotifyGive(processing_buffer_handle); 
                    }
                    else
                    {
                        ESP_LOGE(HTTP_TAG, "processing handle is NULL.\n");
                    }

                    currentBuffer = (currentBuffer + 1) % 2;

                    // ako je downloadovano 100 bajtova
                    // a u trenutnom baferu bilo mjesta za 10
                    // ostalo je 90 bajtova, nesacuvanih
                    // Ovde mozda treba to upisati u novi currentBuffer?
                }
                else {
                    ESP_LOGE(HTTP_TAG, "song_buffer->buffer_index[currentBuffer]: %d", song_buffer->buffer_index[currentBuffer]);
                }
            }

        //printf("Message: %s\n", song_buffer->buffer[currentBuffer]);
        }
        break;
    }
    default:
    {
        ESP_LOGD(HTTP_TAG, "eventId: %d", evt->event_id);
        break;
    }
    }
    return ESP_OK;
}

void get_song()
{
    int download_start = 0;
    char range[50]={0};
    int total_file_size = 0;

    esp_http_client_config_t esp_http_client_config = {
        .url = "http://radio-esp32.000.pe/tekstfajl.txt",
        .method = HTTP_METHOD_HEAD,
        .event_handler = http_handler,
        .user_data = &song_buffer,
        .buffer_size = 10 * BUFFER_SIZE,
        .timeout_ms = 1000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);

    // Get the total file size during the first request
    if (total_file_size == 0) {
        // Perform the request to fetch headers
        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK)
        {
            total_file_size = esp_http_client_get_content_length(client);
            ESP_LOGI(HTTP_TAG, "Total file size: %d bytes", total_file_size);
            esp_http_client_cleanup(client);
        }
        else
        {
            ESP_LOGE(HTTP_TAG, "Failed to get file size: %s", esp_err_to_name(err));
            esp_http_client_cleanup(client);
            return; // Exit if we can't determine file size.
        }
    }

    esp_http_client_config.method = HTTP_METHOD_GET;
    client = esp_http_client_init(&esp_http_client_config);
    while(download_start < total_file_size)
    {
        sprintf(range, "bytes=%d-%d", download_start, download_start + BUFFER_SIZE - 1);
        ESP_LOGE(HTTP_TAG, "Requesting range: %s", range);
        ESP_LOGE(HTTP_TAG, "Download data: %d", download_start);

        esp_err_t err = ESP_OK;

        esp_http_client_set_header(client, "Range", range);
        ESP_LOGW(HTTP_TAG, "Waiting on sem: %d", currentBuffer);
        if(xSemaphoreTake(buffer_ready[currentBuffer], portMAX_DELAY) == pdTRUE)
        {
            err = esp_http_client_perform(client);
        }

        if(err == ESP_OK)
        {
            ESP_LOGI(HTTP_TAG, "GET status = %d, result = %s\n",esp_http_client_get_status_code(client), song_buffer.buffer[currentBuffer]);
            //ESP_LOGI(HTTP_TAG, "GET status = %d, result = %s\n",esp_http_client_get_status_code(client), song_buffer.buffer[1]);
        }
        else
        {
            ESP_LOGI(HTTP_TAG, "GET request failed: %s\n", esp_err_to_name(err));
        }

        download_start += BUFFER_SIZE;
    }

    ESP_LOGI(HTTP_TAG, "Download complete");
    esp_http_client_cleanup(client);

    // notify maja that the download is complete

    // samo pozovi majinu funkciju za pustanje pjesme, i prosledi joj ime fajla
    //pustiPjesmu("tekstfajl.txt");
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
    
    song_buffer.buffer[0] =calloc(BUFFER_SIZE, 1);
    song_buffer.buffer[1] = calloc(BUFFER_SIZE, 1);
    if (song_buffer.buffer[0] == NULL || song_buffer.buffer[1] == NULL) 
    {
        ESP_LOGE(HTTP_TAG, "Memory allocation failed for song buffer.\n");
        return;  
    }
    buffer_ready[0] = xSemaphoreCreateBinary();
    buffer_ready[1] = xSemaphoreCreateBinary();

    xSemaphoreGive(buffer_ready[0]);
    xSemaphoreGive(buffer_ready[1]);

    xTaskCreate(get_song_task, "get_song_task", 4096, NULL, 5, NULL);
    
    //xTaskCreate(processing_buffer, "processing buffer", 4096, NULL, 5, &processing_buffer_handle);

    BaseType_t result;
    result = xTaskCreate(processing_buffer, "processing buffer", 4096, NULL, 5, &processing_buffer_handle);
    if (result != pdPASS) {
        ESP_LOGE(HTTP_TAG, "Failed to create processing_buffer task!");
        return;
    }
}