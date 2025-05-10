// LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

// 	HAL
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

// MCAL
#include "INT_interface.h"

void func (void) {
	GPIO_StdErrorWritePin(PortF, PIN2, PIN_HIGH);
	Systick_StdErrorDelayIn_ms(2000);
}

u8 flag;

int main(void){
	// GPIO init
	GPIO_StdErrorInit(PortF);
	GPIO_StdErrorSetPinDir(PortF, PIN4, PIN_INPUT);
	GPIO_StdErrorSetPinDir(PortF, PIN1, PIN_OUTPUT);
	GPIO_StdErrorSetPinDir(PortF, PIN2, PIN_OUTPUT);
	
	// Application Init
	flag = 0;
	GPIO_StdErrorWritePin(PortF, PIN1, PIN_LOW);
	GPIO_StdErrorWritePin(PortF, PIN2, PIN_LOW);
	
	// Interrupt init
	INT_voidPORTF_Enable(PIN4);
	INT_voidFunc(PortF, PIN4, &func);
	
	while(1){
		GPIO_StdErrorWritePin(PortF, PIN2, PIN_LOW);
		if(flag == 0){
			GPIO_StdErrorWritePin(PortF, PIN1, PIN_HIGH);
			flag = 1;
		}
		else{
			GPIO_StdErrorWritePin(PortF, PIN1, PIN_LOW);
			flag = 0;
		}
		Systick_StdErrorDelayIn_ms(750);
	}
}