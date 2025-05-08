////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                GPS               /////////
////                Version:1.1       /////////
///         DATE:   4-30-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#include <math.h> // to import trig functions
#include <string.h> // for string functions
#include "UART_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPS_Private.h"
#include "GPS_Config.h"
#include "GPS_Interface.h"
#include "CLCD_interface.h"
#include "LED_interface.h"
#include "SYSTICK_interface.h"



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
    f64 a,c;
    f64 Local_f64differenceOfLat ;
    f64 Local_f64differenceOfLong;
    // CLCD_VoidClearDisplay();
    // CLCD_VoidDataSetCursor(LINE_1, 0);
    // CLCD_VoidDataSendString("Lat:");
    // CLCD_VoidSendNum((u16)Copy_f64LatGPS);
    // CLCD_VoidDataSendString(".");
    // // Display decimal part (4 digits)
    // CLCD_VoidSendNum((u16)((Copy_f64LatGPS - (u16)Copy_f64LatGPS) * 10000));
    
    // CLCD_VoidDataSetCursor(LINE_2, 0);
    // CLCD_VoidDataSendString("Lng:");
    // CLCD_VoidSendNum((u16)Copy_f64LongGPS);
    // CLCD_VoidDataSendString(".");
    // // Display decimal part (4 digits)
    // CLCD_VoidSendNum((u16)((Copy_f64LongGPS - (u16)Copy_f64LongGPS) * 10000));
    Copy_f64LatGPS = GPS_f64ToRadians(Copy_f64LatGPS);
    Copy_f64LatSaved = GPS_f64ToRadians(Copy_f64LatSaved);
    Copy_f64LongGPS = GPS_f64ToRadians(Copy_f64LongGPS);
    Copy_f64LongSaved = GPS_f64ToRadians(Copy_f64LongSaved);
    
    Local_f64differenceOfLat = Copy_f64LatSaved - Copy_f64LatGPS;
    Local_f64differenceOfLong = Copy_f64LongSaved - Copy_f64LongGPS;

    a = sin(Local_f64differenceOfLat / 2) * sin(Local_f64differenceOfLat / 2) +
               cos(Copy_f64LatGPS) * cos(Copy_f64LatSaved) *
               sin(Local_f64differenceOfLong / 2) * sin(Local_f64differenceOfLong / 2);

    c = 2 * atan2(sqrt(a), sqrt(1 - a)); //atan(y/x) --- atan2(y, x) both are tan inverse in difference format  

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
GPS_Status_t GPS_stdStatusGetLocation(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude,f64 *Copy_ptrf64Longitude, f64 *Copy_ptru8Time) {
    u8 Local_arru8Buffer[SENTENCE_SIZE];
    u8 *Local_pu8Token;
    u8 Local_u8ValidFlag = 0;
    GPS_Status_t Local_Status;
    f64 Local_f64LatTemp;
    u8 Local_u8LatDir;
    f64 Local_f64LongTemp;
    u8 Local_u8LongDir; 
    char *saveptr; // Add a saveptr for thread-safe tokenizing
    
    // Try to find a valid GPRMC sentence
    u8 Local_u8Attempts = 0;
    while (Local_u8Attempts < 2) { // Try up to 2 NMEA sentences
        Local_Status = GPS_stdStatusReadNMEASentence(Copy_ptrUartConfig, Local_arru8Buffer);
        
        if (Local_Status == GPS_VALID_DATA) {
            // Check if it's a GPRMC sentence --- strstr fucntion to find a substring -- return a point of first occurance 
            if (strstr((char*)Local_arru8Buffer, "$GPRMC") != NULL) {
                break;
            }
        }
        Local_u8Attempts++;
    }
    
    if (Local_u8Attempts >= 5)  return GPS_NO_DATA;
        
    // Tokenize the GPRMC sentence
    // $GPRMC,time,status,latitude,N/S,longitude,E/W,...
    // CLCD_VoidClearDisplay();
    // CLCD_VoidDataSetCursor(LINE_1, 0);
    // CLCD_VoidDataSendString(Local_arru8Buffer);
    
    Local_pu8Token = (u8*)strtok_r((char*)Local_arru8Buffer, ",", &saveptr);  // Skip the $GPRMC part
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    
    //Get Time
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    *Copy_ptru8Time = GPS_CustomStringToFloat(Local_pu8Token);
    
    // Get status - 'A' means valid data, 'V' means warning/invalid
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL || Local_pu8Token[0] != 'A') {
        return GPS_INVALID_DATA;
    }
    
    // Get latitude value
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_f64LatTemp = GPS_CustomStringToFloat(Local_pu8Token);
    //LED_voidTurnOnLed(PortA, PIN7);
    
    // Get latitude direction (N/S)
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_u8LatDir = Local_pu8Token[0];
    
    // Get longitude value
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_f64LongTemp = GPS_CustomStringToFloat(Local_pu8Token);
    // Get longitude direction (E/W)
    Local_pu8Token = (u8*)strtok_r(NULL, ",", &saveptr);
    if (Local_pu8Token == NULL) return GPS_INVALID_DATA;
    Local_u8LongDir = Local_pu8Token[0];
    
    // CLCD_VoidClearDisplay();
    // // Display latitude on line 1
    // CLCD_VoidDataSetCursor(LINE_1, 0);
    // CLCD_VoidDataSendString("Lat:");
    // CLCD_VoidSendNum((u16)Local_f64LatTemp);
    // CLCD_VoidDataSendString(".");
    // // Display the fractional part
    // CLCD_VoidSendNum((u16)((Local_f64LatTemp - (u16)Local_f64LatTemp) * 10000));
    
    // // Display longitude on line 2
    // CLCD_VoidDataSetCursor(LINE_2, 0);
    // CLCD_VoidDataSendString("Lng:");
    // CLCD_VoidSendNum((u16)Local_f64LongTemp);
    // CLCD_VoidDataSendString(".");
    // // Display the fractional part
    // CLCD_VoidSendNum((u16)((Local_f64LongTemp - (u16)Local_f64LongTemp) * 10000));


    // Convert to decimal degrees
    *Copy_ptrf64Latitude = GPS_ConvertToDecimalDegrees(Local_f64LatTemp);
    *Copy_ptrf64Longitude = GPS_ConvertToDecimalDegrees(Local_f64LongTemp);


    // CLCD_VoidClearDisplay();
    // CLCD_VoidDataSetCursor(LINE_1, 0);
    // CLCD_VoidDataSendString("Lat:");
    // CLCD_VoidSendNum((u16)*Copy_ptrf64Latitude);
    // CLCD_VoidDataSendString(".");
    // // Display decimal part (4 digits)
    // CLCD_VoidSendNum((u16)((*Copy_ptrf64Latitude - (u16)*Copy_ptrf64Latitude) * 10000));
    
    // CLCD_VoidDataSetCursor(LINE_2, 0);
    // CLCD_VoidDataSendString("Lng:");
    // CLCD_VoidSendNum((u16)*Copy_ptrf64Longitude);
    // CLCD_VoidDataSendString(".");
    // // Display decimal part (4 digits)
    // CLCD_VoidSendNum((u16)((*Copy_ptrf64Longitude - (u16)*Copy_ptrf64Longitude) * 10000));
    // Systick_StdErrorDelayIn_ms(2000);

    // Apply directions
    if (Local_u8LatDir == 'S') *Copy_ptrf64Latitude = -(*Copy_ptrf64Latitude);
    if (Local_u8LongDir == 'W') *Copy_ptrf64Longitude = -(*Copy_ptrf64Longitude);
    
    return GPS_VALID_DATA;
}

// Function to wait until valid GPS data is available with timeout
GPS_Status_t GPS_stdStatusWaitForValidData(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude, f64 *Copy_ptrf64Longitude, f64 *Copy_ptru8Time,u16 Copy_u16Timeout) {
    GPS_Status_t Local_GpsStatus = GPS_NO_DATA;
    u16 Local_u16Attempts = 0;

    while (Local_u16Attempts < Copy_u16Timeout) {
        Local_GpsStatus = GPS_stdStatusGetLocation(Copy_ptrUartConfig, Copy_ptrf64Latitude, Copy_ptrf64Longitude, Copy_ptru8Time);
        
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


f64 GPS_CustomStringToFloat(u8 *str) {
    f64 result = 0.0;
    f64 decimalPlace = 0.1;
    u8 decimalFound = 0;

    while (*str) {
        if (*str == '.') {
            decimalFound = 1;
        } else if (*str >= '0' && *str <= '9') {
            if (!decimalFound) {
                result = (result * 10) + (*str - '0');
            } else {
                result += (*str - '0') * decimalPlace;
                decimalPlace *= 0.1;
            }
        }
        str++;
    }

    return result;
}

