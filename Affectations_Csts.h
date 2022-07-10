
//           Affectations

#define LeftIR   PORTB.B3
#define RightIR  PORTB.B2
#define Trig     latb.B0
#define Echo     portb.B1


#define testled  LATB.B6
#define testled2 LATB.B7

//           Csts

#define OnBlack  1
#define OnWhite  0

#define Forward  1
#define Backward 2
#define Left     3
#define Right    4
#define T180     5
#define TL90     6
#define TR90     7
#define Stop     0


#define _delayFwdToAxis 170
#define _delayTurnTo90  127
#define _delayTurnTo180 6000

#define ForwardAvoidTime 140
#define TimeCoeff        100

#define TransCount        2000
