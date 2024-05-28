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
            setTimer3(1000); // timer for event not press
            setTimer4(100);  // count down when not press
            setTimer5(100);
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


void fsm_simple_buttons_run(){

	if(isButton1Pressed() == 1){
		count = 0;
		setTimer3(1000);
		precount = count;
	}

	if(isButton2Pressed() == 1 || (isButton2LongPressed() && timer5_flag == 1)) {
	    // Increase time in count but not update in count
	    if (timer3_flag == 1) {
	        count = precount - 1;
	    }

	    if (count <= 9) {
	        count = count + 1;
	    }
	    if (count == 10) {
	        count = 0;
	    }
	    setTimer3(1000);
	    precount = count;
	    setTimer5(100);
	}

	if(isButton3Pressed() == 1 || (isButton3LongPressed() && timer5_flag == 1)) {
	    // Decrease time
	    if (timer3_flag == 1) {
	        count = precount + 1;
	    }

	    if (count >= 0) {
	        count = count - 1;
	    }
	    if (count < 0) {
	        count = 9;
	    }
	    setTimer3(1000);
	    precount = count;
	    setTimer5(100);
	}


	if(timer3_flag == 1){
		if(timer4_flag == 1){
			count--;
			setTimer4(100);
		}
	}
}

