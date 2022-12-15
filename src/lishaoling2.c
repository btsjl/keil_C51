#include<reg52.h>
#define team P1
sbit key=P3^2;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
unsigned int z=0;
unsigned int t=0;
unsigned int a=0;
unsigned int se1=0;
unsigned int se2=0;
unsigned int mi1=0;
unsigned int mi2=0;
unsigned int ho1=0;
unsigned int ho2=0;
unsigned int h=-1;
unsigned int b=-1;
unsigned char led[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//0 1 2
unsigned int shu[6]={0,0,0,0,0,0};

void delay(unsigned int ms)
{
   unsigned int i,j;
   for(i=ms;i>0;i--)
	    for(j=110;j>0;j--);	
}
void chushi(void)
{

	IT0=1;
	EX0=1;
	EA=1;
}
unsigned int get()
{	
  h=-1;
	team=0xef;                  //1
	if(team!=0xef)
	{
		delay(10);
		  switch(team)
			{
				case(0xee):h=-1;break;
				case(0xed):h=-1;break;
				case(0xeb):h=-1;break;
				case(0xe7):h=-1;break;	
			}
		delay(10);	
		while(team!=0xef);
	}

	team=0xdf;                // 2
	if(team!=0xdf)
	{
		delay(10);
		  switch(team)
			{
				case(0xde):h=-1;break;
				case(0xdd):h=-1;break;
				case(0xdb):h=9;break;
				case(0xd7):h=8;break;	
			}
		delay(10);	
		while(team!=0xdf);
	}
	team=0xbf;                 //3
	if(team!=0xbf)
	{
		delay(10);
		  switch(team)
			{
				case(0xbe):h=7;break;
				case(0xbd):h=6;break;
				case(0xbb):h=5;break;
				case(0xb7):h=4;break;	
			}
		delay(10);	
		while(team!=0xbf);
	}
	team=0x7f;                   //4
	if(team!=0x7f)
	{
		delay(10);
		  switch(team)
			{
				case(0x7e):h=3;break;
				case(0x7d):h=2;break;
				case(0x7b):h=1;break;
				case(0x77):h=0;break;	
			}
		delay(10);	
		while(team!=0x7f);
	}
	return h;
}

void exti0(void) interrupt 0
{
	if(key==0)
	{
	shu[0]++;
	while(key==0);
	}
}

void xianshi()
{
 
	for(t=0;t<6;t++)
	{
	 switch(t)
		{
			case 0:
				LSC=0;LSB=0;LSA=0;break;
			case 1:
				LSC=0;LSB=0;LSA=1;break;	
			case 2:
				LSC=0;LSB=1;LSA=0;break;
			case 3:
				LSC=0;LSB=1;LSA=1;break;
			case 4:
				LSC=1;LSB=0;LSA=0;break;
			case 5:
				LSC=1;LSB=0;LSA=1;break;
		
		}
		P0=led[shu[t]];
		delay(2);
	}
	
}
void nur()
{
	b=get();
	if(b!=-1&&se1==0)
	{
  shu[0]=b;
	se1=1;
	}else if(b!=-1&&se2==0)
	{
		shu[1]=b;
     se2=1;
		
	}else if(b!=-1&&mi1==0)
	{
 shu[2]=b;
	mi1=1;
	}else if(b!=-1&&mi2==0)
	{
 shu[3]=b;
	mi2=1;
	}else if(b!=-1&&ho1==0)
	{
  shu[4]=b;
	ho1=1;
	}else if(b!=-1&&ho2==0)
	{
  shu[5]=b;
	ho2=1;
	}
	if(shu[0]>=10)
	{
		shu[0]=0;
		shu[1]++;
	}
	if(shu[1]>=10)
	{
		shu[1]=0;
		shu[2]++;
	}
	if(shu[2]>=10)
	{
		shu[2]=0;
		shu[3]++;
	}
	if(shu[3]>=10)
	{
		shu[3]=0;
		shu[4]++;
	}
	if(shu[4]>=10)
	{
		shu[4]=0;
		shu[5]++;
	}
	if(shu[5]>=10)
	{
		shu[5]=0;
		shu[6]++;
	}
	if(shu[6]>=10)
	{
		for(z=0;z++;z<6)
		{
			shu[z]=0;
		}
	}
}
void main()
{
	chushi();
	
  while(1)
	{
		nur();
		xianshi();
	}
  
}