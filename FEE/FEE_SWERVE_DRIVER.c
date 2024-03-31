/*******************************    INCLUDES   ********************************/

#include "FEE_SWERVE_DRIVER.h"
#include "dwt_stm32_delay.h"
#include "math.h"
#include "main.h"
#define PI 3.14159265358979
#define L 0.7534246575342466
#define W 0.6575342465753425
#define angle 		Compass1.z_Axis
#define AngleRT 	Compass1.zAngle
#define FEE_PES     FEE.H_PES.cmd_b
#define FEE_PES_Js  FEE.H_PES.joystick_b
#define FEE_PES_Btn FEE.H_PES.button_b

/***************************    GLOBAL VARIABLES   ****************************/

uint8_t connect[]= {0x01,0x06,0x20,0xAF,0x00,0x01,0x73,0xEB};
uint8_t che_do_speed[]= {0x01,0x06,0x20,0x0D,0x00,0x03,0x53,0xC8};
uint8_t enable[]= {0x01,0x06,0x20,0x0E,0x00,0x08,0xE2,0x0F};
uint8_t run[]= {0x01,0x06,0x20,0x0E,0x00,0x10,0xE2,0x05};
uint8_t run_dong_bo[]= {0x01,0x06,0x20,0x0F,0x00,0x00,0xB2,0x09};
uint8_t run_dc_trai[]= {0x01,0x06,0x20,0x88,0x00,0x64,0x43,0xB9};
uint8_t run_dong_bo1[]= {0x01,0x10,0x20,0x88,0x00,0x02,0x04,0x00,0x64,0x00,0x64,0x23,0x9C};
int32_t en_xoay1,en_xoay2,en_xoay3,en_xoay4;
int32_t en_xoay11,en_xoay22,en_xoay33,en_xoay44;
int32_t en_xoay111,en_xoay222,en_xoay333,en_xoay444;
int8_t trangthai[5];

uint8_t dc1,dc2,dc3,dc4;
uint16_t SW_xoay_speed = 50;
uint8_t arrived;
uint8_t mode_ve_VT;
extern FEE_MOTOR DC1, DC2, DC3, DC4;
extern FEE_Compass_struct_def Compass1;
extern int16_t goc_rb;
AngleInfo result;

FEE_MOTOR SWR1, SWR2, SWR3, SWR4;
int va,vb,vc,vd;
int chieu_tt1=1,chieu_tt2=0,chieu_tt3=0,chieu_tt4;
int van_toc_thuc=0;
double _R,_A,_B,_C,_D,_max,_E;
double speed[4];
int16_t speed_thuc[4];
int16_t Angle1,Angle2,Angle3,Angle4;
int16_t goc_htaiA,goc_htaiB,goc_htaiC,goc_htaiD;
int mode_dc1,mode_dc2,mode_dc3=0;
float _RB_4OM_V_Quay_thuc=0;
int _RB_4OM_van_toc_thuc=0;

/***************************       FUNCTIONS       ****************************/

int Limit(int VT_RAW, int VTG)
{
    if ( VT_RAW > VTG )   VT_RAW=VTG;
    else if ( VT_RAW < -VTG )  VT_RAW=-VTG;
    return VT_RAW;
}

void _Robot_4_omini (uint16_t Van_toc_Chay, int Goc_Chay, uint8_t Van_toc_Xoay, int Goc_Xoay, float HS_Goc,float HS_tang_goc, uint8_t V_tang, uint8_t V_giam)
{
    // Khai bao bien
    int16_t PWMA,PWMB,PWMC,PWMD;//Xung DC
    int8_t chieu1,chieu2,chieu3,chieu4; // Chieu quay DC
    // set van toc tang, giam tu tu
    if ( Van_toc_Chay != _RB_4OM_van_toc_thuc)
    {
        if (_RB_4OM_van_toc_thuc + V_tang < Van_toc_Chay) {
            _RB_4OM_van_toc_thuc += V_tang;
        }
        else if ( _RB_4OM_van_toc_thuc - V_giam> Van_toc_Chay) {
            _RB_4OM_van_toc_thuc -= V_giam;
        }
        else {
            _RB_4OM_van_toc_thuc = Van_toc_Chay;
        }
    }
    // P goc quay cua Robot
    int V_Xoay_tinh=  (Goc_Xoay-AngleRT)* HS_Goc;

    if(V_Xoay_tinh>Van_toc_Xoay) {
        V_Xoay_tinh=Van_toc_Xoay;
    }
    else if(V_Xoay_tinh<-Van_toc_Xoay) {
        V_Xoay_tinh=-Van_toc_Xoay;
    }

    if(_RB_4OM_V_Quay_thuc<V_Xoay_tinh&&V_Xoay_tinh>0) {
        _RB_4OM_V_Quay_thuc+=HS_tang_goc;
    }
    else if (_RB_4OM_V_Quay_thuc>V_Xoay_tinh&&V_Xoay_tinh<0) {
        _RB_4OM_V_Quay_thuc-=HS_tang_goc;
    }
    else (_RB_4OM_V_Quay_thuc=V_Xoay_tinh);
    // Xong P goc quay
    // tinh toc do chay
    Goc_Chay=Goc_Chay-angle;  // nhân 10 goc de tinh toan
    PWMA = _RB_4OM_V_Quay_thuc + _RB_4OM_van_toc_thuc * cos((Goc_Chay - 2250) * 0.00174533); //v A			-2250  PI/1800=0.00174533
    PWMB = _RB_4OM_V_Quay_thuc + _RB_4OM_van_toc_thuc * cos((Goc_Chay + 450)  * 0.00174533); //v B			+450
    PWMC = _RB_4OM_V_Quay_thuc + _RB_4OM_van_toc_thuc * cos((Goc_Chay - 450)  * 0.00174533); //v C			-450
    PWMD = _RB_4OM_V_Quay_thuc + _RB_4OM_van_toc_thuc * cos((Goc_Chay - 1350) * 0.00174533); //v D			-1350
    // Set Chieu và toc do cac dong co

    if(PWMA>0) {
        chieu1=0;
    }
    else {
        PWMA=-PWMA;
        chieu1=1;
    }
    if(PWMB>0) {
        chieu2=0;
    }
    else {
        PWMB=-PWMB;
        chieu2=1;
    }
    if(PWMC>0) {
        chieu3=0;
    }
    else {
        PWMC=-PWMC;
        chieu3=1;
    }
    if(PWMD>0) {
        chieu4=0;
    }
    else {
        PWMD=-PWMD;
        chieu4=1;
    }

    if(PWMA<4) {
        PWMA=2;
    }
    else if(PWMA>250) {
        PWMA=250;
    }
    if(PWMB<4) {
        PWMB=2;
    }
    else if(PWMB>250) {
        PWMB=250;
    }
    if(PWMC<4) {
        PWMC=2;
    }
    else if(PWMC>250) {
        PWMC=250;
    }
    if(PWMD<4) {
        PWMD=2;
    }
    else if(PWMD>250) {
        PWMD=250;
    }
    //Dung khan
    if(ktra_khoa==1)	 {
        PWMA=PWMB=PWMC=PWMD=2;
    }
    // Gui tin hieu dieu khien
    DC1.Dir = chieu1, DC1.Speed = PWMA;
    DC2.Dir = chieu2, DC2.Speed = PWMB;
    DC3.Dir = chieu3, DC3.Speed = PWMC;
    DC4.Dir = chieu4, DC4.Speed = PWMD;
}


