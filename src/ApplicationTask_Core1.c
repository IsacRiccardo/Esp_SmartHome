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

#define CORE_ID    (1u)

#define APPLICATIONTASK_CORE1_TASK_NO    (3u)
/******************************************************************************/
/*                             LOCAL DATA TYPES                               */
/******************************************************************************/

// Task structure
typedef struct
{
    TaskFunction_t pvTaskCode;           // Function that implements the task
    const char *const pcName;            // Name of the task (for debugging)
    const uint32_t usStackDepth;         // Stack size in words (not bytes)
    void *pvParameters;                  // Parameters passed to the task function
    UBaseType_t uxPriority;             // Task priority (0 to configMAX_PRIORITIES-1)
    TaskHandle_t *const pvCreatedTask;  // Handle to the created task (output)
    TickType_t period_ticks;             // Period in FreeRTOS ticks
} ApplicationTask_Core1_t;

/******************************************************************************/
/*                             LOCAL FUNCTION DECLARATIONS                    */
/******************************************************************************/

// Generic task handler
static void ApplicationTask_Core1_Generic(void *pvParameters);

// Specific function for each task configured
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

// Static configuration array for CORE1 tasks
static ApplicationTask_Core1_t ApplicationTask_Core1_TaskConfig[APPLICATIONTASK_CORE1_TASK_NO] =
{
    {
        ApplicationTask_Core1_1ms,
        "ApplicationTask_Core1_1ms",
        1024,
        NULL,
        1,
        &ApplicationTask_Core1_1ms_Handle,
        pdMS_TO_TICKS(1)
    },
    {
        ApplicationTask_Core1_5ms,
        "ApplicationTask_Core1_5ms",
        1024,
        NULL,
        1,
        &ApplicationTask_Core1_5ms_Handle,
        pdMS_TO_TICKS(5)
    },
    {
        ApplicationTask_Core1_10ms,
        "ApplicationTask_Core1_10ms",
        1024,
        NULL,
        1,
        &ApplicationTask_Core1_10ms_Handle,
        pdMS_TO_TICKS(10)
    }
};

/******************************************************************************/
/*                             GLOBAL FUNCTION DEFINITIONS                    */
/******************************************************************************/

int ApplicationTask_Core1_Init(void) 
{
    int RetVal = APPLICATIONTASK_CORE1_SUCCESS;

    for (int i = 0; i < APPLICATIONTASK_CORE1_TASK_NO; i++)
    {
        if (xTaskCreatePinnedToCore(
                ApplicationTask_Core1_Generic,
                ApplicationTask_Core1_TaskConfig[i].pcName,
                ApplicationTask_Core1_TaskConfig[i].usStackDepth,
                &ApplicationTask_Core1_TaskConfig[i],
                ApplicationTask_Core1_TaskConfig[i].uxPriority,
                ApplicationTask_Core1_TaskConfig[i].pvCreatedTask,
                CORE_ID) != pdPASS
        )
        {
            ESP_LOGE(TAG, "Failed to create task: %s", ApplicationTask_Core1_TaskConfig[i].pcName);
            RetVal = APPLICATIONTASK_CORE1_ERROR;
            break;
        }
    }
    return RetVal;
}


int ApplicationTask_Core1_Start(void) 
{
    int RetVal = APPLICATIONTASK_CORE1_SUCCESS;

    for (int i = 0; i < APPLICATIONTASK_CORE1_TASK_NO; i++)
    {
        if (*(ApplicationTask_Core1_TaskConfig[i].pvCreatedTask) != NULL)
        {
            xTaskNotifyGive(*(ApplicationTask_Core1_TaskConfig[i].pvCreatedTask));
        }
        else
        {
            RetVal = APPLICATIONTASK_CORE1_ERROR;
        }
    }

    if (RetVal == APPLICATIONTASK_CORE1_SUCCESS)
    {
        ESP_LOGI(TAG, "All Core1 tasks started successfully");
    }

    return RetVal;
}


/******************************************************************************/
/*                             LOCAL FUNCTION DEFINITIONS                     */
/******************************************************************************/
static void ApplicationTask_Core1_Generic(void *pvParameters)
{
    ApplicationTask_Core1_t *cfg = (ApplicationTask_Core1_t *)pvParameters;
    TickType_t xLastWakeTime;

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Wait for Start()
    ESP_LOGI(TAG, "%s started", cfg->pcName);

    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        cfg->pvTaskCode(cfg->pvParameters);  // Call actual task body
        vTaskDelayUntil(&xLastWakeTime, cfg->period_ticks);
    }
}


static void ApplicationTask_Core1_1ms(void *pvParameters)
{
    // Do 1ms stuff here
}

static void ApplicationTask_Core1_5ms(void *pvParameters)
{
    // Do 5ms stuff here
}

static void ApplicationTask_Core1_10ms(void *pvParameters)
{
    // Do 10ms stuff here
}

