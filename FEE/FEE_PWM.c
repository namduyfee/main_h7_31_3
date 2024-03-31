/*******************************    INCLUDES   ********************************/

#include "FEE_PWM.h"
#include "main.h"
/***************************    GLOBAL VARIABLES   ****************************/


/***************************       FUNCTIONS       ****************************/
void FEE_PWM_Innit(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    DC_PWM1(0,0);
    DC_PWM2(0,0);
    DC_PWM3(0,0);
    DC_PWM4(0,0);
}

void DC_PWM1(uint8_t chieu, uint8_t toc_do)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,chieu); //DIR1
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1, toc_do*4);
}

void DC_PWM2(uint8_t chieu, uint8_t toc_do)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,chieu); //DIR2
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2, toc_do*4);
}

void DC_PWM3(uint8_t chieu, uint8_t toc_do)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,chieu); //DIR3
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3, toc_do*4);
}

void DC_PWM4(uint8_t chieu, uint8_t toc_do)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,chieu); //DIR4
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4, toc_do*4);
}