//declare libray
#include <commons.h>
#include <lcd-control/esp-lcd-16x2.h>


//main config
#define SERIAL_INIT 9600
LiquidCrystal lcd(12,0,5,4,3,2);//declare pin number of arduino for rs, en, d4, d5, d6, d7 LCD16x2 pin


// declare global main variable



// declare function name for main
void setupSerial();
void lucky();
