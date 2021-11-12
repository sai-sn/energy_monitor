/*
 * interrupt.c
 *
 * Created: 23/10/2020 3:52:08 PM
 *  Author: krish
 */ 

#include "common.h"

extern volatile uint8_t flag;
extern volatile uint8_t adc_count;
extern volatile bool sampleFinished;
volatile uint16_t pfTimer = 0;

ISR(INT0_vect) {
	sampleFinished = false;
	if(flag == 0){
		//intialises timer0 which is used to trigger the adc conversion.  sampling only begins once the zero crossing rising edge occurs.
		timer_init();
		flag = 1;
		//intialises timer1 which is used to calculate the phase shift
		timer1_init();
	}
	else if(flag == 1 && adc_count == 20){
		//disables int0 interrupt (voltage zero crossing) once the voltage sampling is complete. enables int1 (current zero crossing) to start the current sampling
		interrupt0_disable();
		timer_stop_clear();
		flag = 2;
		adc_count = 0;
		interrupt1_enable();
	}
}

ISR(INT1_vect) {
	if(flag == 2){
		timer_init();
		//changes ADMUX channel to ADC1 for current sampling
		ADMUX = 0b01000001;
		flag = 3;
	}
	else if(flag == 3 && adc_count == 20){
		//stops int1 interrupt (current zero crossing) once the current conversion is complete and re-enables int0 (voltage zero crossing) for the next voltage conversion.
		interrupt1_disable();
		//stops the timer1 which is used to measure the phase shift and stores the timer value for further calculation
		timer1_stop();
		pfTimer = TCNT1;
		TCNT1 = 0;
		timer_stop_clear();
		flag = 0;
		//changes channel back to ADC0 for voltage sampling
		ADMUX = 0b01000000;
		adc_count = 0;
		sampleFinished = true;
		interrupt0_enable();
	}
}

void interrupt0_enable(){
	//enables interrupt on rising edge of INT0
	EICRA = 0b00000011;
	EIMSK |= (1 << INT0);
}

void interrupt1_enable(){
	//enables interrupt on rising edge of INT1
	EICRA = 0b00001100;
	EIMSK |= (1 << INT1);
}

void interrupt0_disable(){
	//disables INT0 interrupt
	EICRA = 0b00000000;
	EIMSK = 0b00000000;
}

void interrupt1_disable(){
	//disables INT1 interrupt
	EICRA = 0b00000000;
	EIMSK = 0b00000000;
}