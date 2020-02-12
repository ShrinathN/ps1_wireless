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
	PSX_ATT_LOW;

	PSX_ATT_HIGH;
}

void PSX_TransRecieveBlock(__UINT8_TYPE__ * block, __UINT8_TYPE__ length)
{

}