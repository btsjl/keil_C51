#include <reg52.h>
#include "../MyHeadFile/Button.h"
void main()
{	
	u8 key=0;
	while(1)
	{
	   	key=key_matrix_ranks_scan();
		if(key!=0)
			SMG_A_DP_PORT=gsmg_code[key-1];//得到的按键值减1换算成数组下标对应0-F段码		
	}		
}