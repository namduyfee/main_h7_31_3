#ifndef		__FEE_ADC_H__
#define		__FEE_ADC_H__

/*******************************    INCLUDES   ********************************/
//#include "main.h"
#include "cmsis_os.h"
#include "stm32h7xx_hal.h"
#include "FEE_Kalman_Filter.h"
/***************************   GLOBAL VARIABLES  ******************************/

extern struct FEE_def	FEE;
extern	ADC_HandleTypeDef hadc1;
extern	DMA_HandleTypeDef hdma_adc1;

extern	I2C_HandleTypeDef hi2c1;
extern	I2C_HandleTypeDef hi2c2;

extern	SPI_HandleTypeDef hspi1;

extern	TIM_HandleTypeDef htim2;
extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim4;

extern	UART_HandleTypeDef huart4;
extern	UART_HandleTypeDef huart5;
extern	UART_HandleTypeDef huart7;
extern	UART_HandleTypeDef huart8;
extern	UART_HandleTypeDef huart1;
extern	UART_HandleTypeDef huart2;
extern	UART_HandleTypeDef huart3;
extern	UART_HandleTypeDef huart6;
extern	DMA_HandleTypeDef hdma_uart4_rx;
extern	DMA_HandleTypeDef hdma_uart5_rx;
extern	DMA_HandleTypeDef hdma_uart7_rx;
extern	DMA_HandleTypeDef hdma_uart8_rx;
extern	DMA_HandleTypeDef hdma_usart1_rx;
extern	DMA_HandleTypeDef hdma_usart2_rx;
extern	DMA_HandleTypeDef hdma_usart3_rx;
extern	DMA_HandleTypeDef hdma_usart6_rx;

/***************************       FUNCTIONS       ****************************/

void FEE_ADC_Innit(void);
// luu du lieu tu DMA
void FEE_ADC_Get_Raw(void);
// tinh gia tri dien ap tu gia tri tho
void FEE_ADC_Get_Volt(void);
// tinh toan du lieu tu dien ap do duoc
void FEE_ADC_Get_Result(void);
// Kalman Filter
void FEE_ADC_Kalman_Filter(void);

#endif
