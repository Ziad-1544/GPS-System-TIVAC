////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                LED               /////////
////                Version:3.0       /////////
///         DATE:   10-5-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#include "LED_interface.h"
#include "LED_private.h"
#include "GPIO_Interface.h"
#include "SYSTICK_interface.h"

void LED_VoidInitInternalLeds(void)
{
    GPIO_StdErrorInit(PortF);
    GPIO_StdErrorSetPinDir(PortF, RED_LED_PIN, PIN_OUTPUT);
    GPIO_StdErrorSetPinDir(PortF, BLUE_LED_PIN, PIN_OUTPUT);
    GPIO_StdErrorSetPinDir(PortF, GREEN_LED_PIN, PIN_OUTPUT);

    // Default all off
    GPIO_StdErrorWritePin(PortF, RED_LED_PIN, LED_OFF);
    GPIO_StdErrorWritePin(PortF, BLUE_LED_PIN, LED_OFF);
    GPIO_StdErrorWritePin(PortF, GREEN_LED_PIN, LED_OFF);
}

STD_ERROR LED_StdErrorSetInternalLedValue(u8 Copy_u8LedId, u8 Copy_u8LedState)
{
    STD_ERROR local_functionStatus=NOK;
    switch (Copy_u8LedId)
    {
    case RED_LED_PIN:
        GPIO_StdErrorWritePin(PortF, RED_LED_PIN, Copy_u8LedState);
        local_functionStatus = OK;
        break;
    case BLUE_LED_PIN:
        GPIO_StdErrorWritePin(PortF, BLUE_LED_PIN, Copy_u8LedState);
        local_functionStatus = OK;
        break;
    case GREEN_LED_PIN:
        GPIO_StdErrorWritePin(PortF, GREEN_LED_PIN, Copy_u8LedState);
        local_functionStatus = OK;
        break;
    default:
        break;
    }
    return local_functionStatus;
}

void LED_voidInitExternalLed(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    GPIO_StdErrorInit(Copy_u8Port);
    GPIO_StdErrorSetPinDir(Copy_u8Port, Copy_u8Pin, PIN_OUTPUT);
    GPIO_StdErrorWritePin(Copy_u8Port, Copy_u8Pin, LED_OFF);
}

// STD_ERROR LED_GetStatus(u8 Port, u8 Pin, u8* Status)
// {
//     return GPIO_ReadPin(Port, Pin, Status);
// }

void LED_voidTurnOnLed(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    GPIO_StdErrorWritePin(Copy_u8Port, Copy_u8Pin, LED_ON);

}

void LED_voidTurnOffLed(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    GPIO_StdErrorWritePin(Copy_u8Port, Copy_u8Pin, LED_OFF);

}

void LED_voidToggleExternalLed(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8DelayInms)
{
    u8 currentState = 0;
    if (GPIO_StdErrorReadPin(Copy_u8Port, Copy_u8Pin, &currentState) == OK)
    {
        GPIO_StdErrorWritePin(Copy_u8Port, Copy_u8Pin, !currentState);
        Systick_StdErrorDelayIn_ms(Copy_u8DelayInms);
    }
}
