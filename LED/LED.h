////////////////////////////////////////////////////
///////           File:LED.h              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:28/03/2025     ////////
//////////////////////////////////////////////  

#ifndef LED_H_
#define LED_H_

#include "GPIO_Interface.h"

// Define LED port
#define LED_PORT   GPIO_PORTC 

#define RED_LED       0x01  // PC0
#define GREEN_LED     0x02  // PC1
#define YELLOW_LED    0x03  
#define EXTERNAL_LED  0x04 

void LED_SetColor(distance);    //don't forget  distance from gps

void LED_ExternalControl(u32 Port, u8 PinId);

#endif

