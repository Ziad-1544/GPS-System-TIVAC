////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                GPS               /////////
////                Version:1.0       /////////
///         DATE:   4-30-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#include <math.h> // to import trig functions
#include <string.h> // for string functions
#include <stdlib.h> // for atof function
#include "UART_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPS_Private.h"
#include "GPS_Config.h"
#include "GPS_Interface.h"

// long & lat format : ddmm.mmmm d for degree , so need to transform this form to degree
// then we will figure out that the math lib need for angles for the trig functions in radian 

//ex 3007.038 to decimal degrees 30.1173
f64 GPS_ConvertToDecimalDegrees(f64 Copy_f64CoordInGPSFormat) {
    u32 Local_u32Degrees = (u32)(Copy_f64CoordInGPSFormat / 100);
    f64 Local_u32Minutes = Copy_f64CoordInGPSFormat - (Local_u32Degrees * 100);
    return Local_u32Degrees + (Local_u32Minutes / 60.0);
}

f64 GPS_f64ToRadians(f64 degree) {
    return degree * (PI / 180.0);
}

f64 GPS_f64GetDistance_ArgInDegrees(f64 Copy_f64LatGPS, f64 Copy_f64LongGPS, f64 Copy_f64LatSaved, f64 Copy_f64LongSaved) {
    f64 Local_f64differenceOfLat = GPS_f64ToRadians(Copy_f64LatSaved - Copy_f64LatGPS);
    f64 Local_f64differenceOfLong = GPS_f64ToRadians(Copy_f64LongSaved - Copy_f64LongGPS);

    Copy_f64LatGPS = GPS_f64ToRadians(Copy_f64LatGPS);
    Copy_f64LatSaved = GPS_f64ToRadians(Copy_f64LatSaved);

    f64 a = sin(Local_f64differenceOfLat / 2) * sin(Local_f64differenceOfLat / 2) +
               cos(Copy_f64LatGPS) * cos(Copy_f64LatSaved) * sin(Local_f64differenceOfLong / 2) * sin(Local_f64differenceOfLong / 2);

    f64 c = 2 * atan2(sqrt(a), sqrt(1 - a)); //atan(y/x) --- atan2(y, x) both are tan inverse in difference format  

    return EARTH_RADIUS_M * c;
}


// Function to read a complete NMEA sentence
static GPS_Status_t GPS_stdStatusReadNMEASentence(UART_CONFIG_t *Copy_ptrUartConfig, u8 *Copy_arru8Buffer) {
    u8 Local_u8Byte;
    u8 Local_u8Index = 0;
    u8 Local_u8StartFound = 0;
    
    // Clear timeout or add timeout counter if needed
    while (Local_u8Index < SENTENCE_SIZE - 1) {
        if (UART_StdErrorReceiveByte(Copy_ptrUartConfig, &Local_u8Byte) != OK) {
            return GPS_NO_DATA;
        }
        
        // Look for start of a sentence
        if (Local_u8Byte == '$') {
            Local_u8StartFound = 1;
            Local_u8Index = 0;
        }
        
        if (Local_u8StartFound) {
            Copy_arru8Buffer[Local_u8Index++] = Local_u8Byte;
            
            // Check for end of sentence
            if (Local_u8Byte == '\n' || Local_u8Byte == '\r') {
                Copy_arru8Buffer[Local_u8Index] = '\0';
                return GPS_VALID_DATA;
            }
        }
    }
    
    // Buffer full without finding complete sentence
    Copy_arru8Buffer[SENTENCE_SIZE - 1] = '\0';
    return GPS_INVALID_DATA;
}

