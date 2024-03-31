#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_customhid.h"
#include "FEE_Library.h"

extern struct FEE_def	FEE;
extern USBD_HandleTypeDef 				 *pdev1;
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

extern double chieu_dc1,chieu_dc2,chieu_dc3,chieu_dc4,goc_dc1,goc_dc2,goc_dc3,goc_dc4;
FEE_MOTOR DC1, DC2, DC3, DC4, DC5, DC6, DC7, DC8, DC9, DC10;


/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
    /* init code for USB_DEVICE */
//  MX_USB_DEVICE_Init();
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1);
			
        pid_dc1(DC1.Dir, DC1.Speed);
        pid_dc2(!DC2.Dir, DC2.Speed);
        pid_dc3(!DC3.Dir, DC3.Speed);
        pid_dc4(!DC4.Dir, DC4.Speed);
        pid_dc5(DC5.Dir, DC5.Speed);
        pid_dc6(DC6.Dir, DC6.Speed);
        pid_dc7(DC7.Dir, DC7.Speed);
        pid_dc8(DC8.Dir, DC8.Speed);

    }
    /* USER CODE END 5 */
}











