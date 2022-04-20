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
float Iinput, Vinput,out_fis;
int asum=0, adata=0, a[500];
double Vsq [SampleData], Vrms[1], ADCVrms[1], Vsum[1], Vadc[1], iadcx[1];
double Vsq2 [SampleData], Vrms2[1], ADCVrms2[1], Vsum2[1], Vadc2[1], iadcx2[1];
uint32_t Tegangan[1];
int alert=0;
int flag_ds=0;
float ds=0;
float data[11];
float temp_data[11];
int count_sd=0;
float sudut=90;
double p;
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
int flag_error=0;
unsigned int millis=0;
unsigned int millis_serial=0;
int c1=0;
int dat=0;
int count=0;
int cDelay=0;
int del=1000;
int relay_state=0;
float set_point=40.0;
//protokol
char header[15]="$fauqi";
char csuhu[15]="50";
char ctegangan[15]="150";
char csudut[15]="120";
char cerror[99]="40";
char cderror[99]="5";
char cout_fis[99]="0.5";
char crelay_state[15]="0";
char cset_point[15]="0";
char koma[15]=",";
char b[15]="\r\n";
int flag_konv=0;
//int sudut =0;
int count2=0;
int count3=0;
int counter=0;
float set_tegangan=100.0;



float nadi, suhu,error,derror=0,error2;
float A, B;

//mf gw

float in1mf1[] = {-6.123, 0.4658, 7.055};
float in1mf2[] = {0.4658, 7.055, 13.64};
float in1mf3[] = {7.055, 13.64, 20.23};
float in1mf4[] = {13.64, 20.23, 26.82};
float in1mf5[] = {20.23, 26.82, 33.41};
float in1mf6[] = {26.8, 33.4, 40};
float in1mf7[] = {33.41, 40, 46.59};

float in2mf1[] ={-0.01407, -1.754e-05, 0.01404};
float in2mf2[] ={-1.75e-05, 0.014, 0.0281};
float in2mf3[] ={0.01404, 0.02809, 0.04214};
float in2mf4[] ={0.02809, 0.04214, 0.05619};
float in2mf5[] ={0.0421, 0.0562, 0.0702};
float in2mf6[] ={0.05619, 0.07025, 0.0843};
float in2mf7[] ={0.07025, 0.0843, 0.09835};



float sakit = 0;
float ks = 0.5;
float sehat = 1;

float out1mf1=   0.8021;
float out1mf2=   0.778;
float out1mf3=   0.8566;
float out1mf4= 0;
float out1mf5= 0;
float out1mf6= 0;
float out1mf7= 0;
float out1mf8=  0.4591;
float out1mf9=   0.4482;
float out1mf10=   0.4168;
float out1mf11=   0.3137;
float out1mf12=  0.2165;
float out1mf13= 0;
float out1mf14= 0;
float out1mf15=   0.1457;
float out1mf16=  0.1488;
float out1mf17=   0.1485;
float out1mf18=   0.1687;
float out1mf19=  0.163;
float out1mf20= 0;
float out1mf21= 0;
float out1mf22=   0.1727;
float out1mf23=   0.1687;
float out1mf24=   0.1652;
float out1mf25=  0.1556;
float out1mf26=  0.1529;
float out1mf27=  0.15;
float out1mf28= 0;
float out1mf29=   0.163;
float out1mf30=   0.156;
float out1mf31=   0.149;
float out1mf32=   0.1442;
float out1mf33=   0.1361;
float out1mf34=   0.1297;
float out1mf35= 0;
float out1mf36=  0.0815;
float out1mf37=   0.0815;
float out1mf38=  0.07473 ;
float out1mf39=   0.07028;
float out1mf40=   0.06775;
float out1mf41=  0.06407 ;
float out1mf42=  0.06136 ;
float out1mf43=   -8.304e-06;
float out1mf44=  -3.965e-05 ;
float out1mf45=  -4.522e-05;
float out1mf46=  0.0004035 ;
float out1mf47=   3.729e-05;
float out1mf48=   9.353e-05;
float out1mf49=   -0.0001988;




