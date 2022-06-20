/*  Timer interrupt example
*   Operate an Red LED using an timer interrupt. 
*
*   Board: NUCLEO L476RG
*   Author: Dr Craig Evans
*   Editied: Andrew Knowles 2022
*   MBED OS: 6.14
*/ 
 
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
 