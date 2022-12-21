#ifndef _24c02_H
#define _24c02_H
#include "./Total.h"
#include "./iic.h"
void at24c02_write_one_byte(u8 addr,u8 dat);//AT24C02指定地址写数据
u8 at24c02_read_one_byte(u8 addr);//AT24C02指定地址读数据
void at24c02_write_one_byte(u8 addr,u8 dat)
{				   	  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//发送写命令	    	  
	iic_wait_ack();	   
    iic_write_byte(addr);	//发送写地址   
	iic_wait_ack(); 	 										  		   
	iic_write_byte(dat);	//发送字节    							   
	iic_wait_ack();  		    	   
    iic_stop();				//产生一个停止条件
	delay_ms(10);	 
}

u8 at24c02_read_one_byte(u8 addr)
{				  
	u8 temp=0;		  	    																 
    iic_start();  
	iic_write_byte(0XA0);	//发送写命令	   
	iic_wait_ack(); 
    iic_write_byte(addr); 	//发送写地址  
	iic_wait_ack();	    
	iic_start();  	 	   
	iic_write_byte(0XA1); 	//进入接收模式         			   
	iic_wait_ack();	 
    temp=iic_read_byte(0);	//读取字节		   
    iic_stop();				//产生一个停止条件    
	return temp;			//返回读取的数据
}
#endif