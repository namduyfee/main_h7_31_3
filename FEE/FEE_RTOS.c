/*******************************    INCLUDES   ********************************/

#include "main.h"
#include "usbd_customhid.h"
//#define AngleRT FEE.H_Compass.Angle
#include "FEE_Library.h"


#define FEE_GPIOIn  FEE.H_GPIO

/***************************    GLOBAL VARIABLES   ****************************/

USBD_HandleTypeDef 				    *pdev1;
USBD_CUSTOM_HID_HandleTypeDef       *hhid1;

struct FEE_def		    FEE;
int i = 0;
int EncoderCount = 0;
char EncoderVal =0;
int EncoderCount1 = 0;
char EncoderVal1 =0;
extern FEE_Compass_struct_def Compass1;
extern FEE_Compass_struct_def Compass2;

extern uint8_t check_xoay_tha_lua; 

extern uint8_t enable_di_chuyen_td7; 

uint8_t comple_receiver_main_1[20] = {0}; 
uint8_t comple_receiver_main_2[20] = {0}; 

/***************************       FUNCTIONS       ****************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_0)
    {
        FEE_GPIOIn.EXTI_Counter1++;
    }
    if(GPIO_Pin==GPIO_PIN_1)
    {
        FEE_GPIOIn.EXTI_Counter2++;
    }
    if(GPIO_Pin==GPIO_PIN_2)
    {
        FEE_GPIOIn.EXTI_Counter3++;
    }
    if(GPIO_Pin==GPIO_PIN_3)
    {
        FEE_GPIOIn.EXTI_Counter4++;
    }
    if(GPIO_Pin==GPIO_PIN_4||GPIO_Pin==GPIO_PIN_5)
    {
        int Array1[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
        char A = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4);
        char B = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
        EncoderVal = EncoderVal<<2;
        EncoderVal = ((A<<1)|B|EncoderVal)&0x0f;
        EncoderCount += Array1[EncoderVal];
        FEE_GPIOIn.EXTI_Counter7 = EncoderCount/4;

    }
    if(GPIO_Pin==GPIO_PIN_6||GPIO_Pin==GPIO_PIN_9)
    {
        int Array1[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
        char A = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
        char B = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
        EncoderVal1 = EncoderVal1<<2;
        EncoderVal1 = ((A<<1)|B|EncoderVal1)&0x0f;
        EncoderCount1 += Array1[EncoderVal1];
        FEE_GPIOIn.EXTI_Counter8 = EncoderCount1/4;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1) // C8T6
    {
        FEE_STM32C8T6_Read();
    }

    if(huart->Instance == USART2) // PES
    {
        pes_uart_event_handle();
    }

    if(huart->Instance == USART3) // ComPass1
    {
        FEE_Compass_Process(&Compass1);
    }

	if(huart->Instance == UART5) //Main Phu 1
	{
		FEE_Main_Phu_Read(1); 
		
		if(FEE.Main_Phu_1.rxBuffer[0] == 'a') {
			if(0 == comple_receiver_main_1[1]) {
				FEE.TuDong.tudong_number = 2; 
				comple_receiver_main_1[1] = 1; 
				FEE.TuDong.done_tudong_main1[1] = 1; 
			}
		}
		
		if(FEE.Main_Phu_1.rxBuffer[0] == 'B')  {
			if(0 == comple_receiver_main_1[4]) {
				FEE.TuDong.tudong_number = 4; 
				comple_receiver_main_1[4] = 1; 
			}
		}
		if(FEE.Main_Phu_1.rxBuffer[0] == 'c') {
			if(0 == comple_receiver_main_1[6]) {
				FEE.TuDong.tudong_number = 6; 
				comple_receiver_main_1[6] = 1; 
			}
		}
		
		
		// da xoay xong sau khi tha 2 lua 
		if(FEE.Main_Phu_1.rxBuffer[0] == 'd')
			if(0 == comple_receiver_main_1[7])
				comple_receiver_main_1[7] = 1; 
		
		// da xoay xong sau khi tha 4 lua 
		if(FEE.Main_Phu_1.rxBuffer[0] == 'e') 
			if(0 == comple_receiver_main_1[8]) 
				comple_receiver_main_1[8] = 1; 

		// da xoay xong sau khi tha 6 lua 
		if(FEE.Main_Phu_1.rxBuffer[0] == 'f') 
			if(0 == comple_receiver_main_1[9]) 
				comple_receiver_main_1[9] = 1; 
	
		
		// da san sang tha 2 lua ke cuoi 
		if(FEE.Main_Phu_1.rxBuffer[0] == 'g') 
			if(0 == comple_receiver_main_1[10]) 
				comple_receiver_main_1[10] = 1; 			
		
		// san sang tha 2 lua cuoi 
		if(FEE.Main_Phu_1.rxBuffer[0] == 'h') 
			if(0 == comple_receiver_main_1[11]) 
				comple_receiver_main_1[11] = 1;					
			
			
		if(FEE.Main_Phu_1.rxBuffer[0] == '^') {
			if(0 == comple_receiver_main_1[18]) {
				comple_receiver_main_1[18] = 1;		
				day_lua_ra(); 
		}
	}			
			
		if(FEE.Main_Phu_1.rxBuffer[0] == '&') {
			if(0 == comple_receiver_main_1[19]) {
				comple_receiver_main_1[19] = 1;		
				day_tay_tha_lua(); 
		}
	}
		
	if(FEE.Main_Phu_1.rxBuffer[0] == 'N') 
		if(enable_di_chuyen_td7 == 1)
			enable_di_chuyen_td7 = 0; 
		
		HAL_UART_Receive_IT(&huart5, &FEE.H_UART5.rxBuffer[0], 1);
	}		
	
	if(huart->Instance == USART6)
		HAL_UART_Receive_IT(&huart6, &FEE.TuDong.cam_bien_mau, 1); 	
	
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

}

void FEE_Data_Innit(void)
{
    FEE.UART_Update 		= 0;
    FEE.UART_Loss 			= 0;

    FEE.Process_Mode		= 0;
    FEE.Process_done		= 0;
    FEE.Request_Save_Flash	= 0;
    FEE.Request_Read_Flash	= 0;

    FEE.Pulse 				= 0;
    FEE.Buff_Duty 			= 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{

}

void FEE_RTOS_Innit(void)
{
    FEE_LCD_Innit();
    FEE_Data_Innit();
    FEE_ADC_Innit();
    FEE_USB_Innit();
    FEE_EXTI_Innit();
    FEE_GPIO_Innit();
//	FEE_PWM_Innit();
    FEE_SPI_Innit();
    FEE_UART_Innit();
    HAL_Delay(100);
}


