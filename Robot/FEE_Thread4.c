#include "main.h"
#include "usbd_customhid.h"
#include "dwt_stm32_delay.h"
#include "FEE_Library.h"
extern struct FEE_def	FEE;
//extern USBD_HandleTypeDef 								*pdev1;
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
extern char String_LCD[30];

uint8_t mode = 0;
int check_start = 0; 
uint8_t tem = 0; 

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
    /* USER CODE BEGIN StartTask04 */
    /* Infinite loop */
	
	FEE_TuDong_Init(); 

	for(;;)
	{
			
	// =======  ve goc 0, 	dieu khien chieu quay banh ====== //
		osDelay(1);
		
		if(FEE_PES.L2==0)
			vegoc0();
		else if(FEE_PES.L1==0&&FEE_PES.Select==0)
		{	
			osDelay(200);
			vegoc04();
		}
			
			
// ================== thiet lap mode tu dong or lai tay ====== // 		
		if(0 == FEE_PES.Start)
		{
			if(0 == check_start) {
				if(mode == 1)
					mode = 0; 
				else if(mode == 0)
					mode = 1; 
				check_start = 1;
			}
//			while(FEE_PES.TamGiac==1 && FEE_GPIOIn.EXTI_Counter8<1000)
//			{
//		testtd=TocDoen(20,30,200,FEE_GPIOIn.EXTI_Counter8,1000,5,30);
//		//testtd=TocDoenmoi(20,100,100,50,200,FEE_GPIOIn.EXTI_Counter8,1000,10,20,10,10);
//		Swerve_3(90,testtd,0,50,30,24,2,2,1);
//			}
		}
		else 
			check_start = 0;
	
		
// ========== chon che do san =============== // 
		
		if (0 == FEE_PES.Select && 0 == FEE_PES.Left) {
			// san do 
			FEE.Ts_San.mau_san = 'D';
			FEE.Ts_San.vi_tri_dung_1 = 3; 
			FEE.Ts_San.vi_tri_dung_2 = 6; 
			FEE.Ts_San.vi_tri_dung_3 = 9;
			tem = 1; 
		}
		
		else if ( 0 == FEE_PES.Select && 0 == FEE_PES.Right ) {
			// san xanh 
			FEE.Ts_San.mau_san = 'X';
			FEE.Ts_San.vi_tri_dung_1 = 2; 
			FEE.Ts_San.vi_tri_dung_2 = 5; 
			FEE.Ts_San.vi_tri_dung_3 = 8; 
		}
//		if(('X' == FEE.Ts_San.mau_san) || ('D' == FEE.Ts_San.mau_san)) {
//			sprintf(String_LCD, "%c", FEE.Ts_San.mau_san);
//			lcd_put_cur(1,5);
//			lcd_send_string(String_LCD);
//		}		

	}
}
