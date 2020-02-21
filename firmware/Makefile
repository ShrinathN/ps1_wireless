CC = avr-gcc
MMCU = atmega8
CFLAGS = -I. -I/usr/avr/include/ -Os -mmcu=$(MMCU)a

SRC = main.c \
psx_controller.c \
battery.c \
spi.c \
NRF24L01.c

all: main.hex

main.hex: main
	avr-objcopy -j .text -j .data -O ihex main main.hex

main: $(SRC)

clean:
	rm main main.hex *.o