#include "main.h"
#include "usbd_customhid.h"
#include "stdio.h"
#include "FEE_Library.h"

extern struct FEE_def	FEE;
//extern USBD_HandleTypeDef 			   *pdev1;
//extern USBD_CUSTOM_HID_HandleTypeDef     *hhid1;

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

/* USER CODE BEGIN Header_StartTask07 */
/**
* @brief Function implementing the myTask07 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask07 */
void StartTask07(void const * argument)
{
    /* USER CODE BEGIN StartTask07 */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1);
        if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0)
        {
            osDelay(1);
            while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0);
            FEE.H_UART3.txBuffer[0] = 'F';
            HAL_UART_Transmit(&huart3, &FEE.H_UART3.txBuffer[0], 1, 100);
        }
    }
    /* USER CODE END StartTask07 */
}
