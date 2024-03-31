/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
//#include "usb_device.h"
//#include "usbd_customhid.h" // thu vien ussb hid

//#include "FEE_RTOS.h"
//#include "FEE_USB.h"
//#include "FEE_ADC.h"
//#include "FEE_EXTI.h"
//#include "FEE_GPIO.h"
//#include "FEE_PWM.h"
//#include "FEE_SPI.h"
//#include "FEE_LCD.h"
//#include "FEE_UART.h"
//#include "FEE_PES_Control.h"
//#include "FEE_Compass.h"
//#include "FEE_Robot.h"
//#include "FEE_SWERVE_DRIVER.h"
//#include "FEE_AT24C128.h"
//#include "FEE_Kalman_Filter.h"
//#include "DEV_Config.h"
//#include "LCD_1in69.h"
//#include "GUI_Paint.h"
//#include "image.h"
//#include "FEE_STM32F103C8T6.h"
//#include "FEE_Absolute_Encoder.h"




/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
/* USER CODE BEGIN EM */
//#define PI 3.141592654
//#define angle 		FEE.H_Compass.z_Axis
//#define AngleRT 	FEE.H_Compass.zAngle
//#define FEE_PES     FEE.H_PES.cmd_b
//#define FEE_PES_Js  FEE.H_PES.joystick_b
//#define FEE_PES_Btn FEE.H_PES.button_b
//#define FEE_UART1   FEE.H_UART1
//#define FEE_UART2   FEE.H_UART2
//#define FEE_UART3   FEE.H_UART3
//#define FEE_UART4   FEE.H_UART4
//#define FEE_UART5   FEE.H_UART5
//#define FEE_UART6   FEE.H_UART6
//#define FEE_UART7   FEE.H_UART7
//#define FEE_GPIOIn  FEE.H_GPIO
//#define Sick2       FEE.H_ADC.adc_value_Volt[2]
//#define Sick4       FEE.H_ADC.adc_value_Volt[4]

//#define SS9         FEE_GPIOIn.S9
//#define SS10        FEE_GPIOIn.S10
//#define SS11        FEE_GPIOIn.S11
//#define SS12        FEE_GPIOIn.S12
//#define SS13        FEE_GPIOIn.S13
//#define SS14         FEE_GPIOIn.S14
//#define SS15         FEE_GPIOIn.S15
//#define SS16         FEE_GPIOIn.S16



#define angle 		Compass1.z_Axis
#define AngleRT 	Compass1.zAngle

/* USER CODE END EM */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
typedef enum
{
    X_axis,
    Y_axis,
    Z_axis,
    All_axis,
}_Axis;




	struct FEE_Thong_So_San_struct_def 
	{
		char mau_san; 
		uint8_t vi_tri_dung_1; 
		uint8_t vi_tri_dung_2; 
		uint8_t vi_tri_dung_3; 
		uint8_t huong_start; 
		uint8_t huong_la_thanh; 
		uint8_t toc_do_lua_doc; 
		uint8_t toc_do_lua_ngang; 
	};

	struct FEE_Step_Tudong_struct_def 
	{
		uint8_t tudong_number; 
		uint8_t done_tudong_main1[20]; 
		uint8_t done_tudong_main2[20]; 
		uint8_t dk_cam_bien; 
		uint8_t enable_count; 
		uint8_t cam_bien_mau; 
		uint8_t cam_bien_line; 
		uint8_t Connected_sensor_line ; 
		uint8_t Connected_sensor_color ; 
		
	uint8_t vi_tri_hang_can_den; 
	uint8_t vi_tri_cot_can_den; 
	uint8_t loai_bong_can_lay; 
		
	uint8_t count_bong; 
	uint8_t  check_count_bong; 
	uint8_t enable_count_bong; 
	uint8_t start_count_bong; 	
		
		
	uint8_t vi_tri_bong[3][7]; 
		
	}; 
	
	// struc luu tru du lu main phu 
	struct FEE_Main_Phu_struct_def {
		uint8_t		rxBuffer[8];
		uint8_t		txBuffer[8];
		uint8_t 	Verify;
		uint8_t 	isConnected;
	}; 


// struct luu tru du lieu UART
typedef struct FEE_UART_t
{
		uint8_t		rxBuffer[64];
		uint8_t		txBuffer[64];
		uint8_t		DMA_rxBuffer[64];	
		uint8_t		rx_Data[64];
		uint8_t		CMD1[4];
		uint8_t		CMD2[4];
		uint16_t	RX_size;
		uint16_t	RX_Done;
		uint16_t	RX_Start;
		uint16_t	RX_Counter;
		uint8_t 	TX_Start;
		uint16_t	TX_size;
		uint8_t	TX_Done;
		uint16_t	Disconnect;
		uint16_t	Protect;		
		uint8_t		Update;
		uint16_t	Loss;
}FEE_UART_struct_def;

