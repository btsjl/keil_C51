#ifndef __ShIXUN_H__
#define __ShIXUN_H__
#include <reg52.h>
#define LCD P0//数码管
#define KEY_MATRIX_PORT	P1   //矩阵按键
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
//全局变量
u8 n=-1;//密码输入到几位，n=0时为输入了一位，n=1时为输入了两位
u8 flag=0;//用来接收check函数的返回值，返回值为0则密码错误，返回值为1则密码正确
u8 flag_1=0;//密码输入错误的次数，默认0，错一次+1，对一次变为0
u8 flag_2=1;//检测密码是否输入完全即输入8位，输入完就为1，使用k3可将其变为0
u8 flag_3=0;//flag_3=flag_1,它们作用不同，flag_3用来计算处罚时间时间为4*flag_3秒
u8 PassOrLock[2]={0x73,0};//输入正确或错误时数码管显示，正确为0x73(‘P’),错误为0x38('L')
u8 passwd[8]={1,2,3,4,5,6,7,8};//正确的密码
u8 scanpasswd[8]={16,16,16,16,16,16,16,16};//用户输入的密码存储到这里
u8 scanpasswdcode[8];//用户输入对应的数码管显示的编码存储到这里
sbit LSA=P2^2;//数码管的位显示选择
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit BEEP=P2^5;//蜂鸣器对应的引脚

///////////////////////////
void delay_10us(u16 ten_us)//延时10us
{
	while(ten_us--);	
}
//////////////////////////
void delay_ms(u16 ms)//延时1ms
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}
///////////////////////////
void Buzzer(u16 i)//蜂鸣器警报函数
{	
	while(i--)
	{
		BEEP=!BEEP;
        delay_10us(100);
	}
    BEEP=1;
}
///////////////////////////
void External_Interrupt_0()//外部中断0
{
    IT0=1;
    EX0=1;
    EA=1;
}
///////////////////////////
void External_Interrupt_1()//外部中断1
{
    IT1=1;
    EX1=1;
    EA=1;
}
///////////////////////////
void Timer_Interrupt_0_1()//T0的16位计时器模式，ET0貌似不可以和矩阵行列扫描同时使用
{
    TMOD|=0x01;
    TH0=0xFC;
    TL0=0x18;
    EA=1;   
}
///////////////////////////
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
            case 6: LSC=0;LSB=0;LSA=1;break;
            case 7: LSC=0;LSB=0;LSA=0;break;
        }
        LCD=num[i];
        delay_10us(100);
        LCD=0;
        }
}
///////////////////////////
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
    case 16:return 0x40;
    }
}
///////////////////////////
u8 check()//用以检查输入密码是否正确
{
    u8 l;
    u8 s=0;
    flag_2=1;
    for(l=0;l<8;l++)
    {
        if(passwd[l]!=scanpasswd[l])
        {
            s=1;//只要数组有一个不对s就等于1否则为0
        }
    }
    if(s)//s为2
    {
        flag_1++;
        Buzzer(100);//错误一次滴一声
        if(flag_1>=3)
        Buzzer(1000);//连续错误三次 报警
        return 0;//错了返回0
    }
    else //s为0
    {
        flag_1=0;//对了错误次数归零
        return 1;//对了返回1
    }
}
///////////////////////////
u8 key_matrix_ranks_scan_2(void)//按键扫描函数
{
	u8 key_value=10;

	KEY_MATRIX_PORT=0xf7;//给第一列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xf7)//判断第一列按键是否按下
	{
		delay_10us(100);//消抖
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
    }//等待按键松开，加入显示函数，防止输入的时候闪烁
	
	KEY_MATRIX_PORT=0xfb;//给第二列赋值0，其余全为1
	if(KEY_MATRIX_PORT!=0xfb)//判断第二列按键是否按下
	{
		delay_10us(100);//消抖
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
		delay_10us(100);//消抖
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
		delay_10us(100);//消抖
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