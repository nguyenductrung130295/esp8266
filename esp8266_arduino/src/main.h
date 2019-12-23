//declare libray
#include <common/commons.h>
#include <lcd-control/esp-lcd-16x2.h>
#include <firebase-service/firebase-service.h>
#include <wifi-control/wifi-control.h>


//main config and const
#define WIFI_SSID "Tien"
#define WIFI_PASSWORD "99999999"

#define FIRE_B_HOST_URL "front-angular-76558.firebaseio.com"
#define FIRE_B_AUTH_KEY "Q1qoNQHNoc6kJMWGicb26WzaIoOk3rFs0Gdmmv9z"

#define PIN_INPUT_CLICK_BUTTON D0
#define PIN_OUTPUT_YELLOW_LED D7

LiquidCrystal lcd(12,0,5,4,3,2);    //declare pin number of arduino for rs, en, d4, d5, d6, d7 LCD16x2 pin
FirebaseData firebaseData;          //Declare the Firebase Data object in global scope

int buttonD0State = 0;              // variable for reading the pushbutton status


// declare global main variable
uint8_t analogMode = OUTPUT;
uint8_t pwmPinFadeLed = D5;

// declare function name for main
void setupPinMode();

void readAndWriteDataWithFirebase();
void turnOnYellowLight();
void readAnalogPin();
void fadeLedByPWMPin(uint8_t pwmPin);
void onClickBtnOpenRedLight();
void lucky();
