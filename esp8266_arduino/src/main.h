/**
 * ================ PIN STATUS =============
 * A0 : ADC0:TOUT
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
 * D2 :                 [04]
 * D3 : FLASH           [00]
 * D4 :                 [02]
 * 3V3 :
 * GND :
 * D5 :  : HSCLKZ       [14]
 * D6 : : HMISO         [12]
 * D7 : RXD2 : HMOSI    [13]
 * D8 :TXD2:HCS         [15]
 * RX :RXD0             [03]
 * TX :TXD0             [01]
 * GND :
 * 3V3 :
 * 
*/

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
