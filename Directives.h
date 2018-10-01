#define _SERVO_DEBUG (enables debug messages in set motor speed rc and pwm

#define SignalON LOW  // defined so I can change the "phase of the SignalLED" easily.
#define SignalOFF HIGH



//#define _DefaultPrintOut 1 // for printing the defaults on eprom save so you can save them in the RocSubs:SetDefaultSVs() function 
// #define _Use_Wifi_Manager // uncomment this to use a "standard" fixed SSID and Password

//---------------AUDIO--------------------

#define _AudioDAC  // to use Earle F Philhowers's audio libraries and I2C dac for audio 
//#define _AudioNoDAC  //  to use Earle F Philhowers's audio libraries and his clever single transistor 1 bit oversampling dac for audio 

//--- These are set depending on the two defines above..
// I could probably be cleverer with this set!! but they work
#if defined _AudioNoDAC || defined _AudioDAC
#define _Audio // sets some common audio compiler stuff
#endif

// -- end of audio defines

//----SET THESE WHEN INITIALLY SETTING UP THE CODE -------------- to set the eeprom to reasonably sensible defaults.
// from ver 15 equivalents to these should set if the eeprom is empty.. So they may not be needed, but if you have to reset anything, they may be useful.
// Then comment them out and re-program so that the loc addr etc can be set via rocrail
//#define _ForceRocnetNodeID_to_subIPL // stops the ability of rocnet to change the node number, but prevents the possibility of two nodes having same node number
//#define _ForceDefaultEEPROM //
//#define _Force_Loco_Addr 3 

//---------------------------------------------------------------end of compiler #defines--------------
// old define

// #define _RFID 1  // if using rfid reader THIS IS AN OLD part of the code and not tested recently. 
//                    It adds a RFID reader and sends sensor messages depending on the RFID tag "read.
//                    it's interaction with the new code is UNTESTED.

#include "pin_defines.h"
