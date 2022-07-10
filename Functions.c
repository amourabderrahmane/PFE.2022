#include "Functions.h"
#include "Movement.h"
#include "Assignement_csts.h"

char AvoidingDir; // R/L 0/1
char Avoidingsec; // 1/2
int  ElpTime;

unsigned int LBC=0;
unsigned int RBC=0;
unsigned int LWC=0;
unsigned int RWC=0;

char LeftIRStatus=OnBlack;
char RightIRStatus=OnBlack;



void init(){
 TRISB.B0=0;
 TRISB.B2=1;
 TRISB.B3=1;
 TRISB.B1=1;
 TRISB.B6=0;
 TRISB.B7=0;
 TRISC.B0=0;
 TRISC.B2=0;
 TRISC.B3=0;
 TRISC.B4=0;
 TRISC.B5=0;
 TRISD=0;
 ANSELB=0;
 ANSELC=0;
 ANSELD=0;
 //LATB=0;
 LATC=0;
 ENM1=1;
 ENM2=1;
 pfepwminit ();

 INTCON.PEIE=1;                  // for bth
 INTCON.GIE=1;
 PIE1.RCIE=1;
 UART1_Init(9600);
 delay_ms(100);
 
 TRISC.B7=1;    //  tx/rx
 TRISC.B6=1;
 
 InitTimer0();                        // timer0 off


}

void stayOnLine(){
 testled2=1;
 while(LeftIRStatus == OnWhite || RightIRStatus == OnWhite){
    updateTestIR();
  if (LeftIRStatus == OnBlack && RightIRStatus == OnWhite){
       Command(Left);
      //}
     //else{
     //while(LeftIRStatus == OnBlack && RightIRStatus == OnWhite){updateTestIR();}
  }
  if (LeftIRStatus == OnWhite && RightIRStatus == OnBlack){
   Command(Right);
   //while(LeftIRStatus == OnWhite && RightIRStatus == OnBlack){updateTestIR();}
  }
  if (LeftIRStatus == OnWhite && RightIRStatus == OnWhite){
   Command(Forward);
   //while(LeftIRStatus == OnWhite && RightIRStatus == OnWhite){updateTestIR();}
  }
 }
 testled2=0;
}


void deliver(unsigned int nchamber, char activateT){
 //LATB.B3=1;
 if(activateT){
   if(nchamber%2==0) Command(TR90);
   else              Command(TL90);
 }
 ignore();
 stayOnLine();
 
 Command(Stop);
 delay_ms(5000);
 Command(T180);
 
 ignore();
 stayOnLine();
 //LATB.B3=0;
}
   
void ignore(){
  testled=1;
  updateTestIR();

 Command(Forward);
 while(LeftIRStatus == OnBlack  &&  RightIRStatus == OnBlack){updateTestIR();}
 testled=0;
}
    
void returne(unsigned int nchamber){
 //LATB.B1=1;
 unsigned int m;
 Command(Stop);
 if(nchamber%2==0) {Command(TL90); m=nchamber/2;}
 else       {Command(TR90); m=(nchamber+1)/2;}
 
 while(m != 0){
  ignore();
  stayOnLine();
  m--;
 }
 Command(Stop);
 Command(T180);

 //LATB.B1=0;
}


void InitTimer0(){              //3 ms
  T0CON         = 0x08;                // timer is off
  TMR0H         = 0xE8;
  TMR0L         = 0x90;
  GIE_bit         = 1;
  TMR0IE_bit         = 1;
}
void SetObsTime(){              //3 ms temps echo
  T0CON         = 0x88;
  TMR0H         = 0xE8;
  TMR0L         = 0x90;
}
void SetTestTime(){             //100 ms trig
  T0CON         = 0x81;
  TMR0H         = 0x3C;
  TMR0L         = 0xB0;
}

void pfepwminit ()  {
  PWM1_Init(600);
  PWM1_Set_Duty(128);
}

