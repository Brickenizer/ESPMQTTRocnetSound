#ifndef _PIN_DEFINES_H
#define _PIN_DEFINES_H

/*
 * 
 * 
 */
/*/ uses RX/d9, D8, and D4 pins.

  static const uint8_t D4   =  2;  and Blue Led on SP8266
  static const uint8_t D5   = 14; for chuff output
  static const uint8_t D8   = 15;
*/

/* PIN References... Also defined somewhere else in the esp included code so do not unhide this section!!!...
  static const uint8_t D0   = 16;  and Red Led on NodeMcu V2 (not present on NodeMCU v3)
  
  static const uint8_t D1   =  5;
  static const uint8_t D2   =  4;
  static const uint8_t D3   =  0;
  static const uint8_t D4   =  2;  and Blue Led on ESP8266 also is i2c clk?

  static const uint8_t D5   = 14;
  static const uint8_t D6   = 12;
  static const uint8_t D7   = 13;
  static const uint8_t D8   = 15;
  static const uint8_t D9   =  3;
  static const uint8_t D10  =  1;



PWMA-GPIO5.
PWMB-GPIO4.
DA-GPIO0.
DB-GPIO2.

  #define NodeMCUPinD[SignalLed] 2 // same as PIN D4!

*/




#define SignalLed 0 // NodeMCU D0! expects LED +resistor to +ve! DO not change this..
#define _LocoDrivePort 1  // if using as mobile (LOCO) node.. node becomes a loco with servo on port D "1"  for motor control
#define _LocoPWMDirPort  3         // add this second Port if using PWM loco motor control assumes L293 inputs driven from port D(_LocoDrivePort) and D(_LocoPWMDirPort)
                                     //
// assume if a loco then you need front and back lights...
#ifdef _LocoDrivePort
  #define BACKLight 2  // NodeMCU D2
  #define FRONTLight 5 // NodeMCU D5
//  #define SteamOutputPin 6
#endif

#ifdef _Audio              //RX/D9, D8, and D4 pins.defined below    
    #define I2SDAC_LRC 4  // D4 is used in no dac because of default i2s settings (is i2s clock?) but can be used as input if you need the pin in no dac..
                           // but needs to be defined in order for NoDac to work
    #define I2SDAC_DIN 9   // D9/rx used for both Audio types
#ifdef _AudioDAC
     #define I2SDAC_CLK 8 // D8 used by DAC only
#endif 
#endif

#define SERVO1 D1
#define SERVO2 D2
#define SERVO3 D3
#define SERVO4 D4
#define SERVO5 D5
#define SERVO6 D6
#define SERVO7 D7
#define SERVO8 D8

/** Typical (MISO MOSI SCLK and CS are hard coded in MFRC522....) pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      ESP866            NodeMCU     NUMBER
               Reader/PCD
   Signal      Pin          Pin
   -----------------------------------------------------------------------------------------
   cs                                                      15
   SPI MOSI    MOSI         GPIO13             D7          13
   SPI MISO    MISO         GPIO12             D6          12
   SPI SCK     SCK          GPIO14             D5          14
                            GPIO9              SD2
                            GPIO10             SD3
   RST/Reset   RST          GPIO4              D2          4
   SPI SS      SDA(SS)      GPIO5              D1          5
   **/
#define RST_PIN         D0           // Configurable, see typical pin layout above
#define SS_PIN          D1           // Configurable, see typical pin layout above


/* MCU Pins */
  #define MCU_D0 D0
  #define MCU_D1 D1
  #define MCU_D2 D2
  #define MCU_D3 D3
  #define MCU_D4 D4
  #define MCU_D5 D5
  #define MCU_D6 D6
  #define MCU_D7 D7
  #define MCU_D8 D8

//    static const uint8_t D9   = 3;
//  static const uint8_t D10  = 1;

#endif
// End of pin defines.
