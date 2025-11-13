void delay(unsigned int);
void lcd_config(void);
void lcd_cmd(unsigned char cmd);
void data_display(unsigned char data);
void string_display(unsigned char*);

//i2c
void i2c_start(void);
void i2c_write(unsigned char);
unsigned char i2c_noack(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_init(void);

//EEPROM
void data_send(unsigned char,unsigned char,unsigned char);
unsigned char data_read(unsigned char,unsigned char);