void _Robot_cua(uint16_t V_chay,int Goc_chay,float HS_Goc,float HS_tang_goc, uint8_t V_tang, uint8_t V_giam,uint8_t HS_lech)
{
    int16_t PWMA,PWMB,PWMC,PWMD;//Xung DC
    int8_t chieu1,chieu2,chieu3,chieu4; // Chieu quay DC
    if ( V_chay != _RB_4OM_van_toc_thuc)
    {
        if (_RB_4OM_van_toc_thuc + V_tang < V_chay) {
            _RB_4OM_van_toc_thuc += V_tang;
        }
        else if ( _RB_4OM_van_toc_thuc - V_giam> V_chay) {
            _RB_4OM_van_toc_thuc -= V_giam;
        }
        else {
            _RB_4OM_van_toc_thuc = V_chay;
        }
    }


    PWMA= -	V_chay + (Goc_chay-AngleRT)*HS_Goc;
    PWMB= 	V_chay + (Goc_chay-AngleRT)*HS_Goc;

    if(PWMA>0) {
        chieu1=0;
    }
    else {
        PWMA=-PWMA;
        chieu1=1;
    }
    if(PWMB>0) {
        chieu2=0;
    }
    else {
        PWMB=-PWMB;
        chieu2=1;
    }

    if (PWMA<4) {
        PWMA=2;
    }
    else  if (PWMA>250) {
        PWMA=250;
    }
    if (PWMB<4) {
        PWMB=2;
    }
    else  if (PWMB>250) {
        PWMB=250;
    }
    //Dung khan
    if(ktra_khoa==1) {
        PWMA=PWMB=PWMC=PWMD=2;
    }
    // Gui tin hieu dieu khien
    DC1.Dir = chieu1, DC1.Speed = PWMA;
    DC2.Dir = chieu2, DC2.Speed = PWMB - HS_lech;
    DC3.Dir = chieu3, DC3.Speed = PWMC;
    DC4.Dir = chieu4, DC4.Speed = PWMD;
}

int G_SS_Run(int G_Run, int ADC_RUn, int ADC_Now, float HS_Goc, int Bu_G_Max)
{
    int SS_ADC=(-ADC_Now+ADC_RUn)/100;
    int G_Run_Tinh =  SS_ADC*HS_Goc;
    if(G_Run_Tinh>Bu_G_Max) {
        return G_Run+Bu_G_Max;
    }
    else if (G_Run_Tinh<-Bu_G_Max) {
        return G_Run-Bu_G_Max;
    }
    else return G_Run+G_Run_Tinh;
}

int G_SS_Run_2(int G_Run, int ADC_Run, int ADC_Now, float HS_Goc, int Bu_G_Max)
{
    int SS_ADC=(-ADC_Run+ADC_Now)/100;
    int G_Run_Tinh =  SS_ADC*HS_Goc;
    if(G_Run_Tinh>Bu_G_Max) {
        return G_Run+Bu_G_Max;
    }
    else if (G_Run_Tinh<-Bu_G_Max) {
        return G_Run-Bu_G_Max;
    }
    else return G_Run+G_Run_Tinh;
}


int songSongThanh(int adc_kc_thanh,int adc_ht,int sai_so_adc,int goc_chay,int sai_so,int chieu)
{
	
    //debug_adc_ht = adc_ht;
    int16_t k;
    int khoang_cach_adc= adc_ht-adc_kc_thanh;
    if(khoang_cach_adc>=0)          khoang_cach_adc=khoang_cach_adc/sai_so_adc;
    else if( khoang_cach_adc<=0)    khoang_cach_adc=-khoang_cach_adc/sai_so_adc;

    if(chieu==0)
    {
        if(adc_ht>adc_kc_thanh) {
            k=goc_chay+(khoang_cach_adc);
        }
        if(adc_ht<adc_kc_thanh) {
            k=goc_chay-(khoang_cach_adc);
        }
    }
    if(chieu==1)
    {
        if(adc_ht<adc_kc_thanh) {
            k=goc_chay+(khoang_cach_adc);
        }
        if(adc_ht>adc_kc_thanh) {
            k=goc_chay-(khoang_cach_adc);
        }
    }
    if(k>goc_chay+sai_so) {
        return k=goc_chay+sai_so;
    }
    else if (k<goc_chay-sai_so) {
        return k=goc_chay-sai_so;
    }
    else return k;
}

