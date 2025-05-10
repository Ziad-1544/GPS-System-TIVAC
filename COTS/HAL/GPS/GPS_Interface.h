////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                GPS               /////////
////                Version:3.0       /////////
///         DATE:   5-10-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_

#include "../../LIB/STD/STD_TYPES.h"
#include "../../LIB/BITMATH/BIT_MATH.h"
#include "GPS_Private.h"
#include "GPS_Config.h"

// Define status values
typedef enum {
    GPS_NO_DATA = 0,
    GPS_INVALID_DATA = 1,
    GPS_VALID_DATA = 2
} GPS_Status_t;

f64 GPS_ConvertToDecimalDegrees(f64 Copy_f64CoordInGPSFormat);
f64 GPS_f64ToRadians(f64 degree);
f64 GPS_f64GetDistance_ArgInDegrees(f64 Copy_f64LatGPS, f64 Copy_f64LongGPS, f64 Copy_f64LatSaved, f64 Copy_f64LongSaved);
GPS_Status_t GPS_stdStatusGetLocation(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude,f64 *Copy_ptrf64Longitude, f64 *Copy_ptru8Time);
GPS_Status_t GPS_stdStatusWaitForValidData(UART_CONFIG_t *Copy_ptrUartConfig, f64 *Copy_ptrf64Latitude, f64 *Copy_ptrf64Longitude, f64 *Copy_ptru8Time,u16 Copy_u16Timeout);
u8 GPS_IsWithinRadius(f64 Copy_f64CurrentLat, f64 Copy_f64CurrentLong, f64 Copy_f64TargetLat, f64 Copy_f64TargetLong, f64 Copy_f64RadiusInMeters);

#endif
