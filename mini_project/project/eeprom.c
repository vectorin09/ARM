#include"header.h"
#include<lpc21xx.h>
void data_send(unsigned char slave_add,unsigned char word_add,unsigned char data)
{
	i2c_start();
	i2c_write(slave_add);
	i2c_write(word_add);
	i2c_write(data);
	i2c_stop();
	delay(100);
}
unsigned char data_read(unsigned char slave_add,unsigned char word_add)
{
	unsigned char data;
	i2c_start();
	i2c_write((slave_add<<1));
	i2c_write(word_add);
	i2c_restart();
	i2c_write(slave_add<<1|1);
	data=i2c_noack();
	i2c_stop();
	return data;
}
