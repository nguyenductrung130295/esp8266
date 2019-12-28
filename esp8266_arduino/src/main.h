//declare libray
#include <common/commons.h>
// #include <lcd-control/esp-lcd-16x2.h>
#include <firebase-service/firebase-service.h>
#include <wifi-control/wifi-control.h>
#include <Servo.h>
#include <time.h>

#include <firebase-service/url-service.h>

//main config and const
#define WIFI_SSID "Tien"
#define WIFI_PASSWORD "99999999"

#define TIME_ZONE 7

#define FIRE_B_HOST_URL "front-angular-76558.firebaseio.com"
#define FIRE_B_AUTH_KEY "Q1qoNQHNoc6kJMWGicb26WzaIoOk3rFs0Gdmmv9z"

#define PIN_IN_BTN_EAT_1 D0
#define PIN_IN_BTN_EAT_2 D2
#define PIN_IN_BTN_EAT_3 10 // SD3

#define PIN_IN_BTN_DRINK_1 D1
#define PIN_IN_BTN_DRINK_2 D7
#define PIN_IN_BTN_DRINK_3 9 // SD2

#define PIN_OUT_LIGHT_01 D4
#define PIN_OUT_LIGHT_02 D8 // RX
#define PIN_OUT_LIGHT_03 3 // TX

#define PIN_SERVO_1 D3
#define PIN_SERVO_2 D5
#define PIN_SERVO_3 D6

#define PIZZA_NUMBER 150
#define GUN_NUMBER 0
#define TIME_OPEN_DOOR 5000

uint8_t CURRENT_HOUR = 0;
uint8_t times_feeding_in_time = 0;
uint8_t times_feeding_not_in_time = 0;
// LiquidCrystal lcd(12,0,5,4,3,2);    //declare pin number of arduino for rs, en, d4, d5, d6, d7 LCD16x2 pin
FirebaseData firebaseData;          //Declare the Firebase Data object in global scope
// declare servo
Servo servo_1;
Servo servo_2;
Servo servo_3;
// Servo servo_4;
/* default the door to feed chicken is false to close the door*/
bool servo_1_sta = false;
bool servo_2_sta = false;
bool servo_3_sta = false;
// bool servo_4_sta = false;
// int buttonD0State = 0;              // variable for reading the pushbutton status

/* default status = true, the box of food for chicken is not empty*/
bool btn_eat_1_sta = 1;// 0 = false, 1 = true
bool btn_eat_2_sta = 1;
bool btn_eat_3_sta = 1;
// bool btn_eat_4_sta = 0;
bool btn_dri_1_sta = 1;
bool btn_dri_2_sta = 1;
bool btn_dri_3_sta = 1;
// bool btn_dri_4_sta = 0;
// declare global main variable
// uint8_t analogMode = OUTPUT;
// uint8_t pwmPinFadeLed = D5;

// declare function name for main
void setupPinMode();
void getTimeNow();
void configTimerNTP();

void turnOnOffTheLights();
void turnOnOffLight(uint8_t groupNumber);
void feedingControl();
void feedingEat(uint8_t groupNumber);
void turnOnOffDoor(bool status, uint8_t groupNumber);
void readAndUpdate(uint8_t pinNumberEat, uint8_t pinNumberDrink, bool &previousStatusEat, bool &previousStatusDrink, String pathEat, String pathDrink, bool isEat);
void eatOfEachGroup(uint8_t groupNumber, bool isEat);
void readAndUpdateEatDrink();
// void readAndWriteDataWithFirebase();
// void turnOnYellowLight();
// void readAnalogPin();
// void fadeLedByPWMPin(uint8_t pwmPin);
// void onClickBtnOpenRedLight();
// void lucky();

/**
 * DEV ERROR: 
 * serial not print, maybe reason is fail boot, please check if using TX, D3, D4 is LOW, D8 is HIGH
 * 
 * can not upload code, maybe another process is running quickly, fix: unplugin the usb cab, and plugin try again.
 * 
 * 
 * 
 * */