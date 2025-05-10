#include "../../LIB/STD/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../LIB/BITMATH/BIT_MATH.h"
#include "../../MCAL/SYSTICK/SYSTICK_interface.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../../HAL/CLCD/CLCD_interface.h"
#include "../../HAL/SW/SW_interface.h"
#include "../../HAL/LED/LED_interface.h"
#include "../../HAL/GPS/GPS_Interface.h"
#include "../../MCAL/EEPROM/EEPROM_interface.h"


#define RED_LED_THRESHOLD 50
#define YELLOW_LED_THRESHOLD 25
#define GREEN_LED_THRESHOLD 10


typedef struct{
    u8 name [15];
    f64 Lat;
    f64 Long;
} SavedLocations_t; // Struct that holds three values, place name and its lat & long. Initialize this as array of size [LocationsNum]

typedef struct{
    u8 name [15];
    f64 distance;
} ClosestPlace_t; // Holds two variables only, closest place's name and the distance to it from your current location.


void PeripheralsInit(void);
void BuzzerTrigger(void);
void TurnOffAllLeds(void);
void EEPROM_TimesVisitedIncrement(u32 Copyu32_EEPROMAddresses);
void ConvertUTCtoLocalTime(f64 utcTime, u8* timeStr);
void StringCopy(u8 *destination, u8 *source, u8 maxLength);
