/*
 * fsm_automatic.c
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#include "fsm_automatic.h"
#include "led.h"
#include "software_timer.h"
#include "button.h"
#include "main.h"



void fsm_automatic(){
    switch(status){
        case INIT:
            status++;
            setTimer1(100);
            setTimer2(100);
            break;
        case START:
            if(timer1_flag == 1){
                display7SEG(count);
            }
            if(timer2_flag == 1 ){
            	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            	setTimer2(100);
            }
            break;
        default:
            break;
    }
}


void fsm_button(){

	if(isButton1Pressed() == 1){
		count = 1;
	}

	if(isButton2Pressed() == 1){ // increase time in count but not update in count
		if(count < 9){
			count = count + 1;
		}
	}

	if(isButton3Pressed() == 1){ // set increase time
		if(count > 1){
			count = count - 1;
		}
	}
}

