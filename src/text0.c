#include "../MyHeadFile/interrupt.h"
#include "../MyHeadFile/SEG.h"
sbit L=P1^0;
int sum=0;
sbit rst=P1^1;
sbit rst1=P1^2;
void main()
{	while(1)
    {
    rst=0;
    rst1=0;
    }
}
void Timer() interrupt 1
{
    static int time_1=0;
    while(time_1==1000)
    {
        sum++;
        time_1=0;
    }
    time_1++;
    TH0=0xFC;
    TL0=0x18;
}