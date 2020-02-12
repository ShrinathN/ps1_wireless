#include "psx_controller.h"
#include "avr/io.h"

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

__UINT8_TYPE__ PSX_TransRecieveByte(__UINT8_TYPE__ data)
{
	__UINT8_TYPE__ received_byte = 0;
	//setting ATT low, thus starting session
	PSX_ATT_LOW;
	//waiting for mandatory ATT delay
	PSX_DELAY_US(PSX_ATT_DELAY_US);
	for(__UINT8_TYPE__ i = 0; i < 8; i++)
	{
		//setting CMD line low or high according to data
		(data & (1 << i)) ? PSX_CMD_HIGH : PSX_CMD_LOW;
		//clock low for first part
		PSX_CLK_LOW;
		PSX_DELAY_US(PSX_DELAY_CLK_PRE_SAMPLE_US);
		//sampling before second part
		received_byte |= PSX_READ_DATA << i;
		//waiting for second part
		PSX_DELAY_US(PSX_DELAY_CLK_POST_SAMPLE_US);
		//setting clock high for sum of both parts
		PSX_CLK_HIGH;
		PSX_DELAY_US(PSX_DELAY_CLK_PRE_SAMPLE_US + PSX_DELAY_CLK_POST_SAMPLE_US);
	}
	//waiting for ACK, optional I guess
	PSX_WAIT_ACK;
	//setting ATT low, thus ending session
	PSX_ATT_HIGH;
	PSX_DELAY_US(PSX_ATT_DELAY_US);
}

void PSX_TransRecieveBlock(__UINT8_TYPE__ * transmit_block, __UINT8_TYPE__ * recieve_block, __UINT8_TYPE__ length)
{
	__UINT8_TYPE__ byte_counter = 0;

	//setting ATT low, thus starting session
	PSX_ATT_LOW;
	//waiting for mandatory ATT delay
	PSX_DELAY_US(PSX_ATT_DELAY_US);

	for(__UINT8_TYPE__ byte_counter = 0; byte_counter < length; byte_counter++)
	{
		for(__UINT8_TYPE__ i = 0, recieve_block[byte_counter] = 0; i < 8; i++)
		{
			//setting CMD line low or high according to data
			(transmit_block[byte_counter] & (1 << i)) ? PSX_CMD_HIGH : PSX_CMD_LOW;
			//clock low for first part
			PSX_CLK_LOW;
			PSX_DELAY_US(PSX_DELAY_CLK_PRE_SAMPLE_US);
			//sampling before second part
			recieve_block[byte_counter] |= PSX_READ_DATA << i;
			//waiting for second part
			PSX_DELAY_US(PSX_DELAY_CLK_POST_SAMPLE_US);
			//setting clock high for sum of both parts
			PSX_CLK_HIGH;
			PSX_DELAY_US(PSX_DELAY_CLK_PRE_SAMPLE_US + PSX_DELAY_CLK_POST_SAMPLE_US);
		}
		//waiting for ACK, optional I guess
		PSX_WAIT_ACK;
	}

	PSX_ATT_HIGH;
	PSX_DELAY_US(PSX_ATT_DELAY_US);
}

__UINT8_TYPE__ PSX_GetControllerType()
{
	return PSX_TransRecieveByte(0x01);
}