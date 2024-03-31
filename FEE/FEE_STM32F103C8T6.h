 #ifndef FEE_STM32F103C8T6_H
 #define FEE_STM32F103C8T6_H
 /*******************************    INCLUDES   ********************************/

#include "stm32h7xx_hal.h"

/***************************    GLOBAL VARIABLES   ****************************/

extern struct FEE_def           FEE;
//extern struct AngleInfo result;
/***************************       FUNCTIONS       ****************************/
void FEE_STM32F103C8T6_Innit(void);
void FEE_STM32C8T6_Read(void);
void FEE_STM32C8T6_Send(void);
void FEE_STM32C8T6P_Read(void);
void FEE_STM32C8T6P_Send(void);
#endif
