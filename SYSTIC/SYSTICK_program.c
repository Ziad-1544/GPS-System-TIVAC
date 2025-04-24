////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                SYSTICK           /////////
////                Version:2.0       /////////
///        DATE:   4-25-2025         /////////
//        AUTHOR: Ziad Kassem       /////////
////////////////////////////////////////////

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"

STD_ERROR Systick_StdErrorDelayInTicks(u32 Copy_u32delayInTicks)
{
    STD_ERROR Local_FunctionStatus = NOK;
    STK->CTRL = 0;
    STK->LOAD = Copy_u32delayInTicks - 1;
    STK->VAL = 0;
    STK->CTRL = ((STK_CTRL_CLK_SOURCE << 2 ) | (STK_CTRL_TICKINT << 1) | Enable_SYSTICK );
    while ((STK->CTRL & CTRL_COUNTFLAG_MASK) == 0);
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR Systick_StdErrorDelayIn_ms(u32 Copy_u32Millseconds)
{   
    STD_ERROR Local_FunctionStatus = OK;
    u32 i;
    STK->VAL = 0; // RESET THE VAL IN THE BEGINNING OF EVERY DELAY FUNCTION TO AVOID RESIDUAL VALUES LEFT IN THE REGISTER
    for (i = 0; i < Copy_u32Millseconds; i++)
    {
        Local_FunctionStatus = Systick_StdErrorDelayInTicks(No_Of_Tick_To_Delay_1ms); // Delay 1 millisecond
        if (Local_FunctionStatus)
        {
            Local_FunctionStatus = NOK;
            break;
        }
    }
    return Local_FunctionStatus;
}

void Systick_VoidReset(void)
{
    //Disable SysTick timer
    STK->CTRL &= ~CTRL_ENABLE_MASK;
    //Clear the current value & Clear the count flag
    STK->VAL = 0;
    //Set the reload value to 0
    STK->LOAD = 0;
}

u32 Systick_u32GetRemainingCounts(void)
{
    return STK->VAL;
}


STD_ERROR Systick_StdErrorDelayIn_us(u32 Copy_u32Microseconds)
{
    STD_ERROR Local_FunctionStatus = NOK;

    //Calculate the number of ticks required for the given microseconds
    u32 TicksRequired = ((Copy_u32Microseconds * SYS_CLK) / 1000000);
    STK->VAL = 0; // RESET THE VAL IN THE BEGINNING OF EVERY DELAY FUNCTION TO AVOID RESIDUAL VALUES LEFT IN THE REGISTER
    //Check if the ticks required is within the valid range 0->2^24-1
    if (TicksRequired <= 0x00FFFFFF)
    {
        //Set the reload value of the SysTick timer
        STK->LOAD = TicksRequired;

        //Enable the SysTick timer
        STK->CTRL = ((STK_CTRL_CLK_SOURCE <<2 ) | (STK_CTRL_TICKINT << 1) | Enable_SYSTICK );

        //Wait until the COUNTFLAG bit is set (indicates timer has counted down to zero)
        while (!(STK->CTRL & CTRL_COUNTFLAG_MASK));

        //Disable the SysTick timer
        STK->CTRL &= ~CTRL_ENABLE_MASK;

        //Reset the timer value
        STK->VAL = 0;

        Local_FunctionStatus = OK;
    }

    return Local_FunctionStatus;
}






















// u32 Systick_GetElapsedCounts(void)
// {
//     static u32 Local_PreviousValue = 0; //Store the previous SysTick timer value 
//     u32 Local_CurrentValue = STK->VAL;  //Get the current SysTick timer value 
//     u32 Local_ElapsedTicks;
//     //Check if the timer has wrapped around (current value is less than the previous value)
//     if (Local_CurrentValue < Local_PreviousValue)
//     {
//         //Calculate elapsed ticks considering timer overflow
//         Local_ElapsedTicks = Local_PreviousValue - Local_CurrentValue;
//     }
//     else
//     {
//         //Calculate elapsed ticks without timer overflow 
//         Local_ElapsedTicks = STK->LOAD - (Local_CurrentValue - Local_PreviousValue);
//     }

//     //Update the previous value for the next call 
//     Local_PreviousValue = Local_CurrentValue;

//     return Local_ElapsedTicks;
// }
