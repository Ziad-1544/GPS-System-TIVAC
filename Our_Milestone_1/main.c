
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "SYSTICK_interface.h"
#include "LED_interface.h"
#include "SW_interface.h"
#include "CLCD_interface.h"

u8 CurrentLED = 0;
u8 SW2Pressed;
void ClearAllLeds(void);
void PowerOnAllLeds(void);
//MODES
void ManualMode(void);
void AutoToggleMode(void);
void BlinkMode(void);
void CounterMode(void);

u8 var_mode1 = 0;
    u8 var_mode2 = 0;
    u8 var_mode3 = 0;
    u8 var_mode4 = 0;

int main(void){
		u8 SW1Pressed ;
    u8 CurrentMode = 0;
	u8 i;
		GPIO_StdErrorInit(PortA);
		GPIO_StdErrorInit(PortB);
    CLCD_StdErrorDataPinsInit();

    //LED_VoidInitInternalLeds();
    LED_voidInitExternalLed(PortA, 5);
    LED_voidInitExternalLed(PortA, 6);
    LED_voidInitExternalLed(PortA, 7);



    SW_StdErrorInitInternal(Internal_SW1); 
    SW_StdErrorInitInternal(Internal_SW2); 
    
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,1);

  
    while(1){
        SW1Pressed = SW_u8InternalSWIsPressed(Internal_SW1); //Where isSW1Pressed fetches the status of switch 1
        
         if(SW1Pressed ){ // Assume SW1 is an active-high button
             CurrentMode = (CurrentMode+1) % 4; // Common method of making sure a variable doesn't exceed a certain number.     
        }
        // Create functions for each mode
        switch(CurrentMode){ 
            case 0:
                ManualMode(); break;
            case 1:
                AutoToggleMode(); break;
            case 2: 
                BlinkMode(); break;
            case 3:
                CounterMode(); break;
        }  
        //Systick_StdErrorDelayIn_ms(1000);
    }
    LED_voidTurnOffLed(PortA, 5);
    LED_voidTurnOffLed(PortA, 6);
    LED_voidTurnOffLed(PortA, 7);
}

void ManualMode(void){
    if(var_mode1 == 0){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,0);
    CLCD_voidDataSendString("Manual Mode");
    var_mode1 = 1;
    
    var_mode2 = 0;
    var_mode3 = 0;
    var_mode4 = 0;
    }
    //int PreviousLED = 2; UNUSED THEREFORE COMMENTED
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); //Where isSW2Pressed fetches the status of switch 2
    

    if(SW2Pressed == 1){

        switch(CurrentLED){ //ACCORDING TO CURRENTLED VALUE, TURN ON LED(VALUE) AND TURN OFF ALL OTHERS
            case 0: LED_voidTurnOnLed(PortA, 5); LED_voidTurnOffLed(PortA, 6); LED_voidTurnOffLed(PortA, 7);CLCD_voidDataSetCursor(LINE_2,1);CLCD_voidDataSendString("LED: 0");break;
            case 1: LED_voidTurnOffLed(PortA, 5); LED_voidTurnOnLed(PortA, 6); LED_voidTurnOffLed(PortA, 7);CLCD_voidDataSetCursor(LINE_2,1);CLCD_voidDataSendString("LED: 1");break;
            case 2: LED_voidTurnOffLed(PortA, 5); LED_voidTurnOffLed(PortA, 6); LED_voidTurnOnLed(PortA, 7);CLCD_voidDataSetCursor(LINE_2,1);CLCD_voidDataSendString("LED: 2");break;

        }

       // PreviousLED = CurrentLED; UNUSED THEREFORE COMMENTED

        CurrentLED = (CurrentLED+1) % 3; // Makes sure CurrentLed doesn't exceed 2 as we only have leds 0-2

        /* LCD UPDATING: SEND THRU CurrentMode VARIABLE WHICH SHOULD POINT TO ManualMode AND PASS CurrentLed VALUE WHICH SHOULD POINT TO EL LEDAYA EL MENAWARA */ 
        Systick_StdErrorDelayIn_ms(1000);
    }
}

