#include "../MyHeadFile/SEG.h"
#include "../MyHeadFile/Button.h"
u8 num[8]={0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40};
u8 n=-1;
u8 key;

void main()
{
    while(1)
    {
        key=key_matrix_flip_scan();
        if(key!=0)
        {
            n++;
            num[n]=gsmg_code[key-1];
            changenum(num[n]);
        }
        display(num,8);
    }
}