int TocDoen(int v0, int v1, int vmax,int quangduonght, uint16_t quangDuongCanDen, int phanTramTangToc, int phanTramGiamToc)
{
    uint16_t vt1;
    uint16_t quangDuongTangToc = (quangDuongCanDen * phanTramTangToc) / 100;
    uint16_t quangDuongGiamToc = (quangDuongCanDen * phanTramGiamToc) / 100;

    if (quangduonght < quangDuongTangToc) {
        vt1 = v0 + (vmax - v0) * quangduonght/ quangDuongTangToc;
    }
    if (quangduonght >= (quangDuongCanDen-quangDuongGiamToc) && quangduonght < quangDuongCanDen) {
        //     vt1 = vmax - (vmax - v1) * (quangduonght-(quangDuongCanDen-quangDuongGiamToc))/(quangDuongCanDen-(quangDuongCanDen-quangDuongGiamToc));
        vt1=v1+(vmax-v1)*(quangDuongCanDen-quangduonght)/quangDuongGiamToc;
    }
    return vt1;
}

uint16_t tocdo_1(uint16_t en, uint16_t toc_do_thap,uint16_t toc_do_cao,uint16_t quang_duong,uint16_t quang_duong_tang,uint16_t quang_duong_giam)
{
    int16_t l1,l2;
    uint16_t vt1;
    l1=(quang_duong_tang*quang_duong)/100;
    l2=((100-quang_duong_giam)*quang_duong)/100;
    if(en<l1) {
        vt1=toc_do_cao;
    }
    if(en>=l2&&en<quang_duong) {
        vt1=toc_do_cao-(toc_do_cao-toc_do_thap)*(en-l2)/(quang_duong-l2);
    }
    return vt1;
}

int tinh_goc_xoay(int goc_can_lay, int van_toc_goc)
{
    int output_c;
    int sai_so_goc_truoc, sai_so_goc;
    sai_so_goc =  goc_can_lay-angle;
    output_c = sai_so_goc*0.2+sai_so_goc*0.0001;
    output_c = Limit(output_c, van_toc_goc);
    return output_c;
}

int TocDo1(int v0, int v1, int vmax,int viTriHtai,int viTriGoc, int quangDuongCanDen, int phanTramTangToc, int phanTramGiamToc) {
    uint16_t vt;
    quangDuongCanDen=quangDuongCanDen-viTriGoc;
    int khoang_cach_ht = viTriHtai-viTriGoc;
    uint16_t quangDuongTangToc = (abs(quangDuongCanDen) * phanTramTangToc) / 100;
    uint16_t quangDuongGiamToc = (abs(quangDuongCanDen) * phanTramGiamToc) / 100;
    if (abs(khoang_cach_ht) < quangDuongTangToc) {
        vt = v0 + (vmax - v0) * abs(khoang_cach_ht) / quangDuongTangToc;
    }
    if (abs(khoang_cach_ht) >= (abs(quangDuongCanDen)-quangDuongGiamToc) && abs(khoang_cach_ht) < abs(quangDuongCanDen)) {
        vt = vmax - (vmax - v1) * (abs(khoang_cach_ht)-(abs(quangDuongCanDen)-quangDuongGiamToc)) / (abs(quangDuongCanDen)-(abs(quangDuongCanDen)-quangDuongGiamToc));
    }
    return vt;
}


void xoay_dc1(int goc_banh,float toc_do) {
    uint64_t en_xoay=(abs(goc_banh)*510*7)/360;
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,!SWR1.Dir);
    if(SWR1.Dir==0) {
        va=va+en_xoay;
    }
    else {
        va=va-en_xoay;
    };
    while(en_xoay--)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
        DWT_Delay_us(toc_do);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
        DWT_Delay_us(toc_do);
    }
}
void xoay_dc2(int goc_banh,float toc_do) {
    uint64_t en_xoay=(abs(goc_banh)*510*7)/360;
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,!SWR2.Dir);
    //if(SWR2.Dir==0){vb=vb+en_xoay;}else {vb=vb-en_xoay;};
    while(en_xoay--)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
        DWT_Delay_us(toc_do);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
        DWT_Delay_us(toc_do);
    }
}
void xoay_dc3(int goc_banh,float toc_do) {
    uint64_t en_xoay=(abs(goc_banh)*510*7)/360;
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,!SWR3.Dir);
    while(en_xoay--)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1);
        DWT_Delay_us(toc_do);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);
        DWT_Delay_us(toc_do);
    }
}
void xoay_dc4(int goc_banh,float toc_do) {
    uint64_t en_xoay=(abs(goc_banh)*510*7)/360;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,!SWR4.Dir);
    //if(SWR4.Dir==1){vd=vd+en_xoay;}else {vd=vd-en_xoay;};
    while(en_xoay--)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);
        DWT_Delay_us(toc_do);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);
        DWT_Delay_us(toc_do);
    }
}
double modulo(double a, double b)
{
    return (double)(a - b * floor(a / b));
}
double closestAngle(double a, double b)
{
    // L?y hu?ng
    double dir;
    dir = modulo(b, 360.0) - modulo(a, 360.0);

    // Chuy?n d?i t? -360 d?n 360 thành -180 d?n 180
    if (fabs(dir) > 180.0)
    {
        dir = -(copysign(1.0,dir)*360)+dir;
        //(dir < 0) ? dir + 360.0 : dir - 360.0;
    }
    return dir;
}

void goc_gan_nhat(AngleInfo* _result,int16_t goc_htai,int16_t goc_moi,int16_t xd_angle)
{
    int x,y;
    x = closestAngle(goc_htai, goc_moi);
    y = closestAngle(goc_htai, goc_moi + 180.0);

    _result->goc_xoay = (abs(x) <= abs(y)) ? x : y;
    _result->chieu_xoay = (_result->goc_xoay > 0) ? 0 : 1;

    if(xd_angle == 1)
		{chieu_tt1 = (abs(x) <= abs(y)) ? chieu_tt1 : !chieu_tt1;}
    else if(xd_angle == 2)
		{chieu_tt2 = (abs(x) <= abs(y)) ? chieu_tt2 : !chieu_tt2;}
    else if(xd_angle == 3)
		{chieu_tt3 = (abs(x) <= abs(y)) ? chieu_tt3 : !chieu_tt3;}
    else if(xd_angle == 4)
		{chieu_tt4 = (abs(x) <= abs(y)) ? chieu_tt4 : !chieu_tt4;}
}

