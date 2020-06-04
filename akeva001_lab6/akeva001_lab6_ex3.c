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
unsigned char tmpC = 0x00;

enum states {start, light1, light2, light3, wait, pause, restart} state;

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
    TimerSet(125);
    TimerOn();
    PORTC = 0x07;
    state = start;
    while (1) {


         

        buttonPress();
        while(!TimerFlag);
        TimerFlag = 0;ZZ

        
      
    }
     
    return 1;
}
