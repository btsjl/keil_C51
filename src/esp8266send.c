#include "../MyHeadFile/esp8266.h"
u8 *a="right!";
u8 *b="error!";
u8 byt=0xfA;
void main()
{
    UART_Init(byt);
	delay_ms(1000);
	ESP8266_SendCmd("AT+CIPMUX=1");
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");
    ES=1;
    while(1)
    {
        ESP8266_SendData(a);
        delay_ms(1000);
    }
}