/*	Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, led0_on, led1_on} state;

unsigned char button;
unsigned char led = 0x00;

void buttonPress(){

    switch(state){

            case start:
                state = led0_on;
                break;

            case led0_on:
                if((button & 0x01) == 0x01){
                    state = led1_on;
                }
                else{
                    state = led0_on;
                }

                break;

            case led1_on:
                if((button & 0x01) == 0x01){
                    state = led0_on;
                }
                
                else{
                    state = led1_on;
                }
                break;

            default:
                state = start;
                break;
        }

    switch(state){
        case start:
            break;

        case led0_on:
            led = led | (0x01 << 0);
            led = led & ~(0x01 << 1);
            break;

        case led1_on:
            led = led | (0x01 << 1);
            led = led & ~(0x01 << 0);
            break;

        default:
            break;

    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    state = start;

    while (1) {
    	
        button = PINA;
        buttonPress();
        PORTB = led;
    	
    }
     
    return 1;
}
