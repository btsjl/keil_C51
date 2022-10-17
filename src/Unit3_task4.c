#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit K3=P3^2;
sbit K4=P3^3;
u8 i=0;
void delay_ms(u16 ten_us)
{
    u16 ms=110;
    while(ten_us--)
    {
        while(ms--);
    }
}
void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}
void Int0Init()
{
    IT0=1;
    EX0=1;
    EA=1;
}
void Int1Init()
{
    IT1=1;
    EX1=1;
    EA=1;
}
void main()
{
    Int0Init();
    Int1Init();
    P2=~0x01;
    while(1)
    {	
        
    }
}
void Init0() interrupt 0
{
    if(i==7)
    i=0;
    else
    i++;
    P2=~(0x01<<i);
}
void Init1() interrupt 2
{
    if(i==0)
    i=7;
    else
    i--;
    P2=~(0x01<<i);
}