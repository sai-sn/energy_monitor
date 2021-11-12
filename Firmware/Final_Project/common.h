/*
 * common.h
 *
 * Created: 21/10/2020 00:54:12
 *  Author: Sai
 */ 


#ifndef COMMON_H_
#define COMMON_H_


#define F_CPU 800000UL
#include <math.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <math.h>
#include <string.h>

#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "calculations.h"
#include "interrupt.h"

#define BAUDRATE 9600

#endif /* COMMON_H_ */