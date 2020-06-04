/*	Author: akeva001
 *  Partner(s) Name: alex
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){

	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short conv_val = 0x00;
unsigned char tmpD = 0x00;
unsigned short MAX = 0x01F3;

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00; // just need upper nibble
	
	ADC_init();

    /* Insert your solution below */
    while (1) {
	conv_val = ADC;	
	if(conv_val >= MAX/2){
		PORTC = 0x00;
	}
	else if(conv_val < MAX/2){
		PORTC = 0x80;
	}
    }
    return 1;
}
