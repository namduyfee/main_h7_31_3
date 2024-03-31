
#include "FEE_Tu_Dong.h"
#include "FEE_Library.h"

#define sick_song_song_thanh_td7 12500 

#define limit_encoder_khoi_tao_doc 650
#define limit_encoder_khoi_tao_ngang 2350

#define toc_do_khoi_tao_doc 60
#define toc_do_khoi_tao_ngang 30
#define toc_do_khoi_tao_cheo 35

#define goc_di_cheo_san_do 290
#define goc_di_cheo_san_xanh 60

#define limit_sick_count_bong 25000

extern uint8_t mode; 
extern int EncoderCount1; 



//extern uint8_t tx_td7; 
//extern int tem_goc_td7; 
//extern uint8_t tem_break_td7; 
//extern uint8_t tem_reset_encoder_td7; 

extern uint8_t comple_receiver_main_1[20]; 

extern int16_t goc_rb;


int khoi_tao = 0; 

void FEE_TuDong_Init(void) {
	int pc8; 
	FEE.TuDong.dk_cam_bien= 0;
	FEE.TuDong.tudong_number = 0;
	FEE.TuDong.enable_count = 0; 
	for(pc8 = 0; pc8 < 20; pc8++) {
		FEE.TuDong.done_tudong_main1[pc8] = 0;
		FEE.TuDong.done_tudong_main2[pc8] = 0;
	}
	
	FEE.Ts_San.toc_do_lua_doc = 30; 
	FEE.Ts_San.toc_do_lua_ngang = 35; 
	
	
	FEE.TuDong.cam_bien_mau = 0; 
	FEE.TuDong.cam_bien_line = 15; 
	FEE.TuDong.Connected_sensor_line = 0; 
	FEE.TuDong.Connected_sensor_color = 0; 
	FEE.TuDong.loai_bong_can_lay = 0; 
	
	for(int i = 1; i <= 2; i++) {
		for(int j = 1; j <= 6; j++) {
			if(j % 2 == 0) 
				FEE.TuDong.vi_tri_bong[i][j] = 1; 
			else 
				FEE.TuDong.vi_tri_bong[i][j] = 0; 
		}
	}	
	
	FEE.TuDong.count_bong = 0; 
	FEE.TuDong.check_count_bong = 0; 
	FEE.TuDong.enable_count_bong = 0;
	FEE.TuDong.start_count_bong = 1; 
	
	
}


void di_chuyen_start(void) {
	
	
	if(0 == khoi_tao) {
		
		day_lua_ra();
		encoder_di_thang(); 
		reset_encoder(); 
		
		
		int tem_toc_do = toc_do_khoi_tao_doc; 
		int tem_encoder = 0; 
		
		while(EncoderCount1 < limit_encoder_khoi_tao_doc) {
			
			if(0 == mode) {
				FEE.TuDong.tudong_number = 45; 
				break; 
			}
			
			osDelay(1); 
			if(EncoderCount1 - tem_encoder > 17) {
				
				if(tem_toc_do > 25)
					tem_toc_do--; 
				tem_encoder = EncoderCount1; 
			}
			
			goc_rb = Compass1.zAngle; 
			if('D' == FEE.Ts_San.mau_san) 
				Swerve_4_V2(190 ,tem_toc_do,1,100, 1);
			else if('X' == FEE.Ts_San.mau_san)
				Swerve_4_V2(170 ,tem_toc_do,1,100, 1);
		}
		
		khoi_tao = 1; 
	}

		if(1 == khoi_tao) {
			
			encoder_di_ngang(); 
			
			reset_encoder(); 
			
				
			int tem_toc_do = toc_do_khoi_tao_ngang; 
			int tem_encoder = 0; 		
			int tem_huong; 
			
			if('D' == FEE.Ts_San.mau_san) 
				tem_huong = 270; 
			else if('X' == FEE.Ts_San.mau_san) 
				tem_huong = 90; 		
			
			while(EncoderCount1 < limit_encoder_khoi_tao_ngang) {
				
				osDelay(1); 
				
				if(0 == mode) {
					FEE.TuDong.tudong_number = 45; 
					break; 
				}			
				
				if(EncoderCount1 > 1500) {
					if('D' == FEE.Ts_San.mau_san) 
						tem_huong = 271; 
					else if('X' == FEE.Ts_San.mau_san) 
						tem_huong = 89; 		
				}
					
				if(EncoderCount1 - tem_encoder > 50) {
					
					if(tem_toc_do < 50)
						tem_toc_do++; 
					tem_encoder = EncoderCount1; 
				}		
				
				if(FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_1) {
					Swerve_4_V2(0 ,tem_toc_do,1,100, 1);			
					break; 
				}
					
				
				goc_rb = Compass1.zAngle; 
				if('D' == FEE.Ts_San.mau_san) 
					Swerve_4_V2(tem_huong ,tem_toc_do,1,100, 1);
				else if('X' == FEE.Ts_San.mau_san) 
					Swerve_4_V2(tem_huong ,tem_toc_do,1,100, 1);			
			}
			
			khoi_tao = 2; 
	}
	

	if(2 == khoi_tao) {

		int huong_di_chuyen; 
		
		if( 'D' == FEE.Ts_San.mau_san) 
			huong_di_chuyen = goc_di_cheo_san_do; 
		else if( 'X' == FEE.Ts_San.mau_san) 
			huong_di_chuyen = goc_di_cheo_san_xanh;
		
		while(2 == khoi_tao) {
			
			osDelay(1); 
			
			if(0 == mode) {
				FEE.TuDong.tudong_number = 45; 
				break; 
			}			
			
			if(FEE.TuDong.dk_cam_bien == FEE.Ts_San.vi_tri_dung_1)
				huong_di_chuyen = 0; 
				
			if(1 == FEE_GPIOIn.S4 || 1 == FEE_GPIOIn.S5) {
				khoi_tao = 3; 
				break; 
			}
			
			goc_rb = Compass1.zAngle; 
			
			if( 'D' == FEE.Ts_San.mau_san ) 
				Swerve_4_V2(huong_di_chuyen , toc_do_khoi_tao_cheo, 1, 100, 1);
			
			else if('X' == FEE.Ts_San.mau_san) 
				Swerve_4_V2(goc_di_cheo_san_xanh , toc_do_khoi_tao_cheo, 1, 100, 1);
			
		}
		
	}
}

