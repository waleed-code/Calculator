/*
 * Keypad_config.h
 *
 *  Created on: 18/8/2023
 *  Author: waleed gamal
 */

#ifndef KEYPAD_DRIVER_KEYPAD_CONFIG_H_
#define KEYPAD_DRIVER_KEYPAD_CONFIG_H_

#define  default_keypad    'k'

#define K_MIS_R      GPIO_PORTB_MIS_R

#define WITH_INT        18
#define WITHOUT_INT     20

#define KP_MODE         WITH_INT

#define KOUT_PORT    PORTE
#define KIN_PORT     PORTB

#define KP_OUT1     PIN0
#define KP_OUT2     PIN1
#define KP_OUT3     PIN2
#define KP_OUT4     PIN3

#define KP_IN1     PIN0
#define KP_IN2     PIN1
#define KP_IN3     PIN2
#define KP_IN4     PIN3


#endif /* KEYPAD_DRIVER_KEYPAD_CONFIG_H_ */
