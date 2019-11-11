/* On a Mac, run screen /dev/cu.usbmodem* in terminal window as your serial monitor.
   This will disable PD0 and PD1 as they are used for serial communication.
   NOTE: To end a screen session, type Ctrl+a followed by k. */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USARTE85.h"
#include "ioE85.h"      // tiny_printf as well as some reading


void init_counter1(void);
uint16_t conversion(uint16_t);

volatile uint8_t count_flag = 0;


int main(void) {

    uint16_t distance = 0;
    uint16_t count = 0;
    DDRB |= (1 << DDB1); //Output (Trigger)
    DDRB |= (1 << DDB3); //Output (LED)
    PORTB |= (1 << PORTB4); //Input (Button)
    PORTB |= (1 << PORTB0); //Input (Echo)
    
    USART_Init();		//Initiates USART
	printf("Welcome \n\r");

    sei();
    
    while(1) {
        
        
        PORTB |= (1 << PORTB1); //Trigger
        _delay_us(10);
        PORTB &= ~(1 << PORTB1);
        
        init_counter1();
        if(count_flag) {
            TCCR1B &= ~(1 << CS11); // clk/8 prescaler (pg.137);
            count = ICR1;
            PORTB |= (1 << PORTB3); // Turn on LED
            distance = count;
            printf("Distance:%u\n", distance);
            _delay_ms(100);
            PORTB &= ~(1 << PORTB3);

            //count = 0;
            count_flag = 0;
        }
    }
   return 0; 
}

void init_counter1(void) {
    
    TCCR1B |= (1 << CS11); // clk/8 prescaler (pg.137);
}

ISR (TIMER1_CAPT_vect) { //PB0
    count_flag = 1; //Value of count (pg.136)
            //TCNT1 (pg.116)
            //ICR1
}


uint16_t conversion(uint16_t count) {
    return ((count));
}