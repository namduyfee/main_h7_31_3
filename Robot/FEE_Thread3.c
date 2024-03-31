#include "main.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include "usbd_customhid.h"
#include "FEE_Library.h"

extern struct FEE_def	FEE;
extern USBD_HandleTypeDef 			   *pdev1;
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

void SET_MAIN_ADC_Channel(uint8_t Channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    if(Channel == 0) sConfig.Channel = ADC_CHANNEL_3;
    else if(Channel == 1) sConfig.Channel = ADC_CHANNEL_4;
    else if(Channel == 2) sConfig.Channel = ADC_CHANNEL_5;
    else if(Channel == 3) sConfig.Channel = ADC_CHANNEL_7;
    else if(Channel == 4) sConfig.Channel = ADC_CHANNEL_8;
    else if(Channel == 5) sConfig.Channel = ADC_CHANNEL_9;
    else if(Channel == 6) sConfig.Channel = ADC_CHANNEL_10;
    else if(Channel == 7) sConfig.Channel = ADC_CHANNEL_11;

    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_8CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    sConfig.OffsetSignedSaturation = DISABLE;
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    //sConfig.Channel = ADC_CHANNEL_3;
    //sConfig.Rank = 1;
    //sConfig.SamplingTime = ADC_SAMPLETIME_8CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
    /* USER CODE BEGIN StartTask03 */
    /* Infinite loop */
    //HAL_ADC_Start(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    osDelay(10);
    // cai dat ADC DMA
    //HAL_ADC_Start_DMA(&hadc1, (uint32_t*) FEE.H_ADC.DMA_adc_value, 8);
    //osDelay(50);

    for(;;)
    {
        osDelay(1);
        SET_MAIN_ADC_Channel(0);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[0] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(1);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[1] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(2);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[2] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(3);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[3] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(4);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[4] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(5);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[5] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(6);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[6] = HAL_ADC_GetValue(&hadc1);

        //osDelay(1);
        SET_MAIN_ADC_Channel(7);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        FEE.H_ADC.adc_value_Raw[7] = HAL_ADC_GetValue(&hadc1);

        FEE_ADC_Kalman_Filter();
    }
    /* USER CODE END StartTask03 */
}

