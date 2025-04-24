////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                SW                /////////
////                Version:1.1       /////////
///         DATE:   20-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"
#include "SYSTICK_interface.h"
#include "GPIO_Interface.h"



void SW_VoidInit()
{
    GPIO_PadConfig_t Local_PadConfig = {
        SW_RES,
        GPIO_UNLOCKED,
        GPIO_SLEW_RATE_DISABLE
    };

    Local_PadConfig.resType = Copy_ResType;

    GPIO_StdErrorInit(PortF);
    GPIO_StdErrorSetPinDir(PortF, Copy_u8Pin, PIN_INPUT);
    GPIO_StdErrorSetPinPadConfig(Copy_u8Port, Copy_u8Pin, &Local_PadConfig);
    GPIO_StdErrorPinAnalogModeSelect(Copy_u8Port, Copy_u8Pin, PIN_OFF);
}

STD_ERROR SW_StdErrorGetRawValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_u8PinValue)
{
    return GPIO_StdErrorReadPin(Copy_u8Port, Copy_u8Pin, Copy_u8PinValue);
}

u8 SW_U8IsPressed(u8 Copy_u8Port, u8 Copy_u8Pin, GPIO_ResType_t Copy_ResType)
{
    u8 Local_u8PinVal;
    GPIO_StdErrorReadPin(Copy_u8Port, Copy_u8Pin, &Local_u8PinVal);

    if (Copy_ResType == GPIO_PULL_UP)
        return (Local_u8PinVal == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (Local_u8PinVal == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}

// ========== External Switch Support ==========

void EXTSW_VoidInit(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    GPIO_PadConfig_t Local_PadConfig = {
        GPIO_PULL_DOWN,  //pull down for external
        GPIO_UNLOCKED,
        GPIO_SLEW_RATE_DISABLE
    };

    GPIO_StdErrorInit(Copy_u8Port);
    GPIO_StdErrorSetPinDir(Copy_u8Port, Copy_u8Pin, PIN_INPUT);
    GPIO_StdErrorSetPinPadConfig(Copy_u8Port, Copy_u8Pin, &Local_PadConfig);
    GPIO_StdErrorPinAnalogModeSelect(Copy_u8Port, Copy_u8Pin, PIN_OFF);
}

u8 EXTSW_U8IsPressed(u8 Copy_u8Port, u8 Copy_u8Pin, GPIO_ResType_t Copy_ResType)
{
    u8 Local_u8PinVal;
    GPIO_StdErrorReadPin(Copy_u8Port, Copy_u8Pin, &Local_u8PinVal);

    if (Copy_ResType == GPIO_PULL_UP)
        return (Local_u8PinVal == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (Local_u8PinVal == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}
