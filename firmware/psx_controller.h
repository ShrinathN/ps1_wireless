#ifndef PSX_CONTROLLER_H
#define PSX_CONTROLLER_H
#include "main.h"

//constants
#define PSX_DELAY_CLK_US 10
#define PSX_ATT_DELAY_US 20
#define PSX_INTER_BYTE_DELAY_US 20

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
#define PSX_CMD_LOW PSX_CMD_PORT &= ~(1 << PSX_CMD_BIT)
#define PSX_CMD_HIGH PSX_CMD_PORT |= (1 << PSX_CMD_BIT)
#define PSX_READ_DATA ((PSX_DATA_PIN & (1 << PSX_DATA_BIT))?(1):(0))
#define PSX_WAIT_ACK while(PSX_ACK_PIN & (1 << PSX_ACK_BIT))
#define PSX_DELAY_US(x) _delay_us(x)

//different types of controllers
enum
{
	PSX_TYPE_DIGITAL = 0x41,
	PSX_TYPE_NEGCON = 0x23,
	PSX_TYPE_ANALOGUE_RED_LED = 0x73,
	PSX_TYPE_ANALOGUE_GREEN_LED = 0x53
};

//function declarations
void PSX_PinsInit();
void PSX_TransRecieveBlock(uint8_t * transmit_block, uint8_t * recieve_block, uint8_t length);

#endif