typedef struct FEE_MOTOR_def
{
    uint8_t Dir;
    uint8_t Speed;
    int16_t Angle;
		uint8_t mode_dc;
		int16_t en_xoay_raw;
		int16_t en_xoay_result;
		int16_t en_xoay_dc;
	
} FEE_MOTOR;

typedef struct FEE_STM32C8T6_t
{
    uint8_t		rxBuffer[64];
    uint8_t		txBuffer[64];
    uint8_t		DMA_rxBuffer[64];
    uint16_t	RX_size;
    uint16_t	RX_Done;
    uint16_t	TX_size;
    uint16_t	TX_Done;
    uint16_t	Disconnect;

    uint8_t 	CMD1;
    uint8_t 	CMD2;
    uint8_t 	CMD3;
    uint8_t 	CMD4;
    uint8_t 	CMD5;
    uint8_t 	CMD6;
    uint8_t 	CMD7;
    uint8_t 	CMD8;
    uint8_t 	CMD9;
    uint8_t 	CMD10;
    uint8_t 	CMD11;
    uint8_t 	CMD12;
    uint8_t 	CMD13;
    uint8_t 	CMD14;
    uint8_t 	CMD15;
    uint8_t 	CMD16;
    uint8_t 	CMD17;
    uint8_t 	CMD18;
}FEE_STM32C8T6_struct_def;

// struct luu tru du lieu ADC
typedef struct FEE_ADC_struct_def
{
    uint32_t 	DMA_adc_value[8]; 		// du lieu luu tru trong DMA
    uint16_t 	adc_value_Raw[8]; 		// gia tri tho
    double 		adc_value_Volt[8]; 		// gia tri dien ap
    double 		adc_value_Result[8]; 	// ket qua tinh toan tu dien ap
    uint16_t 	DMA_done; 		// gia tri doc xong
}FEE_ADC_struct_def;

// struct luu tru du lieu GPIO
typedef struct FEE_GPIO_t
{
    uint8_t 	S1;
    uint8_t 	S2;
    uint8_t 	S3;
    uint8_t 	S4;
    uint8_t 	S5;
    uint8_t 	S6;
    uint8_t 	S7;
    uint8_t 	S8;

    uint8_t 	S9;
    uint8_t 	S10;
    uint8_t 	S11;
    uint8_t 	S12;
    uint8_t 	S13;
    uint8_t 	S14;
    uint8_t 	S15;
    uint8_t 	S16;

    uint8_t 	S17;
    uint8_t 	S18;
    uint8_t 	S19;
    uint8_t 	S20;
    uint8_t 	S21;
    uint8_t 	S46;
    uint8_t 	Led_Status;
    uint8_t 	DIR4;

    uint8_t 	S22;
    uint8_t 	S23;
    uint8_t 	S24;
    uint8_t 	S25;
    uint8_t 	S26;
    uint8_t 	S27;
    uint8_t 	S28;
    uint8_t 	S29;

    uint8_t 	S30;
    uint8_t 	S31;
    uint8_t 	S32;
    uint8_t 	S33;
    uint8_t 	S34;
    uint8_t 	S35;
    uint8_t 	S36;
    uint8_t 	S37;

    uint8_t 	S38;
    uint8_t 	S39;
    uint8_t 	S40;
    uint8_t 	S41;
    uint8_t 	S42;
    uint8_t 	S43;
    uint8_t 	S44;
    uint8_t 	S45;

    uint8_t 	GPIO_EXTI;
    uint8_t 	GPIO_S1_S8;
    uint8_t 	GPIO_S9_S16;
    uint8_t 	GPIO_S17_S21;
    uint8_t 	GPIO_S22_S29;
    uint8_t 	GPIO_S30_S37;
    uint8_t 	GPIO_S38_S45;

    uint16_t	EXTI_Counter1;
    uint16_t	EXTI_Counter2;
    uint16_t	EXTI_Counter3;
    uint16_t	EXTI_Counter4;
    uint16_t	EXTI_Counter5;
    uint16_t	EXTI_Counter6;
    int16_t	EXTI_Counter7;
    int16_t	EXTI_Counter8;

}FEE_GPIO_struct_def;

// struct luu tru du lieu USB
typedef struct FEE_USB_t
{
    uint8_t		USB_Data_IN[64];
    uint8_t		USB_Data_OUT[64];
    uint8_t 	Ui;
    uint8_t 	Uj;
    uint8_t 	USB_Verify;
    uint8_t 	USB_Connect;
    uint8_t 	USB_Send;

    uint8_t		HID_Counter;
    uint8_t		HID_Counter2;

    uint16_t	HID_Tick;
    uint16_t	HID_Tick2;
    uint8_t		HID_Update;
}FEE_USB_struct_def;


