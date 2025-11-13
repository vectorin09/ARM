#include"header.h"
#include<lpc21xx.h>
void i2c_write(unsigned char data)
{
	I2DAT=data;
	I2CONSET=1<<3;
	while(((I2CONSET>>3)&1)==0);
	

}	
void i2c_restart(void)
{
	I2CONSET=1<<5;
	I2CONCLR=1<<3;
	
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR=1<<5;
}
unsigned char i2c_noack(void)
{
	unsigned data;
	I2CONSET=0X00;
	I2CONCLR=1<<3;
	while(((I2CONSET>>3)&1)==0);
	return data;
}
void i2c_stop(void)
{
	I2CONSET=1<<4;
	I2CONCLR=1<<3;

}
void i2c_start(void)
{
	I2CONSET=1<<5;
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR=1<<5;
}
void i2c_init(void)
{
	PINSEL0=1<<4|1<<6;
	I2SCLL=75;
	I2SCLH=75;
	I2CONSET=1<<6;
	
	
}
