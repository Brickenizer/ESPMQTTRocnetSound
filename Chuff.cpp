

#include "Chuff.h"

  #include "AudioFileSourceSPIFFS.h"
  #include "AudioGeneratorWAV.h"
  
#include "Directives.h";
#ifdef _AudioDAC
  #include "AudioOutputI2SDAC.h"
#endif
#ifdef _AudioNoDAC
  #include "AudioOutputI2SNoDAC.h"
  #endif 

AudioGeneratorWAV *wav;
AudioFileSourceSPIFFS *file;
#ifdef _AudioDAC
  AudioOutputI2SDAC *out;
#endif
 #ifdef _AudioNoDAC
  AudioOutputI2SNoDAC *out;
#endif
int ChuffCycle;  
long LastChuff;
bool WavDoneMsgSent;
bool PlayingSoundEffect;
bool ChuffPlaying;

long SteamOnStarted;
long SteamPulseDuration =50;
long ChuffPeriod;
String LastFilePlayed="--";
String ChuffType; // ="/ch";  //String ChuffType ="/99_H1_";  //alternate chuff sound
uint8_t SoundEffect_Request[3];




extern void DebugSprintfMsgSend(int CX);
extern char DebugMsg[127];
extern uint8_t NodeMCUPinD[12];

extern uint8_t  CV[256];
void SetChuffPeriod(long Setting){
  ChuffPeriod=Setting;
}
void SetSoundEffect(uint8_t Data1,uint8_t Data2,uint8_t Data3){
  SoundEffect_Request[1]=Data1;
  SoundEffect_Request[2]=Data2;
  SoundEffect_Request[3]=Data3;
}
void SetUpChuff(uint32_t TimeNow){ 
 #ifdef _AudioDAC
  out = new AudioOutputI2SDAC();
  #endif
 #ifdef _AudioNoDAC
  out = new AudioOutputI2SNoDAC();
#endif
  delay(200);
  SteamPulseDuration=5;  //5 for use as strobe
  SteamOnStarted=TimeNow;
  
  wav = new AudioGeneratorWAV();
  WavDoneMsgSent=false;
  ChuffCycle=0;
  LastChuff=TimeNow+4000;
  Serial.printf("-- Sound System Initiating -- \n");
 
  PlayingSoundEffect=false;   
  ChuffPlaying=false;
  ChuffPeriod=3000;
 // delay(2000); // allow time for setups..
  LastFilePlayed="--";
  SoundEffect_Request[1]=0;
  SoundEffect_Request[2]=0;
  SoundEffect_Request[3]=0;
/*//Temporary override sound volumes 
CV[100]=127; // Overall volume control
CV[101]=127; //volume for F1 
CV[102]=127;
CV[103]=127;
CV[104]=127;
CV[105]=127;
CV[106]=127;
CV[107]=127;
CV[108]=127; // Volume for F8

CV[110]=127; // volume for chuffs
CV[111]=127; // volume for Brake Squeal
//
*/  
  BeginPlay("/initiated.wav",64);// this wav file will play before anything else.
  
}

void BeginPlay(const char *wavfilename, uint8_t Volume){
  String Filename;
  float Gain;
  if(!PlayingSoundEffect){
  Filename=wavfilename;
  WavDoneMsgSent=false;
  if (Filename.substring(0,3)== ChuffType.substring(0,3)){  // playing chuffs 
            PlayingSoundEffect=false;
            ChuffPlaying=true;
            #ifdef _AudioDebug
            //Serial.printf("Chuff");
            #endif
           }
       else {   // need to truncate previous ?? 
        PlayingSoundEffect=true; 
        if (wav->isRunning()) {
                           wav->stop();
                           #ifdef _AudioDebug
                              Serial.printf("*audio previous wav stopped\n");
                           #endif
                  }
        #ifdef _AudioDebug 
       // Serial.println("");
       // Serial.printf("*Audio  last file was:");
       // Serial.print(LastFilePlayed);
       
        #endif
            }      
            if (LastFilePlayed!="--"){  delete file;    }//housekeeping.. delete last file  
            LastFilePlayed=wavfilename;     
     Serial.printf("Playing <");
     Serial.print(wavfilename);   
     Gain= (float)(Volume*CV[100])/16384; //use master volume each nominally 128 so divide by 128^2 to get "1"
      Serial.print("> @Gain:");
      Serial.println(Gain);
      Serial.println(); 
     file = new AudioFileSourceSPIFFS(wavfilename);
     #ifdef _Audio  // stops some compiler issues if no audio needed
     wav->begin(file, out);
     out->SetGain(Gain); 
     #endif
     delay(1);
  }}


