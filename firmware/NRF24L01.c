#include "NRF24L01.h"


uint8_t NRF_ReadRegister(uint8_t regstr)
{
	uint8_t buffer;
	//000A AAAA
	CSN_LOW;
	SPI_Transmit((uint8_t[]){0b0 | regstr}, 1);
	SPI_Receive(&buffer, 1);
	CSN_HIGH;
	return buffer;

}

void NRF_WriteRegister(uint8_t regstr, uint8_t data)
{
	// 001A AAAA
	CSN_LOW;
	SPI_Transmit((uint8_t[]){0b00100000 | regstr, data}, 2);
	CSN_HIGH;
}


void NRF_WriteTxFIFO(uint8_t * data, uint8_t length)
{
	//1010 0000
	CSN_LOW;
	SPI_Transmit((uint8_t[]){0b10100000}, 1);
	SPI_Transmit(data, length);
	CSN_HIGH;
}

void NRF_ReadRxFIFO(uint8_t * ptr, uint8_t length)
{
	//0110 0001
	CSN_LOW;
	SPI_Transmit((uint8_t[]){0b01100001}, 1);
	SPI_Receive(ptr, length);
	CSN_HIGH;
}

void NRF_SetAddressTx(uint8_t * ptr, uint8_t length)
{
	CSN_LOW;
	SPI_Transmit((uint8_t[]){0b00100000 | 0x10}, 1);
	SPI_Transmit(ptr, length);
	CSN_HIGH;
}

void NRF_SetMode(uint8_t mode)
{
	uint8_t config_reg = NRF_ReadRegister(REG_CONFIG);
	if(mode == CONFIG_PWR_UP_UP)
		config_reg |= CONFIG_PWR_UP_UP;
	else
		config_reg &= ~(CONFIG_PWR_UP_UP);
	NRF_WriteRegister(REG_CONFIG, config_reg);
}

void NRF_Init()
{
	NRF_WriteRegister(REG_CONFIG, 0b01010000);
	NRF_WriteRegister(REG_EN_AA, 0b00000000);
	NRF_WriteRegister(REG_EN_RXADDR, 0b0);
	NRF_WriteRegister(REG_SETUP_AW, 0b01);
	NRF_WriteRegister(REG_SETUP_RETR,0b0);
	NRF_WriteRegister(REG_RF_CH, 15);
	NRF_WriteRegister(REG_RF_SETUP, 0b00100110); //250Kbps @ 0dBm
}