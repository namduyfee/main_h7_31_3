#include "FEE_STM32F103C8T6.h"
#include "main.h"

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

int pc8 = 0;

void FEE_STM32F103C8T6_Innit(void)
{
    for(pc8 = 0; pc8 < 64; pc8++)
    {
        FEE.H_STM32C8T6C.rxBuffer[pc8] = 0;
        FEE.H_STM32C8T6C.txBuffer[pc8] = 0;
        FEE.H_STM32C8T6C.DMA_rxBuffer[pc8] = 0;
    }

    FEE.H_STM32C8T6C.RX_size = 0;
    FEE.H_STM32C8T6C.RX_Done = 0;
    FEE.H_STM32C8T6C.TX_size = 0;
    FEE.H_STM32C8T6C.TX_Done = 0;
    FEE.H_STM32C8T6C.Disconnect = 0;

    FEE.H_STM32C8T6C.CMD1 = 0;
    FEE.H_STM32C8T6C.CMD2 = 0;
    FEE.H_STM32C8T6C.CMD3 = 0;
    FEE.H_STM32C8T6C.CMD4 = 0;
    FEE.H_STM32C8T6C.CMD5 = 0;
    FEE.H_STM32C8T6C.CMD6 = 0;
    FEE.H_STM32C8T6C.CMD7 = 0;
    FEE.H_STM32C8T6C.CMD8 = 0;
    FEE.H_STM32C8T6C.CMD9 = 0;
    FEE.H_STM32C8T6C.CMD10 = 0;
    FEE.H_STM32C8T6C.CMD11 = 0;
    FEE.H_STM32C8T6C.CMD12 = 0;
    FEE.H_STM32C8T6C.CMD13 = 0;
    FEE.H_STM32C8T6C.CMD14 = 0;
    FEE.H_STM32C8T6C.CMD15 = 0;
    FEE.H_STM32C8T6C.CMD16 = 0;
    FEE.H_STM32C8T6C.CMD17 = 0;
    FEE.H_STM32C8T6C.CMD18 = 0;
}

void FEE_STM32C8T6_Read(void)
{
    for(pc8 = 0; pc8 < 20; pc8++)
    {
        FEE.H_STM32C8T6C.rxBuffer[pc8] = FEE.H_UART1.DMA_rxBuffer[pc8];
    }
    FEE.H_STM32C8T6C.RX_Done = 1;
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

    // tiep tuc nhan du lieu
    HAL_UART_Receive_IT(&huart1, FEE.H_UART1.DMA_rxBuffer, 20);
    //HAL_UART_Receive_IT(&huart1, FEE.H_UART1.DMA_rxBuffer, 20);
}

void FEE_STM32C8T6_Send(void)
{
    // ban tin dieu khien GPIO : stm32f103c8t6
    FEE.H_UART1.txBuffer[0] = 'F';
    FEE.H_UART1.txBuffer[1] = 'E';
    FEE.H_UART1.txBuffer[2] = 'E';
    FEE.H_UART1.txBuffer[3] = FEE.H_GPIO.GPIO_S22_S29;
    FEE.H_UART1.txBuffer[4] = FEE.H_GPIO.GPIO_S30_S37;
    FEE.H_UART1.txBuffer[5] = FEE.H_STM32C8T6C.CMD1;
    FEE.H_UART1.txBuffer[6] = FEE.H_STM32C8T6C.CMD2;
    FEE.H_UART1.txBuffer[7] = FEE.H_STM32C8T6C.CMD3;
    FEE.H_UART1.txBuffer[8] = FEE.H_STM32C8T6C.CMD4;
    FEE.H_UART1.txBuffer[9] = FEE.H_STM32C8T6C.CMD5;
    FEE.H_UART1.txBuffer[10] = FEE.H_STM32C8T6C.CMD6;
    FEE.H_UART1.txBuffer[11] = FEE.H_STM32C8T6C.CMD7;
    FEE.H_UART1.txBuffer[12] = FEE.H_STM32C8T6C.CMD8;
    FEE.H_UART1.txBuffer[13] = FEE.H_STM32C8T6C.CMD9;
    FEE.H_UART1.txBuffer[14] = FEE.H_STM32C8T6C.CMD10;
    FEE.H_UART1.txBuffer[15] = FEE.H_STM32C8T6C.CMD11;
    FEE.H_UART1.txBuffer[16] = FEE.H_STM32C8T6C.CMD12;
    FEE.H_UART1.txBuffer[17] = FEE.H_STM32C8T6C.CMD13;
    FEE.H_UART1.txBuffer[18] = FEE.H_STM32C8T6C.CMD14;
    FEE.H_UART1.txBuffer[19] = FEE.H_STM32C8T6C.CMD15;

    HAL_UART_Transmit(&huart1, FEE.H_UART1.txBuffer, 20, 20);
}

void FEE_STM32C8T6P_Read(void)
{
    for(pc8 = 0; pc8 < 10; pc8++)
    {
      FEE.H_STM32C8T6P.rxBuffer[pc8] = FEE.H_UART6.rxBuffer[pc8];
    }
    FEE.H_STM32C8T6P.RX_Done = 1;
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

    // tiep tuc nhan du lieu
		HAL_UART_Receive_IT(&huart6,(uint8_t*) FEE.H_UART6.rxBuffer,10);
}

void FEE_STM32C8T6P_Send(void)
{
//	if(FEE_RTOS_struct.H_UART6.TX_Start)
//	{
//		FEE_RTOS_struct.H_UART6.TX_Start = 0;
    FEE.H_UART6.txBuffer[0] = 'F';
    FEE.H_UART6.txBuffer[1] = 'E';
    FEE.H_UART6.txBuffer[2] = 'E';
    FEE.H_UART6.txBuffer[3] = FEE.H_STM32C8T6P.CMD1;
    FEE.H_UART6.txBuffer[4] = FEE.H_STM32C8T6P.CMD2;
    FEE.H_UART6.txBuffer[5] = FEE.H_STM32C8T6P.CMD3;
    FEE.H_UART6.txBuffer[6] = FEE.H_STM32C8T6P.CMD4;
    FEE.H_UART6.txBuffer[7] = FEE.H_STM32C8T6P.CMD5;
    FEE.H_UART6.txBuffer[8] = FEE.H_STM32C8T6P.CMD6;
    FEE.H_UART6.txBuffer[9] = FEE.H_STM32C8T6P.CMD7;
    FEE.H_UART6.txBuffer[10] = FEE.H_STM32C8T6P.CMD8;
    FEE.H_UART6.txBuffer[11] = FEE.H_STM32C8T6P.CMD9;
    FEE.H_UART6.txBuffer[12] = FEE.H_STM32C8T6P.CMD10;
    FEE.H_UART6.txBuffer[13] = FEE.H_STM32C8T6P.CMD11;
    FEE.H_UART6.txBuffer[14] = FEE.H_STM32C8T6P.CMD12;
    FEE.H_UART6.txBuffer[15] = FEE.H_STM32C8T6P.CMD13;
    FEE.H_UART6.txBuffer[16] = FEE.H_STM32C8T6P.CMD14;
    FEE.H_UART6.txBuffer[17] = FEE.H_STM32C8T6P.CMD15;
    FEE.H_UART6.txBuffer[18] = FEE.H_STM32C8T6P.CMD16;
    FEE.H_UART6.txBuffer[19] = FEE.H_STM32C8T6P.CMD17;
	
    HAL_UART_Transmit(&huart6, FEE.H_UART6.txBuffer, 20, 50);
//	}
}
