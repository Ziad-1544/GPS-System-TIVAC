#ifndef MICROCONFIG_H_
#define MICROCONFIG_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include "math.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "systick.h"
#include "lcd.h"
#include "uart.h"
#include "gps.h"
#define PI 3.141592654
#define F_CPU 80000000  
#define CSV 1
#define Enable_Interrupts()  __asm("CPSIE I")
#define Disable_Interrupts() __asm("CPSID I")

#endif 
