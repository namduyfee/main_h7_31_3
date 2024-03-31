/*******************************    INCLUDES   ********************************/

#include "FEE_EXTI.h"
#include "main.h"
/***************************    GLOBAL VARIABLES   ****************************/


/***************************       FUNCTIONS       ****************************/

void FEE_EXTI_Innit(void)
{
    FEE.H_GPIO.EXTI_Counter1 = 0;
    FEE.H_GPIO.EXTI_Counter2 = 0;
    FEE.H_GPIO.EXTI_Counter3 = 0;
    FEE.H_GPIO.EXTI_Counter4 = 0;
    FEE.H_GPIO.EXTI_Counter5 = 0;
    FEE.H_GPIO.EXTI_Counter6 = 0;
    FEE.H_GPIO.EXTI_Counter7 = 0;
    FEE.H_GPIO.EXTI_Counter8 = 0;
}
