#ifndef PSX_CONTROLLER_H
#define PSX_CONTROLLER_H

//constants
#define PSX_DELAY_CLK_PRE_SAMPLE_US 9
#define PSX_DELAY_CLK_POST_SAMPLE_US 1

//pin definitions
#define PSX_ATT_DDR DDRC
#define PSX_ATT_PORT PORTC
#define PSX_ATT_BIT PC1

#define PSX_CLK_DDR DDRC
#define PSX_CLK_PORT PORTC
#define PSX_CLK_BIT PC2

#define PSX_CMD_DDR DDRC
#define PSX_CMD_PORT PORTC
#define PSX_CMD_BIT PC3

#define PSX_ACK_DDR DDRC
#define PSX_ACK_PORT PORTC
#define PSX_ACK_PIN PINC
#define PSX_ACK_BIT PC4

#define PSX_DATA_DDR DDRC
#define PSX_DATA_PORT PORTC
#define PSX_DATA_PIN PINC
#define PSX_DATA_BIT PC5

//MACROS
#define PSX_CLK_LOW PSX_CLK_PORT &= ~(1 << PSX_CLK_BIT)
#define PSX_CLK_HIGH PSX_CLK_PORT |= (1 << PSX_CLK_BIT)
#define PSX_ATT_LOW PSX_ATT_PORT &= ~(1 << PSX_ATT_BIT)
#define PSX_ATT_HIGH PSX_ATT_PORT |= (1 << PSX_ATT_BIT)
#define PSX_WAIT_ACK while(PSX_ACK_PIN & (1 << PSX_ACK_BIT))

//different types of controllers
enum
{
	PSX_TYPE_DIGITAL = 0x41,
	PSX_TYPE_NEGCON = 0x23,
	PSX_TYPE_ANALOGUE_RED_LED = 0x73,
	PSX_TYPE_ANALOGUE_RED_LED = 0x53
};

//function declarations
void PSX_PinsInit();
__UINT8_TYPE__ PSX_TransRecieveByte(__UINT8_TYPE__ data);
__UINT8_TYPE__ * PSX_TransRecieveBlock(__UINT8_TYPE__ * block, __UINT8_TYPE__ length);

#endif