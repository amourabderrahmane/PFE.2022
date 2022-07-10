#include "Movement.h"
#include "Assignement_csts.h"



void Set_dir(char direction){
 switch(direction){
  case 1:     // Forward
     DirM1=1;
     DirM2=0;
  break;
  case 2 :   // Backward
     DirM1=0;
     DirM2=1;
  break;
  case 3 :  // Left
     DirM1=0;
     DirM2=0;
  break;
  case 4 : // Right
     DirM1=1;
     DirM2=1;
  break;
 }
}
 
  void ON_OFF_Motors(char ON_OFF){
     if(ON_OFF==1){
      PWM1_Start();
     }
     else 
      PWM1_stop();
  }
  

 void Command(char Cmd){
  if ( Cmd== Forward){
     Set_dir(1);
     ON_OFF_Motors(1);
  }
  if ( Cmd== Backward){
     Set_dir(2);
     ON_OFF_Motors(1);
   }
  if ( Cmd== Left){
     Set_dir(3);
     ON_OFF_Motors(1);
   }
  if ( Cmd== Right){
     Set_dir(4);
     ON_OFF_Motors(1);
   }
   if ( Cmd== Stop){
     ON_OFF_Motors(0);
   }
   if ( Cmd== T180){
     Set_dir(4);
     ON_OFF_Motors(1);
     delay_ms(_delayTurnTo180);
     ON_OFF_Motors(0);
   }
   if ( Cmd== TL90){
     Set_dir(1);
     ON_OFF_Motors(1);
     delay_ms(_delayFwdToAxis);
     ON_OFF_Motors(0);
     Set_dir(3);
     ON_OFF_Motors(1);
     delay_ms(_delayTurnTo90);
     ON_OFF_Motors(0);
   }
   if ( Cmd== TR90){
     Set_dir(1);
     ON_OFF_Motors(1);
     delay_ms(_delayFwdToAxis);
     ON_OFF_Motors(0);
     Set_dir(4);
     ON_OFF_Motors(1);
     delay_ms(_delayTurnTo90);
     ON_OFF_Motors(0);
   }
 }
 
 void Command2void(char Cmd){
  if ( Cmd== Forward){
     Set_dir2Avoid(1);
     PWM1_Start();
  }
  if ( Cmd== Backward){
     Set_dir2Avoid(2);
     PWM1_Start();
   }
  if ( Cmd== Left){
     Set_dir2Avoid(3);
     PWM1_Start();
   }
  if ( Cmd== Right){
     Set_dir2Avoid(4);
     PWM1_Start();
   }
   if ( Cmd== Stop){
     PWM1_stop();
   }
   if ( Cmd== T180){
     Set_dir2Avoid(4);
     PWM1_Start();
     delay_ms(_delayTurnTo180);
     PWM1_stop();
   }
   if ( Cmd== TL90){
     Set_dir2Avoid(1);
     PWM1_Start();
     delay_ms(_delayFwdToAxis);
     PWM1_stop();
     Set_dir2Avoid(3);
     PWM1_Start();
     delay_ms(_delayTurnTo90);
     PWM1_stop();
   }
   if ( Cmd== TR90){
     Set_dir2Avoid(1);
     PWM1_Start();
     delay_ms(_delayFwdToAxis);
     PWM1_stop();
     Set_dir2Avoid(4);
     PWM1_Start();
     delay_ms(_delayTurnTo90);
     PWM1_stop();
   }
 }
 
 void Set_dir2Avoid(char direction){
 switch(direction){
  case 1:     // Forward
     DirM1=1;
     DirM2=0;
  break;
  case 2 :   // Backward
     DirM1=0;
     DirM2=1;
  break;
  case 3 :  // Left
     DirM1=0;
     DirM2=0;
  break;
  case 4 : // Right
     DirM1=1;
     DirM2=1;
  break;
 }
}