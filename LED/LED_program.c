////////////////////////////////////////////////////
///////           File:LED.C              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:28/03/2025     ////////
////////////////////////////////////////////// 

#include "LED_interface.h"
#include "LED_private.h"
#include "GPIO_Interface.h"

void LED_InitInternal(void)
{
    GPIO_INIT(LED_PORT);
    GPIO_SetPinDir(LED_PORT, RED_LED_PIN, PIN_OUTPUT);
    GPIO_SetPinDir(LED_PORT, GREEN_LED_PIN, PIN_OUTPUT);

    // Default all off
    GPIO_WritePin(LED_PORT, RED_LED_PIN, LED_OFF);
    GPIO_WritePin(LED_PORT, GREEN_LED_PIN, LED_OFF);
}

void LED_SetInitialValue(u8 LedID, u8 LedState)
{
    switch (LedID)
    {
    case RED_LED:
        GPIO_WritePin(LED_PORT, RED_LED_PIN, LedState);
        break;
    case GREEN_LED:
        GPIO_WritePin(LED_PORT, GREEN_LED_PIN, LedState);
        break;
    case YELLOW_LED:
        GPIO_WritePin(LED_PORT, RED_LED_PIN, LedState);
        GPIO_WritePin(LED_PORT, GREEN_LED_PIN, LedState);
        break;
    default:
        // Do nothing for EXTERNAL_LED, handled manually via GPIO
        break;
    }
}

void LED_InitExternal(u8 Port, u8 Pin)
{
    GPIO_INIT(Port);
    GPIO_SetPinDir(Port, Pin, PIN_OUTPUT);
    GPIO_WritePin(Port, Pin, LED_OFF);
}

STD_ERROR LED_GetStatus(u8 Port, u8 Pin, u8* Status)
{
    return GPIO_ReadPin(Port, Pin, Status);
}

void LED_Toggle(u8 Port, u8 Pin)
{
    u8 currentState = 0;
    if (GPIO_ReadPin(Port, Pin, &currentState) == OK)
    {
        GPIO_WritePin(Port, Pin, !currentState);
    }
}
