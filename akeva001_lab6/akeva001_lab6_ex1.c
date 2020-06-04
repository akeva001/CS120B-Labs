/*	Author: akeva001
 *  Partner(s) Name: alex
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

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

enum states {start, light1, light2, light3} state;

void TimerOn(){
   TCCR1B = 0x0B;

   OCR1A = 125;
   
   TIMSK1 = 0x02;

   TCNT1 = 0;

   _avr_timer_cntcurr = _avr_timer_M;

   SREG |= 0x80;
}

void TimerOFF(){
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

void tickFunc(){
   unsigned char tmpC = 0x00;
   
   switch (state){
   case start:
     state = light1;
     break;
   case light1:
     state = light2;
     break;
   case light2:
     state = light3;
     break;
   case light3:
     state = light1;
     break;
   default:
     state = light1;
     break;       
   }
   
   switch (state){
   case start:
     tmpC = 0x00;
     break;
   case light1:
     tmpC = 0x01;
     break;
   case light2:
     tmpC = 0x02;
     break;
   case light3:
     tmpC = 0x04;
     break;
   default:
     tmpC = 0x00;
     break;
   }
   PORTC = tmpC;

}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(125);
    TimerOn();
   
    while(1){
      tickFunc();
      while(!TimerFlag);
      TimerFlag = 0;
    }
    return 1;
}
