#include <main.h>

void setup()
{
  lcdSetup(&lcd);
}

void loop()
{
    lucky();
}

// place to implement function for main
void lucky(){
  demoPrint(&lcd);
  delay(1000);
  lcd.clear();
  delay(1000);
}