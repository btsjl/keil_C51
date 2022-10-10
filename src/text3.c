#include"reg51.h"
#include"intrins.h"
typedef unsigned char u8;
typedef unsigned int u16;
#define LED P2
sbit k3=P3^2;
sbit k4=P3^3;
int time=50000;
u8 i;
u8 press = 0;//判断开关是否按下的参数
u16 c=0;//利用c值在0或1变化 来中断或开启流水灯
u16 d=0;
void delay(u16 i){
while(i--);
}
void Int0Init()
{
//设置INT0
IT0=1;//跳变沿出发方式（下降沿）
EX0=1;//打开INT0的中断允许。
EA=1;//打开总中断
}
void Int1Init()
{
    IT1=1;
    EX1=1;
    EA=1;
}
void main()
{
Int1Init();
Int0Init(); // 设置外部中断0
while(1)
{
if(press==0) //初始状态，让小灯熄灭
{ LED=0xff; }
if(press==1) //判断按键按下
{ 
    LED=0XFE;
    delay(50000);
    while(1)
    { 
        for(i=0;i<7;i++) //将led左移一位
        {
        while(!c); 
        LED=~(0x01<<i);
            while(time--)
            {
                while(d)
                {
                    delay(50000);
                    LED=~(0xff);
                    delay(50000);
                    LED=~0;
                }
            }
        }

    }

}

}

}



void Int0() interrupt 0 //外部中断0的中断函数
{
delay(100);
if (k3==0)
{ 
    press += 1;
    c=!c;
    if(!c)
    {
        i=-1;
        LED=~(0);
    }
}while(!k3);//判断按键是否松开（没有while（！3）；按键摁下就直接点亮led，加了这句， 按键摁下松手后才会开始点亮）；
}
void Int1() interrupt 2
{
    delay(100);
    if(k4==0)
    {
        d=!d;
    }while(!k4);
}