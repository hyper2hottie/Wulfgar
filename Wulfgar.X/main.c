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

void interrupt isr(void)
{
    //Check if this is a usart receive interrupt
    if(RCIF)
    {
        command = get_USART_char();
    }
    else if(TMR2IF)
    {
        //Clear timer2 interrupt flag
        TMR2IF = 0;
    }
    
    return;
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
            setSpeed(255, 1);
        }
        else
        {
            RB5 = 0;
            setSpeed(128, 1);
        
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