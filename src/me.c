#include <reg52.h>
#include "../MyHeadFile/interrupt.h"
#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Total.h"
sbit KEY1=P3^1;
u8 ho=0,min=0,sc=0;
u8 num[6]={0,0,0,0,0,0};
u8 jilu[6][8]=
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
    
};
static u8 l=0;
u8 num1[6];
u8 num2[6];
u8 flag0=0;
u8 n=0;
static u8 i=0;
u8 t=5;
void getnum_1(u8 *num,u8 ho,u8 min,u8 sc,u8 len)
{
    num[len-1]=sc%10;
    sc/=10;
    num[len-2]=sc;
    //num[len-3]=16;
    num[len-3]=min%10;
    min/=10;
    num[len-4]=min;
    //num[len-6]=16;
    num[len-5]=ho%10;
    ho/=10;
    num[len-6]=ho;
}
void Timer_Interrupt_0_1()//T0的16位计时器模式
{
    TMOD|=0x01;
    TH0=0xD8;
    TL0=0xF0;
    ET0=1;
    EA=1;
    TR0=1;
        
}
u8 key_scan(u8 mode)
{
	static u8 key=1;
	if(mode)key=1;//连续扫描按键
    if(key==1&&KEY1==0)
    {
        delay_10us(5000);
        key=0;
        if(KEY1==0)
        return 1;
    }
	else if(KEY1==1)	//无按键按下
	{
		key=1;			
	}
	return 0;		
}
void main()
{

}