/******************************************************************************/
/*                             INCLUDES                                       */
/******************************************************************************/
#include <stdio.h>
#include "esp_log.h"
#include "esp_http_client.h"
#include "Http.h"

/******************************************************************************/
/*                          LOCAL MACROS & CONSTANTS                          */
/******************************************************************************/
#define HTTP_SERVER_URL "http://192.168.0.184:5000/sensor_data"

/******************************************************************************/
/*                             LOCAL DATA TYPES                               */
/******************************************************************************/

/******************************************************************************/
/*                             LOCAL FUNCTION DECLARATIONS                    */
/******************************************************************************/

extern esp_err_t Http_EventHandler(esp_http_client_event_t *evt);

/******************************************************************************/
/*                             LOCAL VARIABLES                                */
/******************************************************************************/

// This is a static tag for logging purposes
static const char *TAG = "Http";

/******************************************************************************/
/*                             GLOBAL VARIABLES                               */
/******************************************************************************/

static esp_http_client_handle_t client = NULL; // Global HTTP client handle

/******************************************************************************/
/*                             GLOBAL FUNCTION DEFINITIONS                    */
/******************************************************************************/

// Initialize the HTTP client with the server URL and event handler
void Http_Init(void)
{
    // Initialize HTTP client configuration
    esp_http_client_config_t config = {
        .url = HTTP_SERVER_URL, // Concatenate server URL and endpoint
        .event_handler = Http_EventHandler, // Set the event handler
    };

    client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize HTTP client");
        return;
    }
}

void Http_ClientCleanup(void)
{
    if (client) 
    {
        esp_http_client_cleanup(client);
        client = NULL;
        ESP_LOGI(TAG, "HTTP client cleaned up");
    } 
    else 
    {
        ESP_LOGW(TAG, "HTTP client was not initialized");
    }
}

// Send data via HTTP POST request
void Http_JsonSendData(const char *data)
{
    // Set the URL and method for the request
    esp_http_client_set_url(client, HTTP_SERVER_URL);
    esp_http_client_set_method(client, HTTP_METHOD_POST);

    // Set the headers for the request
    esp_http_client_set_header(client, "Content-Type", "application/json");

    // Set the POST data
    esp_http_client_set_post_field(client, data, strlen(data));

    // Perform the request
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP POST request sent successfully");
    }
    else 
    {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    }
}

/******************************************************************************/
/*                             LOCAL FUNCTION DEFINITIONS                     */
/******************************************************************************/

// ==== HTTP Event Handler ====
esp_err_t Http_EventHandler(esp_http_client_event_t *evt) 
{
    switch (evt->event_id) 
    {
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP connected");
            break;

        case HTTP_EVENT_ON_DATA:
            printf("Response: %.*s\n", evt->data_len, (char *)evt->data);
            break;

        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP disconnected");
            break;

        default:
            break;
    }

    return ESP_OK;

}