int16_t goc_gan_nhat_N(int16_t goc_htai,int16_t goc_moi,int16_t xd_angle)
{
    int x,y;
		int16_t goc_xoay,chieu_xoay;
    x = closestAngle(goc_htai, goc_moi);
    y = closestAngle(goc_htai, goc_moi + 180.0);

		goc_xoay = (abs(x) <= abs(y)) ? x : y;
		chieu_xoay = (goc_xoay > 0) ? 0 : 1;
		
    if(xd_angle == 1)
		{chieu_tt1 = (abs(x) <= abs(y)) ? chieu_tt1 : !chieu_tt1;}
    else if(xd_angle == 2)
		{chieu_tt2 = (abs(x) <= abs(y)) ? chieu_tt2 : !chieu_tt2;}
    else if(xd_angle == 3)
		{chieu_tt3 = (abs(x) <= abs(y)) ? chieu_tt3 : !chieu_tt3;}
    else if(xd_angle == 4)
		{chieu_tt4 = (abs(x) <= abs(y)) ? chieu_tt4 : !chieu_tt4;}
		return chieu_xoay;
}
//	if(a<b){if(b-a<180){return gia_tri_goc = b;}else{return gia_tri_goc = b-360;}}
//	else if(a>b){if(a-b<180){return gia_tri_goc = b;}else{return gia_tri_goc = b+360;}}
void Swerve_4(int huong_chay,int toc_do,int goc_xoay,float _L,float _W,int tang,int giam,int HS)//duyken166
{
    int sai_so_goc=(goc_xoay+goc_rb)*HS;

    if(toc_do<van_toc_thuc) {
        van_toc_thuc-=giam;
        if(van_toc_thuc<toc_do) {
            van_toc_thuc=toc_do;
        }
    }
    if(toc_do>van_toc_thuc) {
        van_toc_thuc+=tang;
        if(van_toc_thuc>toc_do) {
            van_toc_thuc=toc_do;
        }
    }

    _R=sqrt(pow(_L, 2) + pow(_W, 2));

    _A=sin((huong_chay+goc_rb)*(PI/180))-sin(sai_so_goc*(PI/180))*(_L/_R);
    _B=sin((huong_chay+goc_rb)*(PI/180))+sin(sai_so_goc*(PI/180))*(_L/_R);
    _C=cos((huong_chay+goc_rb)*(PI/180))-sin(sai_so_goc*(PI/180))*(_W/_R);
    _D=cos((huong_chay+goc_rb)*(PI/180))+sin(sai_so_goc*(PI/180))*(_W/_R);

    speed[0]=sqrt(pow(_B, 2) + pow(_C, 2));
    speed[1]=sqrt(pow(_B, 2) + pow(_D, 2));
    speed[2]=sqrt(pow(_A, 2) + pow(_D, 2));
    speed[3]=sqrt(pow(_A, 2) + pow(_C, 2));

    _max=speed[0];
    for(int i=1; i<4; i++) {
        if(speed[i]>_max) {
            _max=speed[i];
        }
    }

    if(ktra_khoa==1) {
        toc_do=0;
    }

    speed_thuc[0] = (_max > 1) ? (speed[0]/_max)*van_toc_thuc : speed[0]*van_toc_thuc ;
    speed_thuc[1] = (_max > 1) ? (speed[1]/_max)*van_toc_thuc : speed[1]*van_toc_thuc ;
    speed_thuc[2] = (_max > 1) ? (speed[2]/_max)*van_toc_thuc : speed[2]*van_toc_thuc ;
    speed_thuc[3] = (_max > 1) ? (speed[3]/_max)*van_toc_thuc : speed[3]*van_toc_thuc ;

    Angle1=(1.5707-atan2(_C,_B))*(180/PI);
    Angle2=(1.5707-atan2(_D,_B))*(180/PI);   // 15707 = pi/2
    Angle3=(1.5707-atan2(_D,_A))*(180/PI);
    Angle4=(1.5707-atan2(_C,_A))*(180/PI);

    if(Angle1-goc_htaiA!=0) {
        goc_gan_nhat(&result,goc_htaiA,Angle1,1);
        SWR1.Dir=result.chieu_xoay;
        SWR1.Angle=result.goc_xoay;
        xoay_dc1(SWR1.Angle,10);
    }
    if(Angle2-goc_htaiB!=0) {
        goc_gan_nhat(&result,goc_htaiB,Angle2,2);
        SWR2.Dir=result.chieu_xoay;
        SWR2.Angle=result.goc_xoay;
        xoay_dc2(SWR2.Angle,10);
    }
    if(Angle3-goc_htaiC!=0) {
        goc_gan_nhat(&result,goc_htaiC,Angle3,3);
        SWR3.Dir=result.chieu_xoay;
        SWR3.Angle=result.goc_xoay;
        xoay_dc3(SWR3.Angle,10);
    }
    if(Angle4-goc_htaiD!=0) {
        goc_gan_nhat(&result,goc_htaiD,Angle4,4);
        SWR4.Dir=result.chieu_xoay;
        SWR4.Angle=result.goc_xoay;
        xoay_dc4(SWR4.Angle,10);
    }
//pid_dc1(chieu_tt1,speed_thuc[0]);
//pid_dc2(chieu_tt2,speed_thuc[1]);
//pid_dc3(chieu_tt3,speed_thuc[2]);
//pid_dc4(chieu_tt4,speed_thuc[3]);
// code dung
    DC1.Dir = chieu_tt1;
    DC1.Speed = speed_thuc[0];
    DC2.Dir = chieu_tt2;
    DC2.Speed = speed_thuc[1];
    DC3.Dir = chieu_tt3;
    DC3.Speed = speed_thuc[2];
    DC4.Dir = chieu_tt4;
    DC4.Speed = speed_thuc[3];
    goc_htaiA=Angle1;
    goc_htaiB=Angle2;
    goc_htaiC=Angle3;
    goc_htaiD=Angle4;

}


