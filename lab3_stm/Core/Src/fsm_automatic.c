/*
 * fsm_automatic.c
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#include "fsm_automatic.h"


void fsm_automatic_run_normally_1(){

	switch(status1){
		case INIT:
			// TODO
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
			status1 = AUTO_RED;
			led_time_1 = red_time/100;
			setTimer1(red_time);

			break;
		case AUTO_RED:
			// TODO
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

			if(timer1_flag ==1){ // for LED_RED
				led_time_1 = green_time/100;

				status1 = AUTO_GREEN;
				setTimer1(green_time);
			}
			break;
		case AUTO_GREEN:
			// TODO
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

			if(timer1_flag ==1){ // for LED_RED
				led_time_1 = yellow_time/100;
				status1 = AUTO_YELLOW;
				setTimer1(yellow_time);
			}
			break;
		case AUTO_YELLOW:
			// TODO
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);

			if(timer1_flag ==1){ // for LED_RED
				led_time_1 = red_time/100;
				status1 = AUTO_RED;
				setTimer1(red_time);
			}
		default:
			break;
	}
}



void fsm_automatic_run_normally_2(){
	switch(status2){
		case SECOND_INIT:
			// TODO
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
			status2 = AUTO_GREEN;
			led_time_2 = green_time/100;
			setTimer2(green_time);

			break;
		case AUTO_RED:
			// TODO
			HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_RESET);

			if(timer2_flag ==1){ // for LED_RED
				led_time_2 = green_time/100;
				status2 = AUTO_GREEN;
				setTimer2(green_time);
			}
			break;
		case AUTO_GREEN:
			// TODO
			HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_RESET);

			if(timer2_flag ==1){ // for LED_RED
				led_time_2 = yellow_time/100;
				status2 = AUTO_YELLOW;
				setTimer2(yellow_time);
			}
			break;
		case AUTO_YELLOW:
			// TODO
			HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_SET);

			if(timer2_flag ==1){ // for LED_RED
				led_time_2 = red_time/100;
				status2 = AUTO_RED;
				setTimer2(red_time);
			}
			break;
		default:
			break;
	}
}






