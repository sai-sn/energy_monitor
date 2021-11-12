/*
 * calculations.h
 *
 * Created: 21/10/2020 21:26:18
 *  Author: Sai
 */ 


#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

float calculate_rms_voltage(volatile float *v_vs);
float calculate_rms_current(volatile float *v_is);
float calculate_power(volatile float*v_vs, volatile float *v_is);
float power_factor(uint16_t pfTimer);
float calculate_energy(volatile float *v_vs, volatile float *v_is);

#endif /* CALCULATIONS_H_ */