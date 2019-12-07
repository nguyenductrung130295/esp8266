//declare libray
#include <Arduino.h>
#include <lcd-control/esp-lcd-16x2.h>

//define global variable
LiquidCrystal lcd(12,0,5,4,3,2);//declare pin number of arduino for rs, en, d4, d5, d6, d7 LCD16x2 pin


// declare function name for main
void lucky();
