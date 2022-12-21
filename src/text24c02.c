#include "../MyHeadFile/24c02.h"
#include "../MyHeadFile/SEG.h"
#define ADDREES 0
u8 num[8]={16,16,16,16,16,16,16,16};
u8 numcode[8];
void main()
{
    u8 i=0;
    for(i=0;i<8;i++)
    {
        num[i]=at24c02_read_one_byte(ADDREES+i);
    }
    while(1)
    {
        for(i=0;i<8;i++)
        {
            numcode[i]=changenum(num[i]);
        }
        display(numcode,8);
    }
}