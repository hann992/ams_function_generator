#include <stdbool.h>
#include <avr/io.h>
#include <stdio.h>
#include "lcd_menu.h"
#include "liquid_crystal_i2c.h"
#include "lcd_menu.h"
#include "encoder.h"
#include <util/delay.h>


extern Menu menus[3] = {
    {
        .items = {
            {true, "PWM", 1, 250, 250, 5000, " Hz"},
            {true, "Duty", 2, 0, 0, 100, " %"},
            {true, "State", 3, 0, 0, 10, ""},
            {false, "Back", 0, 0, 0, 0, ""}
        },
        .itemNum = 4,
        .Name = "DC Motor"
    },
    {
        .items = {
            {true, "Degree", 4, 0, 0, 180, "°"},
            {true, "State", 5, 0, 0, 10, ""},
            {false, "Back", 0, 0, 0, 0, ""}
        },
        .itemNum = 3,
        .Name = "Servo Motor"
    },
    {
        .items = {
            {true, "Mode", 6, 0, 0, 2, ""},
            {true, "Steps", 7, 1, 1, 1000, ""},
            {true, "State", 8, 0, 0, 10, ""},
            {false, "Back", 0, 0, 0, 0, ""}
        },
        .itemNum = 4,
        .Name = "Stepper Motor"
    }
};

extern volatile int currentMenu = 0;
extern volatile int currentItem = 0;

int executeItemLink(int curMenu, int curItem){

    // If Back was pressed in a submenu
    if(menus[curMenu].items[curItem].Goto == 0){
        // Return to main menu
        return 99;
    }

    // If an editable item was pressed
    if( curMenu != 99 && menus[curMenu].items[curItem].Encoder == true ){
        // Activate CHANGE STATE ENCODER
        setEncoderState(1);
        
        setEncoderPos(menus[curMenu].items[curItem].currentValue);
        SendString("Current Item: ");
        SendString(menus[curMenu].items[curItem].Name);
        SendString("\n\r");
        // Stay on menu!
        
        return curMenu;
    }

    // Vi er i hovedmenuen, og vi kan bruge valgte Item + 1 til at finde undermenuen
    if ( curMenu == 99){
        return curItem;
    }
    SendString("Error w menu, no menu was found!\n\r");

    return 99;
}


int getCurrentMenu(){
    return currentMenu;
}
int getCurrentItem(){
    return currentItem;
}
void setCurrentMenu(int menu){
    currentMenu = menu;
}
void setCurrentItem(int item){
    currentItem = item;
}

int getNumberOfItems(){
    return menus[currentMenu].itemNum;
}

void displayMenu(struct LiquidCrystalDevice_t* device){
    // Display menu on the LCD screen
    lq_clear(device);

    lq_setCursor(device, currentItem, 0);
    lq_print(device, "->");

    // Is it the base menu or not?
    if(currentMenu == 99){
        // It is the base menu
        for(int i = 0; i < 3; i++){
            lq_setCursor(device, i, 3);
            lq_print(device, menus[i].Name);  
        }
    }else{
        // it is a sub-menu
        for(int i = 0; i < menus[currentMenu].itemNum; i++){
            char finalstr[50];

            if(getEncoderState() == 1 && currentItem == i ){
                // BEING EDITED

                // IF STATE?
                //if (menus[currentMenu].items[i].Goto == )
                sprintf(finalstr, "%s: [%d] %s", menus[currentMenu].items[i].Name, menus[currentMenu].items[i].currentValue, menus[currentMenu].items[i].AltName);
            }else{
                if(menus[currentMenu].items[i].Goto == 0){
                    // BACK button
                    sprintf(finalstr, "%s", menus[currentMenu].items[i].Name);
                }else{
                    // NOT back button
                    sprintf(finalstr, "%s: %d %s", menus[currentMenu].items[i].Name, menus[currentMenu].items[i].currentValue, menus[currentMenu].items[i].AltName);
                }
                
            }
            

            lq_setCursor(device, i, 3);
            lq_print(device, finalstr);  
        }
    }


}

