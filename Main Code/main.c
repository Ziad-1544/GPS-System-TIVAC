#include <string.h> // for string functions
#include <float.h> // For max value of f64
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_Interface.h"
#include "SYSTICK_interface.h"
#include "CLCD_interface.h"
#include "LED_interface.h"
#include "SW_interface.h"
#include "UART_interface.h"
#include "GPS_Interface.h"
#include "EEPROM_interface.h"
#include "INT_interface.h"
#include "APP.h"

//Global Variables:
SavedLocations_t Database[14]={
    {"GATE_6", 30.064906, 31.280339},
    {"MOSQUE", 30.064526, 31.280305},
    {"HALLA&B", 30.064190, 31.280488},
    {"HALLC&D", 30.063835, 31.280481},
    {"LUPAN", 30.063349, 31.279324},
    {"CREDIT", 30.063974, 31.278607},
    {"GATE3", 30.063871, 31.277879},
    {"Civil_Bldng", 30.064411, 31.277856},
    {"Fountain", 30.065529, 31.278456},
    {"SAWTIAT", 30.065780, 31.279853},
    {"Library", 30.065296, 31.280117},
    {"GYM", 30.064474, 31.278700},
    {"MODRAGAT", 30.064172, 31.279108},
    {"Football_Field", 30.063810, 31.279489}
};
ClosestPlace_t CurrentLoc, NearestLoc;
f64 Local_GPSLat,Local_GPSLong;
u32 EEPROM_Addresses;
u32 TimesVisited;
f64 TimeUTC;
u8  TimeNow[8];
u32 location; // LOOP ITERATOR
UART_CONFIG_t Local_uart2configuration;

//Time visited Report Variables:
u32 visits;
u8 i;
        

//Functions Prototypes
void TimeVisitedReport(void);

int main (){   

    Local_uart2configuration.Module = UART2;
    Local_uart2configuration.DataBits = DataBits8;
    Local_uart2configuration.StopBits = OneStopBit;
    Local_uart2configuration.ParOnOff = ParityDisable;
    Local_uart2configuration.Parity = OddParity; // doesnt matter already disabled
    Local_uart2configuration.BaudRate = 9600; 

    PeripheralsInit();
    GPIO_StdErrorWritePin(PortD,PIN0,PIN_LOW);
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1,0);
    CLCD_VoidDataSendString("Welcome Back..");
    CLCD_VoidDataSetCursor(LINE_2,0);
    CLCD_VoidDataSendString("Press To start");
    Systick_StdErrorDelayIn_ms(2000);
    
    INT_voidFunc(PortE,PIN3,&TimeVisitedReport);     

    while(1){
        if(SW_u8ExternalSWIsPressed(PortC,PIN6)){
            //Intializing Variables:
           strcpy(NearestLoc.name, "ZIAD");
           NearestLoc.name[sizeof(NearestLoc.name)-1] = '\0'; // Ensure null termination
           NearestLoc.distance=DBL_MAX;

           GPIO_StdErrorWritePin(PortD,PIN0,PIN_LOW);
   
           TurnOffAllLeds();
           //GPIO_StdErrorWritePin(PortD,PIN0,PIN_HIGH);
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Please Wait...");
   
   
           GPS_stdStatusWaitForValidData(&Local_uart2configuration,&Local_GPSLat,&Local_GPSLong,&TimeUTC, 10);
   
            for(location = 0; location < 14; location++){
   
               CurrentLoc.distance=GPS_f64GetDistance_ArgInDegrees(Local_GPSLat,Local_GPSLong,Database[location].Lat,Database[location].Long);
               StringCopy(CurrentLoc.name, Database[location].name, sizeof(CurrentLoc.name) - 1);
   
               if ((CurrentLoc.distance < NearestLoc.distance)){ //&& (CurrentLoc.distance < 100)) {
                   NearestLoc.distance = CurrentLoc.distance;
                   StringCopy(NearestLoc.name, Database[location].name, sizeof(NearestLoc.name) - 1);
                   EEPROM_Addresses = location;
               }
           }
           ConvertUTCtoLocalTime(TimeUTC,TimeNow);
           EEPROM_TimesVisitedIncrement(EEPROM_Addresses);
           // CLCD Prints Current Time
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Current Time: ");
           CLCD_VoidDataSetCursor(LINE_2, 0);
           CLCD_VoidDataSendString(TimeNow);
           Systick_StdErrorDelayIn_ms(4000);
           // CLCD Prints Nearest loc & Distance in between 
           BuzzerTrigger();
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString(NearestLoc.name);
           CLCD_VoidDataSetCursor(LINE_2, 0);
           CLCD_VoidSendNum(NearestLoc.distance);
           CLCD_VoidDataSendString(" meters");
           Systick_StdErrorDelayIn_ms(4000);
   
           // CLCD Prints How many times did i visit this place before
           TimesVisited = EEPROM_u32ReadData(EEPROM_Addresses);
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Times Visited: ");
           CLCD_VoidSendNum(TimesVisited);
           if (TimesVisited > 0){
                CLCD_VoidDataSetCursor(LINE_2, 0);
                CLCD_VoidDataSendString("Missed You..");
           }else
           {
                CLCD_VoidDataSetCursor(LINE_2, 0);
                CLCD_VoidDataSendString("New Place..Nice");
           }
           
           
   
           //LED Handling For Distance Ranges
           if (NearestLoc.distance < GREEN_LED_THRESHOLD){ LED_voidTurnOnLed(PortA, PIN7); }
           else if (NearestLoc.distance < YELLOW_LED_THRESHOLD){LED_voidTurnOnLed(PortA, PIN6);}
           else{ LED_voidTurnOnLed(PortA, PIN5); }
        }
    }
}

