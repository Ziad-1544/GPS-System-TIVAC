#ifndef LED_H_
#define LED_H_

#include "GPIO_Interface.h"

#define LED_PORT   GPIO_PORTF  // Define LED port
#define RED_LED    GPIO_PIN1
#define YELLOW_LED GPIO_PIN2
#define GREEN_LED  GPIO_PIN3

void LED_SetColor(u8 distance);    //don't forget  u8 distance in main

#endif

