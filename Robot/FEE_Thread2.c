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



int check_vi_tri_lua = 0; 
extern uint8_t mode;
extern uint8_t khoi_tao; 




/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
SPI1_Enccoder En1;
double angle_EN1;
void StartTask02(void const * argument)
{
    /* USER CODE BEGIN StartTask02 */
    /* Infinite loop */
    for(;;)
    {
      osDelay(1);		
			if(mode == 1) {
				if(0 != khoi_tao) {
					if(FEE_GPIOIn.S14 == 1 && FEE_GPIOIn.S6 == 1) {
						if(0 == FEE.TuDong.enable_count) {
							if(check_vi_tri_lua == 0) {
								FEE.TuDong.dk_cam_bien++; 
								if(FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_1) {
									FEE.TuDong.tudong_number = 1;
									FEE.TuDong.enable_count = 1; 
								}
								else if ( FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_2) {
									FEE.TuDong.tudong_number = 3; 
									FEE.TuDong.enable_count = 1; 
								}
								else if ( FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_3) {
									FEE.TuDong.tudong_number = 5; 
									FEE.TuDong.enable_count = 1; 
								}
								check_vi_tri_lua = 1; 
							}
						}
					}
					if(FEE_GPIOIn.S14 == 0 && FEE_GPIOIn.S6 == 0)
						check_vi_tri_lua = 0; 	
				}
				
				
				
				
			}		
	}			
}
