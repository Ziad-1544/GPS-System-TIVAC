////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                SW                /////////
////                Version:1.1       /////////
///         DATE:   20-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H


#include "GPIO_Interface.h"
#include "SW_private.h"
#include "SW_config.h"
#include "STD_TYPES.h"



#define SW_PRESSED      1
#define SW_NOT_PRESSED  0

// Internal switch functions
void SW_VoidInit(u8 Copy_u8Port, u8 Copy_u8Pin, GPIO_ResType_t Copy_ResType);
STD_ERROR SW_StdErrorGetRawValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_u8PinValue);
u8 SW_U8IsPressed(u8 Copy_u8Port, u8 Copy_u8Pin, GPIO_ResType_t Copy_ResType);

// External switch functions
void EXTSW_VoidInit(u8 Copy_u8Port, u8 Copy_u8Pin);
u8 EXTSW_U8IsPressed(u8 Copy_u8Port, u8 Copy_u8Pin, GPIO_ResType_t Copy_ResType);

#endif
