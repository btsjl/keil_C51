#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/interrupt.h"
u16 num;//脉冲个数
u8 num1[8];
u8 num2[8];
u8 len;
int i=0;
void Timer_Interrupt_0_1()
{
    TMOD|=0x01;
    TH0=0x3C;
    TL0=0xB0;
    ET0=1;
    EA=1;
    TR0=0;  
}
Counter1_0()
{
    
    TMOD|=0x50;
    TH1=0xFF;
    TL1=0xFF;
    ET1=1;
    EA=1;
    TR0=1;
    delay_10us(11);
    TR1=1;
}
void main()
{
    Timer_Interrupt_0_1();
    Counter1_0();
    while(1)
    {
        getnum(num1,num);
        for(i=0;i<8;i++)
        {
            num1[i]=changenum(num1[i]);
        }
        display(num1,8);
    }
}
void time() interrupt 1
{
    static int i=0;   
    TH0=0x3C;
    TL0=0xB0;
    i++;
    if(i==20)
    {
        TR1=0;
    }
}
void number() interrupt 3
{
    num++;
    TH1=0xFF;
    TL1=0xFF;
}