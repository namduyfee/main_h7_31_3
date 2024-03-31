#ifndef		__FEE_ROBOT_H__
#define		__FEE_ROBOT_H__

/*******************************    INCLUDES   ********************************/

#include "FEE_Library.h"
/***************************    GLOBAL VARIABLES   ****************************/

extern struct FEE_def           FEE;
extern struct AngleInfo result;
/***************************       FUNCTIONS       ****************************/
void FEE_Robot_Innit(void);
void nut_lai_tay(void); 
void encoder_di_ngang(void); 
void encoder_di_thang(void); 
void keo_lua_vao(void); 
void day_lua_ra(void); 
void reset_encoder(void); 
void day_tay_tha_lua(void); 
void thu_tay_tha_lua(void); 

#endif
