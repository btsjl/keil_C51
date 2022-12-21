#include "../MyHeadFile/Total.h"
#include "../MyHeadFile/esp8266.h"
#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/24c02.h"
#define ADDREES 0
u8 byt=0xfA;
static u8 n=0;
u8 UserScan[20];
u8 num[8]={48,48,48,48,48,48,48,48};
u8 passwd[8];
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
		if(UserScan[0]=='+')
        n++;
		else n=0;
		if(n==20)
		{
            if(UserScan[1]=='I'&&UserScan[7]=='1'&&UserScan[8]=='0')
            {
                if(UserScan[10]=='#'&&UserScan[11]=='s')
                {
                    for(c=0;c<8;c++)
                    {
                        num[c]=UserScan[12+c];
                    }
                }
                if(UserScan[10]=='#'&&UserScan[11]=='c')
                {

                    for(i=0;i<8;i++)
                    {
                        at24c02_write_one_byte(ADDREES+i,num[i]);
                    }
                }
            }
            n=0;
		}			
	}	
}