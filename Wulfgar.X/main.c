/* 
 * File:   main.c
 * Author: hyper2hottie
 *
 * Created on December 23, 2012, 9:36 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
/*
 * 
 */
int main(int argc, char** argv)
{
    //Init some important pi variables
    picInit();
    
    //Init usart for transmit and receive
    USART_Init();
    
    while(1)
    {
        char command = get_USART_char();
        if(command == 'A')
        {
            RB5 = 1;
        }
        else
        {
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