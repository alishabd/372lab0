/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0 

void initSwitch1(){
    //TODO: Initialize switch 1
    TRISDbits.TRISD6 = INPUT;   // Enable input for switch
    CNCONDbits.ON = 1;          // Turn on CN device
    CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor
}
