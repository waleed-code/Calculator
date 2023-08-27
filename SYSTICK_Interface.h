/*
 * SYSTICK_Interface.h
 *
 *  Created on: 18/8/2023
 *  Author: waleed gamal
 */

#ifndef SYSTICK_DRIVER_SYSTICK_INTERFACE_H_
#define SYSTICK_DRIVER_SYSTICK_INTERFACE_H_


void SYSTICK_void_INIT(void);
void delay_SYSTICK_ms(int n);     // delay milli second
void delay_SYSTICK_MS(int n);    //  delay micro second

#endif /* SYSTICK_DRIVER_SYSTICK_INTERFACE_H_ */