float minr[50];
float Rule[50];

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
float calculateSD(float data[]) {
    float sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < 10; ++i) {
        sum += data[i];
    }
    mean = sum / 10;
    for (i = 0; i < 10; ++i) {
        SD += pow(data[i] - mean, 2);
    }
    return sqrt(SD / 10);
}

float fin1mf1()
{
        if (error < in1mf1[1])
    {
        return 1;
    }
        else if (error >= in1mf1[1] && error <= in1mf1[2])
    {
        return (in1mf1[2] - error) / (in1mf1[2] - in1mf1[1]);
    }
        else if (error > in1mf1[2])
    {
        return 0;
    }

}
float fin1mf2()
{
    if (error < in1mf2[0])
    {
        return 0;
    }
    else if (error >= in1mf2[0] && error <= in1mf2[1])
    {
        return (error - in1mf2[0]) / (in1mf2[1] - in1mf2[0]);
    }
    else if (error >= in1mf1[1] && error <= in1mf2[2])
    {
        return (in1mf2[2] - error) / (in1mf2[2] - in1mf2[1]);
    }
    else if (error > in1mf2[2])
    {
        return 0;
    }

}

float fin1mf3()
{
    if (error < in1mf3[0])
    {
        return 0;
    }
    else if (error >= in1mf3[0] && error <= in1mf3[1])
    {
        return (error - in1mf3[0]) / (in1mf3[1] - in1mf3[0]);
    }
    else if (error >= in1mf3[1] && error <= in1mf3[2])
    {
        return (in1mf3[2] - error) / (in1mf3[2] - in1mf3[1]);
    }
    else if (error > in1mf3[2])
    {
        return 0;
    }

}

float fin1mf4()
{
    if (error < in1mf4[0])
    {
        return 0;
    }
    else if (error >= in1mf4[0] && error <= in1mf4[1])
    {
        return (error - in1mf4[0]) / (in1mf4[1] - in1mf4[0]);
    }
    else if (error >= in1mf4[1] && error <= in1mf4[2])
    {
        return (in1mf4[2] - error) / (in1mf4[2] - in1mf4[1]);
    }
    else if (error > in1mf4[2])
    {
        return 0;
    }

}
float fin1mf5()
{
    if (error < in1mf5[0])
    {
        return 0;
    }
    else if (error >= in1mf5[0] && error <= in1mf5[1])
    {
        return (error - in1mf5[0]) / (in1mf5[1] - in1mf5[0]);
    }
    else if (error >= in1mf5[1] && error <= in1mf5[2])
    {
        return (in1mf5[2] - error) / (in1mf5[2] - in1mf5[1]);
    }
    else if (error > in1mf5[2])
    {
        return 0;
    }

}

float fin1mf6()
{
    if (error < in1mf6[0])
    {
        return 0;
    }
    else if (error >= in1mf6[0] && error <= in1mf6[1])
    {
        return (error - in1mf6[0]) / (in1mf6[1] - in1mf6[0]);
    }
    else if (error >= in1mf6[1] && error <= in1mf6[2])
    {
        return (in1mf6[2] - error) / (in1mf6[2] - in1mf6[1]);
    }
    else if (error > in1mf6[2])
    {
        return 0;
    }

}

float fin1mf7()
{
    if (error < in1mf7[0])
    {
        return 0;
    }
    else if (error >= in1mf7[0] && error <= in1mf7[1])
    {
        return (error - in1mf7[0]) / (in1mf7[1] - in1mf7[0]);
    }
    else if (error > in1mf7[1])
    {
        return 1;
    }
}