void AutoToggleMode(void){
		static u8 paused = 0; //paused flag
 if(var_mode2 == 0){
        CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,0);
    CLCD_voidDataSendString("Auto Toggle Mode");
    var_mode1 = 0;
    var_mode2 = 1;
    var_mode3 = 0;
    var_mode4 = 0;
}
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); 
    

    if(SW2Pressed ==1){
        paused = !paused; // Change the status of Pause flag for action button
    }
    if (paused){
        CLCD_voidDataSetCursor(LINE_2,1);
        CLCD_voidDataSendString("PAUSED");
        return;
    }else{
        CLCD_voidDataSetCursor(LINE_2,1);
        CLCD_voidDataSendString("RUNNING");
    }

    switch(CurrentLED){
        case 0: LED_voidTurnOnLed(PortA, 5);   break;
        case 1: LED_voidTurnOnLed(PortA, 6);  break;
        case 2: LED_voidTurnOnLed(PortA, 7); break;
        default: ClearAllLeds(); break;
    }
    CurrentLED = (CurrentLED +1) %4;
    Systick_StdErrorDelayIn_ms(1000);
}

void BlinkMode(void){
	  static u32 BlinkSpeed = 0 ; // Initialize variable BlinkSpeed
		u32 BlinkDelay;
        if(var_mode3 == 0){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,0);
    CLCD_voidDataSendString("Blink Mode");
    var_mode1 = 0;
    var_mode2 = 0;
    var_mode3 = 1;
    var_mode4 = 0;
        }
    // BlinkSpeed possible values = 0(slow), 1(medium), 2(fast)
    switch (BlinkSpeed)
    {
    case 0: BlinkDelay = 10000; CLCD_voidDataSetCursor(LINE_2,1); CLCD_voidDataSendString("Speed: Slow");   break;   
    case 1: BlinkDelay = 50000; CLCD_voidDataSetCursor(LINE_2,1); CLCD_voidDataSendString("Speed: Medium"); break;   
    case 2: BlinkDelay = 1000;  CLCD_voidDataSetCursor(LINE_2,1); CLCD_voidDataSendString("Speed: Fast");   break;    
    default: 
        break;
    }
    // SW2Pressed = isSW2pressed();
    SW2Pressed=SW_u8InternalSWIsPressed(Internal_SW2);
    
    if (SW2Pressed)
    {
        BlinkSpeed = (BlinkSpeed+1) % 3;
    }
    
    //Turn on all LEDs then delay(BlinkDelay) then turn off all LEDs then delay(BlinkDelay)
    PowerOnAllLeds();
    Systick_StdErrorDelayIn_ms(BlinkDelay);
    ClearAllLeds();
    Systick_StdErrorDelayIn_ms(BlinkDelay);

}

void CounterMode(void){
		static u8 counter;
    static u8 led1_status ;
    static u8 led2_status ;
    static u8 led3_status ;
    if(var_mode4 == 0){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,0);
    CLCD_voidDataSendString("Counter Mode");
    var_mode1 = 0;
    var_mode2 = 0;
    var_mode3 = 0;
    var_mode4 = 1;
    }
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); 

    counter =counter+1;
    if(SW2Pressed){
        counter = 0;
    }
    led1_status = counter & 1;
    if(led1_status){
        LED_voidTurnOnLed(PortA, 5);
    }
    else {
        LED_voidTurnOffLed(PortA, 5);
    }
    led2_status = counter & 0x2;
    if(led2_status){
        LED_voidTurnOnLed(PortA, 6);
    }
    else {
        LED_voidTurnOffLed(PortA, 6);
    }
    led3_status=counter & 0x4;
    if(led3_status){
        LED_voidTurnOnLed(PortA, 7);
    }
    else {
        LED_voidTurnOffLed(PortA, 7);
    }
    
    Systick_StdErrorDelayIn_ms(1000);
}

void ClearAllLeds(void){
    LED_voidTurnOffLed(PortA, 5); LED_voidTurnOffLed(PortA, 6); LED_voidTurnOffLed(PortA, 7);

}
void PowerOnAllLeds(void){
    LED_voidTurnOnLed(PortA, 5); LED_voidTurnOnLed(PortA, 6); LED_voidTurnOnLed(PortA, 7);

}
