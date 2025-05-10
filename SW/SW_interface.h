////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                SW                /////////
////                Version:3.0       /////////
///         DATE:   10-5-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H


#include "GPIO_interface.h" 
#include "STD_TYPES.h"
#include "SW_private.h"
#include "SW_config.h"



#define Internal_SW1    PIN4
#define Internal_SW2    PIN0

#define SW_PRESSED      1
#define SW_NOT_PRESSED  0

// Internal switch functions
STD_ERROR SW_StdErrorInitInternal(u8 Copy_u8Sw);
u8 SW_u8InternalSWIsPressed(u8 Copy_u8Sw);

// External switch functions
STD_ERROR SW_StdErrorInitExternal(u8 Copy_u8Port, u8 Copy_u8Pin);
u8 SW_u8ExternalSWIsPressed(u8 Copy_u8Port, u8 Copy_u8Pin );

#endif
