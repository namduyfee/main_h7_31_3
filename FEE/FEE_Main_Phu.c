#include "main.h"
#include "FEE_main_phu.h"
#include "FEE_Library.h"


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

int pc = 0;
uint8_t tem_tx_data_main_phu_1 = '&'; 
uint8_t so_lan_trans_main_phu_1 = 40; 

void FEE_Main_Phu_Innit(uint8_t main_phu_number)
{
		for(pc = 0; pc < 8; pc++)
	{
		if(main_phu_number == 1) {
			FEE.Main_Phu_1.rxBuffer[pc] = 0;
			FEE.Main_Phu_1.txBuffer[pc] = 0;
			FEE.Main_Phu_1.Verify = 0;
			FEE.Main_Phu_1.isConnected = 0;
		}
		if(main_phu_number == 2) {
			FEE.Main_Phu_2.rxBuffer[pc] = 0;
			FEE.Main_Phu_2.txBuffer[pc] = 0;
			FEE.Main_Phu_2.Verify = 0;
			FEE.Main_Phu_2.isConnected = 0;
		}
		
	}
}

void FEE_Main_Phu_Read(uint8_t main_phu_number)
{
		for(pc = 0; pc < 8; pc++)
		{
		if(main_phu_number == 1)		 
			FEE.Main_Phu_1.rxBuffer[pc] = FEE.H_UART5.rxBuffer[pc];
		if(main_phu_number == 2) 	 
			FEE.Main_Phu_2.rxBuffer[pc] = FEE.H_UART6.rxBuffer[pc];
		}
							
//		// tiep tuc nhan du lieu
//		if(main_phu_number == 1) 
//				HAL_UART_Receive_IT(&huart5, &FEE_RTOS_struct.Main_Phu_1.rxBuffer[0], 1);
//		if(main_phu_number == 2) 
//				HAL_UART_Receive_IT(&huart6, &FEE_RTOS_struct.Main_Phu_2.rxBuffer[0], 1);
}

void FEE_Main_Phu_Send(uint8_t main_phu_number, uint8_t data)
{
	// send data to main_phu 
	if(main_phu_number == 1) {
		
		if(tem_tx_data_main_phu_1 != data) 
			so_lan_trans_main_phu_1 = 40; 
		
		tem_tx_data_main_phu_1 = data; 
		
		if(so_lan_trans_main_phu_1 > 1) {
			FEE.H_UART5.txBuffer[0] = data; 
			HAL_UART_Transmit(&huart5, FEE.H_UART5.txBuffer, 1, 20);
			so_lan_trans_main_phu_1--; 
		}
		
	}
	
	if(main_phu_number == 2) {
		FEE.H_UART6.txBuffer[0] = data; 
		HAL_UART_Transmit(&huart6, FEE.H_UART6.txBuffer, 1, 20);
	}
	
	
}
