#include "main.h"

void PSX_PinsInit()
{
	//setting ATT as output, and setting it high
	PSX_ATT_DDR |= (1 << PSX_ATT_BIT);
	PSX_ATT_PORT |= (1 << PSX_ATT_BIT);
	//setting CLK as output, and setting it high
	PSX_CLK_DDR |= (1 << PSX_CLK_BIT);
	PSX_CLK_PORT |= (1 << PSX_CLK_BIT);
	//setting CMD as output, and setting it high
	PSX_CMD_DDR |= (1 << PSX_CMD_BIT);
	PSX_CMD_PORT |= (1 << PSX_CMD_BIT);
	//setting ACK as input, and setting pullup resistor
	PSX_ACK_DDR &= ~(1 << PSX_ACK_BIT);
	PSX_ACK_PORT |= (1 << PSX_ACK_BIT);
	//setting DATA as input, and setting pullup resistor
	PSX_DATA_DDR &= ~(1 << PSX_DATA_BIT);
	PSX_DATA_PORT |= (1 << PSX_DATA_BIT);
}


void PSX_TransRecieveBlock(uint8_t * transmit_block, uint8_t * recieve_block, uint8_t length)
{
	uint8_t byte_offset, bit_offset;

	PSX_ATT_LOW;
	PSX_CMD_HIGH;
	PSX_CLK_HIGH;

	for(byte_offset = 0; byte_offset < length; byte_offset++)
	{
		recieve_block[byte_offset] = 0;
		for(bit_offset = 0; bit_offset < 8; bit_offset++)
		{
			if(transmit_block[byte_offset] & (1 << bit_offset))
			{
				PSX_CMD_HIGH;
			}
			else
			{
				PSX_CMD_LOW;
			}
			PSX_CLK_LOW;
			PSX_DELAY_US(PSX_DELAY_CLK_US);
			PSX_CLK_HIGH;
			recieve_block[byte_offset] |= ((PSX_READ_DATA) << bit_offset);
			PSX_DELAY_US(PSX_DELAY_CLK_US);
		}
		PSX_CLK_HIGH;
		PSX_CMD_HIGH;
		// if(byte_offset != length - 1)
			// PSX_WAIT_ACK;
		PSX_DELAY_US(PSX_INTER_BYTE_DELAY_US);
	}

	PSX_CMD_HIGH;
	PSX_CLK_HIGH;
	PSX_ATT_HIGH;
}