////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  MCAL            /////////
////                SYSTICK            /////////
////                Version:1.0       /////////
////         DATE:   4-7-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"

STD_ERROR Systick_DelayInTicks(u32 delay_in_ticks)
{
    STD_ERROR Local_FunctionStatus = NOK;
    STK->CTRL = 0;
    STK->LOAD = delay_in_ticks - 1;
    STK->VAL = 0;
    STK->CTRL = ((STK_CTRL_CLK_SOURCE <<2 ) | Enable_SYSTICK | (STK_CTRL_TICKINT << 1) );
    while ((STK->CTRL & CTRL_COUNTFLAG_MASK) == 0)
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR Systick_DelayIn_ms(u32 Copy_Millseconds)
{
    STD_ERROR Local_FunctionStatus = OK;
    for (u32 i = 0; i < Copy_Millseconds; i++)
    {
        Local_FunctionStatus = Systick_DelayInTicks(No_Of_Tick_To_Delay_1ms); // Delay 1 millisecond
        if (Local_FunctionStatus)
        {
            STD_ERROR Local_FunctionStatus = NOK;
            break;
        }
    }
    return Local_FunctionStatus;
}

void Systick_Reset(void)
{
    //Disable SysTick timer
    STK->CTRL &= ~CTRL_ENABLE_MASK;
    //Clear the current value & Clear the count flag
    STK->VAL = 0;
    //Set the reload value to 0
    STK->LOAD = 0;
}

u32 Systick_GetRemainingCounts(void)
{
    return STK->VAL;
}


STD_ERROR Systick_DelayIn_us(u32 Copy_Microseconds)
{
    STD_ERROR Local_FunctionStatus = NOK;

    //Calculate the number of ticks required for the given microseconds
    u32 TicksRequired = (Copy_Microseconds * (SYS_CLK / 1000000));

    //Check if the ticks required is within the valid range 0->2^24-1
    if (TicksRequired <= 0x00FFFFFF)
    {
        //Set the reload value of the SysTick timer
        STK->LOAD = TicksRequired;

        //Enable the SysTick timer
        STK->CTRL = ((STK_CTRL_CLK_SOURCE <<2 ) | Enable_SYSTICK | (STK_CTRL_TICKINT << 1) );

        //Wait until the COUNTFLAG bit is set (indicates timer has counted down to zero)
        while (!(STK->CTRL & CTRL_COUNTFLAG_MASK))

        //Disable the SysTick timer
        STK->CTRL &= ~CTRL_ENABLE_MASK;

        //Reset the timer value
        STK->VAL = 0;

        Local_FunctionStatus = OK;
    }

    return Local_FunctionStatus;
}