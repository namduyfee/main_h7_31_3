/*******************************    INCLUDES   ********************************/

#include "FEE_UART.h"
#include "main.h"
/***************************    GLOBAL VARIABLES   ****************************/

int pi = 0;

void FEE_UART_Innit(void)
{
    for(pi = 0; pi < 64; pi++)
    {
        FEE.H_UART1.rxBuffer[pi] = 0;
        FEE.H_UART2.rxBuffer[pi] = 0;
        FEE.H_UART3.rxBuffer[pi] = 0;
        FEE.H_UART4.rxBuffer[pi] = 0;
        FEE.H_UART5.rxBuffer[pi] = 0;
        FEE.H_UART6.rxBuffer[pi] = 0;
        FEE.H_UART7.rxBuffer[pi] = 0;
        FEE.H_UART8.rxBuffer[pi] = 0;
        FEE.H_UART9.rxBuffer[pi] = 0;
        FEE.H_UART10.rxBuffer[pi] = 0;
        FEE.H_Remote.rxBuffer[pi] = 0;

        FEE.H_UART1.txBuffer[pi] = 0;
        FEE.H_UART2.txBuffer[pi] = 0;
        FEE.H_UART3.txBuffer[pi] = 0;
        FEE.H_UART4.txBuffer[pi] = 0;
        FEE.H_UART5.txBuffer[pi] = 0;
        FEE.H_UART6.txBuffer[pi] = 0;
        FEE.H_UART7.txBuffer[pi] = 0;
        FEE.H_UART8.txBuffer[pi] = 0;
        FEE.H_UART9.txBuffer[pi] = 0;
        FEE.H_UART10.txBuffer[pi] = 0;
        FEE.H_Remote.txBuffer[pi] = 0;

        FEE.H_UART1.DMA_rxBuffer[pi] = 0;
        FEE.H_UART2.DMA_rxBuffer[pi] = 0;
        FEE.H_UART3.DMA_rxBuffer[pi] = 0;
        FEE.H_UART4.DMA_rxBuffer[pi] = 0;
        FEE.H_UART5.DMA_rxBuffer[pi] = 0;
        FEE.H_UART6.DMA_rxBuffer[pi] = 0;
        FEE.H_UART7.DMA_rxBuffer[pi] = 0;
        FEE.H_UART8.DMA_rxBuffer[pi] = 0;
        FEE.H_UART9.DMA_rxBuffer[pi] = 0;
        FEE.H_UART10.DMA_rxBuffer[pi] = 0;
        FEE.H_Remote.DMA_rxBuffer[pi] = 0;

    }

    for(pi = 0; pi < 4; pi++)
    {
        FEE.H_UART1.CMD1[pi] = 0;
        FEE.H_UART1.CMD2[pi] = 0;

        FEE.H_UART2.CMD1[pi] = 0;
        FEE.H_UART2.CMD2[pi] = 0;

        FEE.H_UART3.CMD1[pi] = 0;
        FEE.H_UART3.CMD2[pi] = 0;

        FEE.H_UART4.CMD1[pi] = 0;
        FEE.H_UART4.CMD2[pi] = 0;

        FEE.H_UART5.CMD1[pi] = 0;
        FEE.H_UART5.CMD2[pi] = 0;

        FEE.H_UART6.CMD1[pi] = 0;
        FEE.H_UART6.CMD2[pi] = 0;

        FEE.H_UART7.CMD1[pi] = 0;
        FEE.H_UART7.CMD2[pi] = 0;

        FEE.H_UART8.CMD1[pi] = 0;
        FEE.H_UART8.CMD2[pi] = 0;

        FEE.H_UART9.CMD1[pi] = 0;
        FEE.H_UART9.CMD2[pi] = 0;

        FEE.H_UART10.CMD1[pi] = 0;
        FEE.H_UART10.CMD2[pi] = 0;

        FEE.H_Remote.CMD1[pi] = 0;
        FEE.H_Remote.CMD2[pi] = 0;
    }


    FEE.H_UART1.RX_size = 0;
    FEE.H_UART2.RX_size = 0;
    FEE.H_UART3.RX_size = 0;
    FEE.H_UART4.RX_size = 0;
    FEE.H_UART5.RX_size = 0;
    FEE.H_UART6.RX_size = 0;
    FEE.H_UART7.RX_size = 0;
    FEE.H_UART8.RX_size = 0;
    FEE.H_UART9.RX_size = 0;
    FEE.H_UART10.RX_size = 0;
    FEE.H_Remote.RX_size = 0;

    FEE.H_UART1.RX_Done = 0;
    FEE.H_UART2.RX_Done = 0;
    FEE.H_UART3.RX_Done = 0;
    FEE.H_UART4.RX_Done = 0;
    FEE.H_UART5.RX_Done = 0;
    FEE.H_UART6.RX_Done = 0;
    FEE.H_UART7.RX_Done = 0;
    FEE.H_UART8.RX_Done = 0;
    FEE.H_UART9.RX_Done = 0;
    FEE.H_UART10.RX_Done = 0;
    FEE.H_Remote.RX_Done = 0;

    FEE.H_UART1.TX_size = 0;
    FEE.H_UART2.TX_size = 0;
    FEE.H_UART3.TX_size = 0;
    FEE.H_UART4.TX_size = 0;
    FEE.H_UART5.TX_size = 0;
    FEE.H_UART6.TX_size = 0;
    FEE.H_UART7.TX_size = 0;
    FEE.H_UART8.TX_size = 0;
    FEE.H_UART9.TX_size = 0;
    FEE.H_UART10.TX_size = 0;
    FEE.H_Remote.TX_size = 0;

    FEE.H_UART1.TX_Done = 0;
    FEE.H_UART2.TX_Done = 0;
    FEE.H_UART3.TX_Done = 0;
    FEE.H_UART4.TX_Done = 0;
    FEE.H_UART5.TX_Done = 0;
    FEE.H_UART6.TX_Done = 0;
    FEE.H_UART7.TX_Done = 0;
    FEE.H_UART8.TX_Done = 0;
    FEE.H_UART9.TX_Done = 0;
    FEE.H_UART10.TX_Done = 0;
    FEE.H_Remote.TX_Done = 0;

    FEE.H_UART1.Disconnect = 0;
    FEE.H_UART2.Disconnect = 0;
    FEE.H_UART3.Disconnect = 0;
    FEE.H_UART4.Disconnect = 0;
    FEE.H_UART5.Disconnect = 0;
    FEE.H_UART6.Disconnect = 0;
    FEE.H_UART7.Disconnect = 0;
    FEE.H_UART8.Disconnect = 0;
    FEE.H_UART9.Disconnect = 0;
    FEE.H_UART10.Disconnect = 0;
    FEE.H_Remote.Disconnect = 0;

}

