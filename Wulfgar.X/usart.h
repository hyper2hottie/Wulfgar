// Header for Operating a USART Port in PIC16F family
// Author: Brian Grosskleg
// Date: March 3, 2012
// Modified: Wyatt Berlinic
// Date: December 22, 2012

#ifndef USART_HEADER		//Macro gaurds to prevent redefining
#define USART_HEADER

//The baud rate to use on usart
#define BAUD_RATE 9600

//Frequency of oscilator
#define Fosc 4000000

//Prototypes
void Set_SPBRG(void);
void clear_usart_errors(void);
unsigned char get_USART_char(void);
unsigned char get_USART_char_timeout(void);
void send_USART_char(unsigned char character);
void send_USART_string(unsigned char const string[]);

void USART_Init(void);


//#include "usart.c"

#endif