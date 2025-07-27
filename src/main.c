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

static const char *TAG = "MainApp";

// ==== HTTP POST Task ====
static void http_post_task(void *pvParameters)
{
    while (1)
    {
        // Prepare data to send
        const char *post_data = "[{\"sensor\": \"ESP32\", \"value\": \"50\", \"type\": \"numeric\"}]";

        // Send data via HTTP POST
        Http_JsonSendData(post_data);

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay for 5 seconds before sending the next request

    }
}

// ==== Shutdown Hook ====
void shutdown_hook(void)
{
    ESP_LOGI(TAG, "Shutdown hook called. Cleaning up...");

    // Clean up HTTP client if it was initialized
    Http_ClientCleanup();
}


// ==== Main Application ====
void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // Initialize Event Manager
    WiFi_Init();

    // Wait for Wi-Fi to connect
    while (!is_wifi_connected) {
        ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    // Initialize HTTP client
    Http_Init();

    xTaskCreate(&http_post_task, "http_post_task", 8192, NULL, 5, NULL);
}
