////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                GPIO              /////////
////                Version:3.0       /////////
///         DATE:   5-10-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"
#include "GPIO_Interface.h"

STD_ERROR GPIO_StdErrorInit(u32 Copy_u32Port)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    GPIO_ENABLE |= 1 << Copy_u32Port;
    while ((GPIO_WAIT & 1 << Copy_u32Port) == 0);

    if(GPIO_StdErrorPortUnlock(Copy_u32Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    if(GPIO_StdErrorPortCommit(Copy_u32Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    if(GPIO_StdErrorPortDigitalEnable(Copy_u32Port,PORT_ON))
        Local_FunctionStatus =NOK;
    else
    {
        Local_FunctionStatus= OK;
    }
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_StdErrorPortUnlock(u32 Copy_u32Port, u8 Copy_u8PortValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PortValue == PORT_ON) {
        Local_Port->GPIOLOCK = LOCK_VALUE;
        Local_FunctionStatus = OK;
    }else if(Copy_u8PortValue == PORT_OFF)
    {
        Local_Port->GPIOLOCK = 0x00000000;
        Local_FunctionStatus = OK;
    }
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_StdErrorPortCommit(u32 Copy_u32Port, u8 Copy_u8PortValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIOCR = Copy_u8PortValue;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

static STD_ERROR GPIO_StdErrorPortDigitalEnable(u32 Copy_u32Port, u8 Copy_u8PortValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIODEN = Copy_u8PortValue;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorSetPinDir(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinDir)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8PinDir == PIN_INPUT || Copy_u8PinDir == PIN_OUTPUT) {
        if(Copy_u8PinDir == PIN_INPUT) {
            CLR_BIT(Local_Port->GPIODIR, Copy_u8PinId);
        } else {
            SET_BIT(Local_Port->GPIODIR, Copy_u8PinId);
        }
        Local_FunctionStatus = OK;
    }
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorSetPortDir(u32 Copy_u32Port, u8 Copy_u8DirValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIODIR = Copy_u8DirValue;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorWritePin(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8PinValue == PIN_LOW || Copy_u8PinValue == PIN_HIGH) {
        if(Copy_u8PinValue == PIN_LOW) {
            CLR_BIT(Local_Port->GPIO_WRITE_DATA, Copy_u8PinId);
        } else {
            SET_BIT(Local_Port->GPIO_WRITE_DATA, Copy_u8PinId);
        }
        Local_FunctionStatus = OK;
    }
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorReadPin(u32 Copy_u32Port, u8 Copy_u8PinId, u8* Copy_u8PinReturnValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7 || Copy_u8PinReturnValue == NULL) {
        return NOK;
    }
    
    *Copy_u8PinReturnValue = GET_BIT(Local_Port->GPIO_WRITE_DATA, Copy_u8PinId);
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorWritePort(u32 Copy_u32Port, u8 Copy_u8PortValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIO_WRITE_DATA = Copy_u8PortValue;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorReadPort(u32 Copy_u32Port, u8* Copy_ptru8ReturnValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_ptru8ReturnValue == NULL) {
        return NOK;
    }
    
    *Copy_ptru8ReturnValue = Local_Port->GPIODATA;
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorSetPinAlternateFunction(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue, u8 Copy_u8AltFunc)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    // Configure alternate function select
    if(Copy_u8PinValue == PIN_OFF) {
        CLR_BIT(Local_Port->GPIOAFSEL, Copy_u8PinId);
    } else {
        u32 mask;
        SET_BIT(Local_Port->GPIOAFSEL, Copy_u8PinId);
        mask = 0xF << (Copy_u8PinId * 4);  // 4-bit mask for the pin's field safe factor to remove extra bits
        Local_Port->GPIOPCTL &= ~mask;       // Clear the 4-bit field to avoid bits high because next step in oring  
        Local_Port->GPIOPCTL |= (Copy_u8AltFunc & 0xF) << (Copy_u8PinId * 4);  // Set the alternate function
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorPinAnalogModeSelect(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8PinValue == PIN_LOW) {
        CLR_BIT(Local_Port->GPIOAMSEL, Copy_u8PinId);
    } else {
        SET_BIT(Local_Port->GPIOAMSEL, Copy_u8PinId);
    }
    Local_FunctionStatus = OK;
    
    return Local_FunctionStatus;
}

STD_ERROR GPIO_StdErrorSetPinPadConfig(u32 Copy_u32Port, u8 Copy_u8PinId, GPIO_PadConfig_t* Copy_PtrGPIO_PadConfig_tConfig)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7 || Copy_PtrGPIO_PadConfig_tConfig == NULL) {
        return NOK;
    }
    
    // Configure pull resistors-safe factor
    CLR_BIT(Local_Port->GPIOPUR, Copy_u8PinId);
    CLR_BIT(Local_Port->GPIOPDR, Copy_u8PinId);
    
    switch(Copy_PtrGPIO_PadConfig_tConfig->resType) {
        case GPIO_PULL_DOWN:  // 0
            SET_BIT(Local_Port->GPIOPDR, Copy_u8PinId);
            break;
        case GPIO_PULL_UP:    // 1
            SET_BIT(Local_Port->GPIOPUR, Copy_u8PinId);
            break;
    }
    
    // Configure slew rate
    if(Copy_PtrGPIO_PadConfig_tConfig->slewRate == GPIO_SLEW_RATE_ENABLE) {
        SET_BIT(Local_Port->GPIOSLR, Copy_u8PinId);
    } else {
        CLR_BIT(Local_Port->GPIOSLR, Copy_u8PinId);
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
    if(Copy_PtrGPIO_PadConfig_tConfig->lockFlag) {
        SET_BIT(Local_Port->GPIOCR, Copy_u8PinId);
    } else {
        CLR_BIT(Local_Port->GPIOCR, Copy_u8PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorInterruptConfig(u32 Copy_u32Port, u8 Copy_u8PinId,u8 Copy_u8ICR,u8 Copy_u8IS,u8 Copy_u8MIS,u8 Copy_u8IBE,u8 Copy_u8IEV){
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;

    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }

    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    GPIO_StdErrorInit(Copy_u32Port);
    
    // Configure interrupt
    // Clear any previous interrupt
    if(Copy_u8ICR == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOICR, Copy_u8PinId);  // Clear interrupt
    } else {
        CLR_BIT(Local_Port->GPIOICR, Copy_u8PinId);  // Don't clear interrupt
    }
    
    // Configure interrupt sense (edge or level)
    if(Copy_u8IS == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOIS, Copy_u8PinId);  // Level-sensitive
    } else {
        CLR_BIT(Local_Port->GPIOIS, Copy_u8PinId);  // Edge-sensitive
    }
    
    // Configure both edges or single edge
    if(Copy_u8IBE == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOIBE, Copy_u8PinId); // Both edges
    } else {
        CLR_BIT(Local_Port->GPIOIBE, Copy_u8PinId); // Single edge 
    }
    
    // Configure rising or falling edge
    if(Copy_u8IEV == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOIEV, Copy_u8PinId); // Rising edge or high level
    } else {
        CLR_BIT(Local_Port->GPIOIEV, Copy_u8PinId); // Falling edge or low level
    }
    
    // Set the interrupt mask based on MIS parameter
    if(Copy_u8MIS == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOIM, Copy_u8PinId);  // Enable interrupt
    } else {
        CLR_BIT(Local_Port->GPIOIM, Copy_u8PinId);  // Disable interrupt
    }

    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

/*STD_ERROR GPIO_PinCommit(u32 Port, u8 Copy_PinId, u8 Copy_Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
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
    volatile GPIO_PORT_t* Local_Port = NULL;
    
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
































// STD_ERROR GPIO_WriteMaskedPins(u32 Port, u8 Copy_Value, u8 Copy_Mask)
// {
//     STD_ERROR Local_FunctionStatus = NOK;
//     volatile GPIO_PORT_t* Local_Port = NULL;
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
//     volatile GPIO_PORT_t* Local_Port = NULL;
    
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
