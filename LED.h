#ifndef LED_H_
#define LED_H_

#include "GPIO_Interface.h"

#define LED_PORT   GPIO_PORTF  // Define LED port
#define RED_LED    0x02
#define YELLOW_LED 0x0A
#define GREEN_LED  0x08

void RGB_Output(uint32_t data);
void LED_SetColor(distance);    //don't forget  distance from gps

#endif