// struct luu tru du lieu USB
typedef struct FEE_PES_t
{
    uint8_t		RX_Data[8];
    uint8_t		DMA_Data[8];
    uint8_t 	Verify;
    uint8_t 	IsConnected;
    TickType_t 	Timeout;

    uint8_t 	Header;
    union {
        uint8_t 	PES[2];
        struct {
            uint16_t Select:1;
            uint16_t L:1;
            uint16_t R:1;
            uint16_t Start:1;
            uint16_t Up:1;
            uint16_t Right:1;
            uint16_t Down:1;
            uint16_t Left:1;

            uint16_t L2:1;
            uint16_t R2:1;
            uint16_t L1:1;
            uint16_t R1:1;
            uint16_t TamGiac:1;
            uint16_t Tron:1;
            uint16_t X:1;
            uint16_t Vuong:1;
        } cmd_b;
    };

    union {
        uint8_t 	US[4]; //uint8_t 	US[3]
        struct {
            uint32_t S1:1;
            uint32_t S2:1;
            uint32_t S3:1;
            uint32_t S4:1;
            uint32_t S5:1;
            uint32_t S6:1;
            uint32_t S7:1;
            uint32_t S8:1;

            uint32_t S9:1;
            uint32_t S10:1;
            uint32_t S11:1;
            uint32_t S12:1;
            uint32_t S13:1;
            uint32_t S14:1;
            uint32_t S15:1;
            uint32_t S16:1;

            uint32_t S17:1;
            uint32_t S18:1;
            uint32_t S19:1;
            uint32_t S20:1;
            uint32_t S21:1;
            uint32_t S22:1;
            uint32_t S23:1;
            uint32_t S24:1;
            uint32_t 	:8;
        } button_b;
    };

    union {
        uint8_t 	Analog;
        struct {
            uint8_t down_L:1;
            uint8_t up_L:1;
            uint8_t right_L:1;
            uint8_t left_L:1;

            uint8_t down_R:1;
            uint8_t up_R:1;
            uint8_t right_R:1;
            uint8_t left_R:1;
        } joystick_b;
    };
    uint8_t 	CMD_Byte8;

}FEE_PES_struct_def;

// struct luu tru du lieu USB
typedef struct FEE_Compass_t
{
    UART_HandleTypeDef* UartCompass;
    uint8_t     get_Axis;
    uint8_t		TX_Data[8];
    uint8_t		RX_Data[8];
    uint8_t		RX_Data_Y[8];
    uint8_t     Header[3];
    uint32_t 	Timeout;
    int16_t 	ss_g_now;
    int16_t 	ss_g_pre;

    uint8_t 	i_compass;
    uint8_t 	isConnected;
    uint8_t     byHeadIsTrue;
    
    uint8_t 	xH;
    uint8_t 	xL;

    uint8_t 	yH;
    uint8_t 	yL;

    uint8_t 	zH;
    uint8_t 	zL;
    
    
    int16_t 	x_offset;
    int16_t 	y_offset;
    int16_t 	z_offset;
    

    int16_t 	x_Axis;
    int16_t 	y_Axis;
    int16_t 	z_Axis;

    int16_t 	xAngle;
    int16_t 	yAngle;
    int16_t 	zAngle;
    int16_t 	fAngle;
}FEE_Compass_struct_def;

typedef struct FEE_EEprom_t
{		
    int16_t 	Read_Start;
    int16_t 	Write_Start;
    int16_t 	Read_Point;
    int16_t 	Write_Point;
    int16_t 	Read_Done;
    int16_t 	Write_Done;
    int16_t 	Cell_Data;
    uint16_t 	Eeprom_Data[20];
    uint16_t 	USB_Data[20];
    uint16_t    Counter;
    uint8_t     PageNum;
}FEE_EEprom_struct_def;

// struct du lieu he thong
struct FEE_def
{
    FEE_UART_struct_def H_UART1;
    FEE_UART_struct_def H_UART2;
    FEE_UART_struct_def H_UART3;
    FEE_UART_struct_def H_UART4;
    FEE_UART_struct_def H_UART5;
    FEE_UART_struct_def H_UART6;
    FEE_UART_struct_def H_UART7;
    FEE_UART_struct_def H_UART8;
    FEE_UART_struct_def H_UART9;
    FEE_UART_struct_def H_UART10;
    FEE_UART_struct_def H_Remote;

    FEE_ADC_struct_def H_ADC;
    FEE_GPIO_struct_def H_GPIO;
    FEE_USB_struct_def H_USB;
    FEE_PES_struct_def H_PES;
    FEE_Compass_struct_def H_Compass;
    FEE_STM32C8T6_struct_def H_STM32C8T6C;
    FEE_STM32C8T6_struct_def H_STM32C8T6P;
    FEE_EEprom_struct_def H_EEprom;
	
		struct FEE_Main_Phu_struct_def Main_Phu_1; 
		struct FEE_Main_Phu_struct_def Main_Phu_2; 
		
		struct FEE_Step_Tudong_struct_def TuDong; 
		struct FEE_Thong_So_San_struct_def Ts_San; 	
    
    uint8_t		UART_Update;
    uint16_t	UART_Loss;

    uint8_t		Process_Mode;
    uint8_t		Process_done;
    uint8_t		Request_Save_Flash;
    uint8_t		Request_Read_Flash;

    uint16_t	Pulse;
    int16_t		Buff_Duty;
    
};

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
