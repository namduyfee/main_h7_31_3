#ifndef		__FEE_USB_H__
#define		__FEE_USB_H__
/*******************************    INCLUDES   ********************************/


/***************************    GLOBAL VARIABLES   ****************************/
#include "stm32h7xx_hal.h"
#include "FEE_AT24C128.h"
/***************************       FUNCTIONS       ****************************/

void FEE_USB_Innit(void);
void HID_Send_Packet(void);
void HID_Read_Packet(void);
void send_50b();

#endif
