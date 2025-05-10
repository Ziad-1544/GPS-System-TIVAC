////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                LED               /////////
////                Version:3.0       /////////
///         DATE:   10-5-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "../../LIB/STD/STD_TYPES.h"
#include "LED_private.h"
#include "LED_config.h"

#define RED_LED_PIN     PIN1
#define BLUE_LED_PIN    PIN2
#define GREEN_LED_PIN   PIN3

// LED States
#define LED_ON   1
#define LED_OFF  0

void LED_VoidInitInternalLeds(void);
STD_ERROR LED_StdErrorSetInternalLedValue(u8 Copy_u8LedId, u8 Copy_u8LedState);
void LED_voidInitExternalLed(u8 Copy_u8Port, u8 Copy_u8Pin);
void LED_voidTurnOnLed(u8 Copy_u8Port, u8 Copy_u8Pin);
void LED_voidTurnOffLed(u8 Copy_u8Port, u8 Copy_u8Pin);
void LED_voidToggleExternalLed(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8DelayInms);

#endif
