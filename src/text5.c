#include "../MyHeadFile/interrupt.h"
#include "../MyHeadFile/SEG.h"
static u16 i=0;
u8 n;
u8 num[8]={0,0,0,0,0,0,0,0};//用0填充num
void main()
{
    Counter1(); 
    while(1)
    {
        getnum(num,i);//把i的值储存数组

        for (n = 0; n < 8; n++)//把num里的数转化成对应的编码
        {
            num[n]=changenum(num[n]);
        }
        display(num,8);//显示num
    }
    
}


void Counter() interrupt 3
{
    i++;
    TH1=0xFF;
    TL1=0xFF;
}