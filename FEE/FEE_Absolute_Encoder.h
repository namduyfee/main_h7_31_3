#ifndef _FEE_ABSOLUTE_ENCODER_
#define _FEE_ABSOLUTE_ENCODER_

/*******************************    INCLUDES   ********************************/
#include "stm32h7xx_hal.h"

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

typedef struct _SPI1_Enccoder
{
    uint16_t _angledata;
    uint8_t state;
    uint8_t crc8;
    double Angle;
}SPI1_Enccoder;

enum
{
    false,
    true,
};

/***************************       FUNCTIONS       ****************************/
uint8_t SAEJ1850_CRC8(uint8_t* data, uint8_t length);
uint8_t StreamReadAngle(uint8_t *state, uint8_t *CRC8, double* ReadRegData);
#endif
