#ifndef SPI_H
#define SPI_H
//header file includes
#include "main.h"

//pin definitions
#define SPI_DIRECTION_REGISTER DDRB
#define SPI_PORT PORTB
#define SPI_SCK_PIN PB5
#define SPI_MISO_PIN PB4
#define SPI_MOSI_PIN PB3
#define SPI_SS_PIN PB2

//macros
#define SPI_WAIT while(!(SPSR & (1 << SPIF))) //for waiting while the SPIF pin is not set in the SPSR register
#define SPI_SS_HIGH SPI_PORT |= (1 << SPI_SS_PIN)
#define SPI_SS_LOW SPI_PORT &= ~(1 << SPI_SS_PIN)

//function declarations
void SPI_Init();
void SPI_Transmit(uint8_t * data, uint8_t length);
void SPI_Receive(uint8_t * buffer, uint8_t length);
void SPI_TransReceive(uint8_t * data, uint8_t * buffer, uint8_t length);

#endif
