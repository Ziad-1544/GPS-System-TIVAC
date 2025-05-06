////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                GPIO              /////////
////                Version:1.1       /////////
///         DATE:   4-7-2025         /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#include "../../LIB/STD/STD_TYPES.h"
#include "../../LIB/BITMATH/BIT_MATH.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"
#include "GPIO_Interface.h"

STD_ERROR GPIO_INIT(u32 Port)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    GPIO_ENABLE |= 1 << Port;
    while ((GPIO_WAIT & 1 << Port) == 0)

    if(GPIO_PortUnlock(Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    if(GPIO_PortCommit(Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    if(GPIO_PortDigitalEnable(Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_PortUnlock(u32 Port, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_Value == PORT_ON) {
        Local_Port->GPIOLOCK = LOCK_VALUE;
        Local_FunctionStatus = OK;
    }else if(Copy_Value == PORT_OFF)
    {
        Local_Port->GPIOLOCK = 0x00000000;
        Local_FunctionStatus = OK;
    }
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_PortCommit(u32 Port, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIOCR = Copy_Value;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_PortDigitalEnable(u32 Port, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIODEN = Copy_Value;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

/*STD_ERROR GPIO_PinCommit(u32 Port, u8 Copy_PinId, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_Value == PIN_OFF) {
        CLR_BIT(Local_Port->GPIOCR, Copy_PinId);
    } else {
        SET_BIT(Local_Port->GPIOCR, Copy_PinId);
    }
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}
*/

/*STD_ERROR GPIO_PinDigitalEnable(u32 Port, u8 Copy_PinId, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_Value == PIN_OFF) {
        CLR_BIT(Local_Port->GPIODEN, Copy_PinId);
    } else {
        SET_BIT(Local_Port->GPIODEN, Copy_PinId);
    }
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}*/

STD_ERROR GPIO_SetPinDir(u32 Port, u8 Copy_PinId, u8 Copy_PinDir)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_PinDir == PIN_INPUT || Copy_PinDir == PIN_OUTPUT) {
        if(Copy_PinDir == PIN_INPUT) {
            CLR_BIT(Local_Port->GPIODIR, Copy_PinId);
        } else {
            SET_BIT(Local_Port->GPIODIR, Copy_PinId);
        }
        Local_FunctionStatus = OK;
    }
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_SetPortDir(u32 Port, u8 Copy_DirValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIODIR = Copy_DirValue;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_WritePin(u32 Port, u8 Copy_PinId, u8 Copy_PinValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_PinValue == PIN_LOW || Copy_PinValue == PIN_HIGH) {
        if(Copy_PinValue == PIN_LOW) {
            CLR_BIT(Local_Port->GPIO_WRITE_DATA, Copy_PinId);
        } else {
            SET_BIT(Local_Port->GPIO_WRITE_DATA, Copy_PinId);
        }
        Local_FunctionStatus = OK;
    }
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_ReadPin(u32 Port, u8 Copy_PinId, u8* Copy_PinReturnValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7 || Copy_PinReturnValue == NULL) {
        return NOK;
    }
    
    *Copy_PinReturnValue = GET_BIT(Local_Port->GPIO_WRITE_DATA, Copy_PinId);
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_WritePort(u32 Port, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIO_WRITE_DATA = Copy_Value;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_ReadPort(u32 Port, u8* Copy_ReturnValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_ReturnValue == NULL) {
        return NOK;
    }
    
    *Copy_ReturnValue = Local_Port->GPIODATA;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_SetPinAlternateFunction(u32 Port, u8 Copy_PinId, u8 Copy_Value, u8 Copy_AltFunc)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    // Configure alternate function select
    if(Copy_Value == PIN_OFF) {
        CLR_BIT(Local_Port->GPIOAFSEL, Copy_PinId);
    } else {
        SET_BIT(Local_Port->GPIOAFSEL, Copy_PinId);
        u32 mask = 0xF << (Copy_PinId * 4);  // 4-bit mask for the pin's field safe factor to remove extra bits
        Local_Port->GPIOPCTL &= ~mask;       // Clear the 4-bit field to avoid bits high because next step in oring  
        Local_Port->GPIOPCTL |= (Copy_AltFunc & 0xF) << (Copy_PinId * 4);  // Set the alternate function
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_PinAnalogModeSelect(u32 Port, u8 Copy_PinId, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_Value == PIN_LOW) {
        CLR_BIT(Local_Port->GPIOAMSEL, Copy_PinId);
    } else {
        SET_BIT(Local_Port->GPIOAMSEL, Copy_PinId);
    }
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_SetPinPadConfig(u32 Port, u8 Copy_PinId, GPIO_PadConfig_t* Copy_Config)
{
    STD_ERROR Local_FunctionStatus = NOK;
    GPIO_PORT_t* Local_Port = NULL;
    
    switch(Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_PinId > PIN7 || Copy_Config == NULL) {
        return NOK;
    }
    
    // Configure pull resistors-safe factor
    CLR_BIT(Local_Port->GPIOPUR, Copy_PinId);
    CLR_BIT(Local_Port->GPIOPDR, Copy_PinId);
    
    switch(Copy_Config->resType) {
        case GPIO_PULL_DOWN:  // 0
            SET_BIT(Local_Port->GPIOPDR, Copy_PinId);
            break;
        case GPIO_PULL_UP:    // 1
            SET_BIT(Local_Port->GPIOPUR, Copy_PinId);
            break;
    }
    
    // Configure slew rate
    if(Copy_Config->slewRate == GPIO_SLEW_RATE_ENABLE) {
        SET_BIT(Local_Port->GPIOSLR, Copy_PinId);
    } else {
        CLR_BIT(Local_Port->GPIOSLR, Copy_PinId);
    }
    
    // // Configure drive strength
    // switch(Copy_Config->currentVal) {
    //     case GPIO_CURRENT_2MA:  // 0
    //         SET_BIT(Local_Port->GPIODR2R, Copy_PinId);
    //         CLR_BIT(Local_Port->GPIODR4R, Copy_PinId);
    //         CLR_BIT(Local_Port->GPIODR8R, Copy_PinId);
    //         break;
    //     case GPIO_CURRENT_4MA:  // 1
    //         CLR_BIT(Local_Port->GPIODR2R, Copy_PinId);
    //         SET_BIT(Local_Port->GPIODR4R, Copy_PinId);
    //         CLR_BIT(Local_Port->GPIODR8R, Copy_PinId);
    //         break;
    //     case GPIO_CURRENT_8MA:  // 2
    //         CLR_BIT(Local_Port->GPIODR2R, Copy_PinId);
    //         CLR_BIT(Local_Port->GPIODR4R, Copy_PinId);
    //         SET_BIT(Local_Port->GPIODR8R, Copy_PinId);
    //         break;
    // }
    
    // Configure commit register
    if(Copy_Config->lockFlag) {
        SET_BIT(Local_Port->GPIOCR, Copy_PinId);
    } else {
        CLR_BIT(Local_Port->GPIOCR, Copy_PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}


































// STD_ERROR GPIO_WriteMaskedPins(u32 Port, u8 Copy_Value, u8 Copy_Mask)
// {
//     STD_ERROR Local_FunctionStatus = NOK;
//     GPIO_PORT_t* Local_Port = NULL;
//     u32 Local_Temp;
    
//     switch(Port) {
//         case PortA: Local_Port = GPIO_PORTA; break;
//         case PortB: Local_Port = GPIO_PORTB; break;
//         case PortC: Local_Port = GPIO_PORTC; break;
//         case PortD: Local_Port = GPIO_PORTD; break;
//         case PortE: Local_Port = GPIO_PORTE; break;
//         case PortF: Local_Port = GPIO_PORTF; break;
//         default: return NOK;
//     }
    
//     Local_Temp = Local_Port->GPIO_WRITE_DATA;
//     Local_Temp &= ~Copy_Mask;              // Clear masked bits
//     Local_Temp |= (Copy_Value & Copy_Mask); // Set new values for masked bits
//     Local_Port->GPIO_WRITE_DATA = Local_Temp;
//     Local_FunctionStatus = OK;
    
//     return Local_FunctionStatus;
// }

// STD_ERROR GPIO_ReadMaskedPins(u32 Port, u8 Copy_Mask, u8* Copy_ReturnValue)
// {
//     STD_ERROR Local_FunctionStatus = NOK;
//     GPIO_PORT_t* Local_Port = NULL;
    
//     switch(Port) {
//         case PortA: Local_Port = GPIO_PORTA; break;
//         case PortB: Local_Port = GPIO_PORTB; break;
//         case PortC: Local_Port = GPIO_PORTC; break;
//         case PortD: Local_Port = GPIO_PORTD; break;
//         case PortE: Local_Port = GPIO_PORTE; break;
//         case PortF: Local_Port = GPIO_PORTF; break;
//         default: return NOK;
//     }
    
//     if(Copy_ReturnValue == NULL) {
//         return NOK;
//     }
    
//     *Copy_ReturnValue = Local_Port->GPIO_WRITE_DATA & Copy_Mask;
//     Local_FunctionStatus = OK;
    
//     return Local_FunctionStatus;
// }
