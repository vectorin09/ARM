#include <lpc21xx.h>
#include "timer.h"
void inti(void);
void cmd(unsigned char);
void data(unsigned char);
#define LCD  (0xFF)
#define RS   (1<<10)
#define E    (1<<11)
#define SW   (1 << 21)  
#define LED  (1 << 23)  


int main() 
{
	unsigned int count=0;
	IODIR0|=LED;
	IODIR0&=~SW;
	while(1)
	{
		if(!(IOPIN0 & SW))
		{
			dimer();
			if(!(IOPIN0 & SW))
					
				   IOCLR0=LED;
		}
		else
		{
			count++;
			IOSET0=LED;
			while(1)
			inti();
			if(count == 1)
			{
				data('a');

			}
			else if(count == 2);
			{
				data('b');
			}
		}
		
		
	}	  
}
void inti(void)
{
	
	IODIR0=LCD|RS|E;            
	cmd(0x01);
	cmd(0x02);
	cmd(0x0c);
	cmd(0x38);
	cmd(0x80);
}			
void cmd(unsigned char s)
{
	IOCLR0=LCD;
	IOSET0=s;
	IOSET0=~RS;
	IOSET0=E;
	dimer();
	IOCLR0=E;
}		   	
void data(unsigned char s)
{
	IOCLR0=LCD;
	IOSET0=s;
	IOSET0=RS;
	IOSET0=E;
	dimer();
	IOCLR0=E;
}


