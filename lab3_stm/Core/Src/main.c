/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "button.h"
#include "fsm_automatic.h"
#include "global.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void displaySegment(int number);
void displaySegment1(int number);
void display7SEG(int number);
void display7SEG2(int number);
void reset_led_each_button();
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  setTimer1(100);

  int mode = 1;

  int red_increase = 0;
  int green_increase = 0;
  int yellow_increase = 0;

  int increase_time = 100;
  int increase_time_in_led = 0;
  int default_red = 500;
  int default_yellow = 200;
  int default_green = 300;
  int limit_time = 10000; // only 10s instead of limit at 100s => real time somtimes can be > than the led time because we use only one led to display


  setTimer3(50);
  setTimer4(50);
  setTimer5(100);

  int index = 4;
  int index2 = 2;

  while (1)
  {
	  fsm_automatic_run_normally_1();
	  fsm_automatic_run_normally_2();


	  if(timer3_flag == 1){ // for control mode and count leds
		  setTimer3(50);
		  displaySegment(index);
		  if(index == 3){
			 display7SEG(mode);
		  }
		  if(index == 4){
		  	 display7SEG(increase_time_in_led);
		  }
		  index--;
		  if(index < 3){
			  index = 4;
		  }
	  }

	  if(timer4_flag == 1){ // for control traffic leds
		  setTimer4(50);
		  displaySegment1(index2);
		  if(index2 == 1){
			 display7SEG2(led_time_1);
		  }
		  if(index2 == 2){
		  	 display7SEG2(led_time_2);
		  }
		  index2--;
		  if(index2 < 1){
		  	  index2 =2;
		  }
	  }

	  if(timer5_flag == 1){
		  setTimer5(100);
		  led_time_1--;
		  led_time_2--;
	  }


	  if(isButton1Pressed() == 1){
		  // TODO
		  mode++;
		  reset_led_each_button();

		  if(mode == 5){
			  mode = 1;
		  }

		  // reset led
		  red_time = default_red;
		  green_time = default_green;
		  yellow_time = default_yellow;
		  status1 = INIT;
		  status2 = SECOND_INIT;
	  }

	  if(isButton2Pressed() == 1){ // increase time in count but not update in count
		  increase_time_in_led++;
		  if(increase_time_in_led == 10){
			  increase_time_in_led = 0;
		  }
		  if(mode == 2){
			  red_increase = red_increase + increase_time;
		  }
		  if(mode == 3){
			  green_increase = green_increase + increase_time;
		  }
		  if(mode == 4){
			  yellow_increase = yellow_increase + increase_time;
		  }
	  }

	  if(isButton3Pressed() == 1){ // set increase time
		  status1 = INIT;
		  status2 = SECOND_INIT;
		  if(mode == 2){
			  red_time = (default_red + red_increase); // + total
			  green_time = default_green;
			  yellow_time = default_yellow;
		  }
		  if(mode == 3){
			  green_time = (default_green + green_increase);
			  red_time = default_red;
			  yellow_time = default_yellow;
		  }
		  if(mode == 4){
			  yellow_time = (default_yellow + yellow_increase);
			  red_time = default_red;
			  green_time = default_green;
		  }
	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void reset_led_each_button(){
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
}

void displaySegment(int number){
	switch(number){
				case 3:
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
					break;
				case 4:
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
					break;
			}
}

void displaySegment1(int number){
	switch(number){
				case 1:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
					break;
				case 2:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
					break;
			}
}

void display7SEG(int number){

	switch(number) {
	    case 0:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);
	        break;
	    case 1:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);
	        break;
	    case 2:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, SET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 3:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 4:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 5:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 6:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 7:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);
	        break;
	    case 8:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    case 9:
	        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET);
	        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET);
	        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET);
	        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET);
	        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
	        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET);
	        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET);
	        break;
	    default:
	        // Handle invalid number
	        break;
	}


}


void display7SEG2(int number){

	if(number == 0){
		HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
		HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
		HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
		HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
		HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, RESET);
		HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET);
		HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, SET);
	}

	if(number == 1){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, SET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, SET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, SET);
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, SET);
	}


	if(number == 2){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, SET); // set
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, RESET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, SET); // set
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}


	if(number == 3){ // a b c d g
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, SET);
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}

	if(number == 4){ // b c f g
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, SET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, SET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}

	if(number == 5){ // a c d f g
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, SET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET);
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}

	if(number == 6){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, SET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, RESET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}

	if(number == 7){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, SET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, SET);
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, SET);
	}

	if(number == 8){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, RESET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET); // set
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}

	if(number == 9){
	    HAL_GPIO_WritePin(SEG7_GPIO_Port, SEG7_Pin, RESET);
	    HAL_GPIO_WritePin(SEG8_GPIO_Port, SEG8_Pin, RESET);
	    HAL_GPIO_WritePin(SEG9_GPIO_Port, SEG9_Pin, RESET);
	    HAL_GPIO_WritePin(SEG10_GPIO_Port, SEG10_Pin, RESET);
	    HAL_GPIO_WritePin(SEG11_GPIO_Port, SEG11_Pin, SET);
	    HAL_GPIO_WritePin(SEG12_GPIO_Port, SEG12_Pin, RESET);
	    HAL_GPIO_WritePin(SEG13_GPIO_Port, SEG13_Pin, RESET);
	}


}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED_SECOND_Pin
                          |LED_YELLOW_SECOND_Pin|LED_GREEN_SECOND_Pin|EN4_Pin|EN0_Pin
                          |EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG10_Pin
                          |SEG11_Pin|SEG12_Pin|SEG13_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin
                          |SEG8_Pin|SEG9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : INPUT1_Pin INPUT2_Pin INPUT3_Pin */
  GPIO_InitStruct.Pin = INPUT1_Pin|INPUT2_Pin|INPUT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin LED_YELLOW_Pin LED_GREEN_Pin LED_RED_SECOND_Pin
                           LED_YELLOW_SECOND_Pin LED_GREEN_SECOND_Pin EN4_Pin EN0_Pin
                           EN1_Pin EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED_SECOND_Pin
                          |LED_YELLOW_SECOND_Pin|LED_GREEN_SECOND_Pin|EN4_Pin|EN0_Pin
                          |EN1_Pin|EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG10_Pin
                           SEG11_Pin SEG12_Pin SEG13_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin SEG7_Pin
                           SEG8_Pin SEG9_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG10_Pin
                          |SEG11_Pin|SEG12_Pin|SEG13_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin|SEG7_Pin
                          |SEG8_Pin|SEG9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timer1Run();
	timer2Run();
	timer3Run();
	timer4Run();
	timer5Run();
	timer6Run();
	getKeyInput1();
	getKeyInput2();
	getKeyInput3();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
