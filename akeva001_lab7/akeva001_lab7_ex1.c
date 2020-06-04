/*    Author: akeva001
 *  Partner(s) Name: Alec
 *    Lab Section:
 *    Assignment: Lab #  Exercise #
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char button1;
unsigned char button2;
unsigned long counter;
unsigned char displayNum = 0x00;

enum States {init, wait, increment, decrement, reset, release} state;

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

void tick(){
  
  
  button1 = ~PINA & 0x01;
  button2 = ~PINA & 0x02;
  //Transitions
  switch(state){
     
    case init:
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
      break;
    case increment:
      if(button1 && button2){
	state = reset;
      }
      else if(button1 && !button2){
       
      }
      else{
	state = release;
      }
      break;
    case decrement:
      if(button1 && button2){
	state = reset;
      }
      else if(!button1 && button2){
	
      }
      else{
	state = release;
      }
      break;
    case reset:
      state = release;
      break;
    case release:
      if(!button1 && !button2){
	state = wait;
      }
      break;
    default:
      state = init;
      break;
}
  
  //States 
  switch(state){

    case init:
      counter = 0;
      break;
    case wait:
      counter = 0;
      break;
    case increment:
      if(displayNum < 0x09 && counter == 0){
	 displayNum = displayNum + 0x01;
	 LCD_Cursor(1);
	 LCD_WriteData(displayNum + '0');
      }
	
      if(displayNum < 0x09 && counter == 1500){
	 displayNum = displayNum + 0x01;
	 LCD_Cursor(1);
         LCD_WriteData(displayNum  + '0');
	 counter = 1;
      }

      counter++;
      break;
    case decrement:
      if(displayNum > 0x00 && counter == 0){
	 displayNum = displayNum - 0x01;
         LCD_Cursor(1);
         LCD_WriteData(displayNum  + '0');
      }
      if(displayNum > 0x00 && counter == 1500){
	 displayNum = displayNum - 0x01;
	 LCD_Cursor(1);
	 LCD_WriteData(displayNum + '0');
	 counter = 1;
      }
      counter++;
      break;
    case reset:
      displayNum = 0x00;
      LCD_Cursor(1);
      LCD_WriteData(displayNum + '0');
     
      break;
    case release:
      break;
    default:
      break;
  }
}

int main(void){
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;


  TimerSet(80);
  TimerOn();

  LCD_init();
  LCD_Cursor(1);
  LCD_WriteData('0');

  state = init;

  while(1){
     tick();
    
    
    while(!TimerFlag)
    {
	TimerFlag = 0;
	}
   
  }

}
