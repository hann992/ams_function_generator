#include <avr/io.h> 
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/cpufunc.h>
#include "TFT_touch_driver.h"
#include "uart.h"
#include <stdint.h>


#define TOUCH_IRQ PE4

#define XPT2046_CS_PIN   PE3
#define XPT2046_CLK_PIN  PH3
#define XPT2046_DIN_PIN  PG5
#define XPT2046_DOUT_PIN PE5


void XPT2046_init() {
  
    // Enable ISR INT4
    EIMSK |= 1<<INT4;

    // Sæt til input
    DDRD &= TOUCH_IRQ;

    // Set pins as outputs
    DDRE |= (1 << XPT2046_CS_PIN);
    DDRH |= (1 << XPT2046_CLK_PIN);
    DDRG |= (1 << XPT2046_DIN_PIN);

    // Set pin as input
    DDRE &= ~(1 << XPT2046_DOUT_PIN);

    // Pull CS pin high
    PORTE |= (1 << XPT2046_CS_PIN);
}

void XPT2046_uninit(){

  // Sluk for interrupt
  EIMSK &= ~(1<<INT4);

  // PULL CS pin low
  PORTE &= ~(1<< XPT2046_CS_PIN);


}

uint16_t XPT2046_read(uint8_t command) {
  uint8_t i;
  uint16_t result = 0;
  
  // Set CS pin low to start communication
  PORTE &= ~(1 << XPT2046_CS_PIN);

  // Send command
  for (i = 0; i < 8; i++) {
    if (command & 0x80) {
      PORTG |= (1 << XPT2046_DIN_PIN);
    } else {
      PORTG &= ~(1 << XPT2046_DIN_PIN);
    }
    PORTH |= (1 << XPT2046_CLK_PIN);
    _delay_us(1);
    PORTH &= ~(1 << XPT2046_CLK_PIN);
    command <<= 1;
  }

  // Read result
  for (i = 0; i < 16; i++) {
    result <<= 1;
    PORTH |= (1 << XPT2046_CLK_PIN);
    _delay_us(1);
    if (PINE & (1 << XPT2046_DOUT_PIN)) {
      result |= 0x01;
    }
    PORTH &= ~(1 << XPT2046_CLK_PIN);
  }
  
  // Set CS pin high to end communication
  PORTE |= (1 << XPT2046_CS_PIN);

  return result;
}