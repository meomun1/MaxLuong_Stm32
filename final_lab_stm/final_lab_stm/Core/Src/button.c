/*
 * button.c
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#include "button.h"

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

// Long press flags and durations
int button2_long_press_flag = 0;
int button3_long_press_flag = 0;

#define LONG_PRESS_DURATION 3000 // 3 seconds in milliseconds

// button1
int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE; // Previous stable state
int TimerForKeyPress = 300;

// button2
int KeyReg02 = NORMAL_STATE;
int KeyReg12 = NORMAL_STATE;
int KeyReg22 = NORMAL_STATE;
int KeyReg32 = NORMAL_STATE; // Previous stable state
int TimerForKeyPress2 = 300;
int LongPressTimer2 = 0;

// button3
int KeyReg03 = NORMAL_STATE;
int KeyReg13 = NORMAL_STATE;
int KeyReg23 = NORMAL_STATE;
int KeyReg33 = NORMAL_STATE; // Previous stable state
int TimerForKeyPress3 = 300;
int LongPressTimer3 = 0;

// button 1 is Pressed
int isButton1Pressed(){
    if(button1_flag == 1){
        button1_flag = 0;
        return 1;
    }
    return 0;
}

// button 2 is Pressed
int isButton2Pressed(){
    if(button2_flag == 1){
        button2_flag = 0;
        return 1;
    }
    return 0;
}

// button 2 long press
int isButton2LongPressed(){
    return button2_long_press_flag;
}

// button 3 is Pressed
int isButton3Pressed(){
    if(button3_flag == 1){
        button3_flag = 0;
        return 1;
    }
    return 0;
}

// button 3 long press
int isButton3LongPressed(){
    return button3_long_press_flag;
}

// subProcess 1
void subKeyProcess1(){
    button1_flag = 1;
}

// subProcess 2
void subKeyProcess2(){
    button2_flag = 1;
}

// subProcess 3
void subKeyProcess3(){
    button3_flag = 1;
}

// HANDLING BUTTON 1
void getKeyInput1(){
    KeyReg0 = KeyReg1;
    KeyReg1 = KeyReg2;
    KeyReg2 = HAL_GPIO_ReadPin(RESET_GPIO_Port, RESET_Pin);
    if(( KeyReg0 == KeyReg1 ) && ( KeyReg1 == KeyReg2 )){
        if(KeyReg3 != KeyReg2){
            KeyReg3 = KeyReg2;
            if(KeyReg2 == PRESSED_STATE){
                subKeyProcess1();
                TimerForKeyPress = 300;
            }
        } else {
            TimerForKeyPress--;
            if(TimerForKeyPress == 0){
                KeyReg3 = NORMAL_STATE;
            }
        }
    }
}

// HANDLING BUTTON INC
void getKeyInput2(){
    KeyReg02 = KeyReg12;
    KeyReg12 = KeyReg22;
    KeyReg22 = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
    if(( KeyReg02 == KeyReg12 ) && ( KeyReg12 == KeyReg22 )){
        if(KeyReg32 != KeyReg22){
            KeyReg32 = KeyReg22;
            if(KeyReg22 == PRESSED_STATE){
                subKeyProcess2();
                TimerForKeyPress2 = 300;
                LongPressTimer2 = 0;
                button2_long_press_flag = 0;
            }
        } else {
            TimerForKeyPress2--;
            if(KeyReg22 == PRESSED_STATE){
                LongPressTimer2++;
                if(LongPressTimer2 >= LONG_PRESS_DURATION){
                    button2_long_press_flag = 1;
                }
            } else {
                LongPressTimer2 = 0;
                button2_long_press_flag = 0;
            }
            if(TimerForKeyPress2 == 0){
                KeyReg32 = NORMAL_STATE;
            }
        }
    }
}

// HANDLING BUTTON DEC
void getKeyInput3(){
    KeyReg03 = KeyReg13;
    KeyReg13 = KeyReg23;
    KeyReg23 = HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin);
    if(( KeyReg03 == KeyReg13 ) && ( KeyReg13 == KeyReg23 )){
        if(KeyReg33 != KeyReg23){
            KeyReg33 = KeyReg23;
            if(KeyReg23 == PRESSED_STATE){
                subKeyProcess3();
                TimerForKeyPress3 = 300;
                LongPressTimer3 = 0;
                button3_long_press_flag = 0;
            }
        } else {
            TimerForKeyPress3--;
            if(KeyReg23 == PRESSED_STATE){
                LongPressTimer3++;
                if(LongPressTimer3 >= LONG_PRESS_DURATION){
                    button3_long_press_flag = 1;
                }
            } else {
                LongPressTimer3 = 0;
                button3_long_press_flag = 0;
            }
            if(TimerForKeyPress3 == 0){
                KeyReg33 = NORMAL_STATE;
            }
        }
    }
}