// Function to parse NMEA sentences and extract needed information
GPS_Status_t GPS_stdStatusGetLocation(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude, f64 *Copy_ptrf64Longitude) {
    u8 Local_arru8Buffer[SENTENCE_SIZE];
    u8 *Local_pu8Token;
    u8 Local_u8ValidFlag = 0;
    GPS_Status_t Local_Status;
    
    // Try to find a valid GPRMC sentence
    u8 Local_u8Attempts = 0;
    while (Local_u8Attempts < 5) { // Try up to 5 NMEA sentences
        Local_Status = GPS_ReadNMEASentence(Copy_ptrUartConfig, Local_arru8Buffer);
        
        if (Local_Status == GPS_VALID_DATA) {
            // Check if it's a GPRMC sentence --- strstr fucntion to find a substring -- return a point of first occurance 
            if (strstr((u8*)Local_arru8Buffer, "$GPRMC") != NULL) {
                break;
            }
        }
        
        Local_u8Attempts++;
    }
    
    if (Local_u8Attempts >= 5) {
        return GPS_NO_DATA;
    }
    
    // Tokenize the GPRMC sentence
    // $GPRMC,time,status,latitude,N/S,longitude,E/W,...
    Local_pu8Token = (u8*)strtok((u8*)Local_arru8Buffer, ",");  // Skip the $GPRMC part
    
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_pu8Token = (u8*)strtok(NULL, ",");  // Get time
    
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_pu8Token = (u8*)strtok(NULL, ",");  // Get status
    
    // Check if data is valid: 'A' = Valid, 'V' = Invalid
    if (Local_pu8Token == NULL || Local_pu8Token[0] != 'A') {
        return GPS_INVALID_DATA;
    }
    
    // Get latitude value
    Local_pu8Token = (u8*)strtok(NULL, ",");
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    f64 Local_f64LatTemp = atof((u8*)Local_pu8Token);
    
    // Get latitude direction (N/S)
    Local_pu8Token = (u8*)strtok(NULL, ",");
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    u8 Local_u8LatDir = Local_pu8Token[0];
    
    // Get longitude value
    Local_pu8Token = (u8*)strtok(NULL, ",");
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    f64 Local_f64LongTemp = atof((u8*)Local_pu8Token);
    
    // Get longitude direction (E/W)
    Local_pu8Token = (u8*)strtok(NULL, ",");
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    u8 Local_u8LongDir = Local_pu8Token[0];
    
    // Convert to decimal degrees
    *Copy_ptrf64Latitude = GPS_ConvertToDecimalDegrees(Local_f64LatTemp);
    *Copy_ptrf64Longitude = GPS_ConvertToDecimalDegrees(Local_f64LongTemp);
    
    // Apply directions
    if (Local_u8LatDir == 'S') *Copy_ptrf64Latitude = -(*Copy_ptrf64Latitude);
    if (Local_u8LongDir == 'W') *Copy_ptrf64Longitude = -(*Copy_ptrf64Longitude);
    
    return GPS_VALID_DATA;
}

// Function to wait until valid GPS data is available with timeout
GPS_Status_t GPS_stdStatusWaitForValidData(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude, f64 *Copy_ptrf64Longitude, u16 Copy_u16Timeout) {
    GPS_Status_t Local_GpsStatus = GPS_NO_DATA;
    u16 Local_u16Attempts = 0;
    
    while (Local_u16Attempts < Copy_u16Timeout) {
        Local_GpsStatus = GPS_stdStatusGetLocation(Copy_ptrUartConfig, Copy_ptrf64Latitude, Copy_ptrf64Longitude);
        
        if (Local_GpsStatus == GPS_VALID_DATA) {
            return GPS_VALID_DATA;
        }
        
        Local_u16Attempts++;
    }
    
    return Local_GpsStatus;
}

// Function to check if the current position is within a certain radius of a target
u8 GPS_IsWithinRadius(f64 Copy_f64CurrentLat, f64 Copy_f64CurrentLong, f64 Copy_f64TargetLat, f64 Copy_f64TargetLong, f64 Copy_f64RadiusInMeters) {
    f64 Local_f64Distance = GPS_f64GetDistance_ArgInDegrees(Copy_f64CurrentLat, Copy_f64CurrentLong, Copy_f64TargetLat, Copy_f64TargetLong);
    
    return (Local_f64Distance <= Copy_f64RadiusInMeters) ? 1 : 0;
}