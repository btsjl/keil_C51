#include<reg52.h>
#define team P1
sbit key=P3^2;
unsigned int t=0;
unsigned int a=0;
unsigned int msec=0;
unsigned int hour=0;
unsigned int minute=0;
unsigned int second=0;
unsigned int se1=0;
unsigned int se2=0;
unsigned int mi1=0;
unsigned int mi2=0;
unsigned int ho1=0;
unsigned int ho2=0;
unsigned int h=-1;
unsigned int b=-1;
unsigned char led[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//0 1 2
unsigned int shu[8]={0,0,0,0,0,0,0,0};
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
void delay(unsigned int ms)
{
   unsigned int i,j;
   for(i=ms;i>0;i--)
	    for(j=110;j>0;j--);	
}
void chushi(void)
{
	TMOD|=0X10;
	
	IT0=0;
	EX0=1;
	
	ET1=0;
  TR1=0;
	ET0=0;
  TR0=0;
	TH1=0XFC;
	TL1=0X18;
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
	
  ET1=1;
  TR1=1;
	while(key==0);
	}
}

void exti1(void) interrupt 3
{
	a++;
	if(a==100)
	{
		a=0;
		msec++;
	}
	if(msec==10)
	{
		second++;
		msec=0;
	}
	if(second==60)
	{
		minute++;
		second=0;
	}
	if(minute==60)
	{
		hour++;
		minute=0;
	}
	if(hour==24)
	{
		hour=0;
	}
	TH1=0XFC;
	TL1=0X18;
}
void xianshi()
{
  shu[0]=second%10;
	shu[1]=second/10;
	shu[3]=minute%10;
	shu[4]=minute/10;
	shu[6]=hour%10;
	shu[7]=hour/10;
	for(t=0;t<8;t++)
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
		  case 6:
				LSC=1;LSB=1;LSA=0;break;
			case 7:
				LSC=1;LSB=1;LSA=1;break;
		}
		if(t==2||t==5)
		{
			P0=0x40;
		}else{
		P0=led[shu[t]];}
		delay(1);
	}
	
}
void nur()
{
	b=get();
	if(b!=-1&&se1==0)
	{
  second=b;
	se1=1;
	}else if(b!=-1&&se2==0)
	{
		second=b*10+second;
     se2=1;
		
	}else if(b!=-1&&mi1==0)
	{
  minute=b;
	mi1=1;
	}else if(b!=-1&&mi2==0)
	{
  minute=b*10+minute;
	mi2=1;
	}else if(b!=-1&&ho1==0)
	{
  hour=b;
	ho1=1;
	}else if(b!=-1&&ho2==0)
	{
  hour=b*10+hour;
	ho2=1;
	}
  if(second>=60)
	{
		minute=second/60;
		second=second%60;
	}
	if(minute>=60)
	{
		hour=minute/60;
		minute=minute%60;
	}
	if(hour>=24)
	{
		hour=0;
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