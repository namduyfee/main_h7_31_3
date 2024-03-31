#ifndef		__FEE_GPIO_H__
#define		__FEE_GPIO_H__

/*******************************    INCLUDES   ********************************/
#include "stm32h7xx_hal.h"


/***************************   GLOBAL VARIABLES  ******************************/
extern struct FEE_def	FEE;


/***************************       FUNCTIONS       ****************************/

//Khoi tao GPIO
void FEE_GPIO_Innit(void);

//Lay du lieu tu GPIO
void FEE_GPIO_Get_Data(void);

#endif
