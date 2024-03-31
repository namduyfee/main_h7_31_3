#ifndef		__FEE_PWM_H__
#define		__FEE_PWM_H__

/*******************************    INCLUDES   ********************************/
#include "stm32h7xx_hal.h"
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

void FEE_PWM_Innit(void);

void DC_PWM1(uint8_t chieu, uint8_t toc_do);
void DC_PWM2(uint8_t chieu, uint8_t toc_do);
void DC_PWM3(uint8_t chieu, uint8_t toc_do);
void DC_PWM4(uint8_t chieu, uint8_t toc_do);
#endif
