#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"

// ADC1_CHANNEL_0 = GPIO_NUM_1;
// ADC1_CHANNEL_1 = GPIO_NUM_2;
// ADC1_CHANNEL_2 = GPIO_NUM_3;

void app_main(void)
{
    adc1_config_width(ADC_BITWIDTH_12);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_12);
    //adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_6);
    //adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_12);

    while(true)
    {
        int red = adc1_get_raw(ADC1_CHANNEL_3);
        //int green = adc1_get_raw(ADC1_CHANNEL_1);
        //int res= adc1_get_raw(ADC1_CHANNEL_2);
        printf("Red %d\n, Resistor %d\n ",red, red);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}