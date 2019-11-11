/* On a Mac, run screen /dev/cu.usbmodem* in terminal window as your serial monitor.
   This will disable PD0 and PD1 as they are used for serial communication.
   NOTE: To end a screen session, type Ctrl+a followed by k. */ 

/*
 * Name: Ricardo Serrano-Smith
 *
 * Program name: ultrasonicV2.c
 * Date created: 09 November 2019
 * Description:  Uses an ultrasonic sensor to measure the distance of an 
 *               object (in centimeters).
 * Components:   1 LED ~ (PortB3) | Optional
                 1 220-Ohm resistor | Optional
                 1 HC-SR04 Ultrasonic Sensor
                    -Trigger (PORTB1)
                    -ECHO (PORTD2)
 * Target device: Arduino UNO (ATMEGA 328p U)
 * Tool version: 64-Bit
 * Dependencies: None
 *
 *
 * Revisions: None
 *
 *
 */

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
    PORTD |= (1 << PORTD2); //Input (Echo)
    
    USART_Init();		//Initiates USART
	printf("Welcome \n\r");
    int0_init();
    
    sei();

    while(1) {
        switch(echo_flag) {
            case 0: //Send pulse
                if(!launched) { //Only sends pulse once
                    PORTB |= (1 << PORTB1); //Send Pulse
                    _delay_us(10); //wait 10 us 
                    PORTB &= ~(1 << PORTB1);
                    launched = 1; // Update that pulse was sent
                }
                break;

            case 1: //Set timer
                if(launched) {  //Makes sure that pulse was sent
                    TCNT0 = 0;  //clears counter
                    timer0_init(); //Starts timer
                    launched = 0; //resets state 0
                }
                break;

            case 2: //read timer
                TCCR0B &= ~(1 << CS01); // Stops timer
                remainder = TCNT0;  //Obtains current count

                distance = convert(count,remainder); //Converts
                printf("Distance: %u cm\n\r", distance);

                PORTB |= (1 << PORTB3); //Blinks LED
                _delay_ms(100);
                PORTB &= ~(1 << PORTB3);
                _delay_ms(300);
    
                echo_flag = 0;  //Resets flag & count
                count = 0;
                break;

            default: //Blinks slowly
                PORTB |= (1 << PORTB3);
                _delay_ms(1000);
                PORTB &= ~(1 << PORTB3);
                _delay_ms(1000);
                break;
        }
    }
    return 0;
}

uint8_t convert(uint16_t count, uint8_t remainder) {
    uint16_t total = (count * 255) + remainder;
    return ((total*35)/4096); // Refer to README.md
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
    if((PIND & (1 << PIND2))) { //Checks if pin is high
        echo_flag = 1;  //Enter Case 1
    } else  //pins is low
        echo_flag = 2; //Enter Case 2
}