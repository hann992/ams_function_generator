#include <stdbool.h>
#include <avr/io.h>
#include <stdio.h>

// Function pointer type for menu item action functions
typedef void (*MenuActionFn)();

// Struct to represent a menu item
typedef struct MenuItem {
    const char* name;
    struct MenuItem* parent;
    struct MenuItem** children;
    uint8_t numChildren;
    MenuActionFn action;
} MenuItem;

// Function prototypes
void handleEncoderTurn(bool clockwise);
void handleEncoderPress();
void displayMenu();
void executeMenuAction();