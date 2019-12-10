

/**
 * Control the LCD16x2
 * aut: trung
 * note: need inject lcd pointer from main in every method
 */
#include <LiquidCrystal.h>

// setup
void lcdSetup(LiquidCrystal *lcd);
// print message at row and column
void lcdPrintMessageAt(LiquidCrystal *lcd, String message, short row, short col);

// demo
void lcdDemoPrint(LiquidCrystal *lcd);