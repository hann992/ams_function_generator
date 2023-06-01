#include <stdbool.h>
#include <avr/io.h>
#include <stdio.h>
#include "lcd_menu.h"

//    const char* name;
//    struct MenuItem* parent;
//    struct MenuItem** children;
//    uint8_t numChildren;
//    MenuActionFn action;

// Menus

// Main Menu
MenuItem mainMenu = { "Main Menu", NULL, NULL, 3, NULL };

// Main menu items:
MenuItem dcMotorMenu = { "DC Motor", &mainMenu, NULL, 2, NULL };
MenuItem stepperMotorMenu = { "Stepper Motor", &mainMenu, NULL, 2, NULL };
MenuItem servoMenu = { "Servo", &mainMenu, NULL, 2, NULL };

MenuItem backMenuItem = { "Back", NULL, NULL, 0, NULL };

// Menu elementer:
MenuItem* mainMenuChildren[] = { &dcMotorMenu, &stepperMotorMenu, &servoMenu };

MenuItem* dcMotorMenuChildren[] = { &backMenuItem };
MenuItem* stepperMotorMenuChildren[] = { &backMenuItem };
MenuItem* servoMenuChildren[] = { &backMenuItem };

void handleEncoderTurn(bool clockwise) {
    // Handle encoder turning logic
    // Update menu selection
}

void handleEncoderPress() {
    // Handle encoder press logic
    // Execute menu action or navigate to child menu
}

void displayMenu() {
    // Display menu on the LCD screen
}

void executeMenuAction() {
    // Execute the selected menu item's action
}
