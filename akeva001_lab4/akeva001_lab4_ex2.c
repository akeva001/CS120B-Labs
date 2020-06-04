/*	Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, wait, increment, decrement, reset} state;

unsigned char button1;
unsigned char button2;
unsigned char tmpC = 0x00;



void buttonPress(){

    button1 = PINA & 0x01;
    button2 = PINA & 0x02;


    switch(state){
            case start:
                state = wait;       
                break;
            case wait:

                if(button1 && !button2){
                    state = increment;
                }
                else if(!button1 && button2){
                    state = decrement;
                }
                else if(button1 && button2){
                    state = reset;
                }
                else{

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
                state = start;
                break;
        }




    switch(state){
        case start:
            break;
        case wait:
            
            break;
        case increment:
            if(tmpC < 0x09){
                tmpC = tmpC + 1;
            }

            break;
        case decrement:
            if(tmpC > 0x00){
                tmpC = tmpC - 1;
            }
            break;
        case reset:
            tmpC = 0x00;
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

    tmpC = 0x07;

    while (1) {

        

        buttonPress();

        PORTC = tmpC;

        
    	
    }
     
    return 1;
}
