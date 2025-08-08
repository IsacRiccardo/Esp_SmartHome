/******************************************************************************/
/*                             INCLUDES                                       */
/******************************************************************************/
#include "Port.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************/
/*                             LOCAL MACROS                                   */
/******************************************************************************/

#define PORT_NO_USED    (2u)
/******************************************************************************/
/*                             LOCAL DATA TYPES                               */
/******************************************************************************/

typedef enum 
{
    PIN_MODE_DIGITAL_INPUT,
    PIN_MODE_DIGITAL_OUTPUT,
    PIN_MODE_ANALOG_INPUT,
    PIN_MODE_ANALOG_OUTPUT
} PortType_e;

typedef struct
{
    PortType_e PortType;
    uint8_t PinNo;
}PortType_t;

/******************************************************************************/
/*                             LOCAL FUNCTION DECLARATIONS                    */
/******************************************************************************/

/******************************************************************************/
/*                             LOCAL VARIABLES                                */
/******************************************************************************/

static PortType_t Port_Config[PORT_NO_USED] = 
{
    {
        PIN_MODE_DIGITAL_INPUT,
        GPIO_NUM_2
    },
    {
        PIN_MODE_ANALOG_INPUT,
        ADC_CHANNEL_6
    }
};

/******************************************************************************/
/*                             GLOBAL FUNCTION DEFINITIONS                    */
/******************************************************************************/

void Port_Init()
{
    for (int i = 0; i < PORT_NO_USED; i++)
    {
        switch (Port_Config[i].PortType) 
        {
            case PIN_MODE_DIGITAL_INPUT: 
                gpio_config_t in_conf = {
                    .pin_bit_mask = (1ULL << Port_Config[i].PinNo),
                    .mode = GPIO_MODE_INPUT,
                    .pull_up_en = GPIO_PULLUP_DISABLE,
                    .pull_down_en = GPIO_PULLDOWN_DISABLE,
                    .intr_type = GPIO_INTR_DISABLE
                };
                gpio_config(&in_conf);
                break;
        

            case PIN_MODE_DIGITAL_OUTPUT: 
                gpio_config_t out_conf = {
                    .pin_bit_mask = (1ULL << Port_Config[i].PinNo),
                    .mode = GPIO_MODE_OUTPUT,
                    .pull_up_en = GPIO_PULLUP_DISABLE,
                    .pull_down_en = GPIO_PULLDOWN_DISABLE,
                    .intr_type = GPIO_INTR_DISABLE
                };
                gpio_config(&out_conf);
                break;
            

            case PIN_MODE_ANALOG_INPUT: 
                // WARNING: Only ADC-capable pins will work here
                // Example: Assume ADC1 channel mapping
                adc1_config_width(ADC_WIDTH_BIT_12);
                // Map GPIO to ADC channel manually (user responsibility)
                // Here I just assume pin == channel mapping for example
                adc1_config_channel_atten((adc1_channel_t)Port_Config[i].PinNo, ADC_ATTEN_DB_11);
                break;
            

            case PIN_MODE_ANALOG_OUTPUT: 
                // WARNING: Only GPIO25/DAC1 or GPIO26/DAC2 work
                if (Port_Config[i].PinNo == GPIO_NUM_25) 
                {
                    dac_output_enable(DAC_CHAN_0);
                } 
                else if (Port_Config[i].PinNo == GPIO_NUM_26) 
                {
                    dac_output_enable(DAC_CHAN_1);
                } 
                else 
                {
                    printf("Error: Pin %d does not support DAC output\n", Port_Config[i].PinNo);
                }
                break;

            default:
                printf("Unknown mode\n");
        }
    }
}


/******************************************************************************/
/*                             LOCAL FUNCTION DEFINITIONS                     */
/******************************************************************************/

