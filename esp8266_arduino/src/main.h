/**
 * ================ PIN STATUS =============
 * A0 : ADC0:TOUT //analog input
 * RSV ://REVERVED
 * RSV ://REVERVED
 * SD3 :SDD3            [10]
 * SD2 :SDD2            [09]
 * SD1 :SDD1:MOSI
 * CMD :SDCMD : CS
 * SD0 : SDD0 : MISO
 * CLK : SDCLK : SCLK
 * GND :
 * 3V3 :
 * EN :
 * RST :
 * GND :
 * VIN :
 * 
 * 
 * D0 : USER : WAKE     [16]
 * D1 :                 [05]
 * D2 :                 [04]//pwm
 * D3 : FLASH           [00]
 * D4 :                 [02]
 * 3V3 :
 * GND :
 * D5 :  : HSCLKZ       [14]//pwm
 * D6 : : HMISO         [12]//pwm
 * D7 : RXD2 : HMOSI    [13]
 * D8 :TXD2:HCS         [15]//pwm
 * RX :RXD0             [03]
 * TX :TXD0             [01]
 * GND :
 * 3V3 :
 * 
*/

//declare libray
#include <common/commons.h>
#include <lcd-control/esp-lcd-16x2.h>
#include <wifi-control/wifi-control.h>


//main config and const
#define PIN_INPUT_CLICK_BUTTON D0
#define PIN_OUTPUT_YELLOW_LED D7
LiquidCrystal lcd(12,0,5,4,3,2);//declare pin number of arduino for rs, en, d4, d5, d6, d7 LCD16x2 pin
int buttonD0State = 0;         // variable for reading the pushbutton status
const char* WIFI_SSID = "Tien";
const char* WIFI_PASSWORD = "99999999";

// declare global main variable
uint8_t analogMode = OUTPUT;
uint8_t pwmPinFadeLed = D5;


// declare function name for main
void setupPinMode();


void turnOnYellowLight();
void readAnalogPin();
void fadeLedByPWMPin(uint8_t pwmPin);
void onClickBtnOpenRedLight();
void lucky();
