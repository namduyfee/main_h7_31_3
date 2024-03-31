#ifndef		__FEE_UART_H__
#define		__FEE_UART_H__

/*******************************    INCLUDES   ********************************/

#include "stm32h7xx_hal.h"

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

/***************************       FUNCTIONS       ****************************/

void FEE_UART_Innit(void);
void FEE_UART_Test(void);
//void drive_ZLAC8015D_int(void);
//uint16_t calculate_custom_crc16(const uint8_t *data, uint32_t length);
//uint16_t calculate1_custom_crc16(const uint8_t *data, uint32_t length);
//void send_uart(uint8_t data);
//void send_uart2(uint8_t data);
//void speed_left (int16_t speed);
//void speed_right  (int16_t speed) ;
//void Dong_bo_speed(int16_t speed);
void pid_dc1(uint8_t chieu,uint8_t tocdo);
void pid_dc2(uint8_t chieu,uint8_t tocdo);
void pid_dc3(uint8_t chieu,uint8_t tocdo);
void pid_dc4(uint8_t chieu,uint8_t tocdo);
void pid_dc5(uint8_t chieu,uint8_t tocdo);
void pid_dc6(uint8_t chieu,uint8_t tocdo);
void pid_dc7(uint8_t chieu,uint8_t tocdo);
void pid_dc8(uint8_t chieu,uint8_t tocdo);
void pid_dc9(uint8_t chieu,uint8_t tocdo);
void pid_dc10(uint8_t chieu,uint8_t tocdo);
void pid_dc11(uint8_t chieu,uint8_t tocdo);
void pid_dc12(uint8_t chieu,uint8_t tocdo);
#endif
