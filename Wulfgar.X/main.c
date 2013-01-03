/* 
 * File:   main.c
 * Author: hyper2hottie
 *
 * Created on December 23, 2012, 9:36 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

char command = 'A';

interrupt void isr(void)
{
    //Disable interrupts
    GIE = 0;
    INTE = 0;

    //Check if this is a usart receive interrupt
    if(RCIF)
    {
        command = get_USART_char();
    }
    //Reenable interrupts
    GIE = 1;
    INTE = 1;
}

int main(int argc, char** argv)
{
    //Init some important pi variables
    picInit();
    
    //Init usart for transmit and receive
    USART_Init(1);

    //Init motor
    motorInit();

    while(1)
    {
        if(command == 'A')
        {
            RB5 = 1;
            //setSpeed(255, 1);
        }
        else
        {

            //setSpeed(128, 1);
            RB5 = 0;
        
        }
    }
    
    return (EXIT_SUCCESS);
}

///This function initializes important registers
///that enable the pic to use usart and pwm.
void picInit()
{

    //Set all pins to digital
    ANSEL = 0;
    ANSELH = 0;
    
    //Set portb5 to an output for an indicator LED
    TRISB5 = 0;

    //Disable interupts
    GIE = 0;

    return;
}