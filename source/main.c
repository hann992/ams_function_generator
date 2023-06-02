#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "pwm.h"
#include "liquid_crystal_i2c.h"
#include "i2c_master.h"
#include "lcd_menu.h"
#include "encoder.h"
#include "SD_Driver.h"

// Arbitrary block number for test
#define Block_1 718
#define Block_2 1234567

unsigned char buffer[12];

int main(void)
{
    InitUART();

    i2c_master_init(I2C_SCL_FREQUENCY_100);
    
    LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_5x8DOTS); // intialize 4-lines display
    lq_turnOnBacklight(&device); // simply turning on the backlight


/* 	SD_init();

    SD_readSingleBlock(Block_1, buffer);

    for(int i = 0; i < 12; i++){
        SendInteger(buffer[i]);
        SendString("\n\r");
    } */


    // Setup encoder interrupts
    setupInterrupts();
    
    // Enable global interrupts
    sei();


    bool input = false;

    // Sæt valgte menu, og menu punkt
    setCurrentMenu(99);
    setCurrentItem(0);

    // Vis start menuen
    displayMenu(&device);

    int tmp = 0;

    while (1) {

        // Afvent UI ændringer loop
        while(input == false){
            // Vi sidder fast her, ind til der er UI feedback
            if(getButtonPressed() == 1 || getEncoderTurned() == 1){
                // Something changed in the interface, time to draw!
                input = true;

                if(getButtonPressed() == 1){

                    if(getEncoderState() == 1){
                        // En værdi skal gemmes!
                        if(menus[currentMenu].items[currentItem].Goto == 1) SendString("PWM Hz!\n\c");
                        if(menus[currentMenu].items[currentItem].Goto == 2) SendString("PWM Duty!\n\c");
                        if(menus[currentMenu].items[currentItem].Goto == 3) SendString("PWM ON OFF!\n\c");

                        setEncoderState(0);
                    }else{
                        tmp = executeItemLink(getCurrentMenu(), getCurrentItem());
                        setCurrentMenu(tmp);
                        
                        // Hvis vi går tilbage til hovedmenuen:
                        if(getCurrentMenu() == 99){
                            setCurrentItem(0);
                        }
                        
                    }
                }

                if(getEncoderTurned() == 1){
                    // Value turning
                    if(getEncoderState() == 1){
                        
                        menus[currentMenu].items[currentItem].currentValue = resolveEncoderValue(
                            menus[currentMenu].items[currentItem].From, 
                            menus[currentMenu].items[currentItem].To, 
                            menus[currentMenu].items[currentItem].currentValue
                            );

                    }


                    // Menu turning
                    if(getEncoderState() == 0){
                        //SendString("Encoder turned!\n\r");
                        if(getCurrentMenu() == 99){
                            setCurrentItem(resolveMenuSelection(3));
                        }else{
                            setCurrentItem(resolveMenuSelection(getNumberOfItems()));
                        }
                    }
                    

                }
            }
        }
        // Reset af UI
        _delay_ms(150);
        input = false;
        resetButton();
        resetEncoder();

        // Tegn ny menu
        displayMenu(&device);
        
        

    }

    return 0;
}

