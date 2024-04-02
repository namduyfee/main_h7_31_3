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


/* USER CODE BEGIN Header_StartTask08 */
/**
* @brief Function implementing the myTask08 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask08 */
void StartTask11(void const * argument)
{
    /* USER CODE BEGIN StartTask08 */
    /* Infinite loop */
    for(;;)
    {
			
      osDelay(1);
//			if(7 <= FEE.TuDong.tudong_number) {
//				if(0 == FEE.TuDong.Connected_sensor_color) {
//					
//					HAL_UART_Receive_IT(&huart6, &FEE.TuDong.cam_bien_mau, 1); 
////					FEE.TuDong.Connected_sensor_color = 1; 
//				}
//			}
    }
    /* USER CODE END StartTask08 */
}

