#ifndef FEE_PES_CONTROL_H
#define FEE_PES_CONTROL_H

/*******************************    INCLUDES   ********************************/

#include "main.h"
#include "FreeRTOSConfig.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stm32h7xx_hal.h"
#include "FEE_SWERVE_DRIVER.h"
/***************************    GLOBAL VARIABLES   ****************************/

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

void FEE_PES_Innit(UART_HandleTypeDef* pes_uart_handle_def);
void FEE_PES_Check_Connect(void);
void pes_uart_event_handle(void);
#endif
