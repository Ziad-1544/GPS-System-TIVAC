#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H


#include "GPIO_Interface.h"
#include "SW_private.h"
#include "SW_config.h"
#include "STD_TYPES.h"



#define SW_PRESSED      1
#define SW_NOT_PRESSED  0

// Internal switch functions
void SW_Init(u8 Port, u8 Pin, GPIO_ResType_t ResType);
STD_ERROR SW_GetRawValue(u8 Port, u8 Pin, u8* Copy_PinValue);
u8 SW_IsPressed(u8 Port, u8 Pin, GPIO_ResType_t ResType);

// External switch functions
void EXTSW_Init(u8 Port, u8 Pin);
u8 EXTSW_IsPressed(u8 Port, u8 Pin, GPIO_ResType_t ResType);

#endif