char ManualNAV(char BB_TN, unsigned int ReqTime){   // BB_TN 1/0     ;;;; return 0 1
 char NPositivetests=0,Nobs=0;
 Command2void(Forward);
 while(1){
   Trig = 1;
   delay_us(10);
   Trig = 0;
   delay_ms(3);

   if(Echo==0) {         //obs detected
     Nobs++;
     if(Nobs==1){
       Command2void(Stop);
     }
     if(Nobs>=50) return 0;
   }
   else  {
     if(Nobs != 0) Command2void(Forward);
     Nobs=0;
     NPositivetests++;
   }
   delay_ms(100);
   
   if(NPositivetests==TimeCoeff){
     ElpTime++;
     NPositivetests=0;
   }
  if(BB_TN==0){
    if(ElpTime==ReqTime ) return 1;
  }
  else {
    updateTestIR();
    if (LeftIRStatus == OnBlack && RightIRStatus == OnBlack)   return 1;
  }
 }
  

}
char Escape(char R_L){        // R/L 0/1           // if error 0 , if succeed 1
  char result;
  if(R_L==0) Command2void(TR90);
  else       Command2void(TL90);
  Avoidingsec=1;
  result= ManualNAV(0, ForwardAvoidTime);
  if (result==1){
    if(R_L==0) Command2void(TL90);
    else       Command2void(TR90);
    Avoidingsec=2;
    result= ManualNAV(1, 0);
    if (result==1){
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

char Undo(){
  char wasIn2ndSec=0;
  if(Avoidingsec ==2){
    Command2void(T180);
    while(~ManualNAV(0, ElpTime));
    if(AvoidingDir==0){
      Command2void(TR90);
    }
    else {
      Command2void(TL90);
    }
    wasIn2ndSec=1;
    Avoidingsec=1;
  }

  if(Avoidingsec ==1){
   if(wasIn2ndSec==0) Command2void(T180);
   
   while(~ManualNAV(1, 0));
   if(AvoidingDir==0){
     Command2void(TR90);
   }
   else {
     Command2void(TL90);
   }
   Trig = 1;
   delay_us(10);
   Trig = 0;
   delay_ms(3);
   return (Echo);
 }


}


char avoidObs(){
  char result;
  AvoidingDir=0;    //R
  result = Escape(0); //R
  if (result==1) {                        // esc ok R
    //continue ... to recheck
    return 10;
  }
  else{                                   // esc no R
    result= Undo();
    if(result==1){                        // obs gone after right
      return 0;
    }
    else {                                // obs presist after right
      AvoidingDir=1;
      result= Escape(1); //L
      if(result==1){                      // obs ok L
        //continue ... to recheck
        return 20;
      }
      else{
        result= Undo();
        if(result==1){                     // obs gone after left
          return 0;
        }
        else{                              // obs presist after left
          while(result==0){
            Trig = 1;
            delay_us(10);
            Trig = 0;
            delay_ms(3);
            if(Echo == 1) result = 1;
            delay_ms(100);
          }
          return 0;
        }
      }
    }
  }

}

  void updateTestIR(){
    if (LeftIR == OnBlack){ 
        LWC=0;
        LBC++;
          if(LBC==TransCount){
            LeftIRStatus=OnBlack;
            //latd.b1= LeftIRStatus;
            LBC=0;
          }
    }
    if(RightIR == OnBlack){
        RWC=0;
        RBC++;
           if(RBC == TransCount){
             RightIRStatus=OnBlack;
             //latd.b0= RightIRStatus;
             RBC=0;
           }
     }
        if (LeftIR == OnWhite){
        LBC=0;
        LWC++;
          if(LWC == TransCount){
            LeftIRStatus=OnWhite;
            //latd.b1= LeftIRStatus;
            LWC=0;
          }
    }
       if (RightIR == OnWhite){
        RWC++;
        RBC=0;
          if(RWC == TransCount){
            RightIRStatus=OnWhite;
            //latd.b0= LeftIRStatus;
            RWC=0;
          }
    }
}