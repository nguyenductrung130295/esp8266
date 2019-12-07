#include <lcd-control/esp-lcd-16x2.h>

void lcdSetup(LiquidCrystal *lcd) {
    lcd->begin(16,2);
    lcd->print("Hello ESP8266");
    lcd->write(" !");
}

void demoPrint(LiquidCrystal *lcd) {
    lcd->setCursor(0,1);
    lcd->print("good luck");
}