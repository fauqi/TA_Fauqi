/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
//cek
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"math.h"
#include "lcd_character.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define SampleData 1000
#define Vzero1 0.0
__IO uint16_t Nilai_ADC[2];
int on=0,i,k=0;
float Iinput, Vinput;
int asum=0, adata=0, a[500];
double Vsq [SampleData], Vrms[1], ADCVrms[1], Vsum[1], Vadc[1], iadcx[1];
double Vsq2 [SampleData], Vrms2[1], ADCVrms2[1], Vsum2[1], Vadc2[1], iadcx2[1];
uint32_t Tegangan[1];


int dataADC,dataADC2,dataADC3;
float Voltage,Voltage2;
float VDC;
float ecurrent;
float offset = 2500;
float sensitivity=100;
char buff[15];
char buff2[15];
char buff3[15];
char buff4[99]="0";
char TX_Data[99]="0";
char RX_Data[2]="0";
float daya;
int flag =0;
int flag2=0;
unsigned int millis=0;
unsigned int millis_serial=0;
int c1=0;
int dat=0;
float sudutPenyalaan=90;
int count=0;
int cDelay=0;
int del=1000;
int relay_state=0;
int set_point=0;
//protokol
char header[15]="$fauqi";
char csuhu[15]="50";
char tegangan[15]="150";
char sudut_penyalaan[15]="120";
char error[15]="40";
char derror[15]="5";
char out_fuzzy[15]="0.5";
char crelay_state[15]="0";
char cset_point[15]="0";
char koma[15]=",";
char b[15]="\r\n";
int flag_konv=0;
int sudut =0;
int count2=0;
int count3=0;
int counter=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void reverse(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 
  
// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 
  
// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART6_UART_Init(void);
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
  MX_TIM1_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  
	lcd_init();
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)Nilai_ADC,2);
  HAL_GPIO_WritePin(GPIOE,relay_konv_Pin,GPIO_PIN_SET);
  	 HAL_UART_Receive_IT(&huart6, (uint8_t *)RX_Data, 2);
	 HAL_UART_Transmit_IT(&huart6, (uint8_t *)TX_Data, 5);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    if(HAL_GPIO_ReadPin(GPIOC,PB_up_Pin)==1)
    {
      
      while(HAL_GPIO_ReadPin(GPIOC,PB_up_Pin)==1){
      HAL_Delay(50);
      counter=counter+1;
			sprintf(buff, "sp:%4d",counter);
		// HAL_Delay(100);
		lcd_gotoxy(0,3);
		lcd_puts(buff);
      }
    }
        if(HAL_GPIO_ReadPin(GPIOC,PB_down_Pin)==1)
    {
      
      while(HAL_GPIO_ReadPin(GPIOC,PB_down_Pin)==1){
			 HAL_Delay(50);
      counter=counter-1;
			sprintf(buff, "sp:%4d",counter);
		// HAL_Delay(100);
		lcd_gotoxy(0,3);
		lcd_puts(buff);
			}
    }
    		
		sprintf(buff, "firing:90");
		// HAL_Delay(100);
		lcd_gotoxy(0,0);
		lcd_puts(buff);
		// HAL_Delay(100);
