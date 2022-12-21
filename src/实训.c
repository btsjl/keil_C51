#include "../MyHeadFile/shixun.h"
void main()
{
    u8 key;
    u8 i=0;
    External_Interrupt_0();
    External_Interrupt_1();
    Timer_Interrupt_0_1();
    UART_Init(byt);
	delay_ms(1000);
	ESP8266_SendCmd("AT+CIPMUX=1");
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");
    ES=1;
    for(i=0;i<8;i++)
    {
        passwd[i]=at24c02_read_one_byte(ADDREES+i);
    }
    while(1)
    {
       
        for(i=0;i<8;i++)
        {
            scanpasswdcode[i]=changenum(scanpasswd[i]);
        }
        display(scanpasswdcode,8);
        key=key_matrix_ranks_scan_2();
        if(key<10&&n!=7)
        {
            n++;
            scanpasswd[n]=key;
        }
        if(n==7)
        {
            flag=check();
            if(flag)
            {
                while(flag_2)
                {
                    LED=0;
                    PassOrLock[0]=0x73;
                    display(PassOrLock,2);
                }
            }
            else
            {
                while(flag_2)
                {
                    PassOrLock[0]=0x38;
                    display(PassOrLock,2);
                    if(flag_1>=3&&flag==0)
                    {
                        flag_3=flag_1;
                        ET0=1;
                        TR0=1;
                        break;
                    }
                }
                while(flag_2)
                {
                    PassOrLock[0]=0x38;
                    display(PassOrLock,2);
                }
            }
            n=-1;
        }
        
        
    }
}
void extend_0() interrupt 0
{
    u8 z=0;
    flag_2=0;
    LED=1;
    for(z=0;z<8;z++)
    {
        scanpasswd[z]=16;
    }
    n=-1;
}
void extend_1() interrupt 2
{
    scanpasswd[n]=16;
    if(n>=0)
    n--;
    else
    n=-1;
}
void Timer() interrupt 1
{
    static int t=0;
    t++;
    EX0=0;
    EX1=0;
    TH0=0xfc;
    TL0=0x18;
    if(t==2000)
    {
        t=0;
        flag_3--;
    }
    if(flag_3==0)
    {
        EX0=1;
        EX1=1;
        n=-1;
        ET0=0;
    }
    
}
void uart() interrupt 4 //串口通信中断函数
{
	if(RI)
	{
		RI=0;
		UserScan[n_0]=SBUF;//读取接收到的数据
		if(UserScan[0]=='+')
        {
            n_0++;
            if(UserScan[n_0-2]=='#'&&UserScan[n_0-1]=='r'&&(EX0==1)&&(EX1==1))
            {
                u8 i=0;
                flag_2=0;
                n=-1;
                n_0=0;
                for(i=0;i<8;i++)
                {
                    scanpasswd[i]=16;
                }
            }
        }
		else 
        n_0=0;
		if(n_0==20)
		{
            if(UserScan[1]=='I'&&UserScan[7]=='1'&&UserScan[8]=='0')
            {
                if(UserScan[10]=='#'&&UserScan[11]=='s')
                {
					u8 c=0;
                    for(c=0;c<8;c++)
                    {
                        scanpasswd[c]=changechartonum(UserScan[12+c]);
						n=7;
                    }
                }
                if(UserScan[10]=='#'&&UserScan[11]=='c')
                {
					u8 i=0;
                    for(i=0;i<8;i++)
                    {
                        at24c02_write_one_byte(ADDREES+i,changechartonum(UserScan[12+i]));
                        passwd[i]=changechartonum(UserScan[12+i]);
                    }
                }
            }
            n_0=0;
		}			
	}	
}