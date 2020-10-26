/*	Author:Tinghui Song
 *  Partner(s) Name: none
 *	Lab Section: 24
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State{
	Start,
	Lock,
	Combo1,
	Combo2,
	Unlock
}State;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	State = Start;
	PORTB = 0x00;
	while (1) {
		Tick();
   	 }
	return 1;
}

void Tick(){
	switch(State){//Transitions
		case Start:
			State = Lock;
			break;
		case Lock:
			if(PINA & 0x04){
				State = Combo1;
			}
			else{
				State = Lock;
			}
			break;
		case Combo1:
			if ( !(PINA & 0x04)){
				State = Combo2;
			}
			else{
				State = Lock;
			}
			break;
		case Combo2:
			if(PINA & 0x02){
				State = Unlock;
			}
			else{
				State = Lock;
			}
			break;
		case Unlock:
			if ( PINA & 0x80){
				State = Lock;
			}
			else{
				State = Unlock;
			}
			break;
		default:
			State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions

	switch(State){//Actions
		case Start:
			break;
		case Lock:
			PORTB = 0x00;
			break;
		case Combo1:
			break;
		case Combo2:
			break;
		case Unlock:
			PORTB = 0x01;
			break;
		default:
			//printf(“default case reached\n”);
			break;
	}//Actions

}
