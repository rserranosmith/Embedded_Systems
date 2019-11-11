/*
 * Name: Ricardo Serrano-Smith
 *
 * Program name: bit_twiddling.c
 * Date created: 09 November 2019
 * Description:  Creates a sweeping type motion with the LED's. LED's turn off *               when button is pressed.
 * Components:   4 LED's ~ PORTS B0-B3
                 4 220 Ohm Resistors
                 1 Button ~ PORTD7
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

#define TIME_ON 100    // 1 second delay
#define MASK 0b00000000 //All bits are off

int main(void) {
    uint8_t counter = 0;
    uint8_t direction = 0;
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3); //Outputs
    PORTD |= (1 << PORTD7); //Input
    while (1) {
        PORTB &= MASK;  //Turns bits off
        switch(counter) {
            case 0:
                PORTB |= (1 << PORTB0); //Bit 0 turns on
                break;
            case 1:
                PORTB |= (1 << PORTB1); //Bit 1 turns on
                break;
            case 2:
                PORTB |= (1 << PORTB2); //Bit 2 turns on
                break;
            case 3:
                PORTB |= (1 << PORTB3); //Bit 3 turns on
                break;
            default:
                PORTB &= MASK;
        }

        if(counter == 3) {
            direction = -1;
        } else if(counter == 0){
            direction = 1;
        }

        if( (PIND & (1 << PIND7)) == 0) {   //Checks button
            counter = 0;
            PORTB &= ~(1 << PORTB0);    //Turns off the first bit
            direction = 1;
        } else {
            counter += direction;   //controls direction of bits
        }
        _delay_ms(TIME_ON);
    
    }
    return 0;
}