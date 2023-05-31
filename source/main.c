#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include "TFT_touch_driver.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <stdlib.h>

volatile int x_coord = 120;
volatile int y_coord = 160;
volatile int new_coords = 0;

int main(void)
{
  // Initialize the display
  DisplayInit();
  // All pixels white (background)
  FillRectangle(0,0,320,240,31,63,31);

  // Draw red parts of danish flag
  //FillRectangle(0,140,100,100,31,0,0);
  //FillRectangle(0,0,100,100,31,0,0);
  //FillRectangle(140,0,320-140,100,31,0,0);
  //FillRectangle(140,140,320-140,100,31,0,0); 

  DisplayOn();

  sei();
  

  while(1)
  {
    // Draw screen
    FillRectangle(x_coord,y_coord,20,20,31,0,0);

    // Done drawing, now listen for touch input:
    XPT2046_init();
    while(new_coords == 0){
      // Waiting for input
    }
    // We got an input, now disable touch while we draw again!
    XPT2046_uninit();
    
    // Reset new coordinate variable
    new_coords = 0;
  } 
}


void update_coords(int *x, int *y){
    uint16_t x_raw = XPT2046_read(0xD0);
    uint16_t y_raw = XPT2046_read(0x90);

    x_coord = (x_raw - 1600)/118;
    y_coord = (y_raw - 2700)/85;

    _delay_ms(10);

}

ISR(INT4_vect)
{
  update_coords(&x_coord, &y_coord);
  new_coords = 1;
}