/*	Author: Tinghui Song
 *  Partner(s) Name: none
 *	Lab Section: 24
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



enum States {Start, Wait, Increment, Decrement, Reset} State;

unsigned char cnt = 7; //initial output PORTC

void Tick()
{
    unsigned char tempA = PINA;
    switch(State){ //transitions
        case Start:
            PORTC = cnt;
            State = Wait;
            break;
        case Wait:
            if((tempA & 0x03) == 0x00){
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
                if(cnt < 9)
                {
                    ++cnt;
                    PORTC = cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
                if(cnt > 0){
                    --cnt;
                    PORTC = cnt;
                }
            }
            else{
                State = Reset;
                cnt = 0;
                PORTC = cnt;
            }
            break;
        case Decrement:
            if((tempA & 0x03) == 0x00){
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
                if(cnt < 9){
                    ++cnt;
                    PORTC = cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
            }
            else{
                State = Reset;
                cnt = 0;
                PORTC = cnt;
            }
            break;
        case Increment:
            if((tempA & 0x03) == 0x00){
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
                if(cnt > 0){
                    --cnt;
                    PORTC = cnt;
                }
            }
            else{
                State = Reset;
                cnt = 0;
                PORTC = cnt;
            }
            break;
        case Reset:
            if((tempA & 0x03) == 0x00){
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
                if(cnt < 9){
                    ++cnt;
                    PORTC =  cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
                if(cnt > 0)
                {
                    --cnt;
                    PORTC = cnt;
                }
            }

            else{
                State  = Reset;
                cnt = 0;
                PORTC = cnt;
            }
            break;
        default:
            State = Start;
            break;
    }
    switch(State){ //Actions
        case Start:
            PORTC =  cnt;
            break;
        case Wait:
            break;
        case Increment:
            break;
        case Decrement:
            break;
        case Reset:
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;  PORTA = 0xFF;
    DDRC = 0xFF;  PORTC = 0x00;

    State = Start;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

