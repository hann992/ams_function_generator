#include <avr/io.h>
#include <stdint.h>

void spi_init();

void spi_selectSlave();

void spi_deselectSlave();

uint8_t spi_transfer(uint8_t data);
