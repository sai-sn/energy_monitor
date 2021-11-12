/*
 * adc.h
 *
 * Created: 21/10/2020 00:52:31
 *  Author: Sai
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init();
void adc_read_voltage();
void adc_read_current();
uint32_t adc_convert(uint16_t value);
//void usart_transmit_current(uint16_t Current);

#endif /* ADC_H_ */