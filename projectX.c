#include <lpc21xx.h>

void Ext_interrupt(void)__irq;
void init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void timer(void)
{
	T1PR=7-1;
	T1TCR=0x01;
	while(T1TC<1);
	T1TCR=0x00;

}

int main(void)
{
    unsigned int count = 0;
	timer();

   
    PINSEL1 &= ~(0x03 << 0);   
    PINSEL1 =  (1<< 0);   

    IODIR0 |= 1 << 19;
	

    EXTMODE  = 0x00; 
	
    EXTPOLAR = 0x00;  

    
    VICIntSelect = 0;
    VICVectCntl1 = (1 << 5)|14;
    VICVectAddr1 = (int)Ext_interrupt;
    VICIntEnable = 1 << 14;
	
	init();
	

    while (1)
    {

        count++;
		  // Do background work
    }
}

void Ext_interrupt(void)__irq
{
    // Toggle LED
	int i;
	int j;
	int count=0;
	count++;
	IOSET0=1<<25;
	for(i=1500;i>0;--i);
	for(j=12000;j>0;--j);
	IOCLR0=1<<25;
   	lcd_cmd(0xc0);
	lcd_data(T1PR);
	lcd_cmd(0xcF);
	lcd_data(count);
    EXTINT = 1 << 0;

    VICVectAddr = 0;
}

void lcd_cmd(unsigned char cmd)
{
	IOCLR0=0xFF;
	IOSET0=cmd;
	IOCLR0=1<<9;
	IOSET0=1<<8;
	timer();
	IOCLR0=1<<8;
}
void lcd_data(unsigned char data)
{
	IOCLR0=0xFF;
	IOSET0=data;
	IOSET0=1<<9;
	IOSET0=1<<8;
	timer();
	IOCLR0=1<<8;

}
void init()
{
	IODIR0=1<<9	|(0xFF)|1<<8;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0C);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
