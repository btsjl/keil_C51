#include "../MyHeadFile/shixun.h"
void main()
{
    u8 key;
    External_Interrupt_0();
    External_Interrupt_1();
    Timer_Interrupt_0_1();
    while(1)
    {
        u8 i=0;
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