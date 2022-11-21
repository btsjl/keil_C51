#include "../MyHeadFile/esp8266.h"
#include "../MyHeadFile/SEG.h"
u8 num[10]="woshishabi";
u8 num1;
u8 n=10;
u8 i;
sbit LED=P2^0;
u8 byt=0xfA;
void main(void)
{
	UART_Init(byt);
	delay_ms(1000);
	ESP8266_SendCmd("AT+CIPMUX=1");
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");
	LED=0;
	ES=1;
	for(i=0;i<n;i++)
	{
		ESP8266_SendData(num);
		LED=!LED;
		delay_ms(1000);
	}
}