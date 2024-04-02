#include "main.h"
#include "usbd_customhid.h"
#include "FEE_Library.h"
extern struct FEE_def	        FEE;
//extern USBD_HandleTypeDef 			        *pdev1;
//extern USBD_CUSTOM_HID_HandleTypeDef        *hhid1;

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
extern uint8_t mode; 

extern uint8_t comple_receiver_main_1[20];  

extern uint8_t tem_trang_thai_td7; 
extern int8_t step_number_td7; 
extern uint8_t enable_send_td7; 
extern uint8_t tx_td7; 
extern uint8_t tx_td5; 

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void const * argument)
{
    /* USER CODE BEGIN StartTask06 */
    /* Infinite loop */
	FEE_Main_Phu_Innit(1); 
	
    for(;;)
    {
			
			osDelay(1);
			
			if (mode == 1) {
				
				for (int i = 1; i < 20; i++) {
					
					if (i == FEE.TuDong.tudong_number) {
						if (1 == FEE.TuDong.done_tudong_main1[i - 1] ) {
							 
								if (1 == FEE.TuDong.tudong_number) {
									FEE_Main_Phu_Send(1, 'a'); 
									
									if(0 == FEE.Main_Phu_1.isConnected) {
										HAL_UART_Receive_IT(&huart5, &FEE.H_UART5.rxBuffer[0], 1);
										FEE.Main_Phu_1.isConnected = 1; 
									}
								}
								
								else if(2 == FEE.TuDong.tudong_number) {
									osDelay(120); 
									keo_lua_vao(); 
									FEE.TuDong.done_tudong_main1[1] = 2; 
								}
								
								else if (3 == FEE.TuDong.tudong_number)
									FEE_Main_Phu_Send(1, 'b'); 
								
								else if (5 == FEE.TuDong.tudong_number) 
									FEE_Main_Phu_Send(1, 'c'); 
								
								else if(7 == FEE.TuDong.tudong_number && enable_send_td7 == 1)
									FEE_Main_Phu_Send(1, tx_td7); 
								
						}
						break; 
					}
					else {
					}
					
				}
			}
			else {
			
			}				
    }
    /* USER CODE END StartTask06 */
}

