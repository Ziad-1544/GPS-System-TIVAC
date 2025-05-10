/////////////////////////////////////////////////
//////////   Author: Mustafa ElSherif ///////////
//////////   Date: 5.10.2025          ///////////
//////////   Version: 3.0             ///////////
//////////   Description: EEPROM      ///////////
//////////   Program file             ///////////
//////////   For TivaC "TM4C123"      ///////////
/////////////////////////////////////////////////


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

void EEPROM_voidSoftwareReset(void){

    SET_BIT(SYSCTL_SREEPROM_R, BIT_0);
    Systick_StdErrorDelayIn_ms(5);
    CLR_BIT(SYSCTL_SREEPROM_R, BIT_0);
    Systick_StdErrorDelayIn_ms(5);
}

void EEPROM_voidFixError(void){
    u8 Local_u8Count = 0;

    while (EEPROM_PRETRY || EEPROM_ERETRY) {

        SET_BIT(EEPROM_EESUPP_R, BIT_0);
        Systick_StdErrorDelayIn_ms(20);

        Local_u8Count++;
        if (Local_u8Count == 10) {
            EEPROM_voidSoftwareReset();
            break;
        }
    }
}

STD_ERROR EEPROM_STD_ERROR_Init (void){
    u8 Local_u8ErrorState = NOK;

    SET_BIT(SYSCTL_RCGCEEPROM_R, BIT_0);
    Systick_StdErrorDelayIn_ms(10);
    EEPROM_WAITING;
    if (EEPROM_PRETRY || EEPROM_ERETRY) {
        Local_u8ErrorState = NOK;
        return Local_u8ErrorState;
    } else {
        Local_u8ErrorState = OK;
    }

    EEPROM_voidSoftwareReset();
    
    Systick_StdErrorDelayIn_ms(10);

    EEPROM_WAITING;

    if (EEPROM_PRETRY || EEPROM_ERETRY) {
        EEPROM_voidFixError();
        Local_u8ErrorState = OK;
    }

    return Local_u8ErrorState;
}

u32 EEPROM_u32ReadData (u32 Copy_u32Address){
    u32 Local_u32Data = 0;

    EEPROM_WAITING;
    EEPROM_voidConfigBlockOffset(Copy_u32Address);
    Local_u32Data = EEPROM_EERDWR_R; // Read data from EEPROM

    return Local_u32Data;
}

STD_ERROR EEPROM_STD_ERROR_WriteData (u32 Copy_u32Address, u32 Copy_u32Data){
    STD_ERROR Local_u8ErrorState = NOK;

    EEPROM_WAITING;
    EEPROM_voidConfigBlockOffset(Copy_u32Address);
    EEPROM_EERDWR_R = Copy_u32Data; // Write data to EEPROM

    if (EEPROM_EEDONE_R & EEPROM_EEDONE_WRBUSY) {
        Local_u8ErrorState = OK;
    } else {
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}

STD_ERROR EEPROM_STD_ERROR_MassEraseData (u32 Copy_u32Address){
    STD_ERROR Local_u8ErrorState = NOK;

    EEPROM_WAITING;
    EEPROM_voidConfigBlockOffset(Copy_u32Address);
    EEPROM_EEDBGME_R = EEPROM_MASS_ERASE_CODE; // Mass erase command
    
    EEPROM_WAITING;

    if (EEPROM_EEDONE_R & EEPROM_EEDONE_WRBUSY) {
        Local_u8ErrorState = OK;
    } else {
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}

void EEPROM_voidConfigBlockOffset(u32 Copy_u32Address){

    EEPROM_EEBLOCK_R = (Copy_u32Address >> 4); // Set block number
    EEPROM_EEOFFSET_R = (Copy_u32Address & 0xF); // Set offset within block

}
