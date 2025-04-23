////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                LED               /////////
////                Version:1.1       /////////
///         DATE:   29-3-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "STD_TYPES.h"
#include "LED_private.h"
#include "LED_config.h"

// LED IDs
#define RED_LED       0x01  // PC0
#define GREEN_LED     0x02  // PC1
#define YELLOW_LED    0x03  // Both PC0 and PC1 ON
#define EXTERNAL_LED  0x04

// LED States
#define LED_ON   1
#define LED_OFF  0

void LED_InitInternal(void);
void LED_SetInitialValue(u8 LedID, u8 LedState);
void LED_InitExternal(u8 Port, u8 Pin);
STD_ERROR LED_GetStatus(u8 Port, u8 Pin, u8* Status);
void LED_TurnOn(u8 Port, u8 Pin);
void LED_TurnOff(u8 Port, u8 Pin);

#endif
