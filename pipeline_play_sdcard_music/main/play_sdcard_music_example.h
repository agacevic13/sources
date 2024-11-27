
#ifndef _PLAY_SDCARD_MUSIC_EXAMPLE_H
#define _PLAY_SDCARD_MUSIC_EXAMPLE_H
#include "audio_common.h"
#include "audio_element.h"
#include "audio_event_iface.h"
#include "audio_pipeline.h"
#include "esp_log.h"
#include "fatfs_stream.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2s_stream.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include <string.h>

#include "esp_spiffs.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "spiffs_stream.h"
#include <sys/stat.h> // Za funkciju stat

 esp_err_t s_example_write_file(const char *path, char *data);
 esp_err_t s_example_read_file(const char *path);
esp_err_t check_file_exists(const char *path);
void list_spiffs_files(void);



#endif 