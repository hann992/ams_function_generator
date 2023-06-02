/* CS/SS : PB 0
 * SCK   : PB 1
 * MOSI  : PB 2
 * MISO  : PB 3 */

#include "SPI_Driver.h"

//SPI initialize for SD card
void SPI_init(void)
{
	SPI_DDR |= 1 << SS_BIT;
	SPI_DDR |= 1 << MOSI_BIT;
	SPI_DDR &= ~(1 << MISO_BIT);
	SPI_DDR |= 1 << SCK_BIT;
	//Setup SPI: Enable, Master mode, MSB first, SCK phase low, SCK idle low, f = fosc/64 = 16 MHz/64 = 250 kHz
	SPCR = 0b01010010;
	SPSR = 0;
}

void SPI_transmit(unsigned char data)
{
unsigned char dummy;
	
	// Start transmission
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)))
	{}
    // Clear flag 		
	dummy = SPDR;
}

unsigned char SPI_receive()
{
	unsigned char data;
	// Wait for reception complete

	SPDR = 0xff;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;

	// Return data register
	return data;
}

// CS active (=low)
void SPI_Chip_Select()
{
	SPI_PORT &= ~(1 << SS_BIT);
}

// CS inactive (=high)
void SPI_Chip_Deselect()
{
	SPI_PORT |= (1 << SS_BIT);
}