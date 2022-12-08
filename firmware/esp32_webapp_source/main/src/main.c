/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "esp_event.h"
#include "esp_netif.h"
#include "esp_spiffs.h"
#include "driver/gpio.h"
#include "esp_wifi.h"
#include "esp_http_server.h"
#include "mdns.h"

#include "cJSON.h"

#include "protocol_examples_common.h"
#include <u8g2.h>
#include "u8g2_esp32_hal.h"

#include "WebServer.h"
#include "util.h"
#include "lcd_handle.h"
#include "flash_nvm.h"

static const char *TAG = "APP";

struct channel_info_t obj[8];

int pos_ch[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

void start_mdns_service()
{
    mdns_init();
    mdns_hostname_set("gaugex");
    mdns_instance_name_set("gaugex sensor hub");
}

void app_main(void)
{
    init_flash();
    ESP_ERROR_CHECK(nvs_flash_init()); // this must be removed later
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());
    start_mdns_service();
    init_server();
    xTaskCreate(lcd_handle_task, "lcd_task", 5 * 1024, NULL, 1, NULL);
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
