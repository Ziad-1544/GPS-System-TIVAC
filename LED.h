#ifndef LED_H_
#define LED_H_

#include "GPIO_Interface.h"

// LED Pin Definitions (Port F)
#define LED_RED    GPIO_PIN1       // PF1
#define LED_BLUE   GPIO_PIN2      // PF2
#define LED_GREEN  GPIO_PIN3     // PF3

#define LED_PORT   GPIO_PORTF

// LED Functions
void LED_Init(void);                   // Initialize LEDs
void LED_On(uint8_t led);             // Turn on a specific LED
void LED_Off(uint8_t led);           // Turn off a specific LED
void LED_Toggle(uint8_t led);       // Toggle a specific LED
void LED_SetColor(uint8_t color);  // Set multiple LEDs at once

#endif /* LED_H_ */
