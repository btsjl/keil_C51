#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Button.h"
#include "intrins.h"
#define keyboard P1
unsigned char Check_Keydown()
{
	unsigned char KeyValue=0;
	keyboard=0x0f;
	if(keyboard!=0x0f)//如果按键按下
	{
		delay_ms(10);//延时10ms消抖
		if(keyboard!=0x0f)//按键确实按下
		{	
			//判断按键所在列，以所在列的第一行的按键键值赋给KeyValue
			keyboard=0X0F;
			switch(keyboard)
			{
				case(0X07):	KeyValue=1;break; //第一列按下
				case(0X0b):	KeyValue=2;break; //第二列按下
				case(0X0d): KeyValue=3;break; //第三列按下
				case(0X0e):	KeyValue=4;break; //第四列按下
			}
			//判断按键所在行
			keyboard=0XF0;
			switch(keyboard)
			{
				case(0X70):	KeyValue=KeyValue;break;  //第一行按下
				case(0Xb0):	KeyValue=KeyValue+4;break;  //第二行按下
				case(0Xd0): KeyValue=KeyValue+8;break;  //第三行按下
				case(0Xe0):	KeyValue=KeyValue+12;break;  //第四行按下
			}
            
			while(keyboard!=0xf0); //按键松手后退出
				return KeyValue;
		}
		else  //否则认为是信号干扰导致
		{
			return 0;  //认为没有按键按下
		}
	}
	return 0;  //如果没有按键按下返回零
}
unsigned char Check_Keyboard()
{
	unsigned char row_scan_code=0x01; //行扫描码
	unsigned char col_scan_code=0xEF;//列扫描码
	unsigned char keycode;  //按键键值
	unsigned char i,x,j;
	//可以做一个消抖处理
	for(i=0;i<4;i++)//逐列扫描，将列线逐列拉低
	{
		keycode=i+1;
		keyboard=col_scan_code;
		x=keyboard; //读取行线状态
		for(j=0;j<4;j++)//逐行扫描
		{
			if(!(x&row_scan_code))//说明对应行的按键按下，使行线被拉低
			{
				keycode+=3*j;
				//如果按键还未释放，则仍有行线被拉至低电平
				while((keyboard&0x0f)!=0x0f);//等待按键释放
				P1=0x0F;     //恢复原状态，为下次按键做准备
				return keycode;     //已检测到按键键码，返回
			}
			else
				row_scan_code=_crol_(row_scan_code,1);
		}
		col_scan_code=_crol_(col_scan_code,1);//左移一位，将下一列线拉低
		row_scan_code=0x01;//重置行扫描码，为下一行扫描作准备
	}
	keycode=0;//没有按键按下，键值记为0
	return keycode;
}
void main()
{	
    int key;
    while(1){
       key=Check_Keyboard();
       if(key==4)
       P2=0x0f;
    }
}