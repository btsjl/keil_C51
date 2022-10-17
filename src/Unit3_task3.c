#include <reg52.h>
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
sbit sound=P1^0;
sbit K3=P3^2;
sbit K4=P3^3;
u8 n=3;
u8 d=0;
u8 z=0;
u8 x=0;
void delay_ms(u16 ten_us)//延时1ms
{
    u16 ms=110;
    while(ten_us--)
    {
        while(ms--);
    }
}
void delay_10us(u16 ten_us)//延时10us
{
	while(ten_us--);	
}
void Int0Init()
{
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
    u8 i=0;
    sound=0;
    Int0Init();
    Int1Init();
    while(1)
    {
        if(d==0)
        {
            while(1)
            {
                for(i=0;i<4;i++)
                {
                    for(n=0;n<10;n++)
                    {
                        P2=~(0x01<<(i*2));
                        delay_10us(5000);
                        while(x)
                        {
                            P2=~0;
                            sound=0;
                            delay_10us(5000);
                            sound=1;
                            delay_10us(5000);
                        }
                        sound=0;
                        P2=~0;
                        delay_10us(5000);
                        while(x)
                        {
                            P2=~0;
                            sound=0;
                            delay_10us(5000);
                            sound=1;
                            delay_10us(5000);
                        }
                        sound=0;
                        if(d!=0)
                        {
                            break;
                            z=1;
                        }
                    }
                    if(z==1)
                    {
                        break;
                    }
                }
                if(d!=0)
                break;
            }
        }
        else
        {
            P2=~0x01;
            for(i=0;i<8;i++)
            {
                P2=~(0x01<<i);			
                delay_10us(50000);
                while(x)
                {
                    P2=~0;
                    sound=0;
                    delay_10us(5000);
                    sound=1;
                    delay_10us(5000);
                }
                sound=0;
                if(d!=1)
                break;
            }
            P2=~(0x80);
            for ( i = 0; i < 8; i++)
            {
                P2=~(0x80>>i);
                delay_10us(50000);
                while(x)
                {
                    P2=~0;
                    sound=0;
                    delay_10us(5000);
                    sound=1;
                    delay_10us(5000);
                }
                sound=0;
                if(d!=1)
                break;
            }
        }
    }
}
void Init0() interrupt 0
{
    x=!x;
}
void Init1() interrupt 2
{
    if(d==1)
    d=0;
    else
    d++;
}