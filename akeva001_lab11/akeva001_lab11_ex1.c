#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include <stdio.h>
#include "io.h"
#include "keypad.h"
#include "scheduler.h"

enum states{LEDS};
unsigned char tmpD = 0x00;

int tick(int state){
	unsigned char x;
	x = GetKeypadKey();
	switch(state){
		case LEDS:
			switch(x){
				case '\0': tmpD = 0x1F; break;
				case '1': tmpD = 0x01; break;
				case '2': tmpD = 0x02; break;
				case '3': tmpD = 0x03; break;
				case '4': tmpD = 0x04; break;
				case '5': tmpD = 0x05; break;
				case '6': tmpD = 0x06; break;
				case '7': tmpD = 0x07; break;
				case '8': tmpD = 0x08; break;
				case '9': tmpD = 0x09; break;
				case 'A': tmpD = 0x0A; break;
				case 'B': tmpD = 0x0B; break;
				case 'C': tmpD = 0x0C; break;
				case 'D': tmpD = 0x0D; break;
				case '#': tmpD = 0x0F; break;
				case '0': tmpD = 0x00; break;
				case '*': tmpD = 0x0E; break;
				default: tmpD = 0x1B; break;
			}
			state = LEDS;
			PORTD = tmpD;
			break;
	}
	return state;
}



int main(void){
	DDRA = 0xF0; PORTA = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick;
	
	unsigned long GCD = tasks[0]->period;
	int j;
	for(j = 1; j < numTasks; ++j){
		GCD = findGCD(GCD,tasks[j]->period);
	}
	
	
	TimerSet(GCD);
	TimerOn();
	
	unsigned short i;
	while(1){
		for(i = 0; i < numTasks; i++){
			if(tasks[i]->elapsedTime == tasks[i]->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += GCD;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
	
}	
	
