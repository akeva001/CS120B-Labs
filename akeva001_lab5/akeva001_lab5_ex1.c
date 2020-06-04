 /* Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
    Lab Section:
 *	Assignment: Lab 5  Exercise 1
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
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    unsigned char tmp1 = 0x00;
    unsigned char tmpC = 0x00;
    //unsigned char tmpD = 0x00;
    while (1) {
    	tmp1 = ~PINA & 0x0F;

    	switch(tmp1){
    		case 0x00:
    			tmpC = 0x40;
    			break;

    		case 0x01:
    		case 0x02:
    			tmpC = 0x60;
    			break;

    		case 0x03:
    		case 0x04:
    			tmpC = 0x70;
    			break;

    		case 0x05:
    		case 0x06:
    			tmpC = 0x38;
    			break;

    		case 0x07:
    		case 0x08:
    		case 0x09:
    			tmpC = 0x3C;
    			break;

    		case 0x0A:
    		case 0x0B:
    		case 0x0C:
    			tmpC = 0x3E;
    			break;

    		case 0x0D:
    		case 0x0E:
    		case 0x0F:
    			tmpC = 0x3F;
    			break;
    		default:
    			tmpC = 0x40;
    			break;
    	}

      
     
	PORTC = tmpC;

     
    }

    return 1;
}
