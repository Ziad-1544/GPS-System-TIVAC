/////////////////////////////////////////////
/////////// Author: Mustafa ElSherif  //////
//////////  Date: 24/4/2025          //////
/////////   Version: 1.0            //////
////////   Description: Interrupt  //////
///////   Program file            //////
//////   For TivaC "TM4C123"     //////
//////////////////////////////////////

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "INT_interface.h"
#include "INT_private.h"
#include "INT_config.h"

typedef void (*Ptr_Func)(void);

Ptr_Func array_A [8];
Ptr_Func array_B [8];
Ptr_Func array_C [8];
Ptr_Func array_D [8];
Ptr_Func array_E [8];
Ptr_Func array_F [8];

STD_ERROR GPIO_stdErrorGetInterruptStatus(u32 Copy_u32Port, u8 Copy_u8PinId, u8* Copy_pu8Status)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
		u32 ris_value;
    
    // Validate the status pointer
    if (Copy_pu8Status == NULL) {
        return NOK;
    }
    
    // Select the GPIO port
    switch (Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    // Validate the pin ID
    if (Copy_u8PinId > 7) {
        return NOK;
    }
    
    // Read the GPIORIS register
    ris_value = Local_Port->GPIORIS;
    
    // Extract the status for the specified pin
    *Copy_pu8Status = (ris_value >> Copy_u8PinId) & 1;
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorSetInterruptClear(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8Value == PIN_HIGH) {
        SET_BIT(Local_Port->GPIOICR, Copy_u8PinId);
    } else {
        CLR_BIT(Local_Port->GPIOICR, Copy_u8PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorSetInterruptSense(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8Value == PIN_HIGH) {  // Level-sensitive
        SET_BIT(Local_Port->GPIOIS, Copy_u8PinId);
    } else {  // Edge-sensitive
        CLR_BIT(Local_Port->GPIOIS, Copy_u8PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorSetInterruptBothEdges(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8Value == PIN_HIGH) {  // Both edges
        SET_BIT(Local_Port->GPIOIBE, Copy_u8PinId);
    } else {  // Single edge
        CLR_BIT(Local_Port->GPIOIBE, Copy_u8PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorSetInterruptEvent(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    if(Copy_u8PinId > PIN7) {
        return NOK;
    }
    
    if(Copy_u8Value == PIN_HIGH) {  // Rising edge or high level
        SET_BIT(Local_Port->GPIOIEV, Copy_u8PinId);
    } else {  // Falling edge or low level
        CLR_BIT(Local_Port->GPIOIEV, Copy_u8PinId);
    }
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

STD_ERROR GPIO_stdErrorSetInterruptMask(u32 Copy_u32Port, u8 Copy_u8Value)
{
    STD_ERROR Local_FunctionStatus = NOK;
    volatile GPIO_PORT_t* Local_Port = NULL;
    
    switch(Copy_u32Port) {
        case PortA: Local_Port = GPIO_PORTA; break;
        case PortB: Local_Port = GPIO_PORTB; break;
        case PortC: Local_Port = GPIO_PORTC; break;
        case PortD: Local_Port = GPIO_PORTD; break;
        case PortE: Local_Port = GPIO_PORTE; break;
        case PortF: Local_Port = GPIO_PORTF; break;
        default: return NOK;
    }
    
    Local_Port->GPIOIM |= Copy_u8Value;
    
    Local_FunctionStatus = OK;
    return Local_FunctionStatus;
}

void NVIC_EnableIRQ(u8 IRQn) {
    // Set the bit corresponding to IRQn in ISER0
    // Since IRQn is 0-30 for GPIO interrupts on TM4C123, it fits within ISER0
    SET_BIT(NVIC_ISER0, IRQn);
}

void NVIC_DisableIRQ(u8 IRQn) {
    // Set the bit corresponding to IRQn in ISER0
    // Since IRQn is 0-30 for GPIO interrupts on TM4C123, it fits within ISER0
    CLR_BIT(NVIC_ISER0, IRQn);
}

void INT_voidPORTA_Enable(u8 Copy_u8PinID) {
    NVIC_EnableIRQ(GPIOA_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortA, 0x00);
    GPIO_stdErrorSetInterruptSense(PortA, Copy_u8PinID, PORTA_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortA, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortA, Copy_u8PinID, PORTA_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortA, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortA, 0xFF);    
    __enable_irq();
}

void INT_voidPORTB_Enable(u8 Copy_u8PinID ){
    NVIC_EnableIRQ(GPIOB_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortB, 0x00);
    GPIO_stdErrorSetInterruptSense(PortB, Copy_u8PinID, PORTB_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortB, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortB, Copy_u8PinID, PORTB_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortB, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortB, 0xFF);    
    __enable_irq();
}

void INT_voidPORTC_Enable(u8 Copy_u8PinID ){
    NVIC_EnableIRQ(GPIOC_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortC, 0x00);
    GPIO_stdErrorSetInterruptSense(PortC, Copy_u8PinID, PORTC_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortC, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortC, Copy_u8PinID, PORTC_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortC, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortC, 0xFF);    
    __enable_irq();
}

void INT_voidPORTD_Enable(u8 Copy_u8PinID ){
    NVIC_EnableIRQ(GPIOD_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortD, 0x00);
    GPIO_stdErrorSetInterruptSense(PortD, Copy_u8PinID, PORTD_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortD, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortD, Copy_u8PinID, PORTD_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortD, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortD, 0xFF);    
    __enable_irq();
}

void INT_voidPORTE_Enable(u8 Copy_u8PinID ){
    NVIC_EnableIRQ(GPIOE_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortE, 0x00);
    GPIO_stdErrorSetInterruptSense(PortE, Copy_u8PinID, PORTE_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortE, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortE, Copy_u8PinID, PORTE_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortE, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortE, 0xFF);    
    __enable_irq();
}

void INT_voidPORTF_Enable(u8 Copy_u8PinID ){
    NVIC_EnableIRQ(GPIOF_IRQn); 

    GPIO_stdErrorSetInterruptMask(PortF, 0x00);
    GPIO_stdErrorSetInterruptSense(PortF, Copy_u8PinID, PORTF_SENSE); 
    GPIO_stdErrorSetInterruptBothEdges(PortF, Copy_u8PinID, 0);
    GPIO_stdErrorSetInterruptEvent(PortF, Copy_u8PinID, PORTF_EVENT); 
    GPIO_stdErrorSetInterruptClear(PortF, Copy_u8PinID, 1);   
    GPIO_stdErrorSetInterruptMask(PortF, 0xFF);    
    __enable_irq();
}

void INT_voidGPIO_Disable(u8 Copy_u8Port){
    switch (Copy_u8Port) {
        case PortA: NVIC_DisableIRQ(GPIOA_IRQn); break;
        case PortB: NVIC_DisableIRQ(GPIOB_IRQn); break;
        case PortC: NVIC_DisableIRQ(GPIOC_IRQn); break;
        case PortD: NVIC_DisableIRQ(GPIOD_IRQn); break;
        case PortE: NVIC_DisableIRQ(GPIOE_IRQn); break;
        case PortF: NVIC_DisableIRQ(GPIOF_IRQn); break;
    }
}

void INT_voidGPIO_DisableGlobal(void){
    __disable_irq(); // Disable global interrupts
}

void INT_voidFunc (u8 Copy_u8Port, u8 Copy_u8PinID,void(*Ptr_Func)(void)){
    switch (Copy_u8Port) {
        case PortA: array_A[Copy_u8PinID] = Ptr_Func; break;
        case PortB: array_B[Copy_u8PinID] = Ptr_Func; break;
        case PortC: array_C[Copy_u8PinID] = Ptr_Func; break;
        case PortD: array_D[Copy_u8PinID] = Ptr_Func; break;
        case PortE: array_E[Copy_u8PinID] = Ptr_Func; break;
        case PortF: array_F[Copy_u8PinID] = Ptr_Func; break;
    }
}

void GPIOA_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortA, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)   // if you find the bit number
		{
			array_A[i]() ;           // it will send the function related to that bin
			GPIO_stdErrorSetInterruptClear(PortA, i, 1);   // clear the flag
		}
	}
	
}

void GPIOB_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortB, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)
		{
			array_B[i] () ;
			GPIO_stdErrorSetInterruptClear(PortB, i, 1); // Clear the interrupt
		}
	}
	
}


void GPIOC_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortC, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)
		{
			array_C[i] () ;
			GPIO_stdErrorSetInterruptClear(PortC, i, 1); // Clear the interrupt
		}
	}
}


void GPIOD_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortD, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)
		{
			array_D[i] () ;
			GPIO_stdErrorSetInterruptClear(PortD, i, 1); // Clear the interrupt
		}
	}
}

void GPIOE_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortE, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)
		{
			array_E[i] () ;
			GPIO_stdErrorSetInterruptClear(PortE, i, 1); // Clear the interrupt
		}
	}
}

void GPIOF_Handler(void)
{
  u8 Local_u8InterruptStatus;
	u8 i;
	for(i = 0 ; i < 8 ; i++)
	{
        GPIO_stdErrorGetInterruptStatus(PortF, i, &Local_u8InterruptStatus); // Get the interrupt status
		if (Local_u8InterruptStatus)
		{
			array_F[i] () ;
			GPIO_stdErrorSetInterruptClear(PortF, i, 1); // Clear the interrupt
		}
	}
}