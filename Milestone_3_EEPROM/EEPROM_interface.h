/////////////////////////////////////////////////
//////////   Author: Mustafa ElSherif ///////////
//////////   Date: 5.10.2025          ///////////
//////////   Version: 3.0             ///////////
//////////   Description: EEPROM      ///////////
//////////   Interface file           ///////////
//////////   For TivaC "TM4C123"      ///////////
/////////////////////////////////////////////////

#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

STD_ERROR EEPROM_STD_ERROR_Init (void);

u32 EEPROM_u32ReadData (u32 Copy_u32Address);

STD_ERROR EEPROM_STD_ERROR_WriteData (u32 Copy_u32Address, u32 Copy_u32Data);

STD_ERROR EEPROM_STD_ERROR_MassEraseData (u32 Copy_u32Address);

void EEPROM_voidConfigBlockOffset(u32 Copy_u32Address);

#endif /* EEPROM_INTERFACE_H */
