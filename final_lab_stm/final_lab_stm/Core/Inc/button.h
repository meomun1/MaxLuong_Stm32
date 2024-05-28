/*
 * button.h
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();

void getKeyInput1();
void getKeyInput2();
void getKeyInput3();



#endif /* INC_BUTTON_H_ */
