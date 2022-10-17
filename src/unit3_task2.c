#include <reg52.h>
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
int num_0[4]={0x18,0x3C,0x7E,0xFF};
u8 d=0;
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
   	u8 i=0;
    Int0Init();
    while(1)
    {
        if(d==0)
        {
            P2=~0x01;
            for(i=0;i<8;i++)
            {
                P2=~(0x01<<i);			
                delay_10us(50000);
                if(d!=0)
                break;
            }
        }
        else if(d==1)
        {
            P2=~(0x80);
            for ( i = 0; i < 8; i++)
            {
                P2=~(0x80>>i);
                delay_10us(50000);
                if(d!=1)
                break;
            }
        }
        else 
        {

            P2=~0;
            for (i = 0; i < 4; i++)
            {
                P2=~(num_0[i]);
                delay_10us(50000);
                if(d!=2)
                break;
            }
            P2=0;
            for(i=0;i<4;i++)
            {
                P2=~num_0[3-i];
                delay_10us(50000);
                if(d!=2)
                break;
            }
            P2=~0;
            delay_10us(50000);
            
        }
    }
}
void Init0() interrupt 0
{
    if(d==2)
    d=0;
    else d++;
}