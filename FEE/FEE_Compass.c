/*******************************    INCLUDES   ********************************/
#include "FEE_Compass.h"

/*******************************    DEFINITONS   ******************************/

#define DISCONNECT_TIMEOUT	500
#define Angle_Data_Size 3
/***************************    GLOBAL VARIABLES   ****************************/
//UART_HandleTypeDef* UartCompass;
//static uint8_t get_Axis;
/***************************       FUNCTIONS       ****************************/

void FEE_Compass_Innit(UART_HandleTypeDef* compass_uart_handle_def, uint8_t Axis, FEE_Compass_struct_def* sensor)
{
    sensor->UartCompass = compass_uart_handle_def;
    sensor->get_Axis = Axis;
//    UartCompass = compass_uart_handle_def;
//    get_Axis = Axis;
    for(uint8_t pc = 0; pc < 8; pc++)
    {
        sensor->RX_Data[pc] = 0;

    }
    // khoi tao Compass Data
    sensor->isConnected = 0;
    sensor->Timeout = 0;

    sensor->xH = 0;
    sensor->xL = 0;
    sensor->yH = 0;
    sensor->yL = 0;
    sensor->zH = 0;
    sensor->zL = 0;

    sensor->xAngle = 0;
    sensor->yAngle = 0;
    sensor->zAngle = 0;

    sensor->x_Axis = 0;
    sensor->y_Axis = 0;
    sensor->z_Axis = 0;

    sensor->ss_g_now = 0;
    sensor->ss_g_pre = 0;

    sensor->TX_Data[0] = 'a';
    HAL_UART_Transmit(sensor->UartCompass, &sensor->TX_Data[0], 1, 100);
    HAL_Delay(100);
    sensor->TX_Data[0] = 'a';
    HAL_UART_Transmit(sensor->UartCompass, &sensor->TX_Data[0], 1, 100);
    HAL_Delay(100);

    switch (Axis)
    {
    case X_axis:
        sensor->TX_Data[0] = 'x';
        break;
    case Y_axis:
        sensor->TX_Data[0] = 'y';
        break;
    case Z_axis:
        sensor->TX_Data[0] = 'z';
        break;
    case All_axis:
        sensor->TX_Data[0] = 'b';
        break;
    default:
        break;
    }

    HAL_UART_Transmit(sensor->UartCompass, &sensor->TX_Data[0], 1, 100);
    HAL_Delay(100);
    HAL_UART_Receive_IT(sensor->UartCompass, &sensor->RX_Data[0], 1);
}

void FEE_Compass_Check_Connect(FEE_Compass_struct_def* sensor)
{
    if(sensor->isConnected) {
        sensor->isConnected = 0;
    }
    else {
        if(xTaskGetTickCount() - sensor->Timeout >= DISCONNECT_TIMEOUT) {
            // todo: reconnect and beep to warning.
            switch (sensor->get_Axis)
            {
            case X_axis:
                sensor->TX_Data[0]= 'x';
                break;
            case Y_axis:
                sensor->TX_Data[0] = 'y';
                break;
            case Z_axis:
                sensor->TX_Data[0] = 'z';
                break;
            case All_axis:
                sensor->TX_Data[0] = 'b';
                break;
            default:
                break;
            }

            HAL_UART_Transmit(sensor->UartCompass, &sensor->TX_Data[0], 1, 100);
            osDelay(100);
            HAL_UART_Receive_IT(sensor->UartCompass, &sensor->RX_Data[0], 1);

//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
//            osDelay(300);
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
//            osDelay(300);

        }
    }
}

int16_t Round_angle(int16_t _Angle)
{
    int16_t int_angle = _Angle/10;
    int16_t dec_part = _Angle%10;
    if(dec_part >= 5)
        return int_angle + 1;
		if(dec_part <= -5)
        return int_angle - 1;
    else
        return int_angle;
}

void FEE_Compass_Process(FEE_Compass_struct_def* sensor)
{
    switch (sensor->get_Axis)
    {
    case X_axis:
        FEE_Compass_Process_X(sensor);
        break;
    case Y_axis:
        FEE_Compass_Process_Y(sensor);
        break;
    case Z_axis:
        FEE_Compass_Process_Z(sensor);
        break;
    case All_axis:
        FEE_Compass_Process_All_Data(sensor);
        break;
    default:
        break;
    }
    HAL_UART_Receive_IT(sensor->UartCompass, &sensor->RX_Data[0], 1);
}

