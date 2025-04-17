

// initialize GPIO, LEDs and LCD
int CurrentLED = 0;
int SW2Pressed
void main{
    
    int CurrentMode = 0;
    while(1){
        int SW1Pressed = isSW1Pressed(); //Where isSW1Pressed fetches the status of switch 1

        if(SW1Pressed == 1){ // Assume SW1 is an active-high button
            int CurrentMode = (CurrentMode+1) % 4; // Common method of making sure a variable doesn't exceed a certain number.
        }

        switch(CurrentMode){ // Create functions for each mode
            case 0:
                ManualMode(); break;
            case 1:
                AutoToggleMode(); break;
            case 2: 
                BlinkMode(); break;
            case 3:
                CounterMode(); break;
        }
    }

}

void ManualMode(void){
    
    int PreviousLED = 2;
    SW2Pressed = isSW2Pressed(); //Where isSW2Pressed fetches the status of switch 2

    if(SW2Pressed == 1){
        // Turn on LED 0
        // Turn off LED 2
        PreviousLED = CurrentLED;
        CurrentLED = (CurrentLED+1) % 3;
        // Update LCD with CurrentMode and CurrentLED
    }
}

void AutoToggleMode(void){
    static bool paused = false; //
    SW2Pressed = isSW2Pressed(); 

    if(SW2Pressed ==1){
        paused = !paused; // Pause flag for action button
    }
    if (paused) return;

    switch(CurrentLED){
        case 0: //turn on led 1 and break;
        case 1: //turn on led 2 and break;
        case 2: // turn on led 3 and break;
        default: //Clear all LEDs
    }
    CurrentLED = (CurrentLED +1) %4;
    // Update LCD with CurrentMode and paused flag


}

void BlinkMode(void){
    // Initialize variable BlinkSpeed
    // BlinkSpeed possible values = 0(slow), 1(medium), 2(fast)
    // SW2Pressed = isSW2pressed();
    // BlinkSpeed = (BlinkSpeed+1) % 3;
    /* switch(BlinkSpeed){
            case0: BlinkDelay = 1000 ms
            case 1: BlinkDelay = 500 ms
            case 2: BlinkDelay = 250 ms
    }
    */
    //Turn on all LEDs then delay(BlinkDelay) then turn off all LEDs then delay(BlinkDelay)
}