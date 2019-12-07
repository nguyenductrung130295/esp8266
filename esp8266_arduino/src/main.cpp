#include <main.h>

void setup()
{
  setupSerial();
  lcdSetup(&lcd);//init lcd 16x2


}

void loop()
{
    lucky();


}

// ========= IMPLEMENTATION FOR MAIN ==============



void setupSerial(){
  Serial.begin(SERIAL_INIT);//init serial logger
  Serial.println("RUN : setup");
}
// demo lcd_16x2
void lucky(){
  Serial.println("LCD: demoPrint");
  demoPrint(&lcd);
  delay(1000);
  lcd.clear();
  delay(1000);
}