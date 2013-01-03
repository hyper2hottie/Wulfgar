
/*
 * File:   motor.c
 * Author: Wyatt Berlinic
 *
 * Created on January 2, 2013, 4:23 PM
 */

#ifndef MOTOR_C
#define	MOTOR_C

#include <xc.h>
#include "pwm.h"

#include "motor.h"

/*Initializes pwm and sets up extra ports for controlling
 * the motors.
 */
void motorInit(void)
{
    //The ports we use for motor direction selection
    TRISA0 = 0;
    TRISA1 = 0;
    TRISA2 = 0;
    TRISA3 = 0;

    RA0 = 1;
    RA1 = 0;
    RA2 = 1;
    RA3 = 0;
    
    pwmInit();

}

void setSpeed(char speed, char motor)
{
    if(speed == 127 || speed == 128)
    {
        setDutyCycle(0, motor);
    }
    else if(speed > 128)
    {
        if(motor == 1)
        {
            RA0 = 1;
            RA1 = 0;
        }
        else
        {
            RA2 = 1;
            RA3 = 0;
        }
        speed = speed - 129;
        speed = speed << 2;
        setDutyCycle(speed, motor);
    }
    else if(speed < 127)
    {
        if(motor == 1)
        {
            RA0 = 0;
            RA1 = 1;
        }
        else
        {
            RA2 = 0;
            RA3 = 1;
        }
        speed = speed << 2;
        setDutyCycle(speed, motor);
    }
}


#endif	/* MOTOR_C */

