#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include <stdio.h>

// void on_timer(TimerHandle_t xTimer){
//    printf("time hit %lld\n", esp_timer_get_time() / 1000);
// }
// void app_main(void){

//      printf("app started %lld\n", esp_timer_get_time() / 1000);
//      TimerHandle_t xTimer = xTimerCreate("my timer", pdMS_TO_TICKS(1000),
//      true, NULL, on_timer); xTimerStart(xTimer, 0);

// }
void timer_callback(void *args) {
  static bool on;
  on = !on;
  gpio_set_level(GPIO_NUM_5, on);
}
void app_main(void) {
  gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);

  const esp_timer_create_args_t esp_timer_create_args = {
      .callback = timer_callback, .name = "My timer"

  };
  esp_timer_handle_t esp_timer_handle;
  esp_timer_create(&esp_timer_create_args, &esp_timer_handle);
  esp_timer_start_periodic(esp_timer_handle, 500000);
 int x = 0; 
//   while (true) {
//     esp_timer_dump(stdout);
//     vTaskDelay(pdMS_TO_TICKS(1000));
//     if(x++ == 5){
//         esp_timer_stop(esp_timer_handle);
//     }
//   }
}
