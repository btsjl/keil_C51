#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "./Total.h"
void External_Interrupt_0()//外部中断0
{
    IT0=1;
    EX0=1;
    EA=1;
}

void External_Interrupt_1()//外部中断1
{
    IT1=1;
    EX1=1;
    EA=1;
}

void Timer_Interrupt_0()//T0的16位计时器模式
{
    TMOD=0x01;
    TH0=0xFC;
    TL0=0x18;
    ET0=1;
    EA=1;
    TR0=1;    
}

void Timer_Interrupt_1()//T1的16位计时器模式
{
    TMOD|=0x10;
    TH1=0xFC;
    TL1=0x18;
    ET1=1;
    EA=1;
    TR1=1;    
}

void Counter()//T0的16位计数器模式
{
    TMOD|=0x05;
    TH0=0xFF;
    TL0=0xFF;
    ET0=1;
    EA=1;
    TR0=1;
}
#endif