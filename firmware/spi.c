#include "spi.h"

/* Setting up the SPI bus
*/
void SPI_Init(void)
{
	//setting up pin directions for SCK, MOSI and SS as output, MISO is input
	SPI_DIRECTION_REGISTER |= (1 << SPI_SCK_PIN) |
							(1 << SPI_MOSI_PIN) |
							(1 << SPI_SS_PIN);

	//implicitly setting clock speed at FCPU / 4
	SPCR = (1 << SPE) | //enabling SPI
			(1 << MSTR) | //setting SPI mode as master
			(0 << CPOL) | //setting CPOL as 0, SCK leading and trailing edges as rising and falling
			(0 << CPHA);  //setting sample at leading edge and setup at trailing edge

	SPI_SS_HIGH; //pulling SS high for the first time
}

void SPI_Transmit(uint8_t * data, uint8_t length)
{
	uint8_t counter = UINT8_MAX;
	for(counter = 0; counter < length; counter++)
	{
		SPDR = data[counter];
		SPI_WAIT;
	}
}

void SPI_Receive(uint8_t * buffer, uint8_t length)
{
	uint8_t counter = UINT8_MAX;
	for(counter = 0; counter < length; counter++)
	{
		SPDR = 0x0;
		SPI_WAIT;
		buffer[counter] = SPDR;
	}
}

void SPI_TransReceive(uint8_t * data, uint8_t * buffer, uint8_t length)
{
	uint8_t counter = UINT8_MAX;
	for(counter = 0; counter < length; counter++)
	{
		SPDR = data[counter];
		SPI_WAIT;
		buffer[counter] = SPDR;
	}
}