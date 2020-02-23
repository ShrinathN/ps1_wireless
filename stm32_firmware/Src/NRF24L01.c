#include "NRF24L01.h"
#include "main.h"

#define CSN_HIGH HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET)
#define CSN_LOW HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET)

extern SPI_HandleTypeDef hspi1;


BYTE NRF_ReadRegister(BYTE regstr)
{
	uint8_t buffer;
	//000A AAAA
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b0 | regstr}, 1, 10);
	HAL_SPI_Receive(&hspi1, &buffer, 1, 10);
	CSN_HIGH;
	return buffer;

}

void NRF_WriteRegister(BYTE regstr, BYTE data)
{
	// 001A AAAA
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b00100000 | regstr, data}, 2, 10);
	CSN_HIGH;
}


void NRF_WriteTxFIFO(BYTE *data, BYTE length)
{
	//1010 0000
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b10100000}, 1, 10);
	HAL_SPI_Transmit(&hspi1, data, length, 10);
	CSN_HIGH;
}

void NRF_ReadRxFIFO(BYTE * ptr, BYTE length)
{
	//0110 0001
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b01100001}, 1, 10);
	HAL_SPI_Receive(&hspi1, ptr, length, 10);
	CSN_HIGH;
}

void NRF_SetAddressTx(BYTE * ptr, BYTE length)
{
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b00100000 | 0x10}, 1, 10);
	HAL_SPI_Transmit(&hspi1, ptr, length, 10);
	CSN_HIGH;
}

void NRF_SetAddressRx(BYTE * ptr, BYTE length, BYTE pipe_number)
{
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b00100000 | (0xa + pipe_number)}, 1, 10);
	HAL_SPI_Transmit(&hspi1, ptr, length, 10);
	CSN_HIGH;
}

void NRF_SetMode(BYTE mode)
{
	BYTE config_reg = NRF_ReadRegister(REG_CONFIG);
	if(mode == CONFIG_PWR_UP_UP)
		config_reg |= CONFIG_PWR_UP_UP;
	else
		config_reg &= ~(CONFIG_PWR_UP_UP);
	NRF_WriteRegister(REG_CONFIG, config_reg);
}

BYTE NRF_ReadRxPayloadWidth()
{
	//0110 0000
	BYTE temp_buffer;
	CSN_LOW;
	HAL_SPI_Transmit(&hspi1, (BYTE[]){0b01100000}, 1, 10);
	HAL_SPI_Receive(&hspi1, &temp_buffer, 1, 10);
	CSN_HIGH;
	return temp_buffer;
}

void NRF_Init()
{
	NRF_WriteRegister(REG_CONFIG, 0b00110001);
	NRF_WriteRegister(REG_EN_AA, 0b00000000);
	NRF_WriteRegister(REG_EN_RXADDR, 0b1);
	NRF_WriteRegister(REG_SETUP_AW, 0b01);
	NRF_WriteRegister(REG_SETUP_RETR,0b0);
	NRF_WriteRegister(REG_RF_CH, 15);
	NRF_WriteRegister(REG_RF_SETUP, 0b00100110); //250Kbps @ 0dBm
}