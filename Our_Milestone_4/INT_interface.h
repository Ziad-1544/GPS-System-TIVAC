/////////////////////////////////////////////////
//////////   Author: Mustafa ElSherif ///////////
//////////   Date: 5.10.2025          ///////////
//////////   Version: 3.0             ///////////
//////////   Description: Interrupt   ///////////
//////////   Interface file           ///////////
//////////   For TivaC "TM4C123"      ///////////
/////////////////////////////////////////////////

#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_

#define EDGE 0
#define LEVEL 1

#define HIGH 0
#define LOW 1

void INT_voidPORTA_Enable(u8 Copy_u8PinID );
void INT_voidPORTB_Enable(u8 Copy_u8PinID );
void INT_voidPORTC_Enable(u8 Copy_u8PinID );
void INT_voidPORTD_Enable(u8 Copy_u8PinID);
void INT_voidPORTE_Enable(u8 Copy_u8PinID );
void INT_voidPORTF_Enable(u8 Copy_u8PinID);

void INT_voidGPIO_Disable(u8 Copy_u8Port);

void INT_voidGPIO_DisableGlobal(void);

void INT_voidFunc (u8 Copy_u8Port, u8 PIN,void(*Ptr_Func)(void));

#endif