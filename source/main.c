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
	Wait,
	Inc,
	Dec,
	Reset
}State;
void Tick();
void Tick(){
	Switch(State){//Transitions
		case Start:
			State = LED0;
			break;
		case LED0:
			State = PA0?LED1:LED0;
			break;
		case LED1:
			State = PA0?LED0:LED1;
			break;
		default:
			State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions
	
	Switch(State){//Actions
	case Start:
		break;
	case LED0:
		PORTB = 0x01
		break;
	case LED1:
		PORTB = 0x02;
		break;
	default:
		//printf(“default case reached\n”);
		break;
	}//Actions

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
	unsigned char tempA = 0x00;
	//unsigned char tempB = 0x00;
	PORTB = 0x01;
	State = Start;
    while (1) {
	tempA = PINA & 0xFF;
	Tick(tempA);
    }
    return 1;
}