float fin2mf1()
{
        if (derror < in2mf1[1])
    {
        return 1;
    }
        else if (derror >= in2mf1[1] && derror <= in2mf1[2])
    {
        return (in2mf1[2] - derror) / (in2mf1[2] - in2mf1[1]);
    }
        else if (derror > in2mf1[2])
    {
        return 0;
    }

}
float fin2mf2()
{
    if (derror < in2mf2[0])
    {
        return 0;
    }
    else if (derror >= in2mf2[0] && derror <= in2mf2[1])
    {
        return (derror - in2mf2[0]) / (in2mf2[1] - in2mf2[0]);
    }
    else if (derror >= in2mf2[1] && derror <= in2mf2[2])
    {
        return (in2mf2[2] - derror) / (in2mf2[2] - in2mf2[1]);
    }
    else if (derror > in2mf2[2])
    {
        return 0;
    }

}
float fin2mf3()
{
    if (derror < in2mf3[0])
    {
        return 0;
    }
    else if (derror >= in2mf3[0] && derror <= in2mf3[1])
    {
        return (derror - in2mf3[0]) / (in2mf3[1] - in2mf3[0]);
    }
    else if (derror >= in2mf3[1] && derror <= in2mf3[2])
    {
        return (in2mf3[2] - derror) / (in2mf3[2] - in2mf3[1]);
    }
    else if (derror > in2mf3[2])
    {
        return 0;
    }

}
float fin2mf4()
{
    if (derror < in2mf4[0])
    {
        return 0;
    }
    else if (derror >= in2mf4[0] && derror <= in2mf4[1])
    {
        return (derror - in2mf4[0]) / (in2mf4[1] - in2mf4[0]);
    }
    else if (derror >= in2mf4[1] && derror <= in2mf4[2])
    {
        return (in2mf4[2] - derror) / (in2mf4[2] - in2mf4[1]);
    }
    else if (derror > in2mf4[2])
    {
        return 0;
    }

}

float fin2mf5()
{
    if (derror < in2mf5[0])
    {
        return 0;
    }
    else if (derror >= in2mf5[0] && derror <= in2mf5[1])
    {
        return (derror - in2mf5[0]) / (in2mf5[1] - in2mf5[0]);
    }
    else if (derror >= in2mf5[1] && derror <= in2mf5[2])
    {
        return (in2mf5[2] - derror) / (in2mf5[2] - in2mf5[1]);
    }
    else if (derror > in2mf5[2])
    {
        return 0;
    }

}
float fin2mf6()
{
    if (derror < in2mf6[0])
    {
        return 0;
    }
    else if (derror >= in2mf6[0] && derror <= in2mf6[1])
    {
        return (derror - in2mf6[0]) / (in2mf6[1] - in2mf6[0]);
    }
    else if (derror >= in2mf6[1] && derror <= in2mf6[2])
    {
        return (in2mf6[2] - derror) / (in2mf6[2] - in2mf6[1]);
    }
    else if (derror > in2mf6[2])
    {
        return 0;
    }

}
float fin2mf7()
{
    if (derror < in2mf7[0])
    {
        return 0;
    }
    else if (derror >= in2mf7[0] && derror <= in2mf7[1])
    {
        return (derror - in2mf7[0]) / (in2mf7[1] - in2mf7[0]);
    }
    else if (derror > in2mf7[1])
    {
        return 1;
    }
}



float Min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else if (b < a)
    {
        return b;
    }
    else
    {
        return a;
    }
}

