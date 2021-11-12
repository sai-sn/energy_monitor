/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
 */ 

#include "common.h"

volatile uint16_t adc_vs[20];
volatile uint16_t adc_is[20];
volatile float v_vs[20];
volatile float i_is[20];
volatile float energy[20];
volatile uint8_t energy_count = 0;
volatile uint8_t flag = 0;
volatile uint8_t adc_count = 0;
volatile bool sampleFinished = false;
float total_energy = 0;

int main(void)
{	
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	while (1) {
		if (sampleFinished == true) {
			adc_read_voltage();
			adc_read_current();
			//transmitting rms voltage through usart. multiply by 10 to fit the scope defined by our usart code
			usart_transmit_voltage((float) calculate_rms_voltage(v_vs) * (float) 10); 
			//transmitting rms voltage through usart. multiply by 100 to fit the scope defined by our usart code
			usart_transmit_current((float) calculate_rms_current(i_is) * (float) 100 * (float) sqrt(2)); 
			//transmitting rms voltage through usart. multiply by 100 to fit the scope defined by our usart code
			usart_transmit_power((float)calculate_power(v_vs, i_is) * (float) 100);
			//summing total W * min and multiplying by 100 to fit the scope defined by our usart code.
			total_energy += calculate_energy(v_vs, i_is);
			usart_transmit_energy((total_energy*100));
			
			/*code for seven segment code. Seven segment code is implemented but not fully functional. Files and code that are part of the seven segment code : display.c/h & some functions in timer.c/h */
			/*Any code that is commented out is part of the seven segment display code that is not fully functional.*/
			
			
			/*timer2_init();
			Segment_Init();
			Disp_Init();
			
			Disp_Set((float) calculate_rms_voltage(v_vs) * (float) 10); //Display seven seg voltage
			Disp_Set((float) calculate_rms_current(v_is) * (float) 1000 * (float) sqrt(2)); //Display seven seg current
			Disp_Set((float)calculate_power(v_vs, v_is) * (float) 100); //Display seven seg power */ 
		}
	}
}
