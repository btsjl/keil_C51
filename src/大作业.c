#include "./dazhuoye.h"
void main()
{
    Timer_Init_0();
    Timer_Init_1();
    while(1)
    {
    }
}
void timer() interrupt 3
{
    static u8 i=0;
    i++;
    TH1=0xfc;
    TL1=0x18;
    if(i==10)
    {
        t++;
    }
}
void timer_0() interrupt 1
{
    static u8 i_0=0;
    i_0++;
    TH0=0xfc;
    TL0=0x18;
    getnum(num,t);
    display(numcode,8);
    TR=0;
    TR=1;
    delay_10us(2);
    TR=0;
}