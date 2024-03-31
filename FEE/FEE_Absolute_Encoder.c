/*******************************    INCLUDES   ********************************/
#include "FEE_Absolute_Encoder.h"
#include "main.h"
/*******************************    DEFINITIONS   ********************************/

#define SPI1_CS_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET)
#define SPI1_CS_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET)

/***************************       FUNCTIONS       ****************************/
uint8_t SAEJ1850_CRC8(uint8_t* data, uint8_t length)
{
    uint8_t i,j,crc,ploy;
    ploy = 0x1d;
    crc = 0xff;
    for(i = 0; i < length; i++)
    {
        crc^= data[i];
        for(j =0; j< 8; j++)
        {
            crc = (crc& 0x80) ? (crc<<1)^ploy: crc <<1;
        }
    }
    crc^=0xff;
    return crc;
}

uint8_t StreamReadAngle(uint8_t *state, uint8_t *CRC8, double* ReadRegData)
{
    uint8_t *rddata,crc8, retry = 0,i;
    SPI1_Enccoder SPIAngle;
    rddata = (uint8_t*)&SPIAngle;
    SPI1_CS_OFF; //bit[0]: Module _spi_ena
    uint8_t data_send = 0x05;
    HAL_SPI_Transmit(&hspi1,&data_send,1,100); //SPI write stream command data.
    for(retry = 0; retry < 6; retry++)
    {
        for(i=0; i<4; i++)
        {
            HAL_SPI_Transmit(&hspi1,0,1,10); //SPI write first command data.
            //Read data
            HAL_SPI_Receive(&hspi1,&rddata[i],1,10);
        }
        crc8 = SAEJ1850_CRC8(rddata,3);
        if(SPIAngle.crc8 == crc8)
        {
            *ReadRegData = ((SPIAngle._angledata>>8)&0x00ff) |
                           (SPIAngle._angledata<<8 & 0xff00);
            *ReadRegData = 360*(*ReadRegData / 65536);
            *state = SPIAngle.state;
            *CRC8 = SPIAngle.crc8;
            SPI1_CS_ON; //bit[0]: Disable SPI function
            return true;
        }
    }
    SPI1_CS_ON; //bit[0]: Disable SPI function
    return false;
}