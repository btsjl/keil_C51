#ifndef __ADC_H__
#define __ADC_H__
#include "./Total.h"
#include "./interrupt.h"
#include<stdio.h>
#include<stdlib.h>
#include<intrins.h>
#include<string.h>
#include "./SEG.h"
sbit ADDC=P1^6;
sbit ADDB=P1^5;
sbit ADDA=P1^4;
u8 num[8]={16,16,16,16,16,16,16,16};
u8 numcode[8];
sbit CLK=P1^3; //clock
sbit ST=P1^2; //start (转换启动信号)
sbit EOC=P1^1; //end of conversion (转换结束信号)
sbit OE=P1^0; //output enable (输出允许信号,用于)
sbit ALE=P1^7;
void Timer_Init()
{
    TMOD|=0x02;
    TH0=100;
    TL0=100;
    EA=1;
    TR0=1;
    ET0=1;
}
void ADCInit_0()
{
    ADDC=0;
	ADDB=0;
	ADDA=0;
	
	CLK=0;
	ST=1; //内部寄存器清零
	EOC=1; // 转换结束(未开始)
	OE=0; 
}
void ADCInit_1()
{
	// ABC=110选择第三通道
	ADDC=0;
	ADDB=0;
	ADDA=1;
	CLK=0;
	ST=1; //内部寄存器清零
	EOC=1; // 转换结束(未开始)
	OE=0; 
}
u16 getinfo(u8 a)
{

    u16 out;
    ST=0;
	_nop_();
	ST=1;
	_nop_();
	ST=0;
    while(EOC==0)
    {
        display(numcode,8);
    }
	OE=1;
    out=P3;
    out=out*100/51;
    ALE=0;
    //OE=0;
    return out;
}
u8 Int2Num(u8 *num,u16 target,u16 target_1)
{
    u8 i=0;
    for(i=0;i<4;i++)
    {
        num[3-i]=target%10;
        target/=10;
    }
    for ( i = 0; i < 4; i++)
    {
        num[7-i]=target_1%10;
        target_1/=10;
    }
    
}
#endif