#ifndef __DAZHUOYE_H__
#define __DAZHUOYE_H__
#include "../MyHeadFile/Total.h"
#include "../MyHeadFile/SEG.h"
sbit LED=P2^0;
sbit TR=P3^0;
sbit Echo=P3^1;
int t=0x18;
int meter=0;

u8 c=0;
u8 num[8];
u8 numcode[8];
void Timer_Init_0()
{
	TMOD|=0x01;
	TH0=0xfc;
	TL0=0x18;
    ET0=1;
    EA=1;
    TR0=1;
}
void Timer_Init_1()
{
	TMOD|=0x10;
	TH1=0xfc;
	TL1=0x18;
    ET1=1;
    EA=1;
}
#endif