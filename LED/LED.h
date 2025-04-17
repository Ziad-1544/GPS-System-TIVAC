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
#define LED_PORT   GPIO_PORTF 

#define RED_LED    0x02
#define YELLOW_LED 0x0A
#define GREEN_LED  0x08

void LED_SetColor(distance);    //don't forget  distance from gps

#endif

