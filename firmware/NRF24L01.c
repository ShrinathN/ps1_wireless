#include "NRF24L01.h"


uint8_t NRF_ReadRegister(uint8_t regstr)
{
	uint8_t buffer;
	//000A AAAA
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b0 | regstr}, 1);
	SPI_Receive(&buffer, 1);
	NRF_CSN_HIGH;
	return buffer;

}

void NRF_WriteRegister(uint8_t regstr, uint8_t data)
{
	// 001A AAAA
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b00100000 | regstr, data}, 2);
	NRF_CSN_HIGH;
}


void NRF_WriteTxFIFO(uint8_t * data, uint8_t length)
{
	//1010 0000
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b10100000}, 1);
	SPI_Transmit(data, length);
	NRF_CSN_HIGH;
}

void NRF_ReadRxFIFO(uint8_t * ptr, uint8_t length)
{
	//0110 0001
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b01100001}, 1);
	SPI_Receive(ptr, length);
	NRF_CSN_HIGH;
}

void NRF_SetAddressTx(uint8_t * ptr, uint8_t length)
{
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b00100000 | 0x10}, 1);
	SPI_Transmit(ptr, length);
	NRF_CSN_HIGH;
}

void NRF_SetMode(uint8_t mode)
{
	uint8_t config_reg = NRF_ReadRegister(REG_CONFIG);
	if(mode == CONFIG_PWR_UP_UP)
	{
		config_reg |= CONFIG_PWR_UP_UP;
	}
	else
	{
		config_reg &= ~(CONFIG_PWR_UP_UP);
	}
	NRF_WriteRegister(REG_CONFIG, config_reg);
}

void NRF_Init()
{
	//setting CE as output, and low
	NRF_CE_DDR |= (1 << NRF_CE_BIT);
	NRF_CE_LOW; //putting CE low

	NRF_CSN_HIGH; //pulling SS high
	//setting IRQ as input, and enabling pullup
	NRF_IRQ_DDR &= ~(1 << NRF_IRQ_BIT);
	// NRF_IRQ_PORT |= (1 << NRF_IRQ_BIT);
	NRF_WriteRegister(REG_CONFIG, 0b01010000);
	NRF_WriteRegister(REG_EN_AA, 0b00000000);
	NRF_WriteRegister(REG_EN_RXADDR, 0b0);
	NRF_WriteRegister(REG_SETUP_AW, 0b01);
	NRF_WriteRegister(REG_SETUP_RETR,0b0);
	NRF_WriteRegister(REG_RF_CH, 15);
	NRF_WriteRegister(REG_RF_SETUP, 0b00100110); //250Kbps @ 0dBm
}

void NRF_Execute()
{
	NRF_CE_HIGH;
	NRF_DELAY_US(20);
	NRF_CE_LOW;
}

void NRF_FlushTxBuffer()
{
	//1110 0001
	NRF_CSN_LOW;
	SPI_Transmit((uint8_t[]){0b11100001}, 1);
	NRF_CSN_HIGH;
}