#ifndef __ESP8266_H__
#define  __ESP8266_H__
#include "./Total.h"
void UART_SendData(u8 dat)//发送一个字节
{
    ES=0;
    TI=0; //清发送完毕中断请求标志位
    SBUF=dat; //发送
    while(TI==0); //等待发送完毕
    TI=0; //清发送完毕中断请求标志位
    ES=1; //允许串口中断
}
void ESP8266_SendCmd(u8 *pbuf)//给ESP8266发送AT指令
{
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	delay_10us(5);
	UART_SendData('\r');//回车
	delay_10us(5);
	UART_SendData('\n');//换行
	delay_ms(1000);
}
void ESP8266_SendData(u8 *pbuf)//ESP8266发送数据
{
	ESP8266_SendCmd("AT+CIPSEND=0,10");
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;
	}
	UART_SendData('\n');//换行	
//	delay_ms(10);
}

void ESP8266_ModeInit(void)//esp8266 初始化
{
	ESP8266_SendCmd("AT+CIPMUX=1");	//开启多连接模式，允许多个各客户端接入
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");	//启动TCP/IP 端口为8080 实现基于网络控制	
} 


void UART_Init(u8 RELOAD_COUNT)//初始化串口中断
{
	SCON|=0X50;			//设置为工作方式1
	TMOD|=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=RELOAD_COUNT;	//计数器初始值设置
	TL1=TH1;
	ES=0;				//关闭接收中断
	EA=1;				//打开总中断
	TR1=1;				//打开计数器
//	TI=1;          //发送中断标记位，如果使用printf函数的必须设置	
}
void totalinit(void)
{
    UART_Init(0xFA);
    ESP8266_ModeInit();
    ES=1;
}
void ESP8266_ReadData()//接受数据
{
    while(!RI);
    RI=0;
    P2=SBUF;
}

#endif