void rule()
{
    minr[1] = Min(fin1mf1(), fin2mf1());
    Rule[1] = out1mf1;
    minr[2] = Min(fin1mf1(), fin2mf2());
    Rule[2] = out1mf2;
    minr[3] = Min(fin1mf1(), fin2mf3());
    Rule[3] = out1mf3;
    minr[4] = Min(fin1mf1(), fin2mf4());
    Rule[4] = out1mf4;
    minr[5] = Min(fin1mf1(), fin2mf5());
    Rule[5] = out1mf5;
    minr[6] = Min(fin1mf1(), fin2mf6());
    Rule[6] = out1mf6;
    minr[7] = Min(fin1mf1(), fin2mf7());
    Rule[7] = out1mf7;

    minr[8] = Min(fin1mf2(), fin2mf1());
    Rule[8] = out1mf8;
    minr[9] = Min(fin1mf2(), fin2mf2());
    Rule[9] = out1mf9;
    minr[10] = Min(fin1mf2(), fin2mf3());
    Rule[10] = out1mf10;
    minr[11] = Min(fin1mf2(), fin2mf4());
    Rule[11] = out1mf11;
    minr[12] = Min(fin1mf2(), fin2mf5());
    Rule[12] = out1mf12;
    minr[13] = Min(fin1mf2(), fin2mf6());
    Rule[13] = out1mf13;
    minr[14] = Min(fin1mf2(), fin2mf7());
    Rule[14] = out1mf14;

    minr[15] = Min(fin1mf3(), fin2mf1());
    Rule[15] = out1mf15;
    minr[16] = Min(fin1mf3(), fin2mf2());
    Rule[16] = out1mf16;
    minr[17] = Min(fin1mf3(), fin2mf3());
    Rule[17] = out1mf17;
    minr[18] = Min(fin1mf3(), fin2mf4());
    Rule[19] = out1mf18;
    minr[19] = Min(fin1mf3(), fin2mf5());
    Rule[19] = out1mf19;
    minr[20] = Min(fin1mf3(), fin2mf6());
    Rule[20] = out1mf20;
    minr[21] = Min(fin1mf3(), fin2mf7());
    Rule[21] = out1mf21;
 
     minr[22] = Min(fin1mf4(), fin2mf1());
    Rule[22] = out1mf22;
    minr[23] = Min(fin1mf4(), fin2mf2());
    Rule[23] = out1mf23;
    minr[24] = Min(fin1mf4(), fin2mf3());
    Rule[24] = out1mf24;
    minr[25] = Min(fin1mf4(), fin2mf4());
    Rule[25] = out1mf25;
    minr[26] = Min(fin1mf4(), fin2mf5());
    Rule[26] = out1mf26;
    minr[27] = Min(fin1mf4(), fin2mf6());
    Rule[27] = out1mf27;
    minr[28] = Min(fin1mf4(), fin2mf7());
    Rule[28] = out1mf28;
    
    minr[29] = Min(fin1mf5(), fin2mf1());
    Rule[29] = out1mf29;
    minr[30] = Min(fin1mf5(), fin2mf2());
    Rule[30] = out1mf30;
    minr[31] = Min(fin1mf5(), fin2mf3());
    Rule[31] = out1mf31;
    minr[32] = Min(fin1mf5(), fin2mf4());
    Rule[32] = out1mf32;
    minr[33] = Min(fin1mf5(), fin2mf5());
    Rule[33] = out1mf33;
    minr[34] = Min(fin1mf5(), fin2mf6());
    Rule[34] = out1mf34;
    minr[35] = Min(fin1mf5(), fin2mf7());
    Rule[35] = out1mf35;

    minr[36] = Min(fin1mf6(), fin2mf1());
    Rule[36] = out1mf36;
    minr[37] = Min(fin1mf6(), fin2mf2());
    Rule[37] = out1mf37;
    minr[38] = Min(fin1mf6(), fin2mf3());
    Rule[38] = out1mf38;
    minr[39] = Min(fin1mf6(), fin2mf4());
    Rule[39] = out1mf39;
    minr[40] = Min(fin1mf6(), fin2mf5());
    Rule[40] = out1mf40;
    minr[41] = Min(fin1mf6(), fin2mf6());
    Rule[41] = out1mf41;
    minr[42] = Min(fin1mf6(), fin2mf7());
    Rule[42] = out1mf42;

    minr[43] = Min(fin1mf7(), fin2mf7());
    Rule[43] = out1mf43;
    minr[44] = Min(fin1mf7(), fin2mf1());
    Rule[44] = out1mf44;
    minr[45] = Min(fin1mf7(), fin2mf2());
    Rule[45] = out1mf45;
    minr[46] = Min(fin1mf7(), fin2mf3());
    Rule[46] = out1mf46;
    minr[47] = Min(fin1mf7(), fin2mf4());
    Rule[47] = out1mf47;
    minr[48] = Min(fin1mf7(), fin2mf5());
    Rule[48] = out1mf48;
    minr[49] = Min(fin1mf7(), fin2mf6());
    Rule[49] = out1mf49;
 
    // // if suhu dingin and nadi lambat then kurang sehat
    // minr[1] = Min(fudingin(), fulambat());
    // Rule[1] = out1mf1;
    // // if suhu dingin and nadi sedang then kurang sehat
    // minr[2] = Min(fudingin(), fusedang());
    // Rule[2] = out1mf2;
    // // if suhu dingin and nadi cepat then sakit
    // minr[3] = Min(fudingin(), fucepat());
    // Rule[3] = out1mf3;
    // // if suhu normal and nadi lambat then kurang sehat
    // minr[4] = Min(funormal(), fulambat());
    // Rule[4] = out1mf4;
    // // if suhu normal and nadi sedang then sehat
    // minr[5] = Min(funormal(), fusedang());
    // Rule[5] = out1mf5;
    // // if suhu normal and nadi cepat then kurang sehat
    // minr[6] = Min(funormal(), fucepat());
    // Rule[6] = out1mf6;
    // // if suhu panas and nadi lambat then kurangg sehat
    // minr[7] = Min(fupanas(), fulambat());
    // Rule[7] = out1mf7;
    // // if suhu panas and nadi sedang then kurang sehat
    // minr[8] = Min(fupanas(), fusedang());
    // Rule[8] = out1mf8;
    // // if suhu panas and nadi cepat then kurang sehat
    // minr[9] = Min(fupanas(), fucepat());
    // Rule[9] = out1mf9;
}
float A, B;
float defuzzyfikasi()
{
    rule();
    A = 0;
    B = 0;
	int i;
    for(i = 1; i <= 49; i++)
    {
        // printf("Rule ke %d = %f\n", i, Rule[i]);
        // printf("Min ke %d = %f\n", i, minr[i]);
        A += Rule[i] * minr[i];
        B += minr[i];
    }
    // printf("Hasil A : %f\n", A);
    // printf("Hasil B : %f\n", B);
    return A / B;
}

