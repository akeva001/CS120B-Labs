/*	Author: Alex Kevakian
 *  Partner(s) Name: Alec Asatoorian
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

enum L_States{L_Start, L_WaitSharp, L_WaitY, L_Unlock, L_Lock} L_States;

unsigned char button0;
unsigned char button1;
unsigned char button2;
unsigned char lock_button;

void House_Lock() {
  button0 = PINA & 0x01;
  button1 = PINA & 0x02;
  button2 = PINA & 0x04;
  lock_button = PINA & 0x80;
  switch(L_States){
    case L_Start:
        L_States = L_WaitSharp;
      break;

    case L_WaitSharp:
      if(!button0 && !button1 && button2){
        L_States = L_WaitY;
      }
      break;

    case L_WaitY:
      if(button1 && !button0 && !button2){
        L_States = L_Unlock;
      }
      break;

    case L_Unlock:
      if(lock_button){
        L_States = L_Lock;
      }
      break;

    case L_Lock:
      L_States = L_WaitSharp;
      break;
  }

  switch(L_States){
     case L_Start:
       break;
    
     case L_WaitSharp:
       break;

     case L_WaitY:   
       break;
       
    case L_Unlock:
    PORTB = 0x01;
    break;
     case L_Lock:
       PORTB = 0x00;
       break;
  }
  
}

int main(void){
  DDRA = 0x00; PORTA = 0xFF;
  DDRB = 0xFF; PORTB = 0x00;

  while(1){
    
    House_Lock();

  }

  return 1;
}
