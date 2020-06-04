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

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char button1;
unsigned char button2;
unsigned char button3;

double myArray[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

unsigned char currNote = 0;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
	TCCR1B = 0x0B;

	OCR1A = 125;
	
	TIMSK1 = 0x02;
	
	TCNT1 = 0;
	
	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
	
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


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

enum NoteStates {init, press, wait} state;

void button(){
	
	button1 = ~(PINA) & 0x01;
	button2 = ~(PINA) & 0x02;
	button3 = ~(PINA) & 0x04;
	
	//transitions
	switch(state){
		case init:
			if(button1){
				state = press;
			}
			break;
		case press:
			state = wait;
			break;
		case wait:
			if(button2){
				state = press;
			}
			else if(button3){
				state = press;
			}
			break;
	}

	//actions
	switch(state){
		case init:
			PWM_on();
			break;
		case press:
			if(button1){
				currNote = 0;
			}
			else if(button2){
				if(currNote < 7){
					++currNote;
				}
				else{}
			}
			else if(button3){
				if(currNote > 0){
					--currNote;
				}
				else{}
			}
			else{}
			set_PWM(myArray[currNote]);
			break;
		case wait:
			break;
	}
}


		

int main(void) {
	
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    state = init;
    
    TimerSet(25);
    TimerOn();
    /* Insert your solution below */
    while (1) {
	
        button();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
