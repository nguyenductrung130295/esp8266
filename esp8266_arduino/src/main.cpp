#include <main.h>

void setup()
{
  setupSerial();
  setupPinMode();//setup pin mode input output
  connectWifi(WIFI_SSID, WIFI_PASSWORD);
  // lcdSetup(&lcd);//init lcd 16x2
  connectFirebase(FIRE_B_HOST_URL, FIRE_B_AUTH_KEY);
  configTimerNTP();
  // init data
  servo_1.write(GUN_NUMBER);
  servo_2.write(GUN_NUMBER);
  servo_3.write(GUN_NUMBER);
}

void loop()
{
  getTimeNow();
  readAndUpdateEatDrink();
  // if ((CURRENT_HOUR == 6 || CURRENT_HOUR == 11 || CURRENT_HOUR == 17) && times_feeding_in_time < 2) {
  //   handleReqFb(Firebase.setBool(firebaseData, GROUP01_FEEDING, true), &firebaseData);
  //   turnOnOffDoor(true, 1);
  //   handleReqFb(Firebase.setBool(firebaseData, GROUP02_FEEDING, true), &firebaseData);
  //   turnOnOffDoor(true, 2);
  //   handleReqFb(Firebase.setBool(firebaseData, GROUP03_FEEDING, true), &firebaseData);
  //   turnOnOffDoor(true, 3);
  //   times_feeding_in_time ++;
  //   times_feeding_not_in_time = 0;
  // }
  // if (CURRENT_HOUR != 6 && CURRENT_HOUR != 11 && CURRENT_HOUR != 17 && times_feeding_not_in_time < 2) {
    feedingControl();
  //   times_feeding_in_time = 0;
  // }
  turnOnOffTheLights();
  // delay(60*1000);

  // fadeLedByPWMPin(pwmPinFadeLed);
  // turnOnYellowLight();
  // readAnalogPin();
  // lucky();
}


// =========SETUP IMPLEMENTATION FOR MAIN ==============

// setup pin mode input output
void setupPinMode() {
  // setup pin for servo
  servo_1.attach(PIN_SERVO_1);
  servo_2.attach(PIN_SERVO_2);
  servo_3.attach(PIN_SERVO_3);
  // setup pin input for button
  // group 1
  pinMode(PIN_IN_BTN_EAT_1, INPUT);
  pinMode(PIN_IN_BTN_DRINK_1, INPUT);
  // group 2
  pinMode(PIN_IN_BTN_EAT_2, INPUT);
  pinMode(PIN_IN_BTN_DRINK_2, INPUT);
  // group 3
  pinMode(PIN_IN_BTN_EAT_3, INPUT);// SD3
  pinMode(PIN_IN_BTN_DRINK_3, INPUT);// SD2
  //output
  pinMode(PIN_OUT_LIGHT_01, OUTPUT);
  pinMode(PIN_OUT_LIGHT_02, OUTPUT); // RX
  pinMode(PIN_OUT_LIGHT_03, OUTPUT); // TX

  // pinMode(pwmPinFadeLed, OUTPUT);
}