bool TimeToChuff(uint32_t TimeNow){
  
   if (ChuffPeriod>=2000){return false;} // switches off chuff at very low or stopped speeds
   if (SoundEffectPlaying()){return false;}
   if (TimeNow<=(LastChuff+ChuffPeriod)){return false;}
    else {LastChuff=TimeNow; return true;}
    }
    

void Chuff (String ChuffChoice){
  String Chuff;
 // if (ChuffPeriod>=60){ChuffChoice="/ch";} // test for switching sound effects with speed this works, but my fast sound clips need work 
 // else{ChuffChoice="/CHF_";} 
  
  ChuffType=ChuffChoice;

  
  if (!PlayingSoundEffect){
   if (wav->isRunning()) {wav->stop();  delay(1);
                           #ifdef _AudioDebug
                             // Serial.print-wav -Truncated\n");
                              #endif
                          }// truncate play
   LastChuff=millis();
   //steamoutputpin stuff  here for one puff per chuff 
   #ifdef _LOCO_SERVO_Driven_Port
   SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH);
   switch (ChuffCycle){ 
                              case 0:Chuff=ChuffType+"1.wav";BeginPlay(Chuff.c_str(),CV[110]);ChuffCycle=1;
                              //Stuff here only for strobe use, one per rev to help set chuff rate
                                  //SteamOnStarted=millis(); digitalWrite (NodeMCUPinD[SteamOutputPin],HIGH);
                              break;
                              case 1:Chuff=ChuffType+"2.wav";BeginPlay(Chuff.c_str(),CV[110]);ChuffCycle=2;break;
                              case 2:Chuff=ChuffType+"3.wav";BeginPlay(Chuff.c_str(),CV[110]);ChuffCycle=3;break;
                              case 3:Chuff=ChuffType+"4.wav";BeginPlay(Chuff.c_str(),CV[110]);ChuffCycle=0;break;
}
#endif
}
}
void AudioLoop(int32_t TimeNow){
 #ifdef SteamOutputPin
              if ((SteamOnStarted+SteamPulseDuration)<=TimeNow){digitalWrite (NodeMCUPinD[SteamOutputPin],LOW);}
 #endif 
  
  
  if (wav->isRunning()) { if (!wav->loop()) {wav->stop();}//
                        } 
           else {delay(10);PlayingSoundEffect=false;
                  if (!WavDoneMsgSent){
                    //wav->stop();
                     WavDoneMsgSent=true;  
                     #ifdef _AudioDebug
                      Serial.printf(" -WAV done\n"); 
                     #endif
                     }
                 }
                
}
  bool SoundEffectPlaying(void){
    return PlayingSoundEffect;
    }
  void SoundEffects(void) {
          if(bitRead(SoundEffect_Request[1],0)==1){
            if (!PlayingSoundEffect){BeginPlay("/F1.wav",CV[101]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F1"));}
                                       }
          if(bitRead(SoundEffect_Request[1],1)==1){
            if (!PlayingSoundEffect){BeginPlay("/F2.wav",CV[102]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F2"));}
                                       }
           if(bitRead(SoundEffect_Request[1],2)==1){
           if (!PlayingSoundEffect){BeginPlay("/F3.wav",CV[103]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F3"));}
                                       }
          if(bitRead(SoundEffect_Request[1],3)==1){
           if (!PlayingSoundEffect){BeginPlay("/F4.wav",CV[104]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F4"));}
                                       }
           if(bitRead(SoundEffect_Request[1],4)==1){
           if (!PlayingSoundEffect){BeginPlay("/F5.wav",CV[105]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F5"));}
                                       }
           if(bitRead(SoundEffect_Request[1],5)==1){
           if (!PlayingSoundEffect){BeginPlay("/F6.wav",CV[106]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F6"));}
                                       }
           if(bitRead(SoundEffect_Request[1],6)==1){
           if (!PlayingSoundEffect){BeginPlay("/F7.wav",CV[107]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F7"));}
                                       }
           if(bitRead(SoundEffect_Request[1],7)==1){  // this is "F8" on DCC sounds 
           if (!PlayingSoundEffect){BeginPlay("/F8.wav",CV[108]);
            DebugSprintfMsgSend( sprintf ( DebugMsg, "sfx-F8"));}
                                       }                            
        
  }  
 

 

