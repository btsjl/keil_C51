#include "../MyHeadFile/Total.h"
#include "../MyHeadFile/esp8266.h"
#include "../MyHeadFile/SEG.h"
u8 byt=0xfA;
static u8 n=0;
u8 UserScan[18];
u8 num[8]={48,48,48,48,48,48,48,48};
u8 numcode[8];
u8 i=0;
u8 c=0;
void main()
{
    UART_Init(byt);
	delay_ms(1000);
	ESP8266_SendCmd("AT+CIPMUX=1");
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");
    ES=1;
    for(i=0;i<8;i++)
    {
        num[i]=48;
    }
    while(1)
    {
        for(i=0;i<8;i++)
        {
            numcode[i]=changechartocode(num[i]);
        }
        display(numcode,8);
    }
}
void uart() interrupt 4 //串口通信中断函数
{
	if(RI)
	{
		RI=0;
		UserScan[n]=SBUF;//读取接收到的数据
		if(UserScan[0]=='+'&&UserScan[1]!='S')
        n++;
		else n=0;
		if(n==18)
		{
            for(c=0;c<8;c++)
            {
                num[c]=UserScan[10+c];
            }
            //ESP8266_SendData(UserScan);
            n=0;
		}			
	}	
}