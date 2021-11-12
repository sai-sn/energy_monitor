/*
 * adc.c
 *
 * Created: 21/10/2020 00:52:03
 *  Author: Sai
 */ 
#include "common.h"

extern volatile uint16_t adc_vs[20];
extern volatile uint16_t adc_is[20];
extern volatile float v_vs[20];
extern volatile float i_is[20];
extern volatile uint8_t adc_count;

//interrupts every 1ms
ISR(ADC_vect) {
	//if reading from ADC0, add value to adc_vs array
	if (ADMUX == 0b01000000 && adc_count < 20) {
		adc_vs[adc_count] = ADC;
		adc_count++;
	}//if reading from ADC1, add value to asc_is array
	else if (ADMUX == 0b01000001 && adc_count < 20) {
		adc_is[adc_count] = ADC;
		adc_count++;
	}
}

void adc_init() {
	//Uses AVcc as reference voltage, starts reading from ADC0
	ADMUX = 0b01000000;
	//Enables ADC in auto trigger mode, enables complete interrupt
	ADCSRA = 0b11101010;
	//auto trigger on Timer/Counter0 Compare Match A
	ADCSRB = 0b00000011;
}

//converts the raw ADC value into voltage
void adc_read_voltage(){
	for (uint8_t i = 0; i < 20; i++) {
		float adc_val = (float) adc_vs[i];
		v_vs[i] = ((float)(adc_val * 5) / (float) 1024 - 2.1) / (float) (0.0454016298);//Gvs*Gvo (gain)
	}
}

//converts the raw ADC value into current
void adc_read_current(){
	for (uint8_t i = 0; i < 20; i++) {
		float adc_val = (float) adc_is[i];
		i_is[i] = (float) ((adc_val * 5) / (float) 1024 - 2.1) / (float) (1.146853147);//Gis*Gio (gain)
	}
}
 