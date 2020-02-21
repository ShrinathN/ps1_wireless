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

const uint8_t psx_poll_request[5] = {0x01,0x42,0,0,0};
static uint8_t recieve_block[5];

void main()
{
	uart_init();
	BATTERY_AdcInit();
	SPI_Init();
	PSX_PinsInit();
	SPI_Init();
	while(1)
	{
		PSX_TransRecieveBlock(psx_poll_request, recieve_block, 5);
	}
}
