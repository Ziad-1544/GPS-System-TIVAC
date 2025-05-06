/////////////////////////////////////////////////
// Author: Mustafa ElSherif
// Date: 24/4/2025
// Version: 1.0
// Description: Interrupt Private file
// For TivaC "TM4C123"
/////////////////////////////////////////////////

#ifndef INT_PRIVATE_H_
#define INT_PRIVATE_H_
/******************************** ENABLE REG ********************************/
/**
 *  NVIC_EN0_R - Interrupt Set-Enable Register 0
 *        This register is used to enable interrupts 0-31 in the NVIC.
 * @address 0xE000E100
 * @type volatile u32
 */

 

#define NVIC_ISER0 (*((volatile u32 *) 0xE000E100))

#define NVIC_DIS0           (*(volatile u32 *)0xE000E180)

#define NVIC_EN0_INT_M          0xFFFFFFFF  // Interrupt Enable

#define GPIOA_IRQn          0  // GPIO Port A interrupt number
#define GPIOB_IRQn          1
#define GPIOC_IRQn          2
#define GPIOD_IRQn          3
#define GPIOE_IRQn          4
#define GPIOF_IRQn          30

#endif