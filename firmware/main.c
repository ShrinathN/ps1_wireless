#include "main.h"

void uart_init()
{
	UCSRB |= (1 << TXEN);
	UCSRC |= (1 << URSEL) |     //selecting UCSRC (NOT UBRRH)
	    (1 << UCSZ0) |      //setting as 8 bits
	    (1 << UCSZ1);
	UBRRL = 103;
}

void uart_send(uint8_t data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t buffer[5];
const uint8_t data[5] = {0x01,0x42,0,0,0};


void main()
{
	uart_init();
	BATTERY_AdcInit();
	PSX_PinsInit();
	while(1)
	{
		uart_send(BATTERY_GetPercentage());
		_delay_ms(500);
	}
}
