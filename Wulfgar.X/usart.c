// C Code for Operating a USART Port in PIC16F family
// Author: Brian Grosskleg
// Date: March 3, 2012
// Modified: Wyatt Berlinic
// Date: December 22, 2012

#ifndef USART_CODE		//Macro gaurds to prevent redefining
#define USART_CODE

#include <string.h>
#include <xc.h>

//Include the header file with important definitions
#include "usart.h"

////////////////////////////////////////////////////////////////
//USART INITIALIZATION

void USART_Init(int receiveInterupts)
{
    //Set portc7 for input and portc6 for output
    TRISC7 = 1;
    TRISC6 = 0;    

    //TXSTA register
    //Clear SYNC bit, set to Asynchronous
    SYNC = 0;

    // Step #1) PIC Datasheet page 158.
    //TXSTA register
    BRGH = 1;	//Configure BAUD generator to high speed
    BRG16 = 0;	//8-bit BAUD generator

    //BAUDCTL register
    //Turns off ninth bit communication
    TX9=0;		//8-bit transmission
    RX9=0;		//8-bit reception

    //SPBRG register
    //BAUD rate calculation pg 165
    //Fosc = 4Mhz
    //Desired BAUD for RN-42(our bluetooth module) = 9600
    //For RN-42:
    // SPBRG = 25
    // SPBRGH = 0
    Set_SPBRG();
    //SPBRG = 25;
    SPBRGH = 0;

    //Step #2) PIC Datasheet page 158.
    //RCSTA register
    //Set SPEN
    SPEN = 1;

    //Step #5) PIC Datasheet page 158.
    //RCSTA register
    //Sets CREN, enables reception
    CREN = 1;

    //Additional configuration
    TXIE=0;		//Disable TX interrupts

    if(receiveInterupts)
    {
        //Enable receive interrupts(as well as global and peripheral)
        RCIE = 1;
        GIE = 1;
        PEIE = 1;
    }
    else
    {
        RCIE = 0;       //Disable receive interrupts
    }
    TXEN=0;		//Reset transmitter
    //__delay_us(2);
    TXEN=1;
    //__delay_us(2);
    return;
}


void Set_SPBRG(void)
{
    if(Fosc == 4000000)
    {
        if(BRGH==1 && BRG16 ==0)
        {
            switch(BAUD_RATE)
            {//Pg 165 PIC16F887 data sheet
            case 1200:	SPBRG = 207;	break;
            case 2400:	SPBRG = 103;	break;
            case 9600:	SPBRG = 25;	break;
            case 10417:	SPBRG = 23;	break;
            case 19200:	SPBRG = 12;	break;
            default:    break;
            }
        }
    }
    //To be expanded

    return;
}


////////////////////////////////////////////////////////////////////
//USART CHARACTER COMMANDS

//RECIEVE COMMANDS
unsigned char get_USART_char(void)
{
    do
    {clear_usart_errors();}
    while(RCIF == 0);  //Continously reset errors until full byte is recieved

    return RCREG;	//Upon reading RCREG, RCIF flag is reset
}


unsigned char get_USART_char_timeout(void)
{
    //Recieve one byte with a timeout
    for(unsigned int timeout_int = 0xFFFF; timeout_int != 0; timeout_int--)
    {
            if (RCIF == 1)	//Continuously check if byte was recieved
            {return RCREG;}
            clear_usart_errors();
    }

    //dummy = RCREG;		//Flush RCREG
    return 0;			//If no byte was recieved within time limit, return 0.
}


//TRANSMIT COMMANDS
void send_USART_char(unsigned char character)
{
    do 		//while the TXREG is full
    {clear_usart_errors();}  	//Continously reset errors
    while(TXIF == 0);

    TXREG = character;		//Write character out to USART
    //__delay_ms((8/BAUD_RATE)*1000);			//Wait for transmission
    //__delay_ms(1);

    return;
}

void send_USART_string(unsigned char const string[])
{
    for(unsigned char iter = 0 ; iter < strlen(string) ; iter++)
    {send_USART_char(string[iter]);}
    return;
}



////////////////////////////////////////////////////////////////////
//USART ERROR CLEARING
void clear_usart_errors(void)
{
    //Dummy byte for flushing the RCREG
    char dummy;
    if (OERR == 1)
    {
            TXEN=0;				//Reset transmitter
            TXEN=1;
            CREN=0;				//Reset continous recieve
            CREN=1;
    }
    if (FERR == 1)
    {
            dummy=RCREG;		//Flush RCREG
            TXEN=0;				//Reset transmitter
            TXEN=1;
    }
    return;
}

#endif
