#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"

// Gray code to direction lookup table
const int8_t grayToDir[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};

// Global variables
volatile int8_t encoderPos = 0;
volatile uint8_t prevEncState = 0;

int getDirection(){
    return encoderPos;
}

void setupInterrupts() {
  // Set PE4 (Digital Pin 2) and PE5 (Digital Pin 3) as inputs with pull-up resistors
  DDRE &= ~(1 << DDE4) & ~(1 << DDE5);
  PORTE |= (1 << PORTE4) | (1 << PORTE5);

  // Configure external interrupt for PE4 (INT4)
  EICRB |= (1 << ISC40) | (1 << ISC41);  // Trigger on any logical change
  EIMSK |= (1 << INT4);                   // Enable INT4 interrupt

  // Configure external interrupt for PE5 (INT5)
  EICRB |= (1 << ISC50) | (1 << ISC51);  // Trigger on any logical change
  EIMSK |= (1 << INT5);                   // Enable INT5 interrupt
}

// Interrupt Service Routine for INT4 (PE4)
ISR(INT4_vect) {
  uint8_t encState = (PINE & ((1 << PINE5) | (1 << PINE4))) >> PINE4;
  int8_t dir = grayToDir[(prevEncState << 2) | encState];
  encoderPos += dir;
  prevEncState = encState;
}

// Interrupt Service Routine for INT5 (PE5)
ISR(INT5_vect) {
  uint8_t encState = (PINE & ((1 << PINE5) | (1 << PINE4))) >> PINE4;
  int8_t dir = grayToDir[(prevEncState << 2) | encState];
  encoderPos += dir;
  prevEncState = encState;
}