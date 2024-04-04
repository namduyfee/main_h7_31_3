#include "main.h"
#include "usbd_customhid.h"
//#define AngleRT FEE.H_Compass.Angle
#include "FEE_Library.h"
#include "math.h"


extern struct FEE_def	FEE;
//extern USBD_HandleTypeDef 			   *pdev1;
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
extern FEE_Compass_struct_def Compass1;

int toc_do=0;
extern uint8_t mode;
extern FEE_MOTOR DC1, DC2, DC3, DC4, DC5, DC6, DC7, DC8, DC9, DC10;
int8_t stop;
extern uint8_t mode_ve_VT;
extern int16_t goc_rb; 
extern int EncoderCount1; 
extern uint8_t comple_receiver_main_1[20]; 

uint8_t tem_en = 0; 				

/**************************** TDD5 **********************************/
uint8_t tx_td5; 
/**************************** TDD7 **********************************/ 
uint8_t tem_trang_thai_td7 = 0; 			// thoat while
int8_t step_number_td7 = 0; 					// cac vi tri tha lua 
uint8_t enable_send_td7 = 0; 				// cho phep truyen 
uint8_t tx_td7; 
uint8_t enable_di_chuyen_td7 = 0; 								

uint8_t enable_lai_tay_td7 = 0; 										// 1 : cho phep lai tay 0 ; la ko dc lai tay
//uint8_t tx_td7; 
//int tem_goc_td7; 
//uint8_t tem_break_td7; 
//uint8_t tem_reset_encoder_td7; 
/************************* TDD6 ***************************************/ 
uint8_t tx_td6; 
uint8_t enable_trans_td6 = 0; 
uint16_t tem_huong_di_chuyen_td6 = 0; 
uint16_t tem_toc_do_danh_td6 = 0; 
uint8_t check_tem_huong_di_chuyen_td6 = 0; 


