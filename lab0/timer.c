/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"
#define frequency 625000
#define sec 1.0
#define prescalar 256

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1 = 0;//clear timer
    PR1 = ((frequency)*(2*sec)/(prescalar))-1;//Initialize PR1
    T1CONbits.TCKPS = 3; //Initialize pre-scaler
    T1CONbits.TCS = 0; //Setting the oscillator
    IEC0bits.T1IE = 1; //Enable the interrupt
    IFS0bits.T1IF = 0; //Put the flag down         
    IPC1bits.T1IP = 3; //Configure the interrupt priority
    T1CONbits.TON = 1; //Turn the timer on
}

initTimer2(){
    
    //TODO: Initialize Timer 2.
    TMR2 = 0; //clear timer
    T2CONbits.TCKPS = 3; //Initialize pre-scaler
    T2CONbits.TCS = 0; //Setting the oscillator
    IFS0bits.T2IF = 0; //Put the flag down
    IPC1bits.T1IP = 3; //Configure the interrupt priority
    T2CONbits.TON = 1;//turn the second timer on
  
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    TMR2 = 0;//clear the timer
    PR2 = delay*624;//initialize PR2
    IFS0bits.T2IF = 0; //put the flag down
    T2CONbits.ON = 1; //timer is on
    while(IFS0bits.T2IF == 0);//while the flag is down
    T2CONbits.ON = 0;//turn the second timer off
}