#ifndef		__FEE_SWERVE_DRIVER_H__
#define		__FEE_SWERVE_DRIVER_H__

/*******************************    INCLUDES   ********************************/

#include "cmsis_os.h"
#include "stdlib.h"
#include "stm32h7xx_hal.h"
#include "FEE_PES_Control.h"
/***************************    GLOBAL VARIABLES   ****************************/

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
	
extern struct FEE_def	FEE;
extern  uint8_t ktra_khoa;

typedef struct  {
    double chieu_xoay;
    double goc_xoay;
    uint8_t chieu_tinh_tien;
}AngleInfo;

/***************************       FUNCTIONS       ****************************/

int Limit(int VT_RAW, int VTG);
void _Robot_4_omini (uint16_t Van_toc_Chay, int Goc_Chay, uint8_t Van_toc_Xoay, int Goc_Xoay, float HS_Goc,float HS_tang_goc, uint8_t V_tang, uint8_t V_giam);
void _Robot_cua(uint16_t V_chay,int Goc_chay,float HS_Goc,float HS_tang_goc, uint8_t V_tang, uint8_t V_giam,uint8_t HS_lech);
int songSongThanh(int adc_kc_thanh,int adc_ht,int sai_so_adc,int goc_chay,int sai_so,int chieu);
int TocDoen(int v0, int v1, int vmax,int quangduonght, uint16_t quangDuongCanDen, int phanTramTangToc, int phanTramGiamToc);
uint16_t tocdo_1(uint16_t en, uint16_t toc_do_thap,uint16_t toc_do_cao,uint16_t quang_duong,uint16_t quang_duong_tang,uint16_t quang_duong_giam);
int G_SS_Run(int G_Run, int ADC_RUn, int ADC_Now, float HS_Goc, int Bu_G_Max);
int TocDo1(int v0, int v1, int vmax,int viTriHtai,int viTriGoc, int quangDuongCanDen, int phanTramTangToc, int phanTramGiamToc);
int G_SS_Run_2(int G_Run, int ADC_Run, int ADC_Now, float HS_Goc, int Bu_G_Max);

void xoay_dc1(int goc_banh,float toc_do);
void xoay_dc2(int goc_banh,float toc_do);
void xoay_dc3(int goc_banh,float toc_do);
void xoay_dc4(int goc_banh,float toc_do);
double closestAngle(double a, double b);
double modulo(double a, double b);
void goc_gan_nhat(AngleInfo *_result,int16_t goc_htai,int16_t goc_moi,int16_t xd_angle);
int16_t goc_gan_nhat_N(int16_t goc_htai,int16_t goc_moi,int16_t xd_angle);
void vegoc0(void);
void vegoc04(void);
void ve_vt(void);
void Swerve_4(int huong_chay,int toc_do,int goc_xoay,float L,float W,int tang,int giam,int HS);
void Swerve_4_V2(int16_t huong_chay,uint8_t toc_do,int16_t goc_xoay,uint8_t toc_do_xoay, uint8_t he_so);
void Swerve_4_V2_laitay(int16_t huong_chay,uint8_t toc_do,int16_t goc_xoay,uint8_t toc_do_xoay);
void Swerve_3(int huong_chay,int toc_do,int goc_xoay,int toc_do_xoay,float L,float W,int tang,int giam);
void stop_sw();
void Stop_PID(void);
void xoay(void);
void xoay_V2();
#endif