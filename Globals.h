#ifndef _globals_h
  #define _globals_h


// stuff for ssid reset
boolean  ResetWiFi;
uint16_t SW_REV = 15;   

//// Debug settings
#define _SERIAL_DEBUG  1
#define _SERIAL_SUBS_DEBUG 1

char DebugMsg[127];
//#include "SV.h"

//one cross reference for each port   
uint8_t NodeMCUPinD[12];



uint8_t recMessage[128];
uint8_t sendMessage[128];
uint8_t TOPIC[20];
char DebugMessage[128];
uint8_t LenDebugMessage;


// any MQTT Stuff??
uint32_t MsgSendTime;
boolean MSGReflected;
uint8_t SentMessage[128];
uint8_t SentMessage_Length;
char SentTopic[20];
int connects;
int oldconnects;



uint8_t Message_Length;
boolean Message_Decoded;

boolean  SensorOutput_Inactive ;

boolean DealtWith  ;
boolean POWERON;
boolean LOCO ;
boolean Phase;


boolean bReaderActive = false;

int RFIDSTATE ;
uint32_t RFIDCycle;
uint8_t RFIDDots;
boolean  Data_Updated;
uint32_t EPROM_Write_Delay;
uint32_t Ten_Sec = 10000;
uint32_t OneDay = 8640000;
uint32_t MSTimer;

uint8_t CV[256];
uint8_t RN[256];

uint16_t ROCNode_Status;

char* Nickname;
uint8_t hrs;
uint8_t mins;
uint8_t secs;   
uint32_t lastsec;

#endif
