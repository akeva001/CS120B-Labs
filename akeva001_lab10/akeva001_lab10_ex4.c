/*	Author: akeva001
 *  Partner(s) Name: Alec
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SpeakerSM {start, on, off} SP_States;
enum ThreeLEDSM {init, LED0, LED1, LED2} TL_States;
enum BlinkingLEDSM{_init, _LED3, _LED0} BL_States;
enum CombineLEDSM {__init, __display} CL_States;

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
double speaker = 0;
double octave = 1;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

volatile unsigned char TimerFlag = 0;

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

void Speaker_Tick(){

	//transitions
	switch(SP_States){
		case start:
			SP_States = off;				
			break;
		case on:
			SP_States = off;
			break;
		case off:
			SP_States = on;	
			break;
		default:
			SP_States = off;
			break;		
	}

	//actions
	switch(SP_States){
		case start:
								
			break;
		case on:
			speaker = 0x01;	
			break;
		case off:
			speaker = 0x00;
			break;
		default:
	
			break;
	}
}

void ThreeLED_Tick(){

	//transitions
	switch (TL_States){
		case init:
			TL_States = LED0;
			break;
		case LED0:
			TL_States = LED1;	
			break;
		case LED1:
			TL_States = LED2;
			break;
		case LED2:
			TL_States = LED0;
			break;
		default:
			TL_States = init;
			break;
	}
	
	//actions
	switch (TL_States){
		case init:
			break;
		case LED0:
			threeLEDs = 0x01;		
			break;
		case LED1:
			threeLEDs = 0x02;
			break;
		case LED2:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}

}

void BlinkingLED_Tick(){
	
	//transitions
	switch (BL_States){
		case _init:
			BL_States = _LED3;
			break;
		case _LED3:
			BL_States = _LED0;
			break;
		case _LED0:
			BL_States = _LED3;
			break;
		default:
			BL_States = init;
			break; 
	}

	//actions
	switch (BL_States){
		case _init:	
			break;
		case _LED3:
			blinkingLED = 0x08;
			break;
		case _LED0:
			blinkingLED = 0x01;
			break;
		default:
			break;
	}
}


void CombineLED_Tick(){
	
	//transitions
	switch (CL_States){
		case __init:
			CL_States = __display;
			break;
		case __display:
			CL_States = __display;
			break;
		default:
			CL_States = __init;
			break;
	}

	//actions
	switch (CL_States){
		case __init:
			break;
		case __display:
			PORTC = blinkingLED | threeLEDs;
			break;
		default:
			break; 
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    TimerSet(1);
    TimerOn();

    unsigned long i = 0;
    unsigned long j = 0;
    unsigned long k = 0;
    while (1) {
	
	if(i == 300){
		ThreeLED_Tick();
		i = 0;
	}
	if(j == 1000){
		BlinkingLED_Tick();
		j = 0;
	}
	if(k == 2){
		if(~PINA & 0x01){
			Speaker_Tick();
		}
		k = 0;
	}
	CombineLED_Tick();

	if((~PINA & 0x02) && !(~PINA & 0x04)){
		octave += 0.5;
	}
	else if(!(~PINA & 0x02) && (~PINA & 0x04)){
		octave -= 0.5;
	}
	PORTD = speaker * octave;
		

	++i;
	++j;
	++k;
		
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
