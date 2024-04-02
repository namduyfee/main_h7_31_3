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
extern int EncoderCount1;
extern int8_t step_number_td7; 

char String_LCD[30];


/* USER CODE BEGIN Header_StartTask08 */
/**
* @brief Function implementing the myTask08 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask08 */
void StartTask12(void const * argument)
{
    /* USER CODE BEGIN StartTask08 */
    /* Infinite loop */
	lcd_put_cur(1,0);
	lcd_send_string("FEE_MPU6050 Start  ");
	FEE_PES_Innit(&huart2);
  lcd_put_cur(1,0);
	lcd_send_string("FEE_PES Start  ");
	lcd_clear();	
    for(;;)
    {
			osDelay(1); 
			
			sprintf(String_LCD, "%4d",Compass1.zAngle);
			lcd_put_cur(0,0);
			lcd_send_string(String_LCD);
		
//			sprintf(String_LCD, "%2d",step_number_td7);
//			lcd_put_cur(1,14);
//			lcd_send_string(String_LCD);
			
			// 260  12336
			
//			sprintf(String_LCD, "%4d",EncoderCount1);
//			lcd_put_cur(0,6);
//			lcd_send_string(String_LCD); 
//		
//			sprintf(String_LCD, "%5.1f",FEE.H_ADC.adc_value_Result[1]);
//			lcd_put_cur(0,8);
//			lcd_send_string(String_LCD);
		
//			sprintf(String_LCD, "%5.1f",FEE.H_ADC.adc_value_Result[0]);
//			lcd_put_cur(0,8);
//			lcd_send_string(String_LCD);			
			
			sprintf(String_LCD, "%5.1f",FEE.H_ADC.adc_value_Result[4]);
			lcd_put_cur(1,0);
			lcd_send_string(String_LCD);
//		
//			sprintf(String_LCD, "%5.1f",FEE.H_ADC.adc_value_Result[5]);
//			lcd_put_cur(1,8);
//			lcd_send_string(String_LCD);		
    }
    /* USER CODE END StartTask08 */
}
