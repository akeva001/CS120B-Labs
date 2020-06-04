/*	Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {init, forward, reverse, wait, waitOff} state;
enum flag {true, false} isForward;

unsigned char button;




void buttonPress(){

    button = ~PINA & 0x01;


    switch(state){
  	    case init:
		state = wait;		
		break;

	    case forward:
		if(button){
			state = waitOff;
		}
		else if(!button){
			state = wait;
		}				
		break;

	    case reverse:
		if(button){
			state = waitOff;
		}
		else if(!button){
			state = wait;	
		}
		break;

	    case wait:
		if((PORTC == 0xFF) && button){
			if(isForward == true){
				isForward = false;
			}
			else if(isForward == false){
				isForward = true;
			}
			PORTC = 0x00;			
		}
		else if(isForward && button){
			state = forward;
		}
		else if(!isForward && button){
			state = reverse;
		}
		break;
	    case waitOff:
		if(button){
		}
		else{
			state = wait;
		}

		break; 
            default:
        
	        break;
        }




    switch(state){
	   case init:

		break;
	   case forward:
		if(PORTC == 0x00){
			PORTC = 0x01;
		}
		else{
			PORTC = PORTC + (PORTC >> 1);		
		}
		break;
	   case reverse:
		if(PORTC == 0x00){
			PORTC = 0x80;
		}
		else{
			PORTC = PORTC + (PORTC << 1); 
		}
		break;
	   case wait:
		
		break;

	   case waitOff:

		break;
	   default:
		
		break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */

    PORTC = 0x01;
    state = init;
    isForward = true;   
    while (1) {

        

        buttonPress();


        
    	
    }
     
    return 1;
}
