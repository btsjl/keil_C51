#include "../MyHeadFile/interrupt.h"
#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Button.h"
sbit KEY1=P3^1;
u8 ho=0,min=0,sc=0;
u8 num[8]={0,0,16,0,0,16,0,0};
u8 jilu[6][8]=
{
  0,0,16,0,0,16,0,0,
  0,0,16,0,0,16,0,0,
  0,0,16,0,0,16,0,0,
  0,0,16,0,0,16,0,0,
  0,0,16,0,0,16,0,0,
  0,0,16,0,0,16,0,0
};
static u8 l=0;
u8 num1[8];
u8 num2[8];
u8 flag0=0;
int n=0;
int sum=0;
static int i=0;
int t=-1;
void getnum_1(u8 *num,u8 ho,u8 min,u8 sc,u8 len)
{
    num[len-1]=sc%10;
    sc/=10;
    num[len-2]=sc;
    num[len-4]=min%10;
    min/=10;
    num[len-5]=min;
    num[len-7]=ho%10;
    ho/=10;
    num[len-8]=ho;
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
    External_Interrupt_0();//外部中断0
    External_Interrupt_1();//外部中断1
    Timer_Interrupt_0_1();
    while(1)
    {
        getnum_1(num,ho,min,sc,8);
        if(TR0==1)
        {
            for(n = 0; n < 8; n++)
            {
                num1[n]=changenum(num[n]);
            }
            display(num1,8);

        }
        else
        {
            if(key_scan(0))
            {
                flag0=1;
                t++;
                if(t==6)
                {
                    t=0;
                }
            }
            if(flag0)
            {
                for(n = 0; n < 8; n++)
                {
                    num2[n]=changenum(jilu[t][n]);
                }
                display(num2,8);
            }
            else
                display(num1,8);
        }
    }
}
void Timer() interrupt 1
{
    while(i==10)
    {
        sc++;
        if(sc==60)
        {
            sc=0;
            min++;
            if(min==60)
            {
                min=0;
                ho++;
                if(ho==24)
                {
                    ho=0;
                }
            }
        }
        i=0;

    }
    TH0=0xD8;
    TL0=0xF0;
    i++;
}
void extend_0() interrupt 0
{
    TR0=!TR0;
    t=-1;
    flag0=0;
}
void extend_1() interrupt 2
{
    int c;
    for(c=0;c<8;c++)
    {
        jilu[l][c]=num[c];
    }
    l++;
    if(l==6)
    {
        l=0;
    }
}