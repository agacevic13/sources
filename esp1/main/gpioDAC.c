#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "driver/dac_oneshot.h"
#include "driver/dac_cosine.h"
#include "driver/dac_continuous.h"

// controlling the brightness of led


void app_main(void)
{
    dac_output_enable(DAC_CHANNEL_2);
    int i = 0;
    for (i = 0; i < 100; ++i)
    {
        dac_output_voltage(DAC_CHANNEL_2, i * 30 % 255);
        printf("....\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}