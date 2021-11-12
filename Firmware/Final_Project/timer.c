/*
 * timer.c
 *
 * Created: 21/10/2020 00:52:46
 *  Author: Sai
 */ 
#include "common.h"
#include "display.h"

ISR (TIMER0_COMPA_vect) {
	
}

void timer_init() {
	//ctc mode
	TCCR0A = 0b00000010;
	//prescaled to 8
	TCCR0B = 0b00000010;
	//triggers on overflow so ADC sample occurs every 1ms
	OCR0A = 99;
	//enable timer interrupt
	TIMSK0 = 0b00000010;
}

void timer_stop_clear(){
	//clears and stops counter
	TCCR0B = 0b00000000;
	TCNT0 = 0;
}

void timer1_init() {
	//initializes timer 1 for phase calculation
	TCCR1A = 0b00000000;
	//prescaled to 8
	TCCR1B = 0b00000010;
}

void timer1_stop() {
	//stops timer 1
	TCCR1B = 0b00000000;
}

/*
ISR(TIMER2_COMPA_vect) {

	//Disp_ScanNext(); //Sends the next digit into shift register for seven seg display every 10ms
}
*/

/*void timer2_init()
{
	TCCR2A = 0b00000010; // Initializes TCCR0A Register to CTC mode
	TCCR2B = 0b00000011; // Initializes TCCR0B Register to CTC mode, sets prescaler
	TIMSK2 = 0b00000010; //Enable output compare match A interrupt
	OCR2A = 124; // Sets 124 as value to count to (period of 10ms)
}
*/