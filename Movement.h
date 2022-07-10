sbit PWM   at LATC.B2;
sbit DirM1 at LATC.B0;
sbit DirM2 at LATC.B5;
sbit ENM1  at LATC.B3;
sbit ENM2  at LATC.B4;


void Set_dir(char direction);
void ON_OFF_Motors(char ON_OFF);
void Command(char Cmd);

void Command2void(char Cmd);
void Set_dir2Avoid(char direction);