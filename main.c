/*
 * File Name: ATMega16_USART02.c
 * Created: 2023-06-13 8:42:15 AM
 * Author : Ashish Sharma
 * Modified: None
 * Description: This program is a demonstration of using USART communication. 
				In this example, data is being sent using an ATMega16 microcontroller.
 */ 
#define F_CPU 8000000UL //Always on top

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void uartInit()
{
	UCSRA |= (1<<U2X);
	UBRRL = 103;
	UBRRH = 0;
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UCSRB &= (~(1<<UCSZ2));
}

void uartTrans(char t)
{
	while (!(UCSRA & (1<<UDRE)));		//Wait for data to be received.
	UDR = t;
}

void uartTrans_Str(char*a)
{
	while (*a!='\0')
	{
		uartTrans(*a);
		a++;
	}
}

int main(void)
{
    uartInit();
    while (1) 
    {
		uartTrans_Str("ATMega16_USART\r\n");
		_delay_ms(1000);
    }
}

