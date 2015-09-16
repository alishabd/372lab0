/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define button PORTDbits.RD6


//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = wait;
volatile int currentstate = 0;
volatile int sec = 0;
        
int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
     while(1){
          //TODO9: Implement a state machine to create the desired functionality
        switch(state){
            case wait:
                if(currentstate == 0)
                {
                  turnOnLED(1);
                  currentstate = 1;
                }
                if(button == 0)
                {
                    T1CONbits.TON = 0;//turn off the timer
                    TMR1 = 0;//clear the timer
                    sec=0;
                    state =  debouncePress;
                } 
                break;
            
            case debouncePress:
                delayMs(100);//delay for 100ms
                T1CONbits.TON = 1;//turn on the timer
                state = wait2;
                break;
               
            case wait2:
                while(button ==0)
                {
                    state=wait2;
                }
                if(button == 1)//if button is released
                {
                T1CONbits.TON = 0;//turn off the timer
                if(sec < 2)
                {
                state = debounceRelease;//go to state debounce release
                }
                else
                    state = debounceRelease2;
                }   
                break;
               
            case debounceRelease:
                delayMs(100);
                if(currentstate == 1)//check if the current state is 1
                {
                //Turn the LED2 
                currentstate = 2;//set the state to 2
                state = led2;//go to led2 state
                }
                else if(currentstate == 2)
                {
                //Turn on LED3
                currentstate = 3;
                state = led3;
                }
                else 
                {
                //Turn on LED1
                currentstate = 1;
                state = led1;
                }
                break;
    
            case debounceRelease2:
                delayMs(100);
                if(currentstate == 1)
                {
                //Turn the LED3 
                currentstate = 3;//set the state to 3          
                state = led3;
                }
                else if(currentstate == 2)
                {
                //Turn on LED1
                currentstate = 1;
                state = led1;
                }
                else 
                {  
                //Turn on LED2
                currentstate = 2;
                state = led2;
                }
                break;
                
            case led1:
                turnOnLED(1);
                state =  wait;
                break;
              
            case led2:
                turnOnLED(2);
                state = wait;
                break;
                
            case led3:
                turnOnLED(3);
                state = wait;
                break;
        }
    } 
       return 0;
}

   void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0;//put the flag down
    sec++;
   }
   
   void __ISR(_TIMER_2_VECTOR, IPL4SRS) _T2Interrupt(){
    IFS0bits.T2IF = 0;//put the flag down
   }
   
 
