#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "mqtt_client.h"
#include "esp_netif.h"

// Custom includes
#include "WiFi.h"
#include "Http.h"
#include "ApplicationTask_Core0.h"
#include "ApplicationTask_Core1.h"

static const char *TAG = "MainApp";

// ==== Shutdown Hook ====
void shutdown_hook(void)
{
    ESP_LOGI(TAG, "Shutdown hook called. Cleaning up...");

    // Clean up HTTP client if it was initialized
    Http_ClientCleanup();
}

void app_init(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // Initialize Wi-Fi
    WiFi_Init();

    // Wait for Wi-Fi to connect
    while (!is_wifi_connected) {
        ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    // Initialize HTTP client
    Http_Init();

    // Initialize the application tasks
    ApplicationTask_Core0_Init();
    ApplicationTask_Core1_Init();
}

void app_start(void)
{
    // Start the application tasks
    ApplicationTask_Core0_Start();
    ApplicationTask_Core1_Start();
}

// ==== Main Application ====
void app_main(void)
{
    // Initialize the application and used modules
    app_init();

    // Start the application tasks
    app_start();
}
