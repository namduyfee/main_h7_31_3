#ifndef FEE_LIBRARY_H
#define FEE_LIBRARY_H

/*******************************    INCLUDES   ********************************/
#include "stm32h7xx_hal.h"
#include "FEE_RTOS.h"
#include "FEE_USB.h"
#include "FEE_ADC.h"
#include "FEE_EXTI.h"
#include "FEE_GPIO.h"
#include "FEE_PWM.h"
#include "FEE_SPI.h"
#include "FEE_LCD.h"
#include "FEE_UART.h"
#include "FEE_PES_Control.h"
#include "FEE_Compass.h"
#include "FEE_SWERVE_DRIVER.h"
#include "FEE_AT24C128.h"
#include "FEE_Kalman_Filter.h"
#include "DEV_Config.h"
#include "LCD_1in69.h"
#include "GUI_Paint.h"
#include "image.h"
#include "FEE_STM32F103C8T6.h"
#include "FEE_Absolute_Encoder.h"
#include "FEE_Robot.h"
#include "FEE_Main_Phu.h"
#include "FEE_Tu_Dong.h"
#include "dwt_stm32_delay.h"

/*******************************    DEFINITIONS   ********************************/

#define PI 3.141592654
#define angle 		FEE.H_Compass.z_Axis
#define AngleRT 	FEE.H_Compass.zAngle
#define FEE_PES     FEE.H_PES.cmd_b
#define FEE_PES_Js  FEE.H_PES.joystick_b
#define FEE_PES_Btn FEE.H_PES.button_b
#define FEE_UART1   FEE.H_UART1
#define FEE_UART2   FEE.H_UART2
#define FEE_UART3   FEE.H_UART3
#define FEE_UART4   FEE.H_UART4
#define FEE_UART5   FEE.H_UART5
#define FEE_UART6   FEE.H_UART6
#define FEE_UART7   FEE.H_UART7
#define FEE_GPIOIn  FEE.H_GPIO
#define Sick2       FEE.H_ADC.adc_value_Volt[2]
#define Sick4       FEE.H_ADC.adc_value_Volt[4]

extern FEE_Compass_struct_def Compass1;
extern FEE_Compass_struct_def Compass2;

#endif