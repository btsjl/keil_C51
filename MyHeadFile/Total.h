#ifndef __TOTAL_H__
#define __TOTAL_H__
#include <reg52.h>
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
void delay_10us(u16 ten_us)//延时10us
{
	while(ten_us--);	
}
void delay_ms(u16 ten_us)//延时1ms
{
    u16 ms=110;
    while(ten_us--)
    {
        while(ms--);
    }
}
#endif