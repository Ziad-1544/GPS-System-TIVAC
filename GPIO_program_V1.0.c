////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  MCAL            /////////
////                GPIO               /////////
///         DATE:   16-3-2025         /////////
//         AUTHOR: Hussein Bahaa     /////////
/////////////////////////////////////////////


#include "BIT_MATH_V1.0.h"
#include "STD_TYPES_V1.0.h"

#include "GPIO_Interface.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"


Std_ReturnType MCAL_GPIO_INIT(u32 Port, GPIO_REGISTERES *Copy_PortId)
{
    Std_ReturnType Local_FunctionStatus = E_OK;

    GPIO_ENABLE |= 1 << Port;
    while ((GPIO_WAIT & 1 << Port) == 0)
        ;
    Copy_PortId->GPIOLOCK = LOCK_VALUE;
    Copy_PortId->GPIOCR |= 1 << Port;

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_GPIO_SetPinMode(GPIO_REGISTERES *Copy_PortId, u8 Copy_PinId, u8 Copy_PinDir, u8 Copy_PinMode)
{
    Std_ReturnType Local_FunctionStatus = E_OK;
    Copy_PortId->GPIOAMSEL &= ~(1 << Copy_PinId);
    Copy_PortId->GPIOAFSEL &= ~(1 << Copy_PinId);
    Copy_PortId->GPIOPCTL &= ~(1111u << Copy_PinId);
    Copy_PortId->GPIODIR &= ~(1 << Copy_PinId);
    Copy_PortId->GPIODIR |= Copy_PinDir << Copy_PinId;
    Copy_PortId->GPIODEN |= 1 << Copy_PinId;
    if (Copy_PinDir == GPIO_PIN_INPUT)
    {
        if (Copy_PinMode == GPIO_INPUT_PULL_UP_MOD)
            Copy_PortId->GPIOPUR |= 1 << Copy_PinId;
        else if (Copy_PinMode == GPIO_INPUT_PULL_DOWN_MOD)
        {
            Copy_PortId->GPIOPDR |= 1 << Copy_PinId;
        }
        else
            Local_FunctionStatus = E_NOT_OK;
    }
    return Local_FunctionStatus;
}

Std_ReturnType MCAL_GPIO_SetPinValue(GPIO_REGISTERES *Gpio_Port, u8 Copy_PinId, u8 Copy_PinValue)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;
	    Gpio_Port->GPIO_WRITE_DATA &= ~( 1 << Copy_PinId);
    Gpio_Port->GPIO_WRITE_DATA |= ((Copy_PinValue & 1) << Copy_PinId);

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_GPIO_GetPinValue(GPIO_REGISTERES *Gpio_Port, u8 Copy_PinId, u8 *Copy_PinReturnValue)
{
    Std_ReturnType Local_FunctionStatus = E_OK;

    if (Copy_PinReturnValue != NULL)
    {
        *Copy_PinReturnValue = (Gpio_Port->GPIO_WRITE_DATA & 1 << Copy_PinId);
        *Copy_PinReturnValue>>=Copy_PinId;
    }

    else
    {
        Local_FunctionStatus = E_NOT_OK;
    }

    return Local_FunctionStatus;
}
