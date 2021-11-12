/*
 * uart.h
 *
 * Created: 20/10/2020 18:10:05
 *  Author: Sai
 */ 


#ifndef UART_H_
#define UART_H_

void usart_init(uint32_t baud_rate);
void usart_transmit(char data);
void usart_transmit_array(char* msg);
void usart_breakdown_ascii(uint16_t number);
void usart_transmit_voltage(int32_t Voltage);
void usart_transmit_current(int32_t Current);
void usart_transmit_power(uint16_t power);
void usart_transmit_energy(uint16_t ENERGY);

#endif /* UART_H_ */
