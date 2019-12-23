#include <main.h>

void setup()
{
  setupSerial();
  // connectWifi(WIFI_SSID, WIFI_PASSWORD);
  lcdSetup(&lcd);//init lcd 16x2
  setupPinMode();//setup pin mode input output
  // connectFirebase(FIRE_B_HOST_URL, FIRE_B_AUTH_KEY);
  // readAndWriteDataWithFirebase();
}

void loop()
{
  fadeLedByPWMPin(pwmPinFadeLed);
  turnOnYellowLight();
  readAnalogPin();
  delay(1000);
  // lucky();
}

// =========SETUP IMPLEMENTATION FOR MAIN ==============


// setup pin mode input output
void setupPinMode(){
  //input
  pinMode(PIN_INPUT_CLICK_BUTTON, INPUT);
  //output
  pinMode(PIN_OUTPUT_YELLOW_LED, OUTPUT);
  pinMode(pwmPinFadeLed, OUTPUT);
}


// ========== LOOP IMPLEMENTATION FOR MAIN==========================
void readAndWriteDataWithFirebase(){
  if (handleReqFb(Firebase.getInt(firebaseData, "/led"), &firebaseData)) {
    Serial.println("red 1");
    if  (firebaseData.dataType() == "int") {
      Serial.println(firebaseData.dataType());
      int val = firebaseData.intData();
      // if (val != redValue) {
      //   redValue = val;
      //   setLedColor();
      Serial.println(val);
      // }
    }
  }
  if (handleReqFb(Firebase.setInt(firebaseData, "/led", 444), &firebaseData)) {
    Serial.println("set red");
    // if  (firebaseData.dataType() == "int") {
    //   Serial.println(firebaseData.dataType());
    //   int val = firebaseData.intData();
    //   // if (val != redValue) {
    //   //   redValue = val;
    //   //   setLedColor();
    //   Serial.println(val);
    //   // }
    // }
  }

  if (handleReqFb(Firebase.getInt(firebaseData, "/led"), &firebaseData)) {
    Serial.println("red 2");
    if  (firebaseData.dataType() == "int") {
      Serial.println(firebaseData.dataType());
      int val = firebaseData.intData();
      // if (val != redValue) {
      //   redValue = val;
      //   setLedColor();
      Serial.println(val);
      // }
    }
  }
}

void turnOnYellowLight(){
  // read the state of the pushbutton value:
  buttonD0State = digitalRead(PIN_INPUT_CLICK_BUTTON);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonD0State == HIGH) {
    // turn LED on:
    digitalWrite(PIN_OUTPUT_YELLOW_LED, HIGH);
  } else {
    // turn LED off:
    digitalWrite(PIN_OUTPUT_YELLOW_LED, LOW);
  }
}
void fadeLedByPWMPin(uint8_t pwmPin){
  int brightness = 0;    // how bright the LED is
  int fadeAmount = 5;    // how many points to fade the LED by
  for (; brightness < 225; brightness += fadeAmount){
    // wait for 30 milliseconds to see the dimming effect
    analogWrite(pwmPin, brightness);
    delay(100);
  }
}

void readAnalogPin(){
  int analogValue = analogRead(A0);
  Serial.println(analogValue);
  lcdPrintMessageAt(&lcd, String(analogValue), 1, 0);
}
//
void onClickBtnOpenRedLight(){
  int buttonState = digitalRead(PIN_INPUT_CLICK_BUTTON);
  Serial.println(buttonState);
  lcdPrintMessageAt(&lcd, String(buttonState), 1, 0);
}
// demo lcd_16x2
void lucky(){
  Serial.println("LCD: demoPrint");
  lcdDemoPrint(&lcd);
  delay(1000);
  lcd.clear();
  delay(1000);
}