//		Vrms[0] = 0.3131*ADCVrms[0] + 0.1456;
		sprintf(buff, "Vrms:%3.2f",Vrms[0]);
		// HAL_Delay(300);
		lcd_gotoxy(0,1);
		lcd_puts(buff);
		ftoa(Vrms[0],buff2,2);
		sprintf(buff, "suhu:%3.2f",Vrms2[0]);
		// HAL_Delay(100);
		lcd_gotoxy(0,2);
		lcd_puts(buff);
			sprintf(buff, "sp:%4d",counter);
		// HAL_Delay(100);
		lcd_gotoxy(0,3);
		lcd_puts(buff);
		ftoa(Vrms[0],buff2,2);
		ftoa(Vrms2[0],csuhu,2);
		//membuat protokol
		strcpy(TX_Data,header);
		strcat(TX_Data,koma);
  	strcat(TX_Data,csuhu);
   	strcat(TX_Data,koma);
		strcat(TX_Data,buff2);
		strcat(TX_Data,koma);
		strcat(TX_Data,sudut_penyalaan);
		strcat(TX_Data,koma);
		strcat(TX_Data,error);
		strcat(TX_Data,koma);
		strcat(TX_Data,derror);
		strcat(TX_Data,koma);
		strcat(TX_Data,out_fuzzy);
		strcat(TX_Data,koma);
	  strcat(TX_Data,b);
		
		
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 41;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, out_konv_Pin|relay_kipas_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(relay_konv_GPIO_Port, relay_konv_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, builtin_led_Pin|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : zcd_Pin */
  GPIO_InitStruct.Pin = zcd_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(zcd_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : out_konv_Pin relay_kipas_Pin */
  GPIO_InitStruct.Pin = out_konv_Pin|relay_kipas_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : relay_konv_Pin */
  GPIO_InitStruct.Pin = relay_konv_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(relay_konv_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : builtin_led_Pin PD0 PD1 PD2
                           PD3 PD4 PD5 PD6
                           PD7 */
  GPIO_InitStruct.Pin = builtin_led_Pin|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PB_up_Pin PB_down_Pin */
  GPIO_InitStruct.Pin = PB_up_Pin|PB_down_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
		if(htim==&htim1)
		{
      //lontong
		count=1300;
    count2=count2+1;
		millis_serial=millis_serial+1;
	if(flag_konv==1)
		millis=millis+1;
    	if(millis_serial>=200000)
	{		
	//dat=dat+1;
//			intToStr(dat,TX_Data,5);
			HAL_UART_Transmit_IT(&huart6,(uint8_t *)TX_Data,strlen(TX_Data));
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
			millis_serial=0;
	}
	if (millis>=counter)
	{
//ktemu 5us
    flag_konv=0;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
			millis=0;
	}
  if(count2>=200)
  {
    Vadc[0]= Nilai_ADC[0]-1777;
		Vsum[0]-=Vsq[k];
		Vsq[k]= Vadc[0] * Vadc[0];
		Vsum[0]+=Vsq[k];
		ADCVrms[0]=sqrt((Vsum[0]/SampleData));
    Vrms[0] = 0.3131*ADCVrms[0] + 0.1456;
		
		Vadc2[0]= Nilai_ADC[1];
		Vsum2[0]+=Vadc2[0];


    k++;
		if(k>=SampleData)
    {
		k=0;
    ADCVrms2[0]=(Vsum2[0]/SampleData);
		Vsq2[0]=(ADCVrms2[0]/4094)*3;
		Vrms2[0]=Vsq2[0]*100;
    Vsum2[0]=0;


//		tegangan = Vrms[0];
//		suhu = Vrms[1];
    }
    count2=0;
  }
}
		}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
	if(strlen(RX_Data)<=2){
	HAL_UART_Receive_IT(&huart6, (uint8_t *)RX_Data,2);
	int data;
	if(strncmp(RX_Data,"lontong",strlen(RX_Data))==0){}
	data=atoi(RX_Data);
	if(data == 40)set_point=40;
	else if (data==50)set_point=50;
	else if (data ==61)set_point=61;
	else if(data==10) {relay_state=1;HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);}
	else if(data==11){relay_state=0;HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);}
	else if(data==20) {relay_state=1;HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,GPIO_PIN_SET);}
	else if(data==21){relay_state=0;HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,GPIO_PIN_RESET);}
	strcpy(RX_Data,"");
	}
	else{}

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==1)
		{
	HAL_GPIO_WritePin(GPIOA,out_konv_Pin,GPIO_PIN_RESET);
  flag_konv=1;
		}
	
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

