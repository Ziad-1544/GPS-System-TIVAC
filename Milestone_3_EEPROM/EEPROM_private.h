/////////////////////////////////////////////////
//////////   Author: Mustafa ElSherif ///////////
//////////   Date: 5.10.2025          ///////////
//////////   Version: 3.0             ///////////
//////////   Description: EEPROM      ///////////
//////////   Private file             ///////////
//////////   For TivaC "TM4C123"      ///////////
/////////////////////////////////////////////////


#ifndef EEPROM_PRIVATE_H
#define EEPROM_PRIVATE_H

#define SYSCTL_SREEPROM_R       (*((volatile u32 *)0x400FE558))

// EEPROM block selection register. Used to select the current block for read/write operations.
#define EEPROM_EEBLOCK_R        (*((volatile u32 *)0x400AF004))

// Sets the word offset (0-15) within the selected block for read/write operations. Auto-increments with EERDWRINC.
#define EEPROM_EEOFFSET_R       (*((volatile u32 *)0x400AF008)) 

// EEPROM read/write register. Used for reading/writing data to/from EEPROM. "0xFFFF FFFF = error"
#define EEPROM_EERDWR_R         (*((volatile u32 *)0x400AF010)) 

// Indicates the status of EEPROM operations, with the WORKING bit (0) showing if an operation is in progress (1) or complete (0).
#define EEPROM_EEDONE_R         (*((volatile u32 *)0x400AF018)) 

#define EEPROM_EEDONE_WRBUSY    0x00000020  // Write Busy
#define EEPROM_EEDONE_WORKING   0x00000001  // EEPROM Working

// Provides support functions, including error status (PRETRY, ERETRY bits) and control for recovery operations like copy buffer erase.
#define EEPROM_EESUPP_R         (*((volatile u32 *)0x400AF01C)) 

#define EEPROM_EESUPP_PRETRY    0x00000008  // Programming Must Be Retried
#define EEPROM_EESUPP_ERETRY    0x00000004  // Erase Must Be Retried

// Used for debug mass erase, requires key 0xE37B shifted by EEPROM_EEDBGME_KEY_S, with ME bit set for erase.
#define EEPROM_EEDBGME_R        (*((volatile u32 *)0x400AF080)) 

#define EEPROM_MASS_ERASE_CODE  0xE37B0001

#define SYSCTL_RCGCEEPROM_R     (*((volatile u32 *)0x400FE658))

#define BIT_0                   0

#define EEPROM_WORKING          (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING)

// This bit is set when the EEPROM module encounters a programming error, indicating a retry is needed for a write operation.
#define EEPROM_PRETRY           (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY) 

// This bit is set when an erase operation fails, signaling a retry is required.
#define EEPROM_ERETRY           (EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY)

#define EEPROM_WAITING          while(EEPROM_WORKING){} // Wait until EEPROM finishes any current operation.

#endif /* EEPROM_PRIVATE_H */
