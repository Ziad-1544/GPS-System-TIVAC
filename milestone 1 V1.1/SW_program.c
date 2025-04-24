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


// =========================================================================== Internal Switch Support ==============================================

STD_ERROR SW_StdErrorInitInternal(u8 Copy_u8Sw)
{
    STD_ERROR local_functionstatus = NOK;

    GPIO_PadConfig_t Local_PadConfig = {
        INTERNAL_SW_RES,
        GPIO_UNLOCKED,
        GPIO_SLEW_RATE_DISABLE
    };

    GPIO_StdErrorInit(PortF);
    if (Copy_u8Sw == Internal_SW1)
    {
        GPIO_StdErrorSetPinDir(PortF, Internal_SW1, PIN_INPUT);
        GPIO_StdErrorSetPinPadConfig(PortF, Internal_SW1, &Local_PadConfig);
        GPIO_StdErrorPinAnalogModeSelect(PortF, Internal_SW1, PIN_OFF);
        local_functionstatus=OK;
    }
    else if (Copy_u8Sw == Internal_SW2){
        GPIO_StdErrorSetPinDir(PortF, Internal_SW2, PIN_INPUT);
        GPIO_StdErrorSetPinPadConfig(PortF, Internal_SW2, &Local_PadConfig);
        GPIO_StdErrorPinAnalogModeSelect(PortF, Internal_SW2, PIN_OFF);
        local_functionstatus=OK;
    }
    else {
        local_functionstatus=NOK;
    }
    return local_functionstatus;
}


u8 SW_u8InternalSWIsPressed(u8 Copy_u8Sw)
{
    u8 Local_u8PinVal;
    GPIO_StdErrorReadPin(PortF, Copy_u8Sw, &Local_u8PinVal);

    if (INTERNAL_SW_RES == GPIO_PULL_UP)
        return (Local_u8PinVal == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (Local_u8PinVal == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}

// =========================================================================== External Switch Support ==============================================

STD_ERROR SW_StdErrorInitExternal(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    STD_ERROR local_functionstatus = OK;

    GPIO_PadConfig_t Local_PadConfig = {
        EXTERNAL_SW_RES,
        GPIO_UNLOCKED,
        GPIO_SLEW_RATE_DISABLE
    };

    local_functionstatus = GPIO_StdErrorInit(Copy_u8Port);
    if (local_functionstatus == NOK)
    {
        return local_functionstatus;
    }
    
    local_functionstatus = GPIO_StdErrorSetPinDir(Copy_u8Port, Copy_u8Pin, PIN_INPUT);
    if (local_functionstatus == NOK)
    {
        return local_functionstatus;
    }
    local_functionstatus = GPIO_StdErrorSetPinPadConfig(Copy_u8Port, Copy_u8Pin, &Local_PadConfig);
    if (local_functionstatus == NOK)
    {
        return local_functionstatus;
    }
    local_functionstatus = GPIO_StdErrorPinAnalogModeSelect(Copy_u8Port, Copy_u8Pin, PIN_OFF);
    
    return local_functionstatus;
}

u8 SW_u8ExternalSWIsPressed(u8 Copy_u8Port, u8 Copy_u8Pin )
{
    u8 Local_u8PinVal;
    GPIO_StdErrorReadPin(Copy_u8Port, Copy_u8Pin, &Local_u8PinVal);

    if (EXTERNAL_SW_RES == GPIO_PULL_UP)
        return (Local_u8PinVal == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (Local_u8PinVal == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}
