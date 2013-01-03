/*
 * File:   pwm.c
 * Author: Wyatt Berlinic
 *
 * Created on January 1, 2013, 7:58 PM
 */

#ifndef PWM_C
#define	PWM_C

#include <xc.h>

#include "pwm.h"

/*This function initializes the CCPx module for pwm
 *mode and sets up Timer2.  Sets up tris bits for pins
 * that ccp is operating on.
 */
void pwmInit()
{
    //Disable ouput drivers on CCP pins
    TRISC1 = 1;
    TRISC2 = 1;
    
    //Max period
    PR2 = 0b11111111;

    //Start with a zero duty cycle
    //CCPR1L = 0b00000000;
    //CCPR2L = 0b00000000;
    CCPR1L = 0b111111111;
    CCPR2L = 0b111111111;
    
    //7-6=00->Single output, p1a modulated
    //5-4=00->lsb's of pwm duty cycle
    //3-0=1100->pwm mode, p1A active high
    CCP1CON = 0b00001100;
    
    //7-6=unimplemented
    //5-4=00->lsb's of pwm duty cycle
    //3-0=1100->pwm mode
    CCP2CON = 0b00001100;


    //Clear timer2 interrupt flag
    TMR2IF = 0;

    //Disable timer 2 interrups
    TMR2IE = 0;

    //Turn on timer2, random postscaler, minimal prescaler
    //7->unimplemented
    //6-3=0000->1:1 postscaler
    //2=1->Timer2 is on
    //1-0=00->prescaler is 1
    T2CON = 0b00000100;

    //Wait for timer2 to overflow, then enable CCPx output
    while(!TMR2IF)
    {
        int temp = 1;
    }
    TRISC1 = 0;
    TRISC2 = 0;
    
}

/*This function sets the duty cycle for the pwm module that is input.
 * @param value - The value for the duty cycle
 * @param module - The module to set the pwm value of
 */
void setDutyCycle(char value, char module)
{
    
    if(module == 1)
    {
        CCPR1L = value;
    }
    else if(module == 2)
    {
        CCPR2L = value;
    }

}

#endif	/* PWM_C */


