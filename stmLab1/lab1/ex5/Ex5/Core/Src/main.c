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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void redOneAndGreenSix(void);
void display7SEG(int counter);
void displaySECOND7SEG(int counter);
void redOneAndYellowFive(void);
void redFourAndYellowTwo(void);
void redFourAndGreenThree(void);

int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();

    /* Infinite loop */
    int counter = 5;
    int loop_status = 0;
    int yellow_time = 2;
  while (1)
  {
	  if(counter == 0){
		  counter = 5;
	  }

      if(loop_status == 0){

    	  if(counter == 5){
    		  redOneAndGreenSix();
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter-yellow_time);
    	  }
    	  if(counter == 4){
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter-yellow_time);
    	  }
    	  if(counter == 3){
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter-yellow_time);
    	  }
    	  if(counter ==  2){
    		  redOneAndYellowFive();
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter);
    	  }
    	  if(counter == 1){
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter);
    		  loop_status = 1;
    	  }
      }
      if(loop_status == 1){

    	  if(counter == 5){
    		  redFourAndGreenThree();
    		  display7SEG(counter-yellow_time);
    		  displaySECOND7SEG(counter);
    	  }
    	  if(counter == 4){
    		  display7SEG(counter-yellow_time);
    		  displaySECOND7SEG(counter);
    	  }
    	  if(counter == 3){
    		  display7SEG(counter-yellow_time);
    		  displaySECOND7SEG(counter);
    	  }
    	  if(counter ==  2){
    		  redFourAndYellowTwo();
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter);
    	  }
    	  if(counter == 1){
    		  display7SEG(counter);
    		  displaySECOND7SEG(counter);
    		  loop_status =0;
    	  }

      }
      counter--;
      HAL_Delay(1000);
  }
}


void redOneAndGreenSix()
{
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);             // 1
  HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_RESET); // 4
  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);     // 2
  HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_SET);
}

void redOneAndYellowFive()
{
	   HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	   HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_SET);
	   HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_RESET);
}

void redFourAndGreenThree()
{
	   HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_SET);
	   HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	   HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_RESET);
}

void redFourAndYellowTwo()
{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(LED_RED_SECOND_GPIO_Port, LED_RED_SECOND_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(LED_YELLOW_SECOND_GPIO_Port, LED_YELLOW_SECOND_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(LED_GREEN_SECOND_GPIO_Port, LED_GREEN_SECOND_Pin, GPIO_PIN_RESET);
}

void display7SEG(int counter)
{
	if(counter == 0){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, RESET);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, RESET);
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, RESET);
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, RESET);
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, RESET);
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, SET);
	}
	if(counter == 1){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, SET);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET); //
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, RESET); //
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, SET);
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, SET);
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, SET);
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, SET);
	}
	if(counter == 2){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, RESET);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, SET); // re
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, RESET);
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, RESET);
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, SET); // re
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, RESET);
	}
	if(counter == 3){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, RESET);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, RESET);
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, RESET);
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, SET); // set
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, SET); // set
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, RESET);
	}
	if(counter == 4){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, SET);// set
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, RESET);
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, SET); // set
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, SET); // set
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, RESET);
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, RESET);
	}
	if(counter == 5){
		HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, RESET);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, SET); // set
		HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, RESET);
		HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, RESET);
		HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, SET); // set
		HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, RESET);
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, RESET);
	}

}


void displaySECOND7SEG(int counter)
{
	if(counter == 0){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, RESET);
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, RESET);
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, RESET);
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, RESET);
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, RESET);
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, RESET);
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, SET);
	}
	if(counter == 1){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, SET);
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, RESET); //
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, RESET); //
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, SET);
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, SET);
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, SET);
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, SET);
	}
	if(counter == 2){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, RESET);
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, RESET);
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, SET); // re
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, RESET);
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, RESET);
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, SET); // re
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, RESET);
	}
	if(counter == 3){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, RESET);
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, RESET);
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, RESET);
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, RESET);
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, SET); // set
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, SET); // set
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, RESET);
	}
	if(counter == 4){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, SET);// set
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, RESET);
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, RESET);
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, SET); // set
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, SET); // set
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, RESET);
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, RESET);
	}
	if(counter == 5){
		HAL_GPIO_WritePin(LED_AA_GPIO_Port, LED_AA_Pin, RESET);
		HAL_GPIO_WritePin(LED_BB_GPIO_Port, LED_BB_Pin, SET); // set
		HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, RESET);
		HAL_GPIO_WritePin(LED_DD_GPIO_Port, LED_DD_Pin, RESET);
		HAL_GPIO_WritePin(LED_EE_GPIO_Port, LED_EE_Pin, SET); // set
		HAL_GPIO_WritePin(LED_FF_GPIO_Port, LED_FF_Pin, RESET);
		HAL_GPIO_WritePin(LED_GG_GPIO_Port, LED_GG_Pin, RESET);
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_SECOND_Pin|LED_YELLOW_SECOND_Pin|LED_GREEN_SECOND_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_DD_Pin
                          |LED_EE_Pin|LED_FF_Pin|LED_GG_Pin|LED_D_Pin
                          |LED_E_Pin|LED_F_Pin|LED_G_Pin|LED_AA_Pin
                          |LED_BB_Pin|LED_CC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_SECOND_Pin LED_YELLOW_SECOND_Pin LED_GREEN_SECOND_Pin LED_RED_Pin
                           LED_YELLOW_Pin LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_RED_SECOND_Pin|LED_YELLOW_SECOND_Pin|LED_GREEN_SECOND_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_A_Pin LED_B_Pin LED_C_Pin LED_DD_Pin
                           LED_EE_Pin LED_FF_Pin LED_GG_Pin LED_D_Pin
                           LED_E_Pin LED_F_Pin LED_G_Pin LED_AA_Pin
                           LED_BB_Pin LED_CC_Pin */
  GPIO_InitStruct.Pin = LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_DD_Pin
                          |LED_EE_Pin|LED_FF_Pin|LED_GG_Pin|LED_D_Pin
                          |LED_E_Pin|LED_F_Pin|LED_G_Pin|LED_AA_Pin
                          |LED_BB_Pin|LED_CC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
