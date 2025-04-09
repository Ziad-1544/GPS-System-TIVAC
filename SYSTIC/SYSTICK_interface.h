////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  MCAL            /////////
////                SYSTICK            /////////
////                Version:1.0       /////////
////         DATE:   4-7-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

#include "STD_TYPES.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"

STD_ERROR Systick_DelayInTicks(u32 delay);
STD_ERROR Systick_DelayIn_ms(u32 Copy_Millseconds);
void Systick_Reset(void);
u32 Systick_GetRemainingCounts(void);
STD_ERROR Systick_DelayIn_us(u32 Copy_Microseconds);


#endif 