///4 banh swerve ban moi
void Swerve_4_V2(int16_t huong_chay,uint8_t toc_do,int16_t goc_xoay,uint8_t toc_do_xoay, uint8_t he_so)
{		
    int sai_so_goc=(goc_xoay-goc_rb) * he_so;
		if(sai_so_goc>=250){sai_so_goc = 250;}else if(sai_so_goc<=-250){sai_so_goc = -250;}
    int RCW=(sai_so_goc)*toc_do_xoay/100;
		
    _A=sin((huong_chay-goc_rb)*(PI/180))*toc_do-RCW*W;
    _B=sin((huong_chay-goc_rb)*(PI/180))*toc_do+RCW*W;
    _C=cos((huong_chay-goc_rb)*(PI/180))*toc_do-RCW*L;
    _D=cos((huong_chay-goc_rb)*(PI/180))*toc_do+RCW*L;
//		if(trangthai[1]-trangthai[2]!=0){trangthai[4] = 1;}

    speed[0]=sqrt(pow(_B, 2) + pow(_C, 2));
    speed[1]=sqrt(pow(_B, 2) + pow(_D, 2));
    speed[2]=sqrt(pow(_A, 2) + pow(_D, 2));
    speed[3]=sqrt(pow(_A, 2) + pow(_C, 2));

    _max=speed[0];
    for(int i=0; i<4; i++) {
        if(speed[i]>_max) {
            _max=speed[i];
        }
    }
		
    speed_thuc[0] = (_max > 250) ? ((speed[0]/_max)*250): (speed[0]);// tocdo banh xe 1
    speed_thuc[1] = (_max > 250) ? ((speed[1]/_max)*250): (speed[1]);// tocdo banh xe 2
    speed_thuc[2] = (_max > 250) ? ((speed[2]/_max)*250): (speed[2]);// tocdo banh xe 3
		speed_thuc[3] = (_max > 250) ? ((speed[3]/_max)*250): (speed[3]);// tocdo banh xe 4

    Angle1=(atan2(_B,_C))*(180/PI);
    Angle2=(atan2(_B,_D))*(180/PI);   // 15707 = pi/2
    Angle3=(atan2(_A,_D))*(180/PI);
    Angle4=(atan2(_A,_C))*(180/PI);

    if(Angle1-goc_htaiA!=0) {
        goc_gan_nhat(&result,goc_htaiA,Angle1,1);
				SWR1.Angle =result.goc_xoay;
        va = va + SWR1.Angle;
				SWR1.en_xoay_raw=SWR1.Angle *10+SWR1.en_xoay_raw;
			int8_t a = SWR1.en_xoay_raw/600;
				SWR1.en_xoay_result=SWR1.en_xoay_raw-5*a;
    }// xoay dc xoay1
		
    if(Angle2-goc_htaiB!=0) {
        goc_gan_nhat(&result,goc_htaiB,Angle2,2);
				SWR2.Angle =result.goc_xoay;
        vb = vb + SWR2.Angle;
				SWR2.en_xoay_raw=SWR2.Angle *10+SWR2.en_xoay_raw;
			int8_t a = SWR2.en_xoay_raw/600;
				SWR2.en_xoay_result=SWR2.en_xoay_raw-5*a;
    }//xoay dc xoay 2
		
    if(Angle3-goc_htaiC!=0)
    {
        goc_gan_nhat(&result,goc_htaiC,Angle3,3);
				SWR3.Angle =result.goc_xoay;			
        vc = vc + SWR3.Angle;
				SWR3.en_xoay_raw=SWR3.Angle *10+SWR3.en_xoay_raw;
			int8_t a = SWR3.en_xoay_raw/600;
				SWR3.en_xoay_result=SWR3.en_xoay_raw-5*a;
		}//xoay dc xoay 3
		
    if(Angle4-goc_htaiD!=0)
    {
        goc_gan_nhat(&result,goc_htaiD,Angle4,4);
				SWR4.Angle = result.goc_xoay;			
        vd = vd + SWR4.Angle;
				SWR4.en_xoay_raw=SWR4.Angle *10+SWR4.en_xoay_raw;
			int8_t a = SWR4.en_xoay_raw/600;
				SWR4.en_xoay_result=SWR4.en_xoay_raw-5*a;
		}	
		//xoay dc xoay 4
		goc_htaiA=Angle1;
    goc_htaiB=Angle2;
    goc_htaiC=Angle3;
		goc_htaiD=Angle4;
//    if(ktra_khoa==1) {
//        speed_thuc[0] = speed_thuc[1] = speed_thuc[2] = speed_thuc[3] = 0;
//    }
    DC1.Dir = chieu_tt1;
    DC1.Speed = speed_thuc[0];
    DC2.Dir = chieu_tt2;
    DC2.Speed = speed_thuc[1];
    DC3.Dir = chieu_tt3;
    DC3.Speed = speed_thuc[2];
    DC4.Dir = chieu_tt4;
    DC4.Speed = speed_thuc[3];	
}
void Swerve_4_V2_laitay(int16_t huong_chay,uint8_t toc_do,int16_t goc_xoay,uint8_t toc_do_xoay)
{
    int sai_so_goc=(goc_xoay);
		if(sai_so_goc>=250){sai_so_goc = 250;}else if(sai_so_goc<=-250){sai_so_goc = -250;}
    int RCW=(sai_so_goc)*toc_do_xoay/100;
		
    _A=sin((huong_chay)*(PI/180))*toc_do-RCW*W;
    _B=sin((huong_chay)*(PI/180))*toc_do+RCW*W;
    _C=cos((huong_chay)*(PI/180))*toc_do-RCW*L;
    _D=cos((huong_chay)*(PI/180))*toc_do+RCW*L;
//		if(trangthai[1]-trangthai[2]!=0){trangthai[4] = 1;}

    speed[0]=sqrt(pow(_B, 2) + pow(_C, 2));
    speed[1]=sqrt(pow(_B, 2) + pow(_D, 2));
    speed[2]=sqrt(pow(_A, 2) + pow(_D, 2));
    speed[3]=sqrt(pow(_A, 2) + pow(_C, 2));

    _max=speed[0];
    for(int i=0; i<4; i++) {
        if(speed[i]>_max) {
            _max=speed[i];
        }
    }
		
    speed_thuc[0] = (_max > 250) ? ((speed[0]/_max)*250): (speed[0]);// tocdo banh xe 1
    speed_thuc[1] = (_max > 250) ? ((speed[1]/_max)*250): (speed[1]);// tocdo banh xe 2
    speed_thuc[2] = (_max > 250) ? ((speed[2]/_max)*250): (speed[2]);// tocdo banh xe 3
		speed_thuc[3] = (_max > 250) ? ((speed[3]/_max)*250): (speed[3]);// tocdo banh xe 4

    Angle1=(atan2(_B,_C))*(180/PI);
    Angle2=(atan2(_B,_D))*(180/PI);   // 15707 = pi/2
    Angle3=(atan2(_A,_D))*(180/PI);
    Angle4=(atan2(_A,_C))*(180/PI);
		
     if(Angle1-goc_htaiA!=0) {
        goc_gan_nhat(&result,goc_htaiA,Angle1,1);
				SWR1.Angle =result.goc_xoay;
        va = va + SWR1.Angle;
				SWR1.en_xoay_raw=SWR1.Angle *10+SWR1.en_xoay_raw;
			int8_t a = SWR1.en_xoay_raw/600;
				SWR1.en_xoay_result=SWR1.en_xoay_raw-5*a;
    }// xoay dc xoay1
		
    if(Angle2-goc_htaiB!=0) {
        goc_gan_nhat(&result,goc_htaiB,Angle2,2);
				SWR2.Angle =result.goc_xoay;
        vb = vb + SWR2.Angle;
				SWR2.en_xoay_raw=SWR2.Angle *10+SWR2.en_xoay_raw;
			int8_t a = SWR2.en_xoay_raw/600;
				SWR2.en_xoay_result=SWR2.en_xoay_raw-5*a;
    }//xoay dc xoay 2
		
    if(Angle3-goc_htaiC!=0)
    {
        goc_gan_nhat(&result,goc_htaiC,Angle3,3);
				SWR3.Angle =result.goc_xoay;			
        vc = vc + SWR3.Angle;
				SWR3.en_xoay_raw=SWR3.Angle *10+SWR3.en_xoay_raw;
			int8_t a = SWR3.en_xoay_raw/600;
				SWR3.en_xoay_result=SWR3.en_xoay_raw-5*a;
		}//xoay dc xoay 3
		
    if(Angle4-goc_htaiD!=0)
    {
        goc_gan_nhat(&result,goc_htaiD,Angle4,4);
				SWR4.Angle = result.goc_xoay;			
        vd = vd + SWR4.Angle;
				SWR4.en_xoay_raw=SWR4.Angle *10+SWR4.en_xoay_raw;
			int8_t a = SWR4.en_xoay_raw/600;
				SWR4.en_xoay_result=SWR4.en_xoay_raw-5*a;
		}	
		//xoay dc xoay 4
		goc_htaiA=Angle1;
    goc_htaiB=Angle2;
    goc_htaiC=Angle3;
		goc_htaiD=Angle4;
//    if(ktra_khoa==1) {
//        speed_thuc[0] = speed_thuc[1] = speed_thuc[2] = speed_thuc[3] = 0;
//    }
    DC1.Dir = chieu_tt1;
    DC1.Speed = speed_thuc[0];
    DC2.Dir = chieu_tt2;
    DC2.Speed = speed_thuc[1];
    DC3.Dir = chieu_tt3;
    DC3.Speed = speed_thuc[2];
    DC4.Dir = chieu_tt4;
    DC4.Speed = speed_thuc[3];
}
void Swerve_3(int huong_chay,int toc_do,int goc_xoay,int toc_do_xoay,float _L,float _W,int tang,int giam)
{
    int sai_so_goc=(goc_xoay-AngleRT);
    int ss= abs(sai_so_goc);
    int a=	(ss >254 ) ? (254) : (ss) ;
    int RCW= ( sai_so_goc ==0 ) ? (0) : ((a*(sai_so_goc)/ss)*toc_do_xoay/100) ;
    if(toc_do<van_toc_thuc) {
        van_toc_thuc-=giam;
        if(van_toc_thuc<toc_do) {
            van_toc_thuc=toc_do;
        }
    }
    if(toc_do>van_toc_thuc) {
        van_toc_thuc+=tang;
        if(van_toc_thuc>toc_do) {
            van_toc_thuc=toc_do;
        }
    }

    _R=sqrt(pow(_L, 2) + pow(_W, 2));

    _A=sin((huong_chay-AngleRT)*(PI/180))*toc_do-RCW*(_W/_R);
    _B=sin((huong_chay-AngleRT)*(PI/180))*toc_do+RCW*(_W/_R);
    _C=cos((huong_chay-AngleRT)*(PI/180))*toc_do-RCW*(_L/_R);
    _D=cos((huong_chay-AngleRT)*(PI/180))*toc_do+RCW*(_L/_R);


    speed[0]=sqrt(pow(_B, 2) + pow(_C, 2));
    speed[1]=sqrt(pow(_B, 2) + pow(_D, 2));
    speed[2]=sqrt(pow(_A, 2) + pow(cos((huong_chay-AngleRT)*(PI/180))*toc_do, 2));

    _max=speed[0];
    for(int i=1; i<=3; i++) {
        if(speed[i]>_max) {
            _max=speed[i];
        }
    }

    speed_thuc[0] = (_max > 254) ? ((speed[0]/_max)*254): (speed[0]);// tocdo banh xe 1
    speed_thuc[1] = (_max > 254) ? ((speed[1]/_max)*254): (speed[1]);// tocdo banh xe 2
    speed_thuc[2] = (_max > 254) ? ((speed[2]/_max)*254): (speed[2]);// tocdo banh xe 3


    Angle1=(1.5707-atan2(_C,_B))*(180/PI);// goc banh xe 1
    Angle2=(1.5707-atan2(_D,_B))*(180/PI);//goc banh xe 2
    Angle3=(1.5707-atan2(cos((huong_chay-AngleRT)*(PI/180))*toc_do,_A))*(180/PI);// goc banh xe 3

// xoay dc xoay1
    if(Angle1-goc_htaiA!=0) {
        goc_gan_nhat(&result,goc_htaiA,Angle1,1);
        SWR1.Dir=result.chieu_xoay;
        SWR1.Angle=result.goc_xoay;// goc_dc1 laf goc thuc cua banh xe 1
        va = va + SWR1.Angle;
				en_xoay1=en_xoay1 + SWR1.Angle *510*7/360;
    }
    if(Angle2-goc_htaiB!=0) {
        goc_gan_nhat(&result,goc_htaiB,Angle2,2);
        SWR2.Dir=result.chieu_xoay;
        SWR2.Angle=result.goc_xoay;// goc_dc2 laf goc thuc cua banh xe 2
        vb = vb + SWR2.Angle;
				en_xoay2=en_xoay2 + SWR2.Angle *510*7/360;
    }//xoay dc xoay 2
    if(Angle3-goc_htaiC!=0)
    {
        goc_gan_nhat(&result,goc_htaiC,Angle3,3);
        SWR3.Dir=result.chieu_xoay;
        SWR3.Angle=result.goc_xoay;// goc_dc3 laf goc thuc cua banh xe 3
        vc = vc + SWR3.Angle;
				en_xoay3=en_xoay3 + SWR3.Angle *510*7/360;    
		}//xoay dc xoay 3

//mode_dc1=mode_dc2=mode_dc3=0;
//pid_dc1(chieu_tt1,speed_thuc[0]);  //chieu_tt1
//pid_dc2(chieu_tt2,speed_thuc[1]);
//pid_dc3(chieu_tt3,speed_thuc[2]);
    //
		if(ktra_khoa==1) {
    speed_thuc[0] = speed_thuc[1] = speed_thuc[2] = speed_thuc[3] = 0;
    }
    DC1.Dir = chieu_tt1;
    DC1.Speed = speed_thuc[0];
    DC2.Dir = chieu_tt2;
    DC2.Speed = speed_thuc[1];
    DC3.Dir = chieu_tt3;
    DC3.Speed = speed_thuc[2];
    goc_htaiA=Angle1;
    goc_htaiB=Angle2;
    goc_htaiC=Angle3;

}
void vegoc0()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
	osDelay(300);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
	osDelay(300);
	
	SWR1.en_xoay_result = -992;
	SWR2.en_xoay_result = 793;
	SWR3.en_xoay_result = -100;
	SWR4.en_xoay_result = -100;
	osDelay(100);
	while(arrived){osDelay(1);}
	osDelay(1000);
	SWR1.Dir = 0;
	SWR2.Dir = 0;
	SWR3.Dir = 0;
	SWR4.Dir = 0;
	SWR1.mode_dc = 1;
	SWR2.mode_dc = 1;
	SWR3.mode_dc = 1;
	SWR4.mode_dc = 1;

	
	while(1)
	{
				 	osDelay(1);
				SW_xoay_speed=400;
        if(FEE.H_GPIO.S11)
					{
						SWR1.mode_dc=0;
					} 
        if(FEE.H_GPIO.S12)
					{
						SWR2.mode_dc=0;
					} 			
        if(FEE.H_GPIO.S10)
					{
						SWR3.mode_dc=0;
					}
				if(FEE.H_GPIO.S9)
					{
						SWR4.mode_dc=0;
					}				
				if(!SWR1.mode_dc&&!SWR2.mode_dc&&!SWR3.mode_dc&&!SWR4.mode_dc)
					{ 

						en_xoay1 = en_xoay1-893;
						en_xoay2  = en_xoay2 + 893;
						osDelay(500);
						break;
					}
	}
	SWR1.Dir=0;
	SWR2.Dir=0;
	SWR3.Dir=0;
	SWR4.Dir=0;	
	SWR1.en_xoay_raw = 0;
	SWR2.en_xoay_raw = 0;
	SWR3.en_xoay_raw = 0;
	SWR4.en_xoay_raw = 0;
	goc_htaiA=Angle1 = 0;
  goc_htaiB=Angle2 = 0;
  goc_htaiC=Angle3 = 0;
	goc_htaiD=Angle4 = 0;
	DC1.Dir = 0;
	DC2.Dir = 0;
	DC3.Dir = 0;
	DC4.Dir = 0;
	SWR1.en_xoay_result = 0;
	SWR2.en_xoay_result = 0;
	SWR3.en_xoay_result = 0;
	SWR4.en_xoay_result = 0;
	en_xoay1 = 0;
	en_xoay2 = 0;
	en_xoay3 = 0;
	en_xoay4 = 0;

		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
		osDelay(300);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
		osDelay(300);
}


