#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Button.h"
u8 num[8]={0x7d,0x40,0x40,0x40,0x40,0x40,0x40,0x40};
u8 k=16;
void main()
{
    while(1)
    {
        k=keyscan();
        if(k!=16)
        {
            num[0]=code_seg[k];
        }
        display(num,1);
    }
}