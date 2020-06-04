/*	Author: akeva001
 *  Partner(s) Name: 
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

double note_C4 = 261.63;
double note_D4 = 293.66;
double note_E4 = 329.63;

unsigned char button1;



void set_PWM(double frequency){
	static double current_frequency;
	
	if(frequency != current_frequency){
		if(!frequency){
			TCCR3B &= 0x08;
		}
		else{
			TCCR3B |= 0x03;
		}

		if(frequency < 0.954){
			OCR3A = 0xFFFF;
		}

		else if(frequency > 31250){
			OCR3A = 0x0000;
		}

		else {
			OCR3A = (short) (8000000 / (128 * frequency)) - 1;
		}

		TCNT3 = 0;
		current_frequency = frequency;

	}	
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);

	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off(){

	TCCR3A = 0x00;

	TCCR3B = 0x00;
}

enum NoteStates {init, noteOn, noteOff} state;

void button(){
	
	button1 = ~(PINA) & 0x07;
	
	//transitions
	switch(state){
		case init:
			state = noteOff;
			break;
		case noteOn:
	        if(!button1){
				state = noteOff;
			}
			break;
		case noteOff:
			if(button1){
				state = noteOn;
			}
			break;
		default:
			state = init;
			break;
	}

	//actions
	switch(state){
		case init:
			PWM_on();
			break;
		case noteOn:
		

			if(button1 == 0x01){
				set_PWM(note_C4);
			}
			else if(button1 == 0x02){
				set_PWM(note_D4);
			}
			else if(button1 == 0x04){
				set_PWM(note_E4);
			}
			else{
			
			}
			PORTC = 0x00;
			break;
		case noteOff:
			set_PWM(0);
			PORTC = 0x01;
			break;
		default:
			state = init;
			break;

	}
}


		

int main(void) {
	
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    state = init;
    

    PWM_on();
    /* Insert your solution below */
    while (1) {
		
		/*
		if(~(PINA) & 0x01){
			set_PWM(note_C4);
		}
		else if(~(PINA) & 0x02){
			set_PWM(note_D4);
		}
		else if(~(PINA) & 0x04){
			set_PWM(note_E4);
		}
		else{
			set_PWM(0);
		}*/
        button();
    }
    return 1;
}