void vegoc04()
{
	int dem1=0;
	while(1)
	{
		SW_xoay_speed = 50;
		if(FEE_PES.Select == 0 && FEE_PES.Left == 1 && FEE_PES.Right == 1)
		{
			while(FEE_PES.Select == 0)
			{osDelay(1);}
			dem1++;
		}
		if(dem1 > 4){dem1=1;}
		
		if(dem1==1)
		{

			if(!FEE_PES.Left)
			{
				SWR1.mode_dc = 1;
				SWR1.Dir = 1;
			}
			else if(!FEE_PES.Right)
			{
				SWR1.mode_dc = 1;
				SWR1.Dir = 0;
			}
			else {SWR1.mode_dc = 0;}
		}
		else if(dem1==2)
		{
			if(!FEE_PES.Left)
			{
				SWR2.mode_dc = 1;
				SWR2.Dir = 1;
			}
			else if(!FEE_PES.Right)
			{
				SWR2.mode_dc = 1;
				SWR2.Dir = 0;
			}
			else
			{
			SWR2.mode_dc = 0;}
			}
		else if(dem1==3)
		{
			if(!FEE_PES.Left)
			{
				SWR3.mode_dc = 1;
				SWR3.Dir = 1;
			}
			else if(!FEE_PES.Right)
			{
				SWR3.mode_dc = 1;
				SWR3.Dir = 0;
			}
			else
			{
				SWR3.mode_dc = 0;
			}
		}
		else if(dem1==4)
		{
			if(!FEE_PES.Left)
			{
				SWR4.mode_dc = 1;
				SWR4.Dir = 1;
			}
			else if(!FEE_PES.Right)
			{
				SWR4.mode_dc = 1;
				SWR4.Dir = 0;
			}
			else
			{
				SWR4.mode_dc = 0;
			}
		}
		if(!FEE_PES.L1){break;}
	}
		
}