void FEE_UART_Test(void)
{
    FEE.H_UART1.txBuffer[0] = 0x11;
    FEE.H_UART1.txBuffer[1] = 0x22;
    FEE.H_UART1.txBuffer[2] = 0x33;
    FEE.H_UART1.txBuffer[3] = 0x44;

    HAL_UART_Transmit(&huart1, FEE.H_UART1.txBuffer, 4, 10);
    //HAL_UART_Transmit(&huart2, FEE.H_UART1.txBuffer, 4, 10);
    //HAL_UART_Transmit(&huart3, FEE.H_UART1.txBuffer, 4, 10);
    HAL_UART_Transmit(&huart4, FEE.H_UART1.txBuffer, 4, 10);
    HAL_UART_Transmit(&huart5, FEE.H_UART1.txBuffer, 4, 10);
    HAL_UART_Transmit(&huart6, FEE.H_UART1.txBuffer, 4, 10);
    HAL_UART_Transmit(&huart7, FEE.H_UART1.txBuffer, 4, 10);
    HAL_UART_Transmit(&huart8, FEE.H_UART1.txBuffer, 4, 10);
}

void send_uart(uint8_t data)
{
    HAL_UART_Transmit(&huart4,&data,1,1);
}

//void send_uart2(uint8_t data)
//{
//    HAL_UART_Transmit(&huart5,&data,1,1);
//}

void pid_dc1(uint8_t chieu,uint8_t tocdo)
{
    send_uart((!chieu<<7)|1);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc2(uint8_t chieu,uint8_t tocdo)
{
    send_uart((!chieu<<7)|2);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc3(uint8_t chieu,uint8_t tocdo)
{
    send_uart((!chieu<<7)|3);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc4(uint8_t chieu,uint8_t tocdo)
{
    send_uart((!chieu<<7)|4);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc5(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|5);
    send_uart(tocdo);
    send_uart(255);

}
void pid_dc6(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|6);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc7(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|7);
    send_uart(tocdo);
    send_uart(255);

}
void pid_dc8(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|8);
    send_uart(tocdo);
    send_uart(255);
}
void pid_dc9(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|9);
    send_uart(tocdo);
    send_uart(255);
}

void pid_dc10(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|10);
    send_uart(tocdo);
    send_uart(255);
}

void pid_dc11(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|11);
    send_uart(tocdo);
    send_uart(255);
}

void pid_dc12(uint8_t chieu,uint8_t tocdo)
{
    send_uart((chieu<<7)|12);
    send_uart(tocdo);
    send_uart(255);
}

