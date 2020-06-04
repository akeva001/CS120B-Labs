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
unsigned char comp_val = (char)((0x03F8) / 10);

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00; // just need upper nibble
	ADC_init();

    /* Insert your solution below */
    while (1) {
	conv_val = ADC;	
        if(conv_val <= (comp_val * 1)){
		PORTC = 0x00; 
	}
	else if(conv_val <=(comp_val * 2) + 0xF0 ){
		PORTC = 0x01;
	}
	else if(conv_val <= (comp_val * 2) + 20 ){
		PORTC = 0x03;
	}
	else if(conv_val <= comp_val * 3){
		PORTC = 0x07;
	}
	else if(conv_val <= comp_val * 4){
		PORTC = 0x0F;
	}
	else if(conv_val <= comp_val * 5){
		PORTC = 0x1F;
	}
	else if(conv_val <= comp_val * 6){
		PORTC = 0x3F;
	}
	else if(conv_val <= comp_val * 7){
		PORTC = 0x7F;
	}		
	else{
		PORTC = 0xFF;
	}
	}
    return 1;
}