void configTimerNTP() {
  configTime(TIME_ZONE*3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
}
// ========== LOOP IMPLEMENTATION FOR MAIN==========================

void turnOnOffTheLights() {
  turnOnOffLight(1);
  turnOnOffLight(2);
  turnOnOffLight(3);
}

void turnOnOffLight(uint8_t groupNumber) {
  switch (groupNumber) {
    case 1:
      if (handleReqFb(Firebase.getBool(firebaseData, GROUP01_LIGHT), &firebaseData)) {
        digitalWrite(PIN_OUT_LIGHT_01, firebaseData.boolData());
      }
      break;
    case 2:
      if (handleReqFb(Firebase.getBool(firebaseData, GROUP02_LIGHT), &firebaseData)) {
        digitalWrite(PIN_OUT_LIGHT_02, firebaseData.boolData());
      }
      break;
    case 3:
      if (handleReqFb(Firebase.getBool(firebaseData, GROUP03_LIGHT), &firebaseData)) {
        digitalWrite(PIN_OUT_LIGHT_03, firebaseData.boolData());
      }
      break;
    default:
      // Serial.println(path);
      break;
  }
}

void readAndUpdateEatDrink() {
  //eat
  eatOfEachGroup(1, true);
  eatOfEachGroup(2, true);
  eatOfEachGroup(3, true);

  //drink
  eatOfEachGroup(1, false);
  eatOfEachGroup(2, false);
  eatOfEachGroup(3, false);  
}

void eatOfEachGroup(uint8_t groupNumber, bool isEat) {
  switch (groupNumber) {
    case 1:
      readAndUpdate(PIN_IN_BTN_EAT_1, PIN_IN_BTN_DRINK_1, btn_eat_1_sta, btn_dri_1_sta, GROUP01_EAT, GROUP01_DRINK, isEat);
      break;
    case 2:
      readAndUpdate(PIN_IN_BTN_EAT_2, PIN_IN_BTN_DRINK_2, btn_eat_2_sta, btn_dri_2_sta, GROUP02_EAT, GROUP02_DRINK, isEat);
      break;
    case 3:
      readAndUpdate(PIN_IN_BTN_EAT_3, PIN_IN_BTN_DRINK_3, btn_eat_3_sta, btn_dri_3_sta, GROUP03_EAT, GROUP03_DRINK, isEat);
      break;
    default:
    break;
  }
}

void readAndUpdate(uint8_t pinNumberEat, uint8_t pinNumberDrink, bool &previousStatusEat, bool &previousStatusDrink, String pathEat, String pathDrink, bool isEat) {
  String path = pathDrink;
  uint8_t pinNumber = pinNumberDrink;
  bool previousStatus = previousStatusDrink;
  if (isEat) {
    path = pathEat;
    pinNumber = pinNumberEat;
    previousStatus =  previousStatusEat;
  }
  bool currentStatus = digitalRead(pinNumber);
  if (previousStatus != currentStatus) {
    Serial.println("Update box status of group");
    if (handleReqFb(Firebase.setBool(firebaseData, path, !currentStatus), &firebaseData)) {
      if (isEat) {
        previousStatusEat = currentStatus;
      } else {
        previousStatusDrink = currentStatus;
      }
    }
  }
}

void turnOnOffDoor(bool status, uint8_t groupNumber) {
  uint8_t value = status ? PIZZA_NUMBER : GUN_NUMBER;
  String path;
  if (groupNumber == 1 && servo_1_sta != status) {
    servo_1.write(value);
    servo_1_sta = status;
    path = GROUP01_FEEDING;
  } else if (groupNumber == 2 && servo_2_sta != status) {
    servo_2.write(value);
    servo_2_sta = status;
    path = GROUP02_FEEDING;
  } else if (groupNumber == 3 && servo_3_sta != status) {
    servo_3.write(value);
    servo_3_sta = status;
    path = GROUP03_FEEDING;
  }
  if (value == PIZZA_NUMBER) {
    delay(TIME_OPEN_DOOR);
    turnOnOffDoor(!status, groupNumber);
    handleReqFb(Firebase.setBool(firebaseData, path, !status), &firebaseData);
    // if (CURRENT_HOUR != 6 && CURRENT_HOUR != 11 && CURRENT_HOUR != 17 && times_feeding_not_in_time < 2) {
    //   times_feeding_not_in_time ++;
    // }
  }
}

void feedingControl() {
  feedingEat(1);
  feedingEat(2);
  feedingEat(3);
}

void feedingEat(uint8_t groupNumber) {
  String path;
  switch (groupNumber) {
    case 1:
      path = GROUP01_FEEDING;
      break;
    case 2:
      path = GROUP02_FEEDING;
      break;
    case 3:
      path = GROUP03_FEEDING;
      break;
    default:
      Serial.println(path);
      break;
  }
  // read feeding status
  if (handleReqFb(Firebase.getBool(firebaseData, path), &firebaseData)) {
    turnOnOffDoor(firebaseData.boolData(), groupNumber);
  }
}

void getTimeNow() {
  time_t now = time(nullptr);
  CURRENT_HOUR = localtime(&now)->tm_hour;
  Serial.println(ctime(&now));
}


// void readAndWriteDataWithFirebase(){
//   if (handleReqFb(Firebase.getInt(firebaseData, "/led"), &firebaseData)) {
//     Serial.println("red 1");
//     if  (firebaseData.dataType() == "int") {
//       Serial.println(firebaseData.dataType());
//       int val = firebaseData.intData();
//       // if (val != redValue) {
//       //   redValue = val;
//       //   setLedColor();
//       Serial.println(val);
//       // }
//     }
//   }
//   if (handleReqFb(Firebase.setInt(firebaseData, "/led", 444), &firebaseData)) {
//     Serial.println("set red");
//     // if  (firebaseData.dataType() == "int") {
//     //   Serial.println(firebaseData.dataType());
//     //   int val = firebaseData.intData();
//     //   // if (val != redValue) {
//     //   //   redValue = val;
//     //   //   setLedColor();
//     //   Serial.println(val);
//     //   // }
//     // }
//   }

//   if (handleReqFb(Firebase.getInt(firebaseData, "/led"), &firebaseData)) {
//     Serial.println("red 2");
//     if  (firebaseData.dataType() == "int") {
//       Serial.println(firebaseData.dataType());
//       int val = firebaseData.intData();
//       // if (val != redValue) {
//       //   redValue = val;
//       //   setLedColor();
//       Serial.println(val);
//       // }
//     }
//   }
// }

// void turnOnYellowLight(){
//   // read the state of the pushbutton value:
//   buttonD0State = digitalRead(PIN_INPUT_CLICK_BUTTON);

//   // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//   if (buttonD0State == HIGH) {
//     // turn LED on:
//     digitalWrite(PIN_OUTPUT_YELLOW_LED, HIGH);
//   } else {
//     // turn LED off:
//     digitalWrite(PIN_OUTPUT_YELLOW_LED, LOW);
//   }
// }
// void fadeLedByPWMPin(uint8_t pwmPin){
//   int brightness = 0;    // how bright the LED is
//   int fadeAmount = 5;    // how many points to fade the LED by
//   for (; brightness < 225; brightness += fadeAmount){
//     // wait for 30 milliseconds to see the dimming effect
//     analogWrite(pwmPin, brightness);
//     delay(100);
//   }
// }

// void readAnalogPin(){
//   int analogValue = analogRead(A0);
//   Serial.println(analogValue);
//   lcdPrintMessageAt(&lcd, String(analogValue), 1, 0);
// }
// //
// void onClickBtnOpenRedLight(){
//   int buttonState = digitalRead(PIN_INPUT_CLICK_BUTTON);
//   Serial.println(buttonState);
//   lcdPrintMessageAt(&lcd, String(buttonState), 1, 0);
// }
// // demo lcd_16x2
// void lucky(){
//   Serial.println("LCD: demoPrint");
//   lcdDemoPrint(&lcd);
//   delay(1000);
//   lcd.clear();
//   delay(1000);
// }