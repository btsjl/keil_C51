#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "./Total.h"
void External_Interrupt_0()
{
    IT0=1;
    EX0=1;
    EA=1;
}

void External_Interrupt_1()
{
    IT1=1;
    EX1=1;
    EA=1;
}

void Timer_Interrupt_0()
{
    TMOD|=0x01;
    TH0=0xFC;
    TL0=0x18;
    ET0=1;
    EA=1;
    TR0=1;    
}

void Timer_Interrupt_1()
{
    TMOD|=0x10;
    TH1=0xFC;
    TL1=0x18;
    ET1=1;
    EA=1;
    TR1=1;    
}
#endif