//int khoang_en[

																				
/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
		osDelay(1);
		
		if(0 == mode) {
			nut_lai_tay();
		}		
	// mode = 1 , mode tu dong
	// xilanh encoder D12 
		else if(1 == mode)
		{
			// ============= DI CHUYEN START =============== //
			if (0 == FEE.TuDong.tudong_number) {
				// start va va ap thanh 
				
				di_chuyen_start();   
			
				while(0 == FEE.TuDong.tudong_number) {
					
				if(0 == mode) {
					FEE.TuDong.tudong_number = 45; 
					break; 
				}		
					osDelay(1); 
					
					// ap thanh di chuyen lay lua
					FEE.Ts_San.toc_do_lua_ngang = 35; 
					
					di_chuyen_lay_lua(); 
					
					if (FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_1) {
						encoder_di_ngang(); 
						reset_encoder(); 
						
						while(EncoderCount1 < 16) {

							osDelay(1); 
							
							if(0 == mode) {
								FEE.TuDong.tudong_number = 45; 
								break; 
							}					
							
							FEE.Ts_San.toc_do_lua_ngang = 35; 
							di_chuyen_lay_lua(); 
						}
						
						FEE.TuDong.done_tudong_main1[0] = 1;
						Stop_PID();
						ve_vt();
						
						break; 
					}
				}
			}
			
			// ============= DI CHUYEN 2 =============== //
			else if (2 == FEE.TuDong.tudong_number) {
				
				reset_encoder(); 

				while (2 == FEE.TuDong.tudong_number) {
					
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}		
					
					if(EncoderCount1 > 200)
						FEE.TuDong.enable_count = 0; 
					
					if(FEE.TuDong.dk_cam_bien < FEE.Ts_San.vi_tri_dung_2 - 1) {
						FEE.Ts_San.toc_do_lua_doc = 29; 
						FEE.Ts_San.toc_do_lua_ngang = 32; 
					}
					else {
						FEE.Ts_San.toc_do_lua_doc = 29 ; 
						FEE.Ts_San.toc_do_lua_ngang = 29; 
					}
					
					di_chuyen_lay_lua(); 
					
					if (FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_2) {
						
						encoder_di_ngang(); 
						reset_encoder(); 
						
						while(EncoderCount1 < 6) {
							osDelay(1); 
							
							if(0 == mode) {
								FEE.TuDong.tudong_number = 45; 
								break; 
							}					
							
							FEE.Ts_San.toc_do_lua_ngang = 32; 
							di_chuyen_lay_lua(); 
						}						 
						Stop_PID();
						FEE.TuDong.done_tudong_main1[2] = 1;
						ve_vt();
						break; 
					}
				}
			}
			
			// ============= DI CHUYEN 4 =============== //
			else if (4 == FEE.TuDong.tudong_number) {
				
				
				reset_encoder(); 
				
				while(4 == FEE.TuDong.tudong_number) {
					
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}	
						
					if(EncoderCount1 > 200) 
						FEE.TuDong.enable_count = 0; 
						
					if(FEE.TuDong.dk_cam_bien < FEE.Ts_San.vi_tri_dung_3 - 1) {
						FEE.Ts_San.toc_do_lua_doc = 35; 
						FEE.Ts_San.toc_do_lua_ngang = 46; 
					}
					else {
						FEE.Ts_San.toc_do_lua_doc = 30; 
						FEE.Ts_San.toc_do_lua_ngang = 34; 
					}
					
					
					di_chuyen_lay_lua(); 
					
					if(FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_3) {
						
						encoder_di_ngang(); 
						reset_encoder(); 
						
						while(EncoderCount1 < 16) {
							
							osDelay(1); 
							
							if(0 == mode) {
								FEE.TuDong.tudong_number = 45; 
								break; 
							}					
							
							FEE.Ts_San.toc_do_lua_ngang = 32; 
							di_chuyen_lay_lua(); 
						}									
						
						Stop_PID();
						
						FEE.TuDong.done_tudong_main1[4] = 1; 
						ve_vt();
						break; 
					}
				}
			}
			
			// ============= DI CHUYEN 6 =============== //
			
			else if(6 == FEE.TuDong.tudong_number) {
				
				
				FEE.TuDong.enable_count = 1; 
				
				if(tem_en == 0) {
					reset_encoder(); 
					encoder_di_thang(); 
					
					Set_Angle(&Compass1,Z_axis,0);
					
					while(EncoderCount1 < 400) {
						
						if(0 == mode) {
							FEE.TuDong.tudong_number = 45; 
							break; 
						}								
						osDelay(1); 
						if(0 == mode) {
							FEE.TuDong.tudong_number = 45; 
							break; 
						}								
						goc_rb = Compass1.zAngle; 
						Swerve_4_V2(180, 25, 0, 100, 1); 				
					}
					tem_en = 1; 
				}
				
				if(goc_rb > -20) 
					day_lua_ra(); 
				else 
					keo_lua_vao(); 
				
				encoder_di_ngang(); 
				
				goc_rb = Compass1.zAngle; 
				
				if(goc_rb < -30) 
					day_tay_tha_lua(); 
				
				if(goc_rb < -80) {
					tx_td6 = 'M'; 
					enable_trans_td6 = 1; 
					FEE.TuDong.done_tudong_main1[5] = 1; 
				}
					
				
				if(goc_rb > -86 && check_tem_huong_di_chuyen_td6 == 0) {
					tem_huong_di_chuyen_td6 = 205; 
					tem_toc_do_danh_td6 = 40; 
				}
				else {
					tem_huong_di_chuyen_td6 = 180; 
					check_tem_huong_di_chuyen_td6 = 1; 
					tem_toc_do_danh_td6 = 100; 
				}
				
				if('D' == FEE.Ts_San.mau_san) 
					Swerve_4_V2(tem_huong_di_chuyen_td6, 28, -90, tem_toc_do_danh_td6, 1); 
				
				if(1 == check_tem_huong_di_chuyen_td6) {
					
					if(FEE.H_ADC.adc_value_Result[4] < 15500) {
						FEE.TuDong.tudong_number = 7; 
						FEE.TuDong.done_tudong_main1[6] = 1;
					}
				} 
			}
			
			// ============= DI CHUYEN 7 =============== //
			
			else if(7 == FEE.TuDong.tudong_number) {
				
				int limit_duoi_encoder; 
				int limit_tren_encoder; 
				
				
				
				uint8_t flag_thu_tay_tha_lua = 0; 
				
				int tem_toc_do_song_song_thanh = 15; 
				
				while(step_number_td7 < 6) {
					
					encoder_di_thang(); 
					
					osDelay(1);
					
					tem_toc_do_song_song_thanh = 15; 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}		 
					
					if(step_number_td7 == 5) {
						limit_duoi_encoder = 200; 
						limit_tren_encoder = 300; 
					}
					else {
						limit_duoi_encoder = 800; 
						limit_tren_encoder = 900; 						
					}
					
					reset_encoder(); 
					
					while(tem_trang_thai_td7 == 0) {
						
						osDelay(1); 
						
						if(0 == mode) {
							FEE.TuDong.tudong_number = 45; 
							break; 
						}						 
						
						if(0 != step_number_td7 && EncoderCount1 > 1400) 
							tem_toc_do_song_song_thanh = 8; 
						
						goc_rb = Compass1.zAngle; 
						
						int tem_goc = songSongThanh(12415, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
						
						Swerve_4_V2(tem_goc, tem_toc_do_song_song_thanh, -90, 100, 1); 
						
						if(FEE_GPIOIn.S2 == 0 || EncoderCount1 > 1535) 
							tem_trang_thai_td7  = 1; 
						
						if(0 != step_number_td7) {
								if(EncoderCount1 < 650)  // 650
									tem_trang_thai_td7 = 0; 
									
								if(1 != step_number_td7) 
									if(EncoderCount1 > limit_duoi_encoder && EncoderCount1 < limit_tren_encoder) {
										
										if(step_number_td7 == 5 && flag_thu_tay_tha_lua == 0) {
											thu_tay_tha_lua(); 	
											flag_thu_tay_tha_lua = 1; 
											osDelay(200); 
										}											
										 tx_td7 = 98 + step_number_td7;   // 'b' + step_number_td7[2,5] =>  d, e, f ... 
										enable_send_td7 = 1; 
									}
						}
					}
					
					
					if(step_number_td7 != 0) {
						
						Stop_PID();  
						
						if(step_number_td7 != 1) {
							while(comple_receiver_main_1[step_number_td7+5] == 0) {
								osDelay(1); 
								if(0 == mode) {
									FEE.TuDong.tudong_number = 45; 
									break; 
								}										
							}
						}
						
						enable_lai_tay_td7 = 1; 
						
						while(FEE_PES.Left == 1) {
							osDelay(1); 
							if(0 == mode) {
								FEE.TuDong.tudong_number = 45; 
								break; 
							}	
						}
						
						enable_lai_tay_td7 = 0; 
						
						tx_td7 = step_number_td7 + 48; 
						
						enable_send_td7 = 1; 															// khi bat dau bat o thu 2 thi moi dc truyen 
																																					// chu khong dc truyen ngay khi bat dau qua trinh tha 
						enable_di_chuyen_td7 = 1; 
						
						while(enable_di_chuyen_td7 == 1) {
							osDelay(1); 
							if(0 == mode) {
								FEE.TuDong.tudong_number = 45; 
								break; 
							}									
					  }
						// thoi gian tha xog lua 
						osDelay(500); 
					}
					

					tem_trang_thai_td7  = 0;           // phai reset tem trang thai roi moi ++ neu khong se gui sai ki tu sang F1
					
					step_number_td7++;  
										
				}
				
				// di encoder tha 2 lua cuoi 
				
				reset_encoder(); 

				while(EncoderCount1 < 1535) {
					
					osDelay(1); 
					
					encoder_di_thang(); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}								
					
					if(EncoderCount1 > 800 && EncoderCount1 < 900) 
						tx_td7 = 'h'; 
					
					
					goc_rb = Compass1.zAngle; 
						
					int tem_goc = songSongThanh(12415, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
					
					Swerve_4_V2(tem_goc, 15, -90, 100, 1); 					
				}
				
				Stop_PID(); 
				
				// wait canh tay xoay xong de tha lua 
				
				while(comple_receiver_main_1[11] == 0) {
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}										
				}		
				
				enable_lai_tay_td7 = 1; 
				
				// wait tin hieu tay ps 
				while(FEE_PES.Left == 1) {
					osDelay(1); 
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}	
				}	
				
				enable_lai_tay_td7 = 0; 
				
				tx_td7 = '6'; 
				
				
				// wait tha xong 2 lua cuoi 
				while(comple_receiver_main_1[12] == 0) {
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}						
				}
			
				Stop_PID(); 					
				FEE.TuDong.tudong_number = 100; 
			}
			
			/*************************** TU DONG 8 ********************************/ 
			else if(8 == FEE.TuDong.tudong_number) {
				
				double tem_sick = FEE.H_ADC.adc_value_Result[0]; 
				int16_t tem_toc_do = 60; 
				
				while(FEE.H_ADC.adc_value_Result[0] > 25000) {
					
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}							
					
					if(tem_sick - FEE.H_ADC.adc_value_Result[0] > 130 || FEE.H_ADC.adc_value_Result[0] > tem_sick) {
						if(tem_toc_do <= 90)
							tem_toc_do++; 
						tem_sick = FEE.H_ADC.adc_value_Result[0]; 
					}
						
					goc_rb = Compass1.zAngle; 
					Swerve_4_V2(90, tem_toc_do, -88, 100, 1); 				
				}
				
				int16_t tem_huong = 90;
				tem_sick = FEE.H_ADC.adc_value_Result[0]; 
				
				while(FEE.H_ADC.adc_value_Result[0] > 9800) {
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}						
					
					if(tem_sick - FEE.H_ADC.adc_value_Result[0] > 160 || FEE.H_ADC.adc_value_Result[0] > tem_sick) {
						if(tem_huong <= 180)
							tem_huong++; 
						tem_sick = FEE.H_ADC.adc_value_Result[0]; 
					}
						
					goc_rb = Compass1.zAngle; 
					Swerve_4_V2(tem_huong, 90, -88, 90, 1); 									
				}
				FEE.TuDong.tudong_number = 9; 
			}
			
			else if(9 == FEE.TuDong.tudong_number) {
				
				encoder_di_ngang();
				reset_encoder(); 
				
				int16_t tem_toc_do; 
				int tem_encoder; 
				int khoang_en_giam_toc; 
				int encoder_limit; 
				int encoder_limit_giam_toc; 
				int toc_do_min; 
				
				if(0 == FEE.TuDong.vi_tri_bong[2][1]) {
					tem_encoder = 3200; 
					tem_toc_do = 90; 
					encoder_limit = 4000; 
					encoder_limit_giam_toc = 3200; 
					khoang_en_giam_toc = 20; 
					toc_do_min = 50; 
				}
				else {
					
					tem_encoder = 3800; 
					tem_toc_do = 95; 					
					encoder_limit = 4800; 
					encoder_limit_giam_toc = 3600; 		
					khoang_en_giam_toc = 40; 
					toc_do_min = 65; 
				}
				
				while(EncoderCount1 < encoder_limit) {
					osDelay(1); 
					
					if(0 == mode) {
						FEE.TuDong.tudong_number = 45; 
						break; 
					}								
					
					if(EncoderCount1 > encoder_limit_giam_toc) {
						if(EncoderCount1 - tem_encoder > khoang_en_giam_toc) {
							if(tem_toc_do > toc_do_min)
								tem_toc_do--; 
							tem_encoder = EncoderCount1; 
						}
					}
					goc_rb = Compass1.zAngle; 
					Swerve_4_V2(180, tem_toc_do, -88, 100, 1); 	
				}
				FEE.TuDong.tudong_number = 10; 
			}
			
			else if(10 == FEE.TuDong.tudong_number) {
				
				if(0 == FEE.TuDong.vi_tri_bong[2][1]) {
					
					int tem_huong = 180; 
					int tem_goc_robot = -88; 
					int tem_toc_do_di_chuyen = 30; 
					int tem_toc_do_danh_goc = 40; 
					
					goc_rb  = Compass1.zAngle;
					
					while(goc_rb < 90) {
						
						if(0 == mode) {
							FEE.TuDong.tudong_number = 45; 
							break; 
						}									
						
						goc_rb  = Compass1.zAngle;
						Swerve_4_V2(tem_huong, tem_toc_do_di_chuyen, tem_goc_robot, tem_toc_do_danh_goc, 1); 	
						
						osDelay(2); 
						
						if(tem_goc_robot < 90)
							tem_goc_robot += 2; 
						if(tem_huong < 272)
							tem_huong += 1; 
						if(tem_toc_do_di_chuyen > 18)
							tem_toc_do_di_chuyen--;  
						if(tem_toc_do_danh_goc < 60)
							tem_toc_do_danh_goc += 2; 
					}
				}
				
				else {
					// sick 4 16500
					// sick 5 21600
					
					double sick4_mong_muon = 16000; 
					double sick5_mong_muon = 21200; 
					double canh_goc_vuong_1 = sick5_mong_muon - FEE.H_ADC.adc_value_Result[5]; 
					double canh_goc_vuong_2 = FEE.H_ADC.adc_value_Result[4] - sick4_mong_muon; 
					
					double ti_le; 
					double huong_radian; 
					double huong_360; 
					
					while(1) {
						
						if(0 == mode) {
							FEE.TuDong.tudong_number = 45; 
							break; 
						}									
						
						if(FEE.H_ADC.adc_value_Result[0] > sick5_mong_muon || FEE.H_ADC.adc_value_Result[0] <  sick4_mong_muon) 
							break; 					
						
						canh_goc_vuong_1 = sick5_mong_muon - FEE.H_ADC.adc_value_Result[0]; 
						canh_goc_vuong_2 = FEE.H_ADC.adc_value_Result[4] - sick4_mong_muon; 
						
						ti_le = canh_goc_vuong_1 / canh_goc_vuong_2; 
						
						huong_radian = atan(ti_le); 
						
						huong_360 = huong_radian * (180 / PI); 
						
						if(FEE.H_ADC.adc_value_Result[0] > sick5_mong_muon || FEE.H_ADC.adc_value_Result[4] <  sick4_mong_muon) 
							break; 								
						
						osDelay(1); 
						
						goc_rb = Compass1.zAngle; 
						Swerve_4_V2(180 + (int)huong_360, 55, -88, 100, 1); 	
						
						if(FEE.H_ADC.adc_value_Result[0] > sick5_mong_muon || FEE.H_ADC.adc_value_Result[4] <  sick4_mong_muon) 
							break; 					
					
					}
				}
				FEE.TuDong.tudong_number = 11; 
			}
			
			else if(11 == FEE.TuDong.tudong_number) {
				
				if(0 == FEE.TuDong.vi_tri_bong[2][1]) {
					Stop_PID(); 
				}
				
				else {
					
					int16_t tem_toc_do = 40; 
					goc_rb = Compass1.zAngle; 
					if(goc_rb < -168)
						tem_toc_do = 18; 
					Swerve_4_V2(190, tem_toc_do, -180, 60, 1); 					
					if(1 == FEE_GPIOIn.S4 && 1 == FEE_GPIOIn.S7) {
						FEE.TuDong.tudong_number = 12; 
						Stop_PID(); 
					}
					
				}
			}
			
//			else if(12 == FEE.TuDong.tudong_number) {
//				
//				xac_dinh_vi_tri_bong_can_lay(); 
//				
//				FEE.TuDong.start_count_bong =  0; 
//				
//				goc_rb = Compass1.zAngle; 
//				Swerve_4_V2(270, 30, -180, 60, 1); 		
//					
//					
//					if(FEE.TuDong.vi_tri_cot_can_den != 1) {
//						
//						goc_rb = Compass1.zAngle; 
//						Swerve_4_V2(270, 30, -180, 60, 1); 					
//						
//						while(FEE.TuDong.count_bong != FEE.TuDong.vi_tri_cot_can_den - 1)
//							osDelay(1); 
//						
//					}					
//					else if(1 == FEE.TuDong.vi_tri_cot_can_den) {
//						
//						
//					}
//					
//				}
//			}
			else if(45 == FEE.TuDong.tudong_number) {
				
				
			}
			
			
			
		}
	}
}	
