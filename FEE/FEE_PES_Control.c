/*******************************    INCLUDES   ********************************/
#include "FEE_PES_Control.h"

/*******************************    DEFINITONS   ******************************/

#define DISCONNETC_TIMEOUT	1000 // 1s (do configTICK_RATE_HZ = 1000Hz)

/***************************    GLOBAL VARIABLES   ****************************/

int ph = 0;

UART_HandleTypeDef* UartPes;

/***************************       FUNCTIONS       ****************************/

void FEE_PES_Innit(UART_HandleTypeDef* pes_uart_handle_def)
{
    UartPes = pes_uart_handle_def;
    memset(&FEE.H_PES, 0, sizeof(FEE_PES_struct_def));

    FEE.H_PES.Analog = 0xFF;
    FEE.H_PES.US[0] = 0xFF;
    FEE.H_PES.US[1] = 0xFF;
    FEE.H_PES.US[2] = 0xFF;
    FEE.H_PES.PES[0] = 0xFF;
    FEE.H_PES.PES[1] = 0xFF;
    HAL_UART_Receive_IT(UartPes, &FEE.H_PES.RX_Data[0], 1);
}

void FEE_PES_Check_Connect(void) {
    static uint8_t fistConnected = 0;

    if(FEE.H_PES.IsConnected) {
        if(!fistConnected) {
            // todo: Beep to warning
            for(uint8_t i_bz= 0; i_bz < 2; i_bz ++) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
                osDelay(200);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
                osDelay(200);
            }
            fistConnected = 1;
        }
        FEE.H_PES.IsConnected = 0;
    }
    else {
        if(xTaskGetTickCount() - FEE.H_PES.Timeout >= DISCONNETC_TIMEOUT) {
            // Reconnect
            HAL_UART_Receive_IT(UartPes, &FEE.H_PES.RX_Data[0], 1);
            // todo: Beep to warning
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
            osDelay(200);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
            osDelay(200);
        }
    }
}

void pes_uart_event_handle(void) {
    static uint8_t byHeadIsTrue = 0;
    static uint8_t i_pes = 0;
    static uint8_t pesBuff[7];

    if(FEE.H_PES.RX_Data[0] == 'F' ) {
        byHeadIsTrue = 1;
        i_pes = 0;
    }
    else {
        if(byHeadIsTrue) {
            pesBuff[i_pes++] = FEE.H_PES.RX_Data[0];
            if(i_pes >= 6) {
                FEE.H_PES.PES[0] = pesBuff[0];
                FEE.H_PES.PES[1] = pesBuff[1];
                FEE.H_PES.Analog = pesBuff[2];
                FEE.H_PES.US[1] = pesBuff[3];
                FEE.H_PES.US[2] = pesBuff[4];
                FEE.H_PES.US[3] = pesBuff[5];

                /*pesBuff[6] = 0xFF; // Khong dung den*/
                i_pes = 0;
                byHeadIsTrue = 0;
                FEE.H_PES.IsConnected = 1;
                FEE.H_PES.Timeout = xTaskGetTickCount();

                if(FEE.H_PES.PES[1] == 0xF5)
                {
                    HAL_NVIC_SystemReset();
                }
                if(FEE.H_PES.PES[1] == 243)
                {
                    ktra_khoa=1;
                    stop_sw(150,30,270,30);
                }
                // TODO: Check khoa DC
            }
        }
    }
    HAL_UART_Receive_IT(UartPes, &FEE.H_PES.RX_Data[0], 1);
}
