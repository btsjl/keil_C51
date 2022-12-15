#include "../MyHeadFile/ADC.h"
void main()
{
    static n=0;
    u8 i=0;
    u16 out_1=0,out_2=0;
    u8 I_1=0x00,I_2=0x01;
    Timer_Init();
    while(1)
    {
        if(n==0)
        {
        ADCInit_0();
        out_1=getinfo(I_1);
        n++;
        }
        else
        {
        ADCInit_1();
		out_2=getinfo(I_2);
        n--;
        }
        Int2Num(num,out_1,out_2);
        for(i=0;i<8;i++)
        {
            numcode[i]=changenum(num[i]);
            ST=1;
        }
        display(numcode,8);
    }
}
void Timer() interrupt 1
{
    TH0=200;
    TL0=200;
    CLK=!CLK;
}