void stop_sw()
{
	Swerve_4_V2_laitay(0,0,360,1);   

}
void ve_vt()
{
    int ma=va/360;
    int mb=vb/360;
    int mc=vc/360;
		int md=vd/360;
		if(!ma&&!mb&&!mc&&!md){if(!arrived){mode_ve_VT = 0;}return;}
		
    if(abs(ma)>=1) 
			{
				mode_ve_VT = 1;
				SWR1.en_xoay_result = ma*3570;
        va=va%360;
    }
    if(abs(mb)>=1) 
			{
				mode_ve_VT = 1;
				SWR2.en_xoay_result = mb*3570;
        vb=vb%360;
    }
    if(abs(mc)>=1) 
			{
				mode_ve_VT = 1;
        SWR3.en_xoay_result = mc*3570;
        vc=vc%360;
    }
    if(abs(md)>=1) 
			{
				mode_ve_VT = 1;
				SWR4.en_xoay_result = md*3570;
        vd=vd%360;
    }
		osDelay(50);

}


void Stop_PID()
{
    _RB_4OM_van_toc_thuc=0;
    DC1.Dir = 0;
    DC1.Speed = 1;
    DC2.Dir = 1;
    DC2.Speed = 1;
    DC3.Dir = 1;
    DC3.Speed = 1;
    DC4.Dir = 0;
    DC4.Speed = 1;
}
void xoay()
{	
	if(en_xoay1!=0){dc1=1; (en_xoay1>0) ? en_xoay1-- : en_xoay1++;SWR1.mode_dc = 0; SW_xoay_speed=30;}
	if(en_xoay2!=0){dc2=1; (en_xoay2>0) ? en_xoay2-- : en_xoay2++;SWR2.mode_dc = 0; SW_xoay_speed=30;}
	if(en_xoay3!=0){dc3=1; (en_xoay3>0) ? en_xoay3-- : en_xoay3++;SWR3.mode_dc = 0; SW_xoay_speed=30;}
	if(en_xoay4!=0){dc4=1; (en_xoay4>0) ? en_xoay4-- : en_xoay4++;SWR4.mode_dc = 0; SW_xoay_speed=30;}
	
	if(SWR1.mode_dc == 1){dc1 = 1;}
	if(SWR2.mode_dc == 1){dc2 = 1;}
	if(SWR3.mode_dc == 1){dc3 = 1;}
	if(SWR4.mode_dc == 1){dc4 = 1;}
	
	if(dc1==1){if(SWR1.Dir==1){en_xoay11++;}else{en_xoay11--;}}
	if(dc2==1){if(SWR2.Dir==1){en_xoay22++;}else{en_xoay22--;}}
	if(dc3==1){if(SWR3.Dir==1){en_xoay33++;}else{en_xoay33--;}}
	if(dc4==1){if(SWR4.Dir==1){en_xoay44++;}else{en_xoay44--;}}
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,SWR1.Dir);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,SWR2.Dir);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,SWR3.Dir);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,SWR4.Dir);

  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,dc1);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,dc2);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,dc3);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,dc4);
	DWT_Delay_us(SW_xoay_speed);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);
	DWT_Delay_us(SW_xoay_speed);

	dc1=dc2=dc3=dc4=0;
	if(!en_xoay1&&!en_xoay2&&!en_xoay3&&!en_xoay4){arrived = 0;}else{arrived = 1;}
}
void xoay_V2()
{	
	if(en_xoay1>SWR1.en_xoay_result){SW_xoay_speed = 30;dc1 = 1;SWR1.Dir =1;en_xoay1--;}else if(en_xoay1<SWR1.en_xoay_result){SW_xoay_speed = 30;dc1 = 1;SWR1.Dir =0;en_xoay1++;}
	if(en_xoay2>SWR2.en_xoay_result){SW_xoay_speed = 30;dc2 = 1;SWR2.Dir =1;en_xoay2--;}else if(en_xoay2<SWR2.en_xoay_result){SW_xoay_speed = 30;dc2 = 1;SWR2.Dir =0;en_xoay2++;}
	if(en_xoay3>SWR3.en_xoay_result){SW_xoay_speed = 30;dc3 = 1;SWR3.Dir =1;en_xoay3--;}else if(en_xoay3<SWR3.en_xoay_result){SW_xoay_speed = 30;dc3 = 1;SWR3.Dir =0;en_xoay3++;}
	if(en_xoay4>SWR4.en_xoay_result){SW_xoay_speed = 30;dc4 = 1;SWR4.Dir =1;en_xoay4--;}else if(en_xoay4<SWR4.en_xoay_result){SW_xoay_speed = 30;dc4 = 1;SWR4.Dir =0;en_xoay4++;}
	
	if(SWR1.mode_dc == 1){dc1 = 1;}
	if(SWR2.mode_dc == 1){dc2 = 1;}
	if(SWR3.mode_dc == 1){dc3 = 1;}
	if(SWR4.mode_dc == 1){dc4 = 1;}
	
	if(dc1==1){if(SWR1.Dir==0){en_xoay11++;}else{en_xoay11--;}}
	if(dc2==1){if(SWR2.Dir==0){en_xoay22++;}else{en_xoay22--;}}
	if(dc3==1){if(SWR3.Dir==0){en_xoay33++;}else{en_xoay33--;}}
	if(dc4==1){if(SWR4.Dir==0){en_xoay44++;}else{en_xoay44--;}}
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,SWR1.Dir);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,SWR2.Dir);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,SWR3.Dir);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,SWR4.Dir);
		
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,dc1);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,dc2);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,dc3);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,dc4);
	DWT_Delay_us(SW_xoay_speed);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);
	DWT_Delay_us(SW_xoay_speed);
	if(!dc1&&!dc2&&!dc3&&!dc4){arrived = 0;}else{arrived = 1;}
	dc1=dc2=dc3=dc4=0;
}
