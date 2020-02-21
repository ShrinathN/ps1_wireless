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

static const uint8_t psx_poll_request[5] = {0x01,0x42,0,0,0};
static uint8_t recieve_block[5];
static uint8_t old_data[3]; //this is the data being sent
//old_data[0] and old_data[1] are PSX bytes
//old_data[2] is the percentage
static uint16_t loop_run_count;

void main()
{
	// uart_init();
	BATTERY_AdcInit();
	PSX_PinsInit();

	//comm system init
	SPI_Init();
	NRF_Init();

	NRF_SetAddressTx((uint8_t[]){0x12,0x23,0x34}, 3);
	NRF_SetMode(CONFIG_PWR_UP_UP);

	loop_run_count = 0;
	while(1)
	{
		PSX_TransRecieveBlock((uint8_t *)psx_poll_request, recieve_block, 5);
		if((recieve_block[3] != old_data[0]) || (recieve_block[4] != old_data[1]))
		{
			old_data[0] = recieve_block[3];
			old_data[1] = recieve_block[4];
			NRF_WriteTxFIFO((uint8_t *)old_data, 3);
			NRF_Execute();
			NRF_IRQ_WAIT;
		}
		if(loop_run_count++ == BATTERY_SAMPLE_TIMER_THRESHOLD)
		{
			loop_run_count = 0;
			old_data[2] = BATTERY_GetPercentage();
		}
	}
}
