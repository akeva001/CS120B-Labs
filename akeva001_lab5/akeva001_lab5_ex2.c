/*	Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, press, wait, increment, decrement, reset} state;

unsigned char button1;
unsigned char button2;



void buttonPress(){

    button1 = ~PINA & 0x01;
    button2 = ~PINA & 0x02;


    switch(state){
            case start:
                state = wait;       
                break;
	    case press:
		if(button1 && !button2){
			state = increment;
			break;
		}
		else if(!button1 && button2){
			state = decrement;
			break;
		}

		else if(button1 && button2){
			state = reset; 
			break;	
		}

		else{
		}	
            case wait:

                if((button1 && !button2)||(!button1 && button2)){
                    break;
                }
                
                else if(button1 && button2){
                    state = reset; break;
                }
                else{
               	    state = press; break;
		}
                
                break;
            case increment:

                state = wait;
                
                break;
            case decrement:
                state = wait;
                
                break;
            case reset:
                state = wait;
                break;
            default:
                break;
        }




    switch(state){
        case start:
            break;
        case press:
	    break;
	case wait:
            
            break;
        case increment:
            if(PORTC < 0x09){
                PORTC = PORTC + 0x01; break;
            }

            break;
        case decrement:
            if(PORTC > 0x00){
                PORTC = PORTC - 0x01;
            }
            break;
        case reset:
            PORTC = 0x00;
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

    PORTC = 0x07;
    state = start;
    while (1) {

        

        buttonPress();


        
    	
    }
     
    return 1;
}
