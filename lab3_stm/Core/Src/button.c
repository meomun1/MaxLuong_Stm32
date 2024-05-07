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

// button1
int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;

int KeyReg3 = NORMAL_STATE; // trang thai on dinh truoc do
int TimerForKeyPress = 200;

// button2
int KeyReg02 = NORMAL_STATE;
int KeyReg12 = NORMAL_STATE;
int KeyReg22 = NORMAL_STATE;

int KeyReg32 = NORMAL_STATE; // trang thai on dinh truoc do
int TimerForKeyPress2 = 200;

// button3
int KeyReg03 = NORMAL_STATE;
int KeyReg13 = NORMAL_STATE;
int KeyReg23 = NORMAL_STATE;

int KeyReg33 = NORMAL_STATE; // trang thai on dinh truoc do
int TimerForKeyPress3 = 200;

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

// button 3 is Pressed
int isButton3Pressed(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}

// subProcess 1
void subKeyProcess1(){ // BUTTON FUNCTION => MOST IMPORTANT
	//TODO
	button1_flag = 1;
}

// subProcess 1
void subKeyProcess2(){
	//TODO
	button2_flag = 1;
}

// subProcess 1
void subKeyProcess3(){
	//TODO
	button3_flag = 1;
}


// HANDLING BUTTON 1
void getKeyInput1(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(INPUT1_GPIO_Port, INPUT1_Pin);
	if(( KeyReg0 == KeyReg1 ) && ( KeyReg1 == KeyReg2 ) ){ // nut nhan on dinh
		if(KeyReg3 != KeyReg2){ // trang thai truoc do != trang thai on dinh => Nhan tha
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){ // trang thai nhan
				//TODO
				subKeyProcess1();
				TimerForKeyPress = 200;

			}
		}else{
			TimerForKeyPress--;
			// TODO nhan de
			if(TimerForKeyPress == 0){
				KeyReg3 = NORMAL_STATE;
			}

		}
	}

}



// HANDLING BUTTON 1
void getKeyInput2(){
	KeyReg02 = KeyReg12;
	KeyReg12 = KeyReg22;
	KeyReg22 = HAL_GPIO_ReadPin(INPUT2_GPIO_Port, INPUT2_Pin);
	if(( KeyReg02 == KeyReg12 ) && ( KeyReg12 == KeyReg22 ) ){ // nut nhan on dinh
		if(KeyReg32 != KeyReg22){ // trang thai truoc do != trang thai on dinh => Nhan tha
			KeyReg32 = KeyReg22;
			if(KeyReg22 == PRESSED_STATE){ // trang thai nhan
				//TODO
				subKeyProcess2();
				TimerForKeyPress2 = 200;

			}
		}else{
			TimerForKeyPress2--;
			// TODO nhan de
			if(TimerForKeyPress2 == 0){
				KeyReg32 = NORMAL_STATE;
			}

		}
	}

}



// HANDLING BUTTON 1
void getKeyInput3(){
	KeyReg03 = KeyReg13;
	KeyReg13 = KeyReg23;
	KeyReg23 = HAL_GPIO_ReadPin(INPUT3_GPIO_Port, INPUT3_Pin);
	if(( KeyReg03 == KeyReg13 ) && ( KeyReg13 == KeyReg23 ) ){ // nut nhan on dinh
		if(KeyReg33 != KeyReg23){ // trang thai truoc do != trang thai on dinh => Nhan tha
			KeyReg33 = KeyReg23;
			if(KeyReg23 == PRESSED_STATE){ // trang thai nhan
				//TODO
				subKeyProcess3();
				TimerForKeyPress3 = 200;

			}
		}else{
			TimerForKeyPress3--;
			// TODO nhan de
			if(TimerForKeyPress3 == 0){
				KeyReg33 = NORMAL_STATE;
			}

		}
	}

}