// int main()
// {
//     int x;
//     for(x=0;x<10;x++)
//     {
//     printf("Masukan error : ");
//     scanf("%f", &error);
//     printf("Masukan derror : ");
//     scanf("%f", &derror);

//     printf("Keanggotaan udingin : %f\n", fudingin());
//     printf("Keanggotaan unormal : %f\n", funormal());
//     printf("Keanggotaan upanas : %f\n", fupanas());

//     printf("Keanggotaan ulambat : %f\n", fulambat());
//     printf("Keanggotaan usedang : %f\n", fusedang());
//     printf("Keanggotaan ucepat : %f\n", fucepat());

//     printf("Hasil Deff : %f\n", defuzzyfikasi());
//     }
//     return 0;
// }

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
		
	//tobe deleted
//		if (flag==0)
//		{
//			sudut =90;
//			flag=1;
//		}

			if(HAL_GPIO_ReadPin(GPIOC,PB_up_Pin)==1)
			{
				
				while(HAL_GPIO_ReadPin(GPIOC,PB_up_Pin)==1){
				
				counter=counter+1;
				sprintf(buff, "counter:%4d",counter);
			// HAL_Delay(100);
					HAL_Delay(50);
			lcd_gotoxy(0,3);
			lcd_puts(buff);
				}
			}
					if(HAL_GPIO_ReadPin(GPIOC,PB_down_Pin)==1)
			{
				
				while(HAL_GPIO_ReadPin(GPIOC,PB_down_Pin)==1){
				 
				counter=counter-1;
				sprintf(buff, "counter:%4d",counter);
					HAL_Delay(50);
			// HAL_Delay(100);
			lcd_gotoxy(0,3);
			lcd_puts(buff);
				}
			}

