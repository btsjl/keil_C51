#ifndef __SEG_h__
#define __SEG_h__
#include "./Total.h"
#define LCD P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
u8 changenum(u8 num)//把数字转换成对应的共阳极数码管的编码
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
void display(u8 num[],u8 n)//显示num数组里的编码，n为编码长度，n<8
{
    u8 i;
    for(i=0;i<n;i++)
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
        LCD=num[i];
        delay_10us(100);
        LCD=0;
    }
}
#endif