/*	Author: aasat003
 *  Partner(s) Name: Alex Kevakian
 *	Lab Section: 022
 *	Assignment: Lab 1 Exercise 1
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
    DDRB = 0xFF; PORTB = 0x00;
    unsigned char LED = 0x00;
    unsigned char Input = 0x00;

    while (1) {
    	Input = PINA & 0x03;
	   if(Input == 0x01) {
		  LED = 0x01;
		  PORTB =  LED;
	   }
	   else{
		  PORTB = 0x00;
   	    }
    }
    
	return 0;
}
