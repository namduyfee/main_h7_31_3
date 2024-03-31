#ifndef FEE_COMPASS_H
#define FEE_COMPASS_H

/*******************************    INCLUDES   ********************************/
#include "stm32h7xx_hal.h"
#include "main.h"

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
void FEE_Compass_Innit(UART_HandleTypeDef* compass_uart_handle_def, uint8_t Axis, FEE_Compass_struct_def* sensor);
void FEE_Compass_Process(FEE_Compass_struct_def* sensor);
int16_t Round_angle(int16_t _Angle);
void FEE_Compass_Check_Connect(FEE_Compass_struct_def* sensor);
void Set_Angle(FEE_Compass_struct_def* sensor, uint8_t axis_set,int16_t G_set);
void FEE_Compass_Process_All_Data(FEE_Compass_struct_def* sensor);
void FEE_Compass_Process_X(FEE_Compass_struct_def* sensor);
void FEE_Compass_Process_Y(FEE_Compass_struct_def* sensor);
void FEE_Compass_Process_Z(FEE_Compass_struct_def* sensor);

#endif
