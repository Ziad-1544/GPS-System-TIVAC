#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H


#include "GPIO_Interface.h"
#include "SW_private.h"
#include "SW_config.h"

void SW_Init(void);           // Initializes all used switch pins (like PD4, PD0)
u8 SW_input(void);            // Reads all switch values and returns combined result

#endif
