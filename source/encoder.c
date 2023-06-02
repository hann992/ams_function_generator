#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "encoder.h"

// Gray code to direction lookup table
const int8_t grayToDir[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};

// Global variables
extern volatile int16_t encoderPos = 0;
extern volatile uint8_t prevEncState = 0;
extern volatile int8_t buttonPressed = 0;
extern volatile int8_t oldEncoderPos = 0;
extern volatile int8_t encoderTurned = 0;
extern volatile int8_t encoderState = 0;

int getEncoderState(){
    return encoderState;
}

void setEncoderState(int state){
    encoderState = state;
}

int getEncoderPos(){
    return encoderPos;
}

void setEncoderPos(int pos){
    encoderPos = pos;
}
int getButtonPressed(){
    return buttonPressed;
}

int getEncoderTurned(){
    return encoderTurned;
}

void resetButton(){
    buttonPressed = 0;
}

void resetEncoder(){
    encoderTurned = 0;
}

void setupInterrupts() {
    // Set PE4 (Digital Pin 2) and PE5 (Digital Pin 3) as inputs with pull-up resistors
    DDRE &= ~(1 << DDE4) & ~(1 << DDE5);
    PORTE |= (1 << PORTE4) | (1 << PORTE5);

    // Configure external interrupt for PE4 (INT4)
    EICRB |= (1 << ISC40) | (1 << ISC41);  // Trigger on any logical change
    EIMSK |= (1 << INT4);                  // Enable INT4 interrupt

    // Configure external interrupt for PE5 (INT5)
    EICRB |= (1 << ISC50) | (1 << ISC51);  // Trigger on any logical change
    EIMSK |= (1 << INT5);                  // Enable INT5 interrupt

    // BUTTON INIT
    // Set PJ0 (PCINT9) as input
    DDRJ &= ~(1 << PJ0);

    // Enable PCINT9 interrupt
    PCICR |= (1 << PCIE1);

    // Enable interrupt on PCINT9 (PJ0)
    PCMSK1 |= (1 << PCINT9);

}

int resolveEncoderValue(int from, int to, int current){


    
    int tmp = encoderPos;

    if(tmp < from){
        tmp = from;
        encoderPos = from;
    }
    if(tmp > to){
        tmp = to;
        encoderPos = to;
    }

    return tmp;

}

int resolveMenuSelection(int numOfMenuItems){

    int tmp = encoderPos;

    if(tmp < 0){
        tmp = 0;
        encoderPos = 0;
    }
    if(tmp > (numOfMenuItems-1)*4){
        tmp = (numOfMenuItems-1)*4;
        encoderPos = (numOfMenuItems-1)*4;
    }

    return (int)(tmp/4);
}

void resolveEncoderPos(){
    SendString("Encoder Pos: ");
    SendInteger(encoderPos);
    SendString("\n\r");
}

// Interrupt Service Routine for INT4 (PE4)
ISR(INT4_vect) {
  uint8_t encState = (PINE & ((1 << PINE5) | (1 << PINE4))) >> PINE4;
  int8_t dir = grayToDir[(prevEncState << 2) | encState];
  if(encoderState == 1){
    dir = dir*10;
  }
  encoderPos += dir;
  prevEncState = encState;
  encoderTurned = 1;
  //resolveEncoderPos();
}

// Interrupt Service Routine for INT5 (PE5)
ISR(INT5_vect) {
  uint8_t encState = (PINE & ((1 << PINE5) | (1 << PINE4))) >> PINE4;
  int8_t dir = grayToDir[(prevEncState << 2) | encState];
  if(encoderState == 1){
    dir = dir*10;
  }
  encoderPos += dir;
  prevEncState = encState;
  encoderTurned = 1;
  //resolveEncoderPos();
}


// Interrupt service routine for PCINT9 (PJ0)
ISR(PCINT1_vect) {
  // Your code here
  buttonPressed = 1;
  // Debounce
  _delay_ms(100);
}