/*******************************    INCLUDES   ********************************/

#include "FEE_Robot.h"
#include "dwt_stm32_delay.h"
#include "stdio.h"
#include "math.h"
#include "main.h"
#include "stdlib.h"
/*******************************    DEFINITONS   ******************************/

//#define PI 3.141592654
//extern USBD_HandleTypeDef 			        *pdev1;
//extern USBD_CUSTOM_HID_HandleTypeDef        *hhid1;
/***************************    GLOBAL VARIABLES   ****************************/
uint8_t Start;
uint8_t ktra_khoa;
uint8_t trang_thai_xilanh = 0; 
uint8_t flag_trang_thai_xilanh = 0; 

uint8_t trang_thai_xilanh_tha_lua = 0; 
uint8_t flag_trang_thai_xilanh_tha_lua = 0; 

int16_t goc_rb; 

extern int8_t stop;
extern uint8_t mode_ve_VT;
uint16_t tdc_high = 70; 
uint16_t tdc_low = 40; 
extern uint8_t mode; 
extern FEE_MOTOR DC1, DC2, DC3, DC4, DC5, DC6, DC7, DC8, DC9, DC10;
extern int EncoderCount1; 

/***************************       FUNCTIONS       ****************************/
FEE_Compass_struct_def Compass1;
FEE_Compass_struct_def Compass2;


void FEE_Robot_Innit(void)
{
    Start=1;
    FEE_Compass_Innit(&huart3,Z_axis,&Compass1);
//   FEE_Compass_Innit(&huart6,X_axis,&Compass2);
   FEE_PES_Innit(&huart2);
}


void reset_encoder(void) {
	EncoderCount1 = 0; 
}

void encoder_di_thang(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1); 
}


void encoder_di_ngang(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0); 
}


void keo_lua_vao(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0); 
}

void day_lua_ra(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1); 
}

void day_tay_tha_lua(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1); 	
}

void thu_tay_tha_lua(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0); 	
}

void nut_lai_tay(void) {
	
	
	// ========================== 2 NUT ===========================

/*************************************** day keo xilanh kho giu lua ************************************/		
	
		if(FEE_PES.R1 == 0 && FEE_PES.TamGiac == 0) {
			if(flag_trang_thai_xilanh == 0) {
				if(trang_thai_xilanh == 0) 
					trang_thai_xilanh = 1; 
				else 
					trang_thai_xilanh = 0; 
				
				if(trang_thai_xilanh == 1)
					day_lua_ra(); 
				else 
					keo_lua_vao(); 
				flag_trang_thai_xilanh = 1; 
			}
		}
		else 
			flag_trang_thai_xilanh = 0; 
		
/*************************** day keo xilanh tha lua ******************************/ 
		
		if(FEE_PES.R1 == 0 && FEE_PES.X == 0) {
			if(flag_trang_thai_xilanh_tha_lua == 0) {
				
				if(trang_thai_xilanh_tha_lua == 0) 
					trang_thai_xilanh_tha_lua = 1; 
				
				else 
					trang_thai_xilanh_tha_lua = 0; 
				
				if(trang_thai_xilanh_tha_lua == 1)
					day_tay_tha_lua(); 
				else 
					thu_tay_tha_lua(); 

				flag_trang_thai_xilanh_tha_lua = 1; 
			}
		}
		else 
			flag_trang_thai_xilanh_tha_lua = 0; 		
		
// toc do nhanh 
		
		if( FEE_PES.L1 == 0 && FEE_PES.Up==0&&FEE_PES.Down&&FEE_PES.Vuong&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_thang(); 
			stop = 0;
			Swerve_4_V2_laitay(0,tdc_high,0,100);
		}	
		else if(FEE_PES.L1 == 0 && FEE_PES.Down==0 &&FEE_PES.Up&&FEE_PES.Vuong&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_thang(); 
			stop = 0;			
			Swerve_4_V2_laitay(180 + 1,tdc_high,0,100);
		}
		else if(FEE_PES.L1 == 0  && FEE_PES.Vuong==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_ngang(); 
			stop = 0;
			Swerve_4_V2_laitay(270 ,tdc_high,0,100);
		}
		else 	if(FEE_PES.L1 == 0  && FEE_PES.Tron==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Vuong&&!mode_ve_VT)
		{
			encoder_di_ngang(); 
			stop = 0;
			Swerve_4_V2_laitay(90 + 1,tdc_high,0,100);
		}				
		
//  toc do cham 
		
		else if(FEE_PES.Up==0 && FEE_PES.Down&&FEE_PES.Vuong&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_thang(); 
			stop = 0;
			Swerve_4_V2_laitay(0,tdc_low,0,100);
		}	
		else if(FEE_PES.Down==0 &&FEE_PES.Up&&FEE_PES.Vuong&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_thang(); 
			stop = 0;			
			Swerve_4_V2_laitay(180 + 1,tdc_low,0,100);
		}
		else if(FEE_PES.Vuong==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Tron&&!mode_ve_VT)
		{
			encoder_di_ngang(); 
			stop = 0;
			Swerve_4_V2_laitay(270 ,tdc_low,0,100);
		}
		else 	if(FEE_PES.Tron==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Vuong&&!mode_ve_VT)
		{
			encoder_di_ngang(); 
			stop = 0;
			Swerve_4_V2_laitay(90 + 1,tdc_low,0,100);
		}						

		else if (FEE_PES_Js.left_R==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Vuong&&FEE_PES.Tron&&FEE_PES_Js.right_R&&!mode_ve_VT)
		{	
			stop = 0;			
			Swerve_4_V2_laitay(0,0,0 + 360,10);    
		}
		else if (FEE_PES_Js.right_R==0&&FEE_PES.Up&&FEE_PES.Down&&FEE_PES.Vuong&&FEE_PES.Tron&&FEE_PES_Js.left_R&&!mode_ve_VT)
		{
			stop = 0;
			Swerve_4_V2_laitay(0,0, 0 - 360,10);    
		}

		else
		{	
			if(stop==0)
			{
				Stop_PID();
//				stop_sw();
				stop = 1;
			}
			else
			{
				DC1.Speed = 0;
				DC2.Speed = 0;
				DC3.Speed = 0;
				DC4.Speed = 0;
			}
			ve_vt();
		}
	
}