void di_chuyen_lay_lua(void) {
	if(FEE_GPIOIn.S4 == 0 || FEE_GPIOIn.S5 == 0) {
		
		goc_rb = Compass1.zAngle; 
		
		if('D' == FEE.Ts_San.mau_san)
			Swerve_4_V2(274,FEE.Ts_San.toc_do_lua_doc,1,100, 1);
		else if ( 'X' == FEE.Ts_San.mau_san )
			Swerve_4_V2(87,FEE.Ts_San.toc_do_lua_doc,0,100, 1);
	}
	else if(1 == FEE_GPIOIn.S4 && 1 == FEE_GPIOIn.S5) {
		if( 'D' == FEE.Ts_San.mau_san )
			Swerve_4_V2(272, FEE.Ts_San.toc_do_lua_ngang, 1, 100, 1);
		else if( 'X' == FEE.Ts_San.mau_san )
						Swerve_4_V2(89, FEE.Ts_San.toc_do_lua_ngang, 0, 100, 1);
	}
}

int xac_dinh_vi_tri_bong_can_lay() {
	
	uint8_t i, j; 
	
	for(i = 1; i <= 2; i++) {
		
		for(j = 1; j <= 6; j++) {
			
			if(FEE.TuDong.vi_tri_bong[i][j] == FEE.TuDong.loai_bong_can_lay) {
				
				if(1 ==  i) {
					FEE.TuDong.vi_tri_hang_can_den = i; 
					FEE.TuDong.vi_tri_cot_can_den = j; 
					return 1;  
				}
				
				else if(2 ==  i) {
					if(2 ==FEE.TuDong.vi_tri_bong[1][j]) {
						FEE.TuDong.vi_tri_hang_can_den = i; 
						FEE.TuDong.vi_tri_cot_can_den = j; 
						return 1;  						
					}
				}
			}
		}
	}
	return 0; 
}


void di_chuyen_den_vi_tri_bong() {

}

void di_chuyen_den_vi_tri_ban_bong_real() {
	
	
	
}

void di_chuyen_den_vi_tri_ban_bong_fake() {
	
	
}




void count_bong_khoi_tao(void) {
	
	int tem_j;  
	
	if(FEE.TuDong.vi_tri_cot_can_den >= 4) {
		
		tem_j = 4; 
		
		for(int j = tem_j; j < FEE.TuDong.vi_tri_cot_can_den; j++) {
			for(int i = 1; i <= 2; i++) {
				if(FEE.TuDong.vi_tri_bong[i][j] != 2) 
					FEE.TuDong.check_count_bong = 1; 
			}
		
			if(FEE.TuDong.check_count_bong == 0) 
				FEE.TuDong.count_bong++; 
			FEE.TuDong.check_count_bong = 0; 
		}		
	}
	
	else if(FEE.TuDong.vi_tri_cot_can_den <= 3) {
		
		tem_j = 3; 
		
		for(int j = tem_j; j > FEE.TuDong.vi_tri_cot_can_den; j--) {
			for(int i = 1; i <= 2; i++) {
				if(FEE.TuDong.vi_tri_bong[i][j] != 2) 
					FEE.TuDong.check_count_bong = 1; 
			}
		
			if(FEE.TuDong.check_count_bong == 0) 
				FEE.TuDong.count_bong--; 
			FEE.TuDong.check_count_bong = 0; 
		}			
	}
}

