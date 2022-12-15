#include "../MyHeadFile/interrupt.h"
#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Button.h"
u8 num[8]={0,0,0,0,0,0,0,0};
u8 num1[8]={0,0,0,0,0,0,0,0};
u8 z;
u8 i=0;
u8 n;
int sum=0;
int Sum(u8 *num,u8 len)
{
    int j=0;
    int sum=0;
    for(j=0;j<len;j++)
    {
        sum*=10;
        sum+=num[j];
    }
    return sum;
}
void main()
{
    P0=0;
    while(1)
    {
        z=key_matrix_ranks_scan_1();
        if(z==11)
        break;
        if(z<=9&&z>=0)
        {
        num[i]=z;
        i++;
        }
        if(i==8)
        break;
    }
    sum=Sum(num,i);
    while(1)
    {
        getnum(num,sum);
        for(n=0;n<8;n++)
            num1[n]=changenum(num[n]);
            display(num1,8);
            External_Interrupt_0();
            
    }
}
void Timer() interrupt 0
{
    sum++;
}