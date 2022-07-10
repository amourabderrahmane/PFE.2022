
#include "Assignement_csts.h"
#include "Functions.h"
#include "Movement.h"

unsigned int nchamber,MA=1,Nobs=0;
char TestOrSet=1;
char obsAvoided=0,avoidStatus=0;
char deliverT;


void interrupt () {


 if (PIR1.RCIF == 1){
    char number=0 ;
    
    number = UART1_Read();
    switch (number){
     case 'a' : nchamber=1; break;
     case 'b' : nchamber=2; break;
     case 'c' : nchamber=3; break;
     case 'd' : nchamber=4; break;
     case 'e' : nchamber=5; break;
     case 'f' : nchamber=6; break;
     default  : nchamber=1; break;
     testled2=1; delay_ms (5000);

    }
    MA=0;
    deliverT=1;
    T0CON.TMR0ON=1;
    PIE1.RCIE=0;
    PIR1.RCIF=0;
   }
   if (TMR0IF_bit){
    if(TestOrSet){      //set
     Trig = 1;
     delay_us(10);
     Trig = 0;
     TestOrSet=0;
     SetObsTime();     // pour voir l'echo
    }
    else{             //test
     if(Echo==0) {
     testled2=1;
      Nobs++;
      PWM1_Stop();                                                               ////////////////////////////////////////////////////////////////////////////// remove the condition if you need help
      if(Nobs>=50 && avoidStatus){
        obsAvoided=avoidObs();
        /*if(obsAvoided == 0) {Nobs=0; PWM1_Start();}
        else                { //you need to know what to do
        }*/
      }
      if (Nobs>50) Nobs=1;
     }
     else     { if(Nobs != 0) {PWM1_Start();} Nobs=0; }
     TestOrSet=1;
     SetTestTime();                                 ////// mybe nkhrjoha
    }

    TMR0IF_bit = 0;


  }
 }

void main() {
  unsigned int m=0;


  init();

  while(1){
   while(MA==1);
   if (LeftIR == OnBlack  && RightIR == OnBlack ){
    testled=1; delay_ms (5000);
    delay_ms (2000); //
    ignore();

    avoidStatus=0;

    //delay_ms (2000);
    stayOnLine();

  testled2=1; delay_ms (3000);
    avoidStatus=0;
    m=m+1;

    if(2*m >= nchamber){
     if(obsAvoided > 0 ) {
       if(nchamber%2==1 && obsAvoided==10) {Command(TL90);  deliverT=0;}
       if(nchamber%2==0 && obsAvoided==20) {Command(TR90);  deliverT=0;}
       stayOnLine();
     }
     deliver(nchamber,deliverT);
     returne(nchamber);
     MA=1;
     T0CON.TMR0ON=0;
     PIE1.RCIE=1;
    }  
     else {
       if(obsAvoided > 0) {
          // esc ok R
         if (obsAvoided == 10) Command(TL90);
         else                  Command(TR90);
         stayOnLine();
         if (obsAvoided == 10) Command(TR90);
         else                  Command(TL90);
         obsAvoided=0;
       }
     }                           // integrqte else situation  to return to base
   }
 }
}