void count_bong(void) {
	
	if(0 == FEE.TuDong.enable_count_bong) {
		
		if(FEE.H_ADC.adc_value_Result[5] < limit_sick_count_bong) {
			
			if(FEE.TuDong.count_bong < FEE.TuDong.vi_tri_cot_can_den) 
				FEE.TuDong.count_bong++; 
			else if(FEE.TuDong.count_bong > FEE.TuDong.vi_tri_cot_can_den) 
				FEE.TuDong.count_bong--; 
			FEE.TuDong.enable_count_bong = 1; 
		}
	}
	
	if(FEE.H_ADC.adc_value_Result[5] > 50000) 
		FEE.TuDong.enable_count_bong = 0; 
	
}

void reset_count_bong(void) {
	
	FEE.TuDong.count_bong = 0; 
	FEE.TuDong.check_count_bong = 0; 
	FEE.TuDong.enable_count_bong = 0; 
}

void ap_thanh_lay_bong(void) {
	
	if(FEE.Ts_San.mau_san == 'D') {
		if(FEE.TuDong.count_bong < FEE.TuDong.vi_tri_cot_can_den) {
			
		}
	}
	
}

//	// gap diem tha lua dau tien 

//void gap_vi_tri_tha_lua_dau_tien(void) {
//	
//	while(tem_break_td7 == 0) {
//		
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//		
//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}	
//	
//}


//// gap o lua thu 2 
//void gap_vi_tri_lua_thu_2(void) {
//	
//	while(tem_break_td7 == 0) {
//		
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//		
//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			
//			Stop_PID(); 
//			
//			while(FEE_PES.TamGiac == 1) {
//				
//				osDelay(1); 
//				
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}										
//			}
//			tx_td7 = '1'; 
//			enable_send_td7 = 1; 
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}	
//}

//// gap o lua thu 3 
//void gap_vi_tri_lua_thu_3(void) {
//	
//	while(tem_break_td7 == 0) {
//	
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//		
//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 150) {
//			tx_td7 = 'd'; 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			
//			Stop_PID(); 
//			
//			while(comple_receiver_main_1[8]) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}	
//			}						
//			
//			while(FEE_PES.TamGiac == 1) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}										
//			}
//			
//			tx_td7 = '2';  
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}				
//}

//// gap o lua thu 4 
//void gap_vi_tri_lua_thu_4(void) {
//	
//	while(tem_break_td7 == 0) {
//					
//		osDelay(1); 

//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						

//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 

//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}

//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 150) {
//			tx_td7 = 'e'; 
//		}

//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			
//			Stop_PID(); 
//			
//			while(comple_receiver_main_1[9]) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}	
//			}						
//			
//			while(FEE_PES.TamGiac == 1) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}										
//			}
//			
//			tx_td7 = '3';  
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}			
//}

//// gap o lua thu 5 

//void gap_vi_tri_lua_thu_5(void) {
//	while(tem_break_td7 == 0) {
//		
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//		
//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 150) {
//			tx_td7 = 'f'; 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			
//			Stop_PID(); 
//			
//			while(comple_receiver_main_1[10]) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}	
//			}						
//			
//			while(FEE_PES.TamGiac == 1) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}										
//			}
//			
//			tx_td7 = '4';  
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}		
//}

//// gap o lua thu 6 

//void gap_vi_tri_lua_thu_6(void) {
//	
//	while(tem_break_td7 == 0) {
//		
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//		
//		if(FEE.TuDong.cam_bien_mau != 0 && tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 150) {
//			tx_td7 = 'g'; 
//		}
//		
//		if(1 == tem_reset_encoder_td7 && EncoderCount1 > 1100) {
//			
//			Stop_PID(); 
//			
//			while(comple_receiver_main_1[11]) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}	
//			}						
//			
//			while(FEE_PES.TamGiac == 1) {
//				osDelay(1); 
//				if(0 == mode) {
//					FEE.TuDong.tudong_number = 45; 
//					tem_break_td7 = 1; 
//					break; 
//				}										
//			}
//			
//			tx_td7 = '5';  
//			tem_reset_encoder_td7 = 0; 
//			break; 
//		}
//	}	
//}

//void tha_2_lua_cuoi(void) {
//	
//	while(tem_break_td7 == 0) {
//		
//		osDelay(1); 
//		
//		if(0 == mode) {
//			FEE.TuDong.tudong_number = 45; 
//			tem_break_td7 = 1; 
//			break; 
//		}						
//		
//		if(tem_reset_encoder_td7 == 0) {
//			tem_reset_encoder_td7 = 1;  
//			reset_encoder(); 
//		}		
//		
//		goc_rb = Compass1.zAngle; 
//		tem_goc_td7 = songSongThanh(sick_song_song_thanh_td7, FEE.H_ADC.adc_value_Result[4], 15, 90, 45, 0); 
//		Swerve_4_V2(tem_goc_td7, 15, -88, 100, 1); 
//	}
//}