void TimeVisitedReport(void){
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1, 0);
    CLCD_VoidDataSendString("Times Visited:");

    for(i = 0; i < 14; i++) {
        // Get visit count for this location from EEPROM
        visits = EEPROM_u32ReadData(i);

        CLCD_VoidClearDisplay();
        CLCD_VoidDataSetCursor(LINE_1, 0);
        CLCD_VoidDataSendString(Database[i].name);
        CLCD_VoidDataSetCursor(LINE_2, 0);
        CLCD_VoidDataSendString("Visits: ");
        CLCD_VoidSendNum(visits);

        // Wait for user to read before showing next location
        Systick_StdErrorDelayIn_ms(2000);
    }

    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1, 0);
    CLCD_VoidDataSendString("Report Done");
    Systick_StdErrorDelayIn_ms(3000);
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1,0);
    CLCD_VoidDataSendString("Press To start..");
}

// int main(){
//     f64 TimeUTC;
//     f64 Local_GPSLat=0.0,Local_GPSLong=0.0;
//     UART_CONFIG_t Local_uart2configuration; 
//     Local_uart2configuration.Module = UART2;
//     Local_uart2configuration.DataBits = DataBits8;
//     Local_uart2configuration.StopBits = OneStopBit;
//     Local_uart2configuration.ParOnOff = ParityDisable;
//     Local_uart2configuration.Parity = OddParity; // doesnt matter already disabled
//     Local_uart2configuration.BaudRate = 9600;
    
//     PeripheralsInit();
//     CLCD_VoidClearDisplay();
//     CLCD_VoidDataSetCursor(LINE_1,0);
//     CLCD_VoidDataSendString("TEST1");
//     Systick_StdErrorDelayIn_ms(2000);   

//     GPS_stdStatusWaitForValidData(&Local_uart2configuration,&Local_GPSLat,&Local_GPSLong,&TimeUTC, 10);
//     GPS_f64GetDistance_ArgInDegrees(Local_GPSLat,Local_GPSLong,Database[1].Lat,Database[1].Long);
//     //GPS_stdStatusGetLocation(&Local_uart2configuration,&Local_GPSLat,&Local_GPSLong,&TimeUTC);
//     //Local_GPSLat=GPS_ConvertToDecimalDegrees(Local_GPSLat);
//     //Local_GPSLong=GPS_ConvertToDecimalDegrees(Local_GPSLong);
    
//     // CLCD_VoidClearDisplay();
//     // CLCD_VoidDataSetCursor(LINE_1, 0);
//     // CLCD_VoidSendNum((u16)Local_GPSLat);
//     // CLCD_VoidDataSetCursor(LINE_2, 0);
//     // CLCD_VoidSendNum((u16)Local_GPSLong);
//     while(1);

// }
