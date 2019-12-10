#include <common/commons.h>



void setupSerial(){
  Serial.begin(SERIAL_INIT);//init serial logger
  Serial.println("RUN : setup");
}