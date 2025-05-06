////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  MCAL            /////////
////                SYSTICK            /////////
////                Version:1.0       /////////
////         DATE:   4-7-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef STK_CONFIG_H_
#define STK_CONFIG_H_
#include "SYSTICK_private.h"
//OPTIONS: 1) CTRL_CLK_SOURCE_INTERNAL  2) CTRL_CLK_SOURCE_DIV4
#define STK_CTRL_CLK_SOURCE CTRL_CLK_SOURCE_INTERNAL
//OPTIONS: 1) CTRL_TICKINT_ENABLE  2) CTRL_TICKINT_DISABLE 
#define STK_CTRL_TICKINT CTRL_TICKINT_DISABLE

#endif 
