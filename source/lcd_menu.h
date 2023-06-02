#include <stdbool.h>
#include <avr/io.h>
#include <stdio.h>
#include "liquid_crystal_i2c.h"

#ifndef LCD_MENU_H_
#define LCD_MENU_H_

#define MAX_ITEMS 10

typedef struct {
    bool Encoder;
    char Name[100];
    int Goto;
    int currentValue;
    int From;
    int To;
    char AltName[100];
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int itemNum;
    char Name[100];
} Menu;


extern Menu menus[];

extern volatile int currentMenu;
extern volatile int currentItem;

void displayMenu(struct LiquidCrystalDevice_t* device);

int getCurrentMenu();

int getCurrentItem();
int getNumberOfItems();
void setCurrentMenu(int menu);
int executeItemLink(int curMenu, int curItem);
void setCurrentItem(int item);

#endif /* LCD_MENU_H_ */