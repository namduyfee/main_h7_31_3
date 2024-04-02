#include "main.h"
#include "usbd_customhid.h"
#include "FEE_Library.h"
extern struct FEE_def	FEE;
extern USBD_HandleTypeDef 								*pdev1;
extern USBD_CUSTOM_HID_HandleTypeDef     *hhid1;

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

extern uint8_t enable_lai_tay_td7; 
extern uint8_t mode;

/* USER CODE BEGIN Header_StartTask08 */
/**
* @brief Function implementing the myTask08 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask08 */
void StartTask13(void const * argument)
{
    /* USER CODE BEGIN StartTask08 */
    /* Infinite loop */
    for(;;)
    {
			
			if(1 == mode && 7 == FEE.TuDong.tudong_number && enable_lai_tay_td7 == 1) 
				nut_lai_tay_td7_san_do(); 
			
				if(FEE.TuDong.cam_bien_mau != 0)
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				else 
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
        osDelay(1);
    }
    /* USER CODE END StartTask08 */
}