//    if(Vrms[0]>set_tegangan+0.5)
// 		{
// 			counter = counter+1;
// 		} 
// 		else if(Vrms[0]<set_tegangan-0.5)
// 		{
// 			counter = counter-1;
// 		}
// 		else if (Vrms[0]>=set_tegangan-0.5&&Vrms[0]<=set_tegangan-0.5)
// 		{
// 			counter=counter;
// 		}

    if (flag_error==0)
    {
    error =set_point-Vrms2[0];
    // error=ds;
    flag_error=1;
    
    }
    else 
    {   error2=set_point-Vrms2[0];
        // derror =error-error2;
        derror=ds;
        error=error2;
    }
    // out_fis=defuzzyfikasi();
    // sudut = out_fis*180.0;
	// if(sudut>=0.0 && sudut <=180.0)
	// {
    //   p=((0.01*sudut)/180)/0.000005;
	//   counter=floor(p);
	// }
		sprintf(buff, "firing:90");
		// HAL_Delay(100);
		lcd_gotoxy(0,0);
		lcd_puts("uji Perhitungan FIS");
		// HAL_Delay(100);
//		Vrms[0] = 0.3131*ADCVrms[0] + 0.1456;
		sprintf(buff, "Vrms:%3.5f",Vrms[0]);
		HAL_Delay(300);
		lcd_gotoxy(0,1);
		lcd_puts(buff);
		ftoa(Vrms[0],buff2,2);
		sprintf(buff, "Suhu:%3.5f",Vrms2[0]);
		// HAL_Delay(100);
		lcd_gotoxy(0,2);
		lcd_puts(buff);
		sprintf(buff, "counter:%4d",counter);
		// HAL_Delay(100);
		lcd_gotoxy(0,3);
		lcd_puts(buff);
		ftoa(Vrms[0],ctegangan,2);
		ftoa(Vrms2[0],csuhu,2);
        ftoa(sudut,csudut,2);
        ftoa(error,cerror,2);
        ftoa(derror,cderror,4);
        ftoa(out_fis,cout_fis,2);

		//membuat protokol
		strcpy(TX_Data,header);
		strcat(TX_Data,koma);
  	    strcat(TX_Data,csuhu);
    	strcat(TX_Data,koma);
		strcat(TX_Data,ctegangan);
		strcat(TX_Data,koma);
		strcat(TX_Data,csudut);
		strcat(TX_Data,koma);
		strcat(TX_Data,cerror);
		strcat(TX_Data,koma);
		strcat(TX_Data,cderror);
		strcat(TX_Data,koma);
		strcat(TX_Data,cout_fis);
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
  if(count2>=20)
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
		// Vrms2[0]=Vsq2[0]*100;
        if(flag_ds==0)
        {
            for(int i=0;i<=10;i++)
            {
                data[i]=Vsq2[0]*100;
                temp_data[i]=Vsq2[0]*100;
            }
            flag_ds=1;
            count_sd=11;
        }
		else
		{
            for(int i=0;i<=10;i++)
            {
                temp_data[10]=Vsq2[0]*100;
                if(i>=1)
                {
                    temp_data[i]=temp_data[i+1];
                }
                else temp_data[0]=temp_data[1];
            }
            ds=calculateSD(temp_data);
            if(ds<=0.1)
            {
                for(int i=0;i<=10;i++)
                {  
                    data[i]=temp_data[i];
                    
                }
                Vrms2[0]=temp_data[9];
            }
            else{
                    for(int x=0;x<=10;x++)
                {  
                    temp_data[x]=data[x];
                }
                alert=1;
            }
		}
    
    // if(count_sd<=10){
    //     data[count_sd]=Vsq2[0]*100;
    //     count_sd++;
    //     // data[0]=45.0;
	// 	// 	data[3]=45.0;
        
    // }
    // else{
    //     ds=calculateSD(data);
    //    if(ds<0.2)
    //    {
    //        Vrms2[0]=data[9];
    //    }
    //    else alert=1;
    //    count_sd=0;

    // }
		
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
	if(data == 40)set_point=40.0;
	else if (data==50)set_point=50.0;
	else if (data ==61)set_point=61.0;
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

