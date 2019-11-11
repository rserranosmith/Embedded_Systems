/* On a Mac, run screen /dev/cu.usbmodem* in terminal window as your serial monitor.
   This will disable PD0 and PD1 as they are used for serial communication.
   NOTE: To end a screen session, type Ctrl+a followed by k. */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USARTE85.h"
#include "ioE85.h"      // tiny_printf as well as some reading


void timer0_init(void);
void int0_init(void);
uint8_t convert(uint16_t, uint8_t);

volatile uint16_t count = 0;
volatile uint8_t echo_flag = 0;

int main(void) {

    uint16_t distance = 0;
    uint16_t remainder = 0;
    uint8_t launched = 0;

    DDRB |= (1 << DDB1); //Output (Trigger)
    DDRB |= (1 << DDB3); //Output (LED)
    PORTB |= (1 << PORTB4); //Input (Button)
    PORTD |= (1 << PORTD2); //Input (Echo)
    
    USART_Init();		//Initiates USART
	printf("Welcome \n\r");
    int0_init();
    timer0_init();
    sei();

    while(1) {
        switch(echo_flag) {
            case 0:
                if(!launched) {
                    PORTB |= (1 << PORTB1); //Send Pulse
                    _delay_us(10);
                    PORTB &= ~(1 << PORTB1);
                    launched = 1;
                }
                break;

            case 1:
                if(launched) {
                    TCNT0 = 0;
                    count = 0;
                    launched = 0;
                }
                break;

            case 2:
                remainder = TCNT0;
                distance = convert(count,remainder);
                printf("Distance: %u cm\n\r", distance);

                PORTB |= (1 << PORTB3);
                _delay_ms(100);
                PORTB &= ~(1 << PORTB3);
                _delay_ms(300);
    
                echo_flag = 0;
                count = 0;
                break;

            default:
                PORTB |= (1 << PORTB3);
                _delay_ms(100);
                PORTB &= ~(1 << PORTB3);
                _delay_ms(100);
                break;
        }
    }
    return 0;
}

uint8_t convert(uint16_t count, uint8_t remainder) {
    uint16_t total = (count * 255) + remainder;
    total = total / 4;
    return ((total*35)/1024); // 343(m/s)*100(cm/m)*10^-6(s/us) approximation
}

void timer0_init(void) {
    TIMSK0 |= (1 << TOIE0); //Sets overflow flag
    TCCR0B |= (1 << CS01); // clk/8
}

void int0_init(void) {
    EICRA |= (1 << ISC00);  //Any Logical Change
    EIMSK |= (1 << INT0); // Activated interrupt
}

ISR (TIMER0_OVF_vect) {
    count++;
}

ISR (INT0_vect) {
    if((PIND & (1 << PIND2))) {
        echo_flag = 1;
    } else
        echo_flag = 2;
}