/******************************************************************************/
/*                             INCLUDES                                       */
/******************************************************************************/
#include <stdio.h>
#include "esp_event_base.h"
#include "esp_wifi_types_generic.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "WiFi.h"

/******************************************************************************/
/*                          LOCAL MACROS & CONSTANTS                          */
/******************************************************************************/

#define WIFI_RECONNECT_MAX_RETRY 5

/******************************************************************************/
/*                             LOCAL DATA TYPES                               */
/******************************************************************************/

/******************************************************************************/
/*                             LOCAL FUNCTION DECLARATIONS                    */
/******************************************************************************/

// Wi-Fi Event Handler
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data);

/******************************************************************************/
/*                             LOCAL VARIABLES                                */
/******************************************************************************/

// This is a static tag for logging purposes
static const char *TAG = "WiFi";
// This variable keeps track of the number of Wi-Fi connection retries
static uint8_t retry_num = 0;

/******************************************************************************/
/*                             GLOBAL VARIABLES                               */
/******************************************************************************/

bool is_wifi_connected = false;  // Flag to indicate Wi-Fi connection status

/******************************************************************************/
/*                             GLOBAL FUNCTION DEFINITIONS                    */
/******************************************************************************/

void WiFi_Init(void)
{
    // Initialize Wi-Fi
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register event handlers
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "WiFi initialization complete. Connecting to SSID: %s", WIFI_SSID);
}

/******************************************************************************/
/*                             LOCAL FUNCTION DEFINITIONS                     */
/******************************************************************************/

// ==== Wi-Fi Event Handler ====
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base != WIFI_EVENT && event_base != IP_EVENT) {
        ESP_LOGE(TAG, "Unexpected event base: %s", event_base);
    }
    else
    {
        switch (event_id) 
        {
            case WIFI_EVENT_STA_START:
                ESP_LOGI(TAG, "WiFi starting...");
                esp_wifi_connect();
                break;
            
            case WIFI_EVENT_STA_CONNECTED:
                ESP_LOGI(TAG, "WiFi connected to AP");
                break;
            
            case WIFI_EVENT_STA_DISCONNECTED:
                ESP_LOGW(TAG, "WiFi disconnected");
                is_wifi_connected = false;
                if (retry_num < WIFI_RECONNECT_MAX_RETRY) {
                    esp_wifi_connect();
                    retry_num++;
                    ESP_LOGI(TAG, "Retrying WiFi connection (%d/%d)...", retry_num, WIFI_RECONNECT_MAX_RETRY);
                } else {
                    ESP_LOGE(TAG, "WiFi connection failed after %d retries", WIFI_RECONNECT_MAX_RETRY);
                }
                break;
            
            case IP_EVENT_STA_GOT_IP:
                is_wifi_connected = true;
                ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
                ESP_LOGI(TAG, "Got IP Address: " IPSTR, IP2STR(&event->ip_info.ip));
                retry_num = 0;
                break;
        }

    }
    
}