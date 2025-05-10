////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                SYSTICK           /////////
////                Version:3.0       /////////
///        DATE:   5-10-2025         /////////
//        AUTHOR: Ziad Kassem       /////////
////////////////////////////////////////////

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

#include "STD_TYPES.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"

STD_ERROR Systick_StdErrorDelayInTicks(u32 Copy_u32delayInTicks);
STD_ERROR Systick_StdErrorDelayIn_ms(u32 Copy_u32Millseconds);
void Systick_VoidReset(void);
u32 Systick_u32GetRemainingCounts(void);
STD_ERROR Systick_StdErrorDelayIn_us(u32 Copy_u32Microseconds);


#endif 





























//void Systick_Init(u32 Copy_Ticks);
//void Systick_Start(void);
//void Systick_Stop(void);
// STD_ERROR Systick_SetIntervalSingle(u32 Copy_Microseconds, void (*Copy_Callback)(void));
// STD_ERROR Systick_SetIntervalPeriodic(u32 Copy_Microseconds, void (*Copy_Callback)(void));
//u32 Systick_GetElapsedCounts(void);
