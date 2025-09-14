#include <LPC21xx.h>

#define led 0xff
#define rs (1 << 9)
#define e (1 << 8)
#define sw 10

void harddelay(int ms);
void init(void);
void cmd(unsigned char cmd_val);
void data(unsigned char da);
int swit(int sw_pin);

int __main(void) {
    /* All variables must be declared at the top in C89 */
    int count;
    int last_switch_state;
    int current_switch_state;
    
    /* Initialize variables */
    count = 0;
    last_switch_state = 0;
    current_switch_state = 0;
    
    init();
    cmd(0x80); /* Set cursor to beginning */
    
    while (1) {
        current_switch_state = swit(sw);
        
        /* Detect switch press (rising edge detection) */
        if (current_switch_state && !last_switch_state) {
            count++;
            if (count > 4) 
                count = 1; /* Cycle through 1-4 */
            
            /* Clear display and set cursor */
            cmd(0x01); /* Clear display */
            harddelay(2); /* Wait for clear to complete */
            cmd(0x80); /* Set cursor to beginning */
            
            /* Display character based on count */
            if (count == 1)
                data('a');
            else if (count == 2)
                data('b');
            else if (count == 3)
                data('c');
            else if (count == 4)
                data('d');
        }
        
        last_switch_state = current_switch_state;
        harddelay(10); /* Small delay to prevent excessive polling */
    }
}

/* Initialize LCD and I/O pins */
void init(void) {
    IODIR0 = led | rs | e; /* Set LED, RS, and E pins as outputs */
    
    /* LCD initialization sequence with proper delays */
    harddelay(50); /* Wait for LCD power-on */
    cmd(0x30); /* Function set (8-bit mode) */
    harddelay(5);
    cmd(0x30); /* Function set (8-bit mode) */
    harddelay(1);
    cmd(0x30); /* Function set (8-bit mode) */
    
    cmd(0x38); /* Function set: 8-bit, 2 line, 5x8 dots */
    cmd(0x0c); /* Display on, cursor off, blink off */
    cmd(0x01); /* Clear display */
    harddelay(2); /* Clear command needs extra time */
    cmd(0x06); /* Entry mode: increment cursor, no shift */
}

/* Send command to LCD */
void cmd(unsigned char cmd_val) {
    IOCLR0 = led;      /* Clear all LED pins first */
    IOSET0 = cmd_val;  /* Set command bits */
    IOCLR0 = rs;       /* Clear RS (command mode) */
    
    /* Generate enable pulse */
    IOSET0 = e;        /* Set enable high */
    harddelay(1);      /* Enable pulse width */
    IOCLR0 = e;        /* Set enable low */
    
    harddelay(1);      /* Command execution time */
}

/* Send data to LCD */
void data(unsigned char da) {
    IOCLR0 = led;      /* Clear all LED pins first */
    IOSET0 = da;       /* Set data bits */
    IOSET0 = rs;       /* Set RS (data mode) */
    
    /* Generate enable pulse */
    IOSET0 = e;        /* Set enable high */
    harddelay(1);      /* Enable pulse width */
    IOCLR0 = e;        /* Set enable low */
    
    harddelay(1);      /* Data execution time */
}

/* Fixed hardware delay using Timer0 */
void harddelay(int ms) {
    T0TCR = 0x02;      /* Reset timer */
    T0PR = 15000 - 1;  /* Set prescaler for 1ms at 15MHz */
    T0TC = 0;          /* Clear timer counter */
    T0TCR = 0x01;      /* Start timer */
    
    while (T0TC < ms) {
        /* Wait until timer reaches desired milliseconds */
    }
    
    T0TCR = 0x00;      /* Stop timer */
}

/* Simple switch detection with debouncing */
int swit(int sw_pin) {
    IODIR0 &= ~(1 << sw_pin); /* Configure pin as input */
    
    if (!(IOPIN0 & (1 << sw_pin))) { /* Switch pressed (active low) */
        harddelay(20); /* Simple debounce delay */
        if (!(IOPIN0 & (1 << sw_pin))) { /* Check again */
            return 1; /* Switch is pressed */
        }
    }
    return 0; /* Switch is not pressed */
}
