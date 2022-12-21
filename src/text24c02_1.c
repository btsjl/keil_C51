#include "../MyHeadFile/24c02.h"
#define ADDREES 0
u8 num[8]={1,2,3,4,5,6,7,9};
void main()
{
    u8 i=0;
    for(i=0;i<8;i++)
    {
        at24c02_write_one_byte(ADDREES+i,num[i]);
    }
    while(1);
}