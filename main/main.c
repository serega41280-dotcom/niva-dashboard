#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

static const char *TAG = "DASHBOARD";

void app_main(void)
{
    ESP_LOGI(TAG, "Niva Dashboard starting...");
    
    int count = 0;
    while (1) {
        ESP_LOGI(TAG, "Dashboard running... count: %d", count++);
        if (count % 10 == 0) {
            size_t free_heap = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
            ESP_LOGI(TAG, "Free heap: %u bytes", (unsigned int)free_heap);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}