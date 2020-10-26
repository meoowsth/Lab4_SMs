/*	Author:Tinghui Song
 *  Partner(s) Name: none
 *	Lab Section: 24
 *	Assignment: Lab #4  Exercise #2
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
	Wait,
	Inc,
	Dec,
	Reset
}State;

unsigned char cnt = 0x07;

unsigned char Tick();



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
	//unsigned char tempA = 0x00;
	//unsigned char cnt = 0x07;
	State = Start;
	//PORTC = 0x07;
    while (1) {
	//tempA = PINA & 0xFF;
	Tick();
	
    }
    return 1;
}

unsigned char Tick(){
	//unsigned char PA0 = PINA & 0x01;
	//unsigned char PA1 = PINA & 0x02;
	switch(State){//Transitions
		case Start:
			State = Wait;
			break;
		case Wait:
			if((PINA & 0x01)){
				State = Inc;
			}
			else if ((PINA & 0x02)){
				State = Dec;
			}
			else if ( (!(PINA & 0x01)) && (!(PINA & 0x02))){
				State = Reset;
			}
			else{
				State = Wait;
			}
			break;
		case Inc:
			State = Wait;
			break;
		case Dec:
			State = Wait;
			break;
		case Reset:
			State = Wait;
			break;
		default:
			State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions

	switch(State){//Actions
		case Start:
			break;
		case Wait:
			PORTC = cnt;
			break;
		case Inc:
			if (cnt < 0x09){
				cnt++;
			}
			PORTC = cnt;
			break;
		case Dec:
			if (cnt > 0x00){
				cnt--;
			}
			PORTC = cnt;
			break;
		case Reset:
			cnt = 0x00;
			PORTC = cnt;
			break;
		default:
			//printf(“default case reached\n”);
			break;
	}//Actions
	return cnt;

}
