#include"header.h"
#include<lpc21xx.h>

#define data_path 0xFF<<4
#define reset 1<<22
#define enable 1<<21

void delay(unsigned int ms)
{
	
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TC=0;
	T0TCR=0x03;
	T0TCR=0x00;
}

void lcd_cmd(unsigned char cmd)
{
	IOCLR0=data_path|reset|enable;
	IOSET0=cmd;
	IOCLR0=reset;
	IOSET0=enable;
	delay(100);
	IOCLR0=enable;
	IOCLR0=data_path|reset|enable;
}

void data_display(unsigned char argu)
{
	IOCLR0=data_path|reset|enable;
	IOSET0=argu;
	IOSET0=reset;
	IOSET0=enable;
	delay(100);
	IOCLR0=enable;
	IOCLR0=data_path|reset|enable;
 }
void string_display(unsigned char *data)
{
	while(*data)
	{
		data_display(*data++);
	}
}

void lcd_config(void)
{
	IODIR0|=data_path|reset|enable;
	lcd_cmd(0x38);  
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);    
	lcd_cmd(0x80); 
}
