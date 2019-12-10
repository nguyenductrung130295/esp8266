#include <lcd-control/esp-lcd-16x2.h>

void lcdSetup(LiquidCrystal *lcd) {
    lcd->begin(16,2);
    lcd->print("Hello ESP8266");
    lcd->write(" !");
}

void lcdPrintMessageAt(LiquidCrystal *lcd, String message, short row, short col){
    if(row != 0 || row != 1 || col >= 16 || col < 0){
        // set default to row 1 column 0 (begin line 2 of LCD 16x2)
        row = 1;
        col = 0; 
    }
    lcd->setCursor(col, row);
    lcd->print(message);
}

void lcdDemoPrint(LiquidCrystal *lcd) {
    lcd->setCursor(0,1);
    lcd->print("good luck");
}