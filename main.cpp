/* Time triggered interrupt
*  ========================
*
*  Function:               Preform an interrupt at a timed interval
*  Circuit Schematic No.:  2 : https://github.com/ELECXJEL2645/Circuit_Schematics
*  Required Libraries:     
*
*  Authored by:            Dr Tim Amsdon
*  Date:                   2022
*  Collaberators:          Andrew Knowles
*  Version:                1.0
*  Revision Date:          06/2022 
*  MBED Studio Version:    1.4.1
*  MBED OS Version:        6.12.0
*  Board:	                NUCLEO L476RG */
 
#include "mbed.h"
 
// Create objects for ticker and red LED
Ticker ticker;
DigitalOut red_led(PA_15);
 
// flag - must be volatile as changes within ISR
// g_ prefix makes it easier to distinguish it as global
volatile int g_timer_flag = 0;
 
// function prototypes
void timer_isr();

int state = 0;
 
int main()
{
    // set-up the ticker so that the ISR it is called every 0.5 seconds
    ticker.attach(&timer_isr,500ms);
    
    red_led = state;
    
    while (1) {
 
        // check if flag is set i.e. interrupt has occured
        if (g_timer_flag) {
            g_timer_flag = 0;  // if it has, clear the flag
            
            state = !state;
            red_led = state;
        }
 
        // put the MCU to sleep until an interrupt wakes it up
        sleep();
    }
}
 
// time-triggered interrupt
void timer_isr(){
    g_timer_flag = 1;   // set flag in ISR
}
 
