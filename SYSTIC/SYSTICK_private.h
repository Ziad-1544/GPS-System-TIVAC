////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                SYSTICK           /////////
////                Version:2.0       /////////
///        DATE:   4-25-2025         /////////
//        AUTHOR: Ziad Kassem       /////////
////////////////////////////////////////////
#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

#include "STD_TYPES.h"

typedef struct STK_RegDef_t
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
} STK_RegDef_t;

#define STK ((STK_RegDef_t *)0xE000E010)


#define CTRL_ENABLE_MASK 0x00000001    // Bit 0 : Counter Enable */
#define CTRL_TICKINT_MASK 0x00000002   // Bit 1 : Interrupt Enable */
#define CTRL_CLKSOURCE_MASK 0x00000004 // Bit 2 : Clock Source */
#define CTRL_COUNTFLAG_MASK 0x00010000 // Bit 16: Count Flag */

#define CTRL_CLK_SOURCE_DIV4 0
#define CTRL_CLK_SOURCE_INTERNAL 1

#define CTRL_TICKINT_ENABLE 1
#define CTRL_TICKINT_DISABLE 0

#define SINGLE_INTERVAL 0
#define PERIOD_INTERVAL 1
#define SYS_CLK 16000000 
#define Enable_SYSTICK 1
#define No_Of_Tick_To_Delay_1ms 48000
#define Counter_flag 0x00010000

#endif 