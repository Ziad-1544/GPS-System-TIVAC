// LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

// 	HAL
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

// MCAL
#include "EEPROM_interface.h"

int main(void){
	u32 data_rx;
	GPIO_StdErrorInit(PortF);
	GPIO_StdErrorSetPinDir(PortF, PIN1, PIN_OUTPUT);
	GPIO_StdErrorSetPinDir(PortF, PIN2, PIN_OUTPUT);
	
	EEPROM_STD_ERROR_Init();
	EEPROM_STD_ERROR_WriteData(1,5);
	Systick_StdErrorDelayIn_ms(10);
	data_rx = EEPROM_u32ReadData(1);
	if(data_rx == 5){
		GPIO_StdErrorWritePin(PortF, PIN1, PIN_HIGH);
	}
	else{
		GPIO_StdErrorWritePin(PortF, PIN2, PIN_HIGH);
	}
	
	while(1);
}