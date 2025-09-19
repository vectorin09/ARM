#include <lpc21xx.h>
#include "timer.h"
#define SW   14  
#define LED  1<<18  

int main() 
{
  	unsigned int count=0;
	IODIR0=LED;
	IOSET0=LED;
	init();
	while(1)
	{	tyc:
		if((((IOPIN0>>SW))&1)==0)
		{
		dimer(200);
		count++;
		IOCLR0=LED;
		while((((IOPIN0>>SW))&1)==0);
		goto label;	
		}

     if(count==0)
		{
			IOSET0=LED;	
			
		}
	}
	label:
		if(count == 1)
		{
				dimer(1000);
				 data('b');
				dimer(1000);

		}
		if(count == 2)
		{
		        count=0;
		        cmd(0x01);	
				dimer(1000);
				data('a');	
				dimer(1000);
		}
		goto tyc;
			  
 }

//// for timer file/////










#define LCD  0xff
#define RS   1<<8
#define E    1<<9
void init(void);
void cmd(unsigned char);
void data(unsigned char);
void dimer(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
		T0TCR=0x03;
		T0TCR=0x00;
}
void init(void)
{
	
	IODIR0=LCD|RS|E;           
	cmd(0x01);
	cmd(0x02);
	cmd(0x0c);
	cmd(0x28);
	cmd(0x80);
}
void cmd(unsigned char s)
{
	IOCLR0=LCD;
	IOSET0=s;
	IOCLR0=RS;
	IOSET0=E;
	dimer(2);
	IOCLR0=E;
}
void data(unsigned char s)
{
	IOCLR0=LCD;
	IOSET0=s;
	IOSET0=RS;
	IOSET0=E;
	dimer(2);
	IOCLR0=E;
}







