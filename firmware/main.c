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
uint32_t v;
uint8_t * ptr;
uint32_t d;
uint8_t pct;

void main()
{
	uart_init();
	BATTERY_AdcInit();
	PSX_PinsInit();
	while(1)
	{
		v = (uint32_t)((133120) / BATTERY_GetAdcRaw());
		ptr = (uint8_t *)&v;
		uart_send(ptr[0]);
		uart_send(ptr[1]);
		uart_send(ptr[2]);
		uart_send(ptr[3]);
		d = ((v - BATTERY_ADC_VMIN) * 100) / (BATTERY_ADC_VMAX - BATTERY_ADC_VMIN);
		pct = (uint8_t)d;
		uart_send(pct);

		pct = 0;
		d = 0;
		v = 0;
		ptr = NULL;
		_delay_ms(500);
	}
}
