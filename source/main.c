#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pwm.h"
#include "liquid_crystal_i2c.h"
#include "i2c_master.h"


int main(void)
{
    InitUART();

    i2c_master_init(I2C_SCL_FREQUENCY_100);
    
    LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_5x8DOTS); // intialize 4-lines display
    lq_turnOnBacklight(&device); // simply turning on the backlight
    lq_setCursor(&device, 0, 4);
    lq_print(&device, "DC MOTOR");
    lq_setCursor(&device, 1, 4);
    lq_print(&device, "SERVO MOTOR");
    lq_setCursor(&device, 2, 4);
    lq_print(&device, "STEPPER MOTOR");



    // Setup encoder interrupts
    setupInterrupts();
    
    // Enable global interrupts
    sei();

    
    while (1) {


        SendString("Direction: ");
        SendInteger(getDirection());
        SendString("\r\n");     
        SendString("\r\n");    
        _delay_ms(100);
    }

    return 0;
}

