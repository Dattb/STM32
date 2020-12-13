/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include"5110.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
 unsigned short Mode_menu=1,Mode_giamsat=1;
 unsigned char T=30,H=100;
 uint8_t Mode_Color,Mode_LCD=1;
 uint8_t int_T=0,int_RH=0,d1=0,d2=0,d3=0;
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
  /* USER CODE BEGIN 2 */
  LCD5110_setup();
  		PCD8544_backlight_state(ON);
  		HAL_Delay(2000);
  		PCD8544_backlight_state(OFF);
  		HAL_Delay(2000);
  		PCD8544_clear_screen(WHITE);
  		PCD8544_backlight_state(ON);
  		HAL_Delay(3000);
  		PCD8544_clear_screen(WHITE);
         HAL_Delay(4000);
      PCD8544_clear_screen(WHITE);
		PCD8544_print_string(1, 0, "    Hien Thi    ", BLACK);
		PCD8544_print_string(1, 2, " Nhiet Do:", WHITE);
		PCD8544_print_string(1, 3, " Do Am:", WHITE);
		PCD8544_print_string(1, 4, " Protect:", WHITE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  switch(Mode_LCD)
	  		 {
	  		  case 1: {
	  					//che do hien thi MAIN MENU
	  					PCD8544_clear_screen(WHITE);
	  					PCD8544_print_string(1, 0, "    MAIN MENU    ", BLACK);
	  					PCD8544_print_string(1, 2, "Cam Bien", WHITE);
	  					PCD8544_print_string(1, 3, "Giam Sat", WHITE);
	  					PCD8544_print_string(1, 4, "R G B", WHITE);

	  					if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin));
	  						Mode_menu++;
	  						if(Mode_menu>3) Mode_menu=3;
	  					}
	  					if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin));
	  						Mode_menu--;
	  						if(Mode_menu<1) Mode_menu=1;
	  					}
	  					if(Mode_menu)
	  					{
	  						PCD8544_print_string(1, 2, "Cam Bien",BLACK);
	  						PCD8544_print_string(1, 3, "Giam Sat", WHITE);
	  						PCD8544_print_string(1, 4, "R G B", WHITE);
	  						if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  						{
	  							while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  							Mode_LCD=2;
	  						}
	  					}
	  					else if(Mode_menu==2)
	  					{
	  						PCD8544_print_string(1, 2, "Cam Bien", WHITE);
	  						PCD8544_print_string(1, 3, "Giam Sat", BLACK);
	  						PCD8544_print_string(1, 4, "R G B", WHITE);
	  						if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  						{
	  							while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  							Mode_LCD=3;
	  						}
	  					}
	  					else if(Mode_menu==3)
	  					{
	  						PCD8544_print_string(1, 2, "Cam Bien", WHITE);
	  						PCD8544_print_string(1, 3, "Giam Sat", WHITE);
	  						PCD8544_print_string(1, 4, "R G B", BLACK);
	  						if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  						{
	  							while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  							Mode_LCD=4;
	  						}
	  					}

	  					break;
	  				  }
	  		  case 2: {
	  					//che do hien thi nhiet do va do am len LCD
	  					PCD8544_clear_screen(WHITE);
	  					PCD8544_print_string(1, 0, "    Cam Bien    ", BLACK);
	  					PCD8544_print_string(1, 2, "Nhiet Do:", WHITE);print_int(45, 2,int_T, WHITE); PCD8544_set_cursor(70,2);PCD8544_print_char('C',WHITE);
	  					PCD8544_print_string(1, 3, "Do Am:", WHITE);print_int(45, 3,int_RH, WHITE); PCD8544_set_cursor(70,3);PCD8544_print_char('%',WHITE);
	  					if(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin));

	  						PCD8544_print_string(1, 2, "Nhiet Do:", WHITE);print_int(45, 2,int_T, WHITE); PCD8544_set_cursor(70,2);PCD8544_print_char('F',WHITE);
	  						PCD8544_print_string(1, 3, "Do Am:", WHITE);print_int(45, 3,int_RH, WHITE); PCD8544_set_cursor(70,3);PCD8544_print_char('%',WHITE);

	  					}
	  					if(!HAL_GPIO_ReadPin(btn_Trai_GPIO_Port, btn_Trai_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_Trai_GPIO_Port, btn_Trai_Pin));

	  						PCD8544_print_string(1, 2, "Nhiet Do:", WHITE);print_int(45, 2,int_T, WHITE); PCD8544_set_cursor(70,2);PCD8544_print_char('C',WHITE);
	  						PCD8544_print_string(1, 3, "Do Am:", WHITE);print_int(45, 3,int_RH, WHITE); PCD8544_set_cursor(70,3);PCD8544_print_char('%',WHITE);

	  					}
	  					if(int_T>=T)
	  					{
	  					 PCD8544_print_string(1, 4, "     OVER T!    ", BLACK);	printf("OVER TEMPT!\r\n");
	  					}
	  					else if(int_RH>=H)
	  					{
	  						PCD8544_print_string(1, 4, "     OVER H!    ", BLACK); printf("OVER HUM!\r\n");
	  					}
	  					else if(int_T>=T&&int_RH>=H)
	  					{
	  						PCD8544_print_string(1, 4, "    OVER T&H!   ", BLACK); printf("OVER HUM!\r\n");
	  					}
	  					else PCD8544_print_string(1, 4, "     SAVE    ", WHITE);
	  					if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  						Mode_LCD=1;
	  					}
	  					break;
	  				  }
	  		  case 3: {
	  			        //che do giam sat nhiet do va do am len LCD
	  					PCD8544_clear_screen(WHITE);
	  					PCD8544_print_string(1, 0, "    Giam Sat    ", BLACK);
	  					PCD8544_print_string(1, 2, "Over T:", WHITE);print_int(45, 2,T, WHITE); PCD8544_set_cursor(70,2);PCD8544_print_char('C',WHITE);
	  					PCD8544_print_string(1, 3, "Over H:", WHITE);print_int(45, 3,H, WHITE); PCD8544_set_cursor(70,3);PCD8544_print_char('%',WHITE);

	  			        if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin))
	  					{
	  						while(!!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin));
	  						Mode_giamsat++;
	  						if(Mode_giamsat>2) Mode_giamsat=2;
	  					}
	  					if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin))
	  					{
	  						while(!!HAL_GPIO_ReadPin(btn_Len_GPIO_Port,btn_Len_Pin));
	  						Mode_giamsat--;
	  						if(Mode_giamsat<1) Mode_giamsat=1;
	  					}
	  					if(Mode_giamsat)
	  					{
	  						PCD8544_print_string(1, 2, "Over T:", BLACK);print_int(45, 2,T, BLACK); PCD8544_set_cursor(70,2);PCD8544_print_char('C',BLACK);
	  						PCD8544_print_string(1, 3, "Over H:", WHITE);print_int(45, 3,H, WHITE); PCD8544_set_cursor(70,3);PCD8544_print_char('%',WHITE);
	  						if(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin))
	  						{
	  						  while(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin));
	  						  T++;
	  						  if(T>50) T=0;
	  						}
	  					}
	  					else if(Mode_giamsat==2)
	  					{
	  						PCD8544_print_string(1, 2, "Over T:",WHITE );print_int(45, 2,T, WHITE); PCD8544_set_cursor(70,2);PCD8544_print_char('C',WHITE);
	  						PCD8544_print_string(1, 3, "Over H:", BLACK);print_int(45, 3,H, BLACK); PCD8544_set_cursor(70,3);PCD8544_print_char('%',BLACK);
	  						if(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin))
	  						{
	  						  while(!HAL_GPIO_ReadPin(btn_phai_GPIO_Port, btn_phai_Pin));
	  						  H++;
	  						  if(T>50) T=0;
	  						}
	  					}
	  					if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  						Mode_LCD=1;
	  					}
	  					break;
	  				  }
	  		  case 4: {
	  					//hien thi che do RGB len LCD
	  					PCD8544_clear_screen(WHITE);
	  					if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port, btn_Len_Pin))
	  					{
	  					  while(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port, btn_Len_Pin))
	  					  Mode_Color++;
	  					}
	  					if(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port, btn_Len_Pin))
	  					{
	  					  while(!HAL_GPIO_ReadPin(btn_Len_GPIO_Port, btn_Len_Pin))
	  					  Mode_Color--;
	  					}
	  					PCD8544_print_string(1, 0, "      R G B     ", BLACK);
	  					PCD8544_print_string(1, 1, "Color:", WHITE);print_int(45, 1,Mode_Color, WHITE);
	  					PCD8544_print_string(1, 2, "% R:", WHITE);print_int(45, 2,d1, WHITE);
	  					PCD8544_print_string(1, 3, "% G:", WHITE);print_int(45, 3,d2, WHITE);
	  					PCD8544_print_string(1, 4, "% B:", WHITE);print_int(45, 4,d3, WHITE);
	  					if(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin))
	  					{
	  						while(!HAL_GPIO_ReadPin(btn_OK_GPIO_Port, btn_OK_Pin));
	  						Mode_LCD=1;
	  					}
	  					break;
	  				  }
	  		 }
	  		HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time 
  */
  __HAL_RCC_PLLI2S_ENABLE();
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
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RST_Pin|DC_Pin|LIGHT_Pin|CS_Pin 
                          |SCLK_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RST_Pin DC_Pin LIGHT_Pin CS_Pin 
                           SCLK_Pin MOSI_Pin */
  GPIO_InitStruct.Pin = RST_Pin|DC_Pin|LIGHT_Pin|CS_Pin 
                          |SCLK_Pin|MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : btn_OK_Pin btn_Len_Pin btn_Xuong_Pin btn_phai_Pin 
                           btn_Trai_Pin */
  GPIO_InitStruct.Pin = btn_OK_Pin|btn_Len_Pin|btn_Xuong_Pin|btn_phai_Pin 
                          |btn_Trai_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/