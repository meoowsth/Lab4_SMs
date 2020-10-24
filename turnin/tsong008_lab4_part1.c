/*	Author:Tinghui Song
 *  Partner(s) Name: none
 *	Lab Section: 24
 *	Assignment: Lab #4  Exercise #1
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
	LED0_Released,
	LED0_Pressed,
	LED1_Released,
	LED1_Pressed
}State;
void Tick(){
	switch(State){//Transitions
		case Start:
			State = LED0_Released;
			break;
		case LED0_Released:
			State = PINA?LED0_Pressed:LED0_Released;
			break;
		case LED0_Pressed:
			State = !PINA?LED1_Released:LED0_Pressed;
			break;
		case LED1_Released:
			State = PINA?LED1_Pressed:LED1_Released;
			break;
		case LED1_Pressed:
			State = !PINA?LED0_Released:LED1_Pressed;
			break;
		default:
			State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions
	
	switch(State){//Actions
		case Start:
			break;
		case LED0_Pressed:
			PORTB = 0x02;
			break;
		case LED1_Pressed:
			PORTB = 0x01;
			break;
		default:
			//printf(“default case reached\n”);
			break;
	}//Actions

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	//unsigned char tempA = 0x00;
	//unsigned char tempB = 0x00;
	PORTB = 0x01;
	State = Start;
    while (1) {
	//tempA = PINA & 0xFF;
	Tick();
    }
    return 1;
}
