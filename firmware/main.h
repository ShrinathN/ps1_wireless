#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint-gcc.h>

#include "psx_controller.h"
#include "battery.h"
#include "spi.h"
#include "NRF24L01.h"


//temp
void uart_send(uint8_t data);