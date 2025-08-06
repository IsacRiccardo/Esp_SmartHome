/******************************************************************************/
/*                             INCLUDES                                       */
/******************************************************************************/
#include "ApplicationTask_Core1.h"
#include "esp_log.h"
#include "esp_task.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************/
/*                             LOCAL MACROS                                   */
/******************************************************************************/

#define CORE_ID 1
/******************************************************************************/
/*                             LOCAL DATA TYPES                               */
/******************************************************************************/

/******************************************************************************/
/*                             LOCAL FUNCTION DECLARATIONS                    */
/******************************************************************************/

static void ApplicationTask_Core1_1ms(void *pvParameters);
static void ApplicationTask_Core1_5ms(void *pvParameters);
static void ApplicationTask_Core1_10ms(void *pvParameters);

/******************************************************************************/
/*                             LOCAL VARIABLES                                */
/******************************************************************************/

static const char *TAG = "ApplicationTask_Core1";

static TaskHandle_t ApplicationTask_Core1_1ms_Handle;
static TaskHandle_t ApplicationTask_Core1_5ms_Handle;
static TaskHandle_t ApplicationTask_Core1_10ms_Handle;

/******************************************************************************/
/*                             GLOBAL FUNCTION DEFINITIONS                    */
/******************************************************************************/

int ApplicationTask_Core1_Init(void) 
{
    xTaskCreatePinnedToCore(ApplicationTask_Core1_1ms, "ApplicationTask_Core1_1ms", 1024, NULL, 1, &ApplicationTask_Core1_1ms_Handle, CORE_ID);
    xTaskCreatePinnedToCore(ApplicationTask_Core1_5ms, "ApplicationTask_Core1_5ms", 1024, NULL, 1, &ApplicationTask_Core1_5ms_Handle, CORE_ID);
    xTaskCreatePinnedToCore(ApplicationTask_Core1_10ms, "ApplicationTask_Core1_10ms", 1024, NULL, 1, &ApplicationTask_Core1_10ms_Handle, CORE_ID);

    return APPLICATIONTASK_CORE1_SUCCESS;
}

int ApplicationTask_Core1_Start(void) 
{
    xTaskNotifyGive(ApplicationTask_Core1_1ms_Handle);    // Resume the 1ms task
    xTaskNotifyGive(ApplicationTask_Core1_5ms_Handle);    // Resume the 5ms task
    xTaskNotifyGive(ApplicationTask_Core1_10ms_Handle);   // Resume the 10ms task

    return APPLICATIONTASK_CORE1_SUCCESS;
}

/******************************************************************************/
/*                             LOCAL FUNCTION DEFINITIONS                     */
/******************************************************************************/

static void ApplicationTask_Core1_1ms(void *pvParameters) 
{
    TickType_t xLastWakeTime;
    
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    // Wait for the task to be resumed
    ESP_LOGI(TAG, "ApplicationTask_Core1_1ms started");
    
    // Initialize the xLastWakeTime variable with the current time
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) 
    {
        // Your task code goes here
        
        // Wait for the next cycle - this ensures fixed periodicity
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}

static void ApplicationTask_Core1_5ms(void *pvParameters) 
{
    TickType_t xLastWakeTime;
    
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    // Wait for the task to be resumed
    ESP_LOGI(TAG, "ApplicationTask_Core1_5ms started");
    
    // Initialize the xLastWakeTime variable with the current time
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) 
    {
        // Your task code goes here
        
        // Wait for the next cycle - this ensures fixed periodicity
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5));
    }
}

static void ApplicationTask_Core1_10ms(void *pvParameters) 
{
    TickType_t xLastWakeTime;
    
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    // Wait for the task to be resumed
    ESP_LOGI(TAG, "ApplicationTask_Core1_10ms started");
    
    // Initialize the xLastWakeTime variable with the current time
    xLastWakeTime = xTaskGetTickCount();
    
    while (1) 
    {
        // Your task code goes here
        
        // Wait for the next cycle - this ensures fixed periodicity
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
    }
}
