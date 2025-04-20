#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"
#include "SYSTICK_interface.h"
#include "GPIO_Interface.h"



void SW_Init(u8 Port, u8 Pin, GPIO_ResType_t ResType)
{
    GPIO_PadConfig_t padConfig = {
        .resType = ResType,
        .lockFlag = GPIO_UNLOCKED,
        .slewRate = GPIO_SLEW_RATE_DISABLE
    };

    GPIO_INIT(Port);
    GPIO_SetPinDir(Port, Pin, PIN_INPUT);
    GPIO_SetPinPadConfig(Port, Pin, &padConfig);
    GPIO_PinAnalogModeSelect(Port, Pin, PIN_OFF);
}

STD_ERROR SW_GetRawValue(u8 Port, u8 Pin, u8* Copy_PinValue)
{
    return GPIO_ReadPin(Port, Pin, Copy_PinValue);
}

u8 SW_IsPressed(u8 Port, u8 Pin, GPIO_ResType_t ResType)
{
    u8 val;
    GPIO_ReadPin(Port, Pin, &val);

    if (ResType == GPIO_PULL_UP)
        return (val == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (val == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}

// ========== External Switch Support ==========

void EXTSW_Init(u8 Port, u8 Pin)
{
    GPIO_PadConfig_t padConfig = {
        .resType = GPIO_PULL_DOWN,  //pull down for external
        .lockFlag = GPIO_UNLOCKED,
        .slewRate = GPIO_SLEW_RATE_DISABLE
    };

    GPIO_INIT(Port);
    GPIO_SetPinDir(Port, Pin, PIN_INPUT);
    GPIO_SetPinPadConfig(Port, Pin, &padConfig);
    GPIO_PinAnalogModeSelect(Port, Pin, PIN_OFF);
}

u8 EXTSW_IsPressed(u8 Port, u8 Pin, GPIO_ResType_t ResType)
{
    u8 val;
    GPIO_ReadPin(Port, Pin, &val);

    if (ResType == GPIO_PULL_UP)
        return (val == 0) ? SW_PRESSED : SW_NOT_PRESSED;
    else
        return (val == 1) ? SW_PRESSED : SW_NOT_PRESSED;
}
