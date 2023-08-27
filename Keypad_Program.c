/*
 *  Keypad_Program.c
 *
 *  Created on: 18/8/2023
 *  Author: waleed gamal
 */

#include "../STD_TYPE.h"  // Include necessary header files
#include "../BIT_MATH.h"
#include "../tm4c123gh6pm.h"
#include "GPIO_driver/GPIO_Interface.h"
#include <Keypad_Driver/Keypad_Interface.h>
#include <Keypad_Driver/Keypad_private.h>
#include <Keypad_Driver/Keypad_config.h>

volatile unsigned char key_flag = 0;  // Flag to indicate a key press
unsigned char key_row = 0;  // Variable to store the active row of the keypad
unsigned char key_col = 0;  // Variable to store the active column of the keypad

unsigned char symbol[4][4] = {  // Array to hold the symbols corresponding to keypad buttons
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'.', '0', '=', '/'}
};

#if KP_MODE == WITH_INT

void KEYPAD_voidInit(void)
{
    // Configure input pins with pull-up resistors and interrupt edge initialization
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN1, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN1);
    Inteupt_Edge_InitPin(KIN_PORT, KP_IN1, LOW_EDGE);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN2, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN2);
    Inteupt_Edge_InitPin(KIN_PORT, KP_IN2, LOW_EDGE);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN3, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN3);
    Inteupt_Edge_InitPin(KIN_PORT, KP_IN3, LOW_EDGE);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN4, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN4);
    Inteupt_Edge_InitPin(KIN_PORT, KP_IN4, LOW_EDGE);

    // Configure output pins
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT1, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT2, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT3, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT4, GPIO_OUTPUT);

    // Set output pins to HIGH
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT2, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT3, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT4, GPIO_HIGH);
}

u8 KEYPAD_u8PressedKey(void)
{
    for (int r = 0; r < 4; r++) {
        GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1 + r, LOW);  // Activate one row at a time
        key_row = r;
        
        // Wait until all column inputs are HIGH, indicating no button press
        while (!GPIO_u8GetPinValue(KIN_PORT, KP_IN1));
        while (!GPIO_u8GetPinValue(KIN_PORT, KP_IN2));
        while (!GPIO_u8GetPinValue(KIN_PORT, KP_IN3));
        while (!GPIO_u8GetPinValue(KIN_PORT, KP_IN4));
        
        GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1 + r, HIGH);  // Deactivate the row
        
        if (key_flag) return 1;  // Return 1 if a button press is detected
    }

    return 0;  // Return 0 if no button press is detected
}

#endif

#if KP_MODE == WITHOUT_INT

void KEYPAD_voidInit(void)
{
    // Configure input pins with pull-up resistors
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN1, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN1);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN2, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN2);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN3, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN3);
    
    GPIO_voidSetPinDirection(KIN_PORT, KP_IN4, GPIO_INPUT);
    GPIO_voidSetPinPullUp(KIN_PORT, KP_IN4);

    // Configure output pins
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT1, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT2, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT3, GPIO_OUTPUT);
    GPIO_voidSetPinDirection(KOUT_PORT, KP_OUT4, GPIO_OUTPUT);

    // Set output pins to HIGH
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT2, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT3, GPIO_HIGH);
    GPIO_voidSetPinValue(KOUT_PORT, KP_OUT4, GPIO_HIGH);
}

u8 KEYPAD_u8PressedKey(void)
{
    for (int r = 0; r < 4; r++) {
        GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1 + r, LOW);  // Activate one row at a time
        key_row = r;
        
        for (int c = 0; c < 4; c++) {
            if (GPIO_u8GetPinValue(KIN_PORT, KP_IN1 + c) == LOW) {
                key_col = c;
                return symbol[key_row][key_col];  // Return the symbol corresponding to the button press
            }
        }
        
        GPIO_voidSetPinValue(KOUT_PORT, KP_OUT1 + r, HIGH);  // Deactivate the row
    }

    return '\0';  // Return null character if no button press is detected
}

#endif


