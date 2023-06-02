#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>

#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SS_BIT   0
#define SCK_BIT  1
#define MOSI_BIT 2
#define MISO_BIT 3

void SPI_init();
void SPI_transmit(unsigned char);
unsigned char SPI_receive();
void SPI_Chip_Select();
void SPI_Chip_Deselect();

#endif /* SPI_DRIVER_H_ */