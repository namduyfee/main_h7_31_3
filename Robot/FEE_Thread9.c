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
void StartTask09(void const * argument)
{
    /* USER CODE BEGIN StartTask08 */
    /* Infinite loop */
    uint8_t* data = (uint8_t*)&FEE.H_EEprom.Eeprom_Data[0];
    EEPROM_Read(FEE.H_EEprom.PageNum,0,data,40);
    FEE.H_EEprom.Read_Done = 1;
    FEE.H_EEprom.Write_Done = 0;

    for(;;)
    {
        osDelay(1);

//        FEE.H_USB.HID_Tick++;
//        if(FEE.H_USB.HID_Tick >= 10) // 100 x osDelay(1) = 100ms
//        {
//            FEE.H_USB.HID_Tick = 0;
//            FEE.H_USB.HID_Update = 1;
//            FEE_STM32C8T6_Send();
//            if(FEE.H_USB.USB_Verify == 1) /// co ban tin usb tu may tinh
//            {
//                FEE.H_USB.USB_Verify = 0;
//                FEE.H_USB.USB_Connect = 1;
//                HID_Read_Packet(); // nhan du lieu tu usb
//                FEE.H_USB.HID_Update = 1;
//            }
//        }

//        if(FEE.H_STM32C8T6C.RX_Done == 1)
//        {
//            FEE.H_STM32C8T6C.RX_Done = 0;
//        }


////        if(FEE.H_USB.USB_Verify == 1) /// co ban tin usb tu may tinh
////        {
////            FEE.H_USB.USB_Verify = 0;
////            FEE.H_USB.USB_Connect = 1;
////            HID_Read_Packet(); // nhan du lieu tu usb
////            FEE.H_USB.HID_Update = 1;
////        }

//        // cap nhat du lieu uart tu FPGA -> USB HID
//        if((FEE.H_USB.HID_Update == 1)&&
//                (FEE.H_USB.USB_Connect == 1))
//        {
//            FEE.H_USB.HID_Update = 0;
//            HID_Send_Packet(); /// gui du lieu len may tinh

//        }
    }
    /* USER CODE END StartTask08 */
}

