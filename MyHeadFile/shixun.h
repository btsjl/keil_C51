#ifndef __ShIXUN_H__
#define __ShIXUN_H__
#include "./Button.h"
#include "./interrupt.h"
#include "./SEG.h"
#include "./esp8266.h"
u8 n=-1;
u8 flag=0;
u8 flag_1=0;
u8 flag_2=1;
u8 flag_3=0;
u8 PassOrLock[2]={0x73,0};
u8 passwd[8]={1,2,3,4,5,6,7,8};
u8 scanpasswd[8]={16,16,16,16,16,16,16,16};
u8 scanpasswdcode[8];
sbit LED=P2^7;
void Timer_Interrupt_0_1()//T0的16位计时器模式
{
    TMOD|=0x01;
    TH0=0xFC;
    TL0=0x18;
    EA=1;   
}
u8 check()
{
    u8 l;
    u8 s=0;
    flag_2=1;
    for(l=0;l<8;l++)
    {
        if(passwd[l]!=scanpasswd[l])
        {
            s=1;
        }
    }
    if(s)
    {
        flag_1++;
        Buzzer(100);
        if(flag_1>=3)
        Buzzer(1000);
        return 0;
    }
    else 
    {
        flag_1=0;
        return 1;
    }
}
void delay_10us_2(u16 ten_us)
{
   while(ten_us--)
   {
      //display(scanpasswdcode,8);
   }
}
u8 key_matrix_ranks_scan_2(void)
{
	u8 key_value=10;

	KEY_MATRIX_PORT=0xf7;//给第一列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xf7)//判断第一列按键是否按下
	{
		delay_10us_2(100);//消抖
		switch(KEY_MATRIX_PORT)//保存第一列按键按下后的键值	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7)
    {
       display(scanpasswdcode,8);
    }//等待按键松开	
	
	KEY_MATRIX_PORT=0xfb;//给第二列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfb)//判断第二列按键是否按下
	{
		delay_10us_2(100);//消抖
		switch(KEY_MATRIX_PORT)//保存第二列按键按下后的键值	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=0;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb)
    {
       display(scanpasswdcode,8);
    }//等待按键松开	
	
	KEY_MATRIX_PORT=0xfd;//给第三列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfd)//判断第三列按键是否按下
	{
		delay_10us_2(100);//消抖
		switch(KEY_MATRIX_PORT)//保存第三列按键按下后的键值	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd)
    {
       display(scanpasswdcode,8);
    }//等待按键松开	
	
	KEY_MATRIX_PORT=0xfe;//给第四列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfe)//判断第四列按键是否按下
	{
		delay_10us_2(100);//消抖
		switch(KEY_MATRIX_PORT)//保存第四列按键按下后的键值	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe)    
    {
       display(scanpasswdcode,8);
    }//等待按键松开	
	
	return key_value;		
}
#endif