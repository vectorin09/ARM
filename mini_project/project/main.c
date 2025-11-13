#include<lpc21xx.h>
#include"header.h"
#define swt 1<<20
#define input 1<<29
#define sensor 1<<16
__irq void ext1(void)
{
	EXTINT=(1<<2);
	
	input=1;
	VICVectAddr=0;
}
__irq void ext2(void)
{
	EXTINT=(1<<3);
	VICVectAddr=0;
}

int main()
{
	PINSEL1=1<<0|3<<8;
	EXTMODE|=(1<<1)|(1<<3);
	EXTPOLAR&=(1<<2)|(1<<3);
	VICIntEnable|=(1<<16)|(1<<17);
	VICVectAddr0=ext1;
	VICVectCntl0=((1<<5)|16);
	
	VICVectAddr0=ext2;
	VICVectCntl1=(1<<5)|17;
	
	IODIR0=input|swt;
	i2c_init();
	lcd_config();
	while(1)
	{
		if(input== 1)
		{
			string_display("LED ON....");
		}
		else
		{
			string_display("LED OFF...");
		}
	}
}

