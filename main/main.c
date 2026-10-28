#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "DASHBOARD";

void app_main(void)
{
    ESP_LOGI(TAG, "Niva Dashboard starting...");
    
    int count = 0;
    while (1) {
        ESP_LOGI(TAG, "Dashboard running... count: %d", count++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}