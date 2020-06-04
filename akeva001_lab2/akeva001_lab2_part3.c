/*	Author: aasat003
 *  Partner(s) Name: Alex Kevakian
 *	Lab Section: 002
 *	Assignment: Lab 1 Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char cntavail = 0x00;
    
    while (1) {
    	
		unsigned char spot1 = PINA & 0x01;
		unsigned char spot2 = PINA & 0x02;
		unsigned char spot3 = PINA & 0x04;
		unsigned char spot4 = PINA & 0x08;

		spot2 = spot2 >> 1;
		spot3 = spot3 >> 2;
		spot4 = spot4 >> 3;

		cntavail = spot1 + spot2 + spot3 + spot4;

		if(cntavail == 0x04){
			cntavail = cntavail | 0x80;	
		}

		PORTC = cntavail;
	}
    return 0;
}
