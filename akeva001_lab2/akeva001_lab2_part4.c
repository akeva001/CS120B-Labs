/** Author: aasat003
 ** Partner(s) Name: Alex Kevakian
 ** Lab Section: 002
 ** Assignment: Lab 2 Exercise 4
 ** Exercise Description: [optional - include for your own benefit]
 **       
 ** I acknowledge all content contained herein, excluding template or example
 ** code, is my own original work.
 **/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    unsigned char inA;
    unsigned char inB;
    unsigned char inC;
    unsigned char outD;
    while(1){
	inA = PINA;
	inB = PINB;
	inC = PINC;
	unsigned total = inA + inB + inC;
	unsigned char tmpD = outD;
    	if(inA > 0x8C){
	       outD = 0x01;
    	}
    	if((inA - inC) > 0x50){
    	   outD = outD | 0x02;
    	}
	PORTD = outD;
    }
    return 0;
}
~        
