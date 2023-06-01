#include <avr/io.h>
#include <stdint.h>

#define DDR_SPI DDRB
#define DD_SS DDB0
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DD_SCK DDB1

void spi_init() {
    // Set MOSI, SCK, and SS as output pins
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

    // Enable SPI, set as Master mode with a clock rate of fck/16
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void spi_selectSlave() {
    // Set SS (Slave Select) low
    PORTB &= ~(1 << DD_SS);
}

void spi_deselectSlave() {
    // Set SS (Slave Select) high
    PORTB |= (1 << DD_SS);
}

uint8_t spi_transfer(uint8_t data) {
    // Start transmission
    SPDR = data;

    // Wait for transmission complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return SPDR;
}
