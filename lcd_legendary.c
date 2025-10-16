#include<lpc21xx.h>
#define data_path 0xFF<<0
#define rs 1<<9
#define en 1<<8
void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=data_path;
	IOSET0=cmd;
	IOCLR0=rs;
	IOSET0=en ;
	delay_ms(5);
	IOCLR0=en;
}
void lcd_data(unsigned char data)
{
	IOCLR0=data_path;
	IOSET0=data;
	IOSET0=rs;
	IOSET0=en;
	delay_ms(5);
	IOCLR0=en;
}
void lcd_scroll(char *msg) {
    char scroll_buf[80];  // buffer to hold padded message
    int i, j, len = 0;

    // Step 1: Get length of message
    while(msg[len] != '\0') len++;

    // Step 2: Add 16 leading spaces (message starts off-screen)
    for(i = 0; i < 16; i++) {
        scroll_buf[i] = ' ';
    }

    // Step 3: Copy the message after the spaces
    for(j = 0; j < len; j++) {
        scroll_buf[i + j] = msg[j];
    }

    // Step 4: Add trailing spaces to clear screen after message scrolls out
    for(j = 0; j < 16; j++) {
        scroll_buf[i + len + j] = ' ';
    }

    scroll_buf[i + len + j] = '\0';  // null terminate

    // Step 5: Scroll from right to left
    while(1) {
        for(i = 0; scroll_buf[i + 15] != '\0'; i++) {
            lcd_cmd(0x80); // Line 1 start
            for(j = 0; j < 16; j++)
			 {
                lcd_data(scroll_buf[i+j]);  // Show 16 chars from current offset
            }
            delay_ms(1000); // Adjust for scroll speed
        }
    }
}
void lcd_string(unsigned char *sr)
{
	while(*sr)
	{
		lcd_data(*sr);
		sr++;
	}
}
void lcd_scroll_with_shift(unsigned char *msg) {
    lcd_cmd(0x01);      // Clear screen
    lcd_cmd(0x06);      // Entry mode: move cursor right
    lcd_cmd(0x80);      // Set cursor to line 1, position 0

    lcd_string(msg);    // Write full message (will overflow)

    delay_ms(500);         // Pause before starting scroll

    // Now shift left one step at a time
    while(1) {
        lcd_cmd(0x18);  // Command to shift display left
        delay_ms(300);     // Adjust scroll speed
    }
}




void lcd_conf(void)
{
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
}
int main()
{

	IODIR0=data_path|rs|en;

	lcd_conf();
	lcd_scroll_with_shift("HAPPY DIWALI FROM VECTOR INDIA");			
	

		
	
}
