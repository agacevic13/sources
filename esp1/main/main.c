#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "inttypes.h"
#include "esp_random.h"
#include "math.h"

#define TAG  "DICE"

int dice_role()
{
    int random = esp_random();
    int positiveNumber = abs(random);
    int diceNumber = (positiveNumber % 6) + 1;
    return diceNumber;
}

void app_main(void)
{
    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "random number %d", dice_role());
    }
    // esp_log_level_set("LOG", ESP_LOG_INFO);
    // ESP_LOGI("Main","Anica");
    // ESP_LOGE("LOG", "This is an error");
    // ESP_LOGW("Warning","Warning");
    // ESP_LOGD("Debug","Debug");
    // ESP_LOGV("Verb","Verbose");
    // return;
}
    