void FEE_Compass_Process_All_Data(FEE_Compass_struct_def* sensor)
{
    static uint8_t compassBuff[64];
    sensor->Header[2] = sensor->Header[1];
    sensor->Header[1] = sensor->Header[0];
    sensor->Header[0] = sensor->RX_Data[0];

    if(sensor->Header[2] == 'F'
            && sensor->Header[1] == 'E'
            && sensor->Header[0] == 'E')
    {
        compassBuff[0] = sensor->Header[2];
        compassBuff[1] = sensor->Header[1];
        compassBuff[2] = sensor->Header[0];
        sensor->byHeadIsTrue = 1;
        sensor->i_compass = 3;
    }
    else if(sensor->byHeadIsTrue == 1)
    {
        compassBuff[sensor->i_compass++] = sensor->RX_Data[0];
        if(sensor->i_compass >= 23)
        {

            sensor->xH = compassBuff[3];
            sensor->xL = compassBuff[4];
            sensor->yH = compassBuff[5];
            sensor->yL = compassBuff[6];
            sensor->zH = compassBuff[7];
            sensor->zL = compassBuff[8];

            sensor->x_offset = (compassBuff[9] << 8) | compassBuff[10];
            sensor->y_offset = (compassBuff[11] << 8) | compassBuff[12];
            sensor->z_offset = (compassBuff[13] << 8) | compassBuff[14];

            sensor->x_Axis = (compassBuff[15] << 8) | compassBuff[16];
            sensor->y_Axis = (compassBuff[17] << 8) | compassBuff[18];
            sensor->z_Axis = (compassBuff[19] << 8) | compassBuff[20];
            sensor->fAngle = (compassBuff[21] << 8) | compassBuff[22];

            sensor->xAngle = Round_angle(sensor->x_Axis);
            sensor->yAngle = Round_angle(sensor->y_Axis);
            sensor->zAngle = Round_angle(sensor->z_Axis);

            sensor->isConnected = 1;
            sensor->Timeout = xTaskGetTickCount();
            sensor->byHeadIsTrue = 0;
        }
    }
    HAL_UART_Receive_IT(sensor->UartCompass, &sensor->RX_Data[0], 1);
}

void Set_Angle(FEE_Compass_struct_def* sensor, uint8_t axis_set,int16_t G_set)
{
    switch(axis_set)
    {
    case X_axis:
        sensor->ss_g_pre=sensor->ss_g_now;
        sensor->ss_g_now=(sensor->xAngle-G_set) + sensor->ss_g_pre;
        break;
    case Y_axis:
        sensor->ss_g_pre=sensor->ss_g_now;
        sensor->ss_g_now=(sensor->yAngle-G_set) + sensor->ss_g_pre;
        break;
    case Z_axis:
        sensor->ss_g_pre=sensor->ss_g_now;
        sensor->ss_g_now=(sensor->zAngle-G_set) + sensor->ss_g_pre;
        break;
    default:
        break;
    }

}


void FEE_Compass_Process_X(FEE_Compass_struct_def* sensor)
{
    static uint8_t compassBuff[3];
    sensor->Header[0] = sensor->RX_Data[0];
    if(sensor->Header[0] == 'x')
    {
        sensor->byHeadIsTrue = 1;
        sensor->i_compass = 0;
    }
    else if(sensor->byHeadIsTrue == 1)
    {
        compassBuff[sensor->i_compass++] = sensor->RX_Data[0];
        if(sensor->i_compass >= Angle_Data_Size)
        {

            sensor->x_Axis = ((compassBuff[0] * 10000 + compassBuff[1] * 100 + compassBuff[2]) - 500000)
                             - (sensor->ss_g_now*10);
            sensor->xAngle = Round_angle(sensor->x_Axis);

            sensor->isConnected = 1;
            sensor->Timeout = xTaskGetTickCount();
            sensor->byHeadIsTrue = 0;
        }
    }
}


void FEE_Compass_Process_Y(FEE_Compass_struct_def* sensor)
{
    static uint8_t compassBuff[3];
    sensor->Header[0] = sensor->RX_Data[0];
    if(sensor->Header[0] == 'y')
    {
        sensor->byHeadIsTrue = 1;
        sensor->i_compass = 0;
    }
    else if(sensor->byHeadIsTrue == 1)
    {
        compassBuff[sensor->i_compass++] = sensor->RX_Data[0];
        if(sensor->i_compass >= Angle_Data_Size)
        {

            sensor->y_Axis = ((compassBuff[0] * 10000 + compassBuff[1] * 100 + compassBuff[2]) - 500000)
                             - (sensor->ss_g_now*10);
            sensor->yAngle = Round_angle(sensor->y_Axis);

            sensor->isConnected = 1;
            sensor->Timeout = xTaskGetTickCount();
            sensor->byHeadIsTrue = 0;
        }
    }
}

void FEE_Compass_Process_Z(FEE_Compass_struct_def* sensor)
{
    static uint8_t compassBuff[3];
    sensor->Header[0] = sensor->RX_Data[0];
    if(sensor->Header[0] == 'z')
    {
        sensor->byHeadIsTrue = 1;
        sensor->i_compass = 0;
    }
    else if(sensor->byHeadIsTrue == 1)
    {
        compassBuff[sensor->i_compass++] = sensor->RX_Data[0];
        if(sensor->i_compass >= Angle_Data_Size)
        {

            sensor->z_Axis = ((compassBuff[0] * 10000 + compassBuff[1] * 100 + compassBuff[2]) - 500000)
                             - (sensor->ss_g_now*10);
            sensor->zAngle = Round_angle(sensor->z_Axis);

            sensor->isConnected = 1;
            sensor->Timeout = xTaskGetTickCount();
            sensor->byHeadIsTrue = 0;
        }
    }
}
