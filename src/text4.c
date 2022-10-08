#include"reg51.h"
#include"intrins.h"
#define LCD P0
typedef unsigned char u8;
typedef unsigned int u16;
int num[6]={0,0,0,0,0,0};
sbit k3=P3^2;
sbit k4=P3^3;
int i=0;
int select=-1;
int time=0;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
void delay(u16 ms){
while(ms--);
}
void Int0Init()
{
    IT0=1;
    EX0=1;
    EA=1;
}
void Int1Init()
{
    IT1=1;
    EX1=1;
    EA=1;
}
int changenum(int num)
{
    //0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
    switch (num)
    {
    case 0:return 0x3f;
    case 1:return 0x06;
    case 2:return 0x5b;
    case 3:return 0x4f;
    case 4:return 0x66;
    case 5:return 0x6d;
    case 6:return 0x7d;
    case 7:return 0x07;
    case 8:return 0x7f;
    case 9:return 0x6f;
    case 10:return 0x77;
    case 11:return 0x7c;
    case 12:return 0x39;
    case 13:return 0x5e;
    case 14:return 0x79;
    case 15:return 0x71;
    }
}
void main()
{
    Int0Init();
    Int1Init();
    while(1)
    {
        for(time=0;time<80;time++)
        {
	        for(i=0;i<6;i++)
	        {
                if(i==select)
                continue;
	    	    switch(i)//位选
		        {
			        case 0: LSC=1;LSB=1;LSA=1;break;
			        case 1: LSC=1;LSB=1;LSA=0;break;
			        case 2: LSC=1;LSB=0;LSA=1;break;
			        case 3: LSC=1;LSB=0;LSA=0;break;
			        case 4: LSC=0;LSB=1;LSA=1;break;
			        case 5: LSC=0;LSB=1;LSA=0;break;
		        }
                LCD=changenum(num[i]);
                delay(100);
                LCD=0;
	        }
        }
        for(time=0;time<80;time++)
        {
            for(i=0;i<6;i++)
	        {
	    	    switch(i)//位选
		        {
			        case 0: LSC=1;LSB=1;LSA=1;break;
			        case 1: LSC=1;LSB=1;LSA=0;break;
			        case 2: LSC=1;LSB=0;LSA=1;break;
			        case 3: LSC=1;LSB=0;LSA=0;break;
			        case 4: LSC=0;LSB=1;LSA=1;break;
			        case 5: LSC=0;LSB=1;LSA=0;break;
		        }
                LCD=changenum(num[i]);
                delay(100);
                LCD=0;
	        }
        }
    }
}
void Init0() interrupt 0
{
    delay(100);
    if(k3==0)
    {
        select++;
        if(select==7)
        select=0;
    }
}
void Init1() interrupt 2
{
    delay(100);
    if(k4==0)
    {
        num[select]+=1;
        if(num[select]==10)
        num[select]=0;
    }
}
