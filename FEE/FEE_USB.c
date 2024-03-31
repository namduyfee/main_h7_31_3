#include "main.h"
#include "usbd_customhid.h"
#include "FEE_USB.h"

extern struct FEE_def           FEE;
extern USBD_HandleTypeDef 								*pdev1;
extern USBD_CUSTOM_HID_HandleTypeDef     *hhid1;
extern FEE_MOTOR SWR1, SWR2, SWR3, SWR4;
int pj = 0;
extern FEE_Compass_struct_def Compass1;
extern FEE_Compass_struct_def Compass2;
extern	UART_HandleTypeDef huart7;
 

void FEE_Send_Compass_USB(FEE_Compass_struct_def * senseor)
{
    FEE.H_USB.USB_Data_OUT[35] =  senseor->xH;
    FEE.H_USB.USB_Data_OUT[36] =  senseor->xL;
    FEE.H_USB.USB_Data_OUT[37] =  senseor->yH;
    FEE.H_USB.USB_Data_OUT[38] =  senseor->yL;
    FEE.H_USB.USB_Data_OUT[39] =  senseor->zH;
    FEE.H_USB.USB_Data_OUT[40] =  senseor->zL;
    FEE.H_USB.USB_Data_OUT[41] = (senseor->fAngle + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[42] = (senseor->fAngle + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[51] =  (senseor->x_offset + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[52] =  (senseor->x_offset + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[53] =  (senseor->y_offset + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[54] =  (senseor->y_offset + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[55] =  (senseor->z_offset + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[56] =  (senseor->z_offset + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[57] =  (senseor->x_Axis + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[58] =  (senseor->x_Axis + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[59] =  (senseor->y_Axis + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[60] =  (senseor->y_Axis + 32768) % 256;
    FEE.H_USB.USB_Data_OUT[61] =  (senseor->z_Axis + 32768) / 256;
    FEE.H_USB.USB_Data_OUT[62] =  (senseor->z_Axis + 32768) % 256;
}

void FEE_USB_Innit()
{
    for(pj = 0; pj < 64; pj++)
    {
        FEE.H_USB.USB_Data_IN[pj] = 0;
        FEE.H_USB.USB_Data_OUT[pj] = 0;
    }

    FEE.H_USB.USB_Data_OUT[0] = 'N';
    FEE.H_USB.USB_Data_OUT[1] = 'A';

    FEE.H_USB.Ui							= 0;
    FEE.H_USB.Uj 							= 0;
    FEE.H_USB.USB_Verify			= 0;
    FEE.H_USB.USB_Connect			= 0;
    FEE.H_USB.USB_Send				= 0;



    FEE.H_USB.HID_Counter 		= 0;
    FEE.H_USB.HID_Counter2 		= 0;

    FEE.H_USB.HID_Tick 				= 0;
    FEE.H_USB.HID_Tick2 			= 0;
    FEE.H_USB.HID_Update 			= 0;
}

void HID_Send_Packet(void)
{
    // Get ADC value
    //HAL_ADC_Start(&hadc1);
    //HAL_ADC_PollForConversion(&hadc1, 10);
    //adc_value[0] = HAL_ADC_GetValue(&hadc1);
//    FEE.H_USB.USB_Data_OUT[2]  =  FEE.H_GPIO.GPIO_EXTI;
    FEE.H_USB.USB_Data_OUT[3]  =  FEE.H_GPIO.GPIO_S1_S8;
    FEE.H_USB.USB_Data_OUT[4]  =  FEE.H_GPIO.GPIO_S9_S16;
    FEE.H_USB.USB_Data_OUT[5]  =  FEE.H_GPIO.GPIO_S17_S21;
    FEE.H_USB.USB_Data_OUT[6]  =  FEE.H_GPIO.GPIO_S22_S29;
    FEE.H_USB.USB_Data_OUT[7]  =  FEE.H_GPIO.GPIO_S30_S37;// d
    FEE.H_USB.USB_Data_OUT[8]  =  FEE.H_GPIO.GPIO_S38_S45;//
    FEE.H_USB.USB_Data_OUT[9]  =  FEE.H_ADC.adc_value_Raw[0] / 256;//
    FEE.H_USB.USB_Data_OUT[10] =  FEE.H_ADC.adc_value_Raw[0] % 256;//
    FEE.H_USB.USB_Data_OUT[11] =  FEE.H_ADC.adc_value_Raw[1] / 256;//
    FEE.H_USB.USB_Data_OUT[12] =  FEE.H_ADC.adc_value_Raw[1] % 256;//
    FEE.H_USB.USB_Data_OUT[13] =  FEE.H_ADC.adc_value_Raw[2] / 256;
    FEE.H_USB.USB_Data_OUT[14] =  FEE.H_ADC.adc_value_Raw[2] % 256;//
    FEE.H_USB.USB_Data_OUT[15] =  FEE.H_ADC.adc_value_Raw[3] / 256;
    FEE.H_USB.USB_Data_OUT[16] =  FEE.H_ADC.adc_value_Raw[3] % 256;//
    FEE.H_USB.USB_Data_OUT[17] =  FEE.H_ADC.adc_value_Raw[4] / 256;
    FEE.H_USB.USB_Data_OUT[18] =  FEE.H_ADC.adc_value_Raw[4] % 256;//
    FEE.H_USB.USB_Data_OUT[19] =  FEE.H_ADC.adc_value_Raw[5] / 256;
    FEE.H_USB.USB_Data_OUT[20] =  FEE.H_ADC.adc_value_Raw[5] % 256;//
    FEE.H_USB.USB_Data_OUT[21] =  FEE.H_ADC.adc_value_Raw[6] / 256;
    FEE.H_USB.USB_Data_OUT[22] =  FEE.H_ADC.adc_value_Raw[6] % 256;//
    FEE.H_USB.USB_Data_OUT[23] =  FEE.H_ADC.adc_value_Raw[7] / 256;
    FEE.H_USB.USB_Data_OUT[24] =  FEE.H_ADC.adc_value_Raw[7] % 256;//
    if(FEE.H_EEprom.Read_Start == 0)
    {
    FEE.H_USB.USB_Data_OUT[2]  = 	FEE.H_GPIO.GPIO_EXTI;
//    FEE.H_USB.USB_Data_OUT[3]  = 	FEE.H_GPIO.GPIO_S1_S8;
//    FEE.H_USB.USB_Data_OUT[4]  = 	FEE.H_GPIO.GPIO_S9_S16;
//    FEE.H_USB.USB_Data_OUT[5]  = 	FEE.H_GPIO.GPIO_S17_S21;
//    FEE.H_USB.USB_Data_OUT[6]  = 	FEE.H_GPIO.GPIO_S22_S29;
//    FEE.H_USB.USB_Data_OUT[7]  = 	FEE.H_GPIO.GPIO_S30_S37;// d
//    FEE.H_USB.USB_Data_OUT[8]  = 	FEE.H_GPIO.GPIO_S38_S45;//
//    FEE.H_USB.USB_Data_OUT[9]  = 	FEE.H_ADC.adc_value_Raw[0] / 256;//
//    FEE.H_USB.USB_Data_OUT[10] =	FEE.H_ADC.adc_value_Raw[0] % 256;//
//    FEE.H_USB.USB_Data_OUT[11] =	FEE.H_ADC.adc_value_Raw[1] / 256;//
//    FEE.H_USB.USB_Data_OUT[12] =	FEE.H_ADC.adc_value_Raw[1] % 256;//
//    FEE.H_USB.USB_Data_OUT[13] =  FEE.H_ADC.adc_value_Raw[2] / 256;
//    FEE.H_USB.USB_Data_OUT[14] =	FEE.H_ADC.adc_value_Raw[2] % 256;//
//    FEE.H_USB.USB_Data_OUT[15] =  FEE.H_ADC.adc_value_Raw[3] / 256;
//    FEE.H_USB.USB_Data_OUT[16] =	FEE.H_ADC.adc_value_Raw[3] % 256;//
//    FEE.H_USB.USB_Data_OUT[17] =  FEE.H_ADC.adc_value_Raw[4] / 256;
//    FEE.H_USB.USB_Data_OUT[18] =	FEE.H_ADC.adc_value_Raw[4] % 256;//
//    FEE.H_USB.USB_Data_OUT[19] =  FEE.H_ADC.adc_value_Raw[5] / 256;
//    FEE.H_USB.USB_Data_OUT[20] =	FEE.H_ADC.adc_value_Raw[5] % 256;//
//    FEE.H_USB.USB_Data_OUT[21] =  FEE.H_ADC.adc_value_Raw[6] / 256;
//    FEE.H_USB.USB_Data_OUT[22] =	FEE.H_ADC.adc_value_Raw[6] % 256;//
//    FEE.H_USB.USB_Data_OUT[23] =  FEE.H_ADC.adc_value_Raw[7] / 256;
//    FEE.H_USB.USB_Data_OUT[24] =  FEE.H_ADC.adc_value_Raw[7] % 256;//
        FEE.H_USB.USB_Data_OUT[25] =  FEE.H_GPIO.EXTI_Counter1 / 256;
        FEE.H_USB.USB_Data_OUT[26] =  FEE.H_GPIO.EXTI_Counter1 % 256;
        FEE.H_USB.USB_Data_OUT[27] =  FEE.H_GPIO.EXTI_Counter2 / 256;
        FEE.H_USB.USB_Data_OUT[28] =  FEE.H_GPIO.EXTI_Counter2 % 256;
        FEE.H_USB.USB_Data_OUT[29] =  FEE.H_GPIO.EXTI_Counter3 / 256;
        FEE.H_USB.USB_Data_OUT[30] =  FEE.H_GPIO.EXTI_Counter3 % 256;
        FEE.H_USB.USB_Data_OUT[31] =  FEE.H_GPIO.EXTI_Counter4 / 256;
        FEE.H_USB.USB_Data_OUT[32] =  FEE.H_GPIO.EXTI_Counter4 % 256;
        FEE.H_USB.USB_Data_OUT[33] =  FEE.H_GPIO.EXTI_Counter5 / 256;
        FEE.H_USB.USB_Data_OUT[34] =  FEE.H_GPIO.EXTI_Counter5 % 256;
    }
    else if(FEE.H_EEprom.Read_Start == 1)
    {
        FEE.H_USB.USB_Data_OUT[2]  = 	FEE.H_EEprom.PageNum;
        if(FEE.H_EEprom.Read_Point == 0)
        {
            FEE.H_USB.USB_Data_OUT[25] =  FEE.H_EEprom.Eeprom_Data[0] / 256;
            FEE.H_USB.USB_Data_OUT[26] =  FEE.H_EEprom.Eeprom_Data[0] % 256;
            FEE.H_USB.USB_Data_OUT[27] =  FEE.H_EEprom.Eeprom_Data[1] / 256;
            FEE.H_USB.USB_Data_OUT[28] =  FEE.H_EEprom.Eeprom_Data[1] % 256;
            FEE.H_USB.USB_Data_OUT[29] =  FEE.H_EEprom.Eeprom_Data[2] / 256;
            FEE.H_USB.USB_Data_OUT[30] =  FEE.H_EEprom.Eeprom_Data[2] % 256;
            FEE.H_USB.USB_Data_OUT[31] =  FEE.H_EEprom.Eeprom_Data[3] / 256;
            FEE.H_USB.USB_Data_OUT[32] =  FEE.H_EEprom.Eeprom_Data[3] % 256;
            FEE.H_USB.USB_Data_OUT[33] =  FEE.H_EEprom.Eeprom_Data[4] / 256;
            FEE.H_USB.USB_Data_OUT[34] =  FEE.H_EEprom.Eeprom_Data[4] % 256;
            FEE.H_USB.USB_Data_OUT[63] =  FEE.H_EEprom.Read_Point;
            FEE.H_EEprom.Read_Point = 1;
        }
        else if(FEE.H_EEprom.Read_Point == 1)
        {
            FEE.H_USB.USB_Data_OUT[25] =  FEE.H_EEprom.Eeprom_Data[5] / 256;
            FEE.H_USB.USB_Data_OUT[26] =  FEE.H_EEprom.Eeprom_Data[5] % 256;
            FEE.H_USB.USB_Data_OUT[27] =  FEE.H_EEprom.Eeprom_Data[6] / 256;
            FEE.H_USB.USB_Data_OUT[28] =  FEE.H_EEprom.Eeprom_Data[6] % 256;
            FEE.H_USB.USB_Data_OUT[29] =  FEE.H_EEprom.Eeprom_Data[7] / 256;
            FEE.H_USB.USB_Data_OUT[30] =  FEE.H_EEprom.Eeprom_Data[7] % 256;
            FEE.H_USB.USB_Data_OUT[31] =  FEE.H_EEprom.Eeprom_Data[8] / 256;
            FEE.H_USB.USB_Data_OUT[32] =  FEE.H_EEprom.Eeprom_Data[8] % 256;
            FEE.H_USB.USB_Data_OUT[33] =  FEE.H_EEprom.Eeprom_Data[9] / 256;
            FEE.H_USB.USB_Data_OUT[34] =  FEE.H_EEprom.Eeprom_Data[9] % 256;
            FEE.H_USB.USB_Data_OUT[63] =  FEE.H_EEprom.Read_Point;
            FEE.H_EEprom.Read_Point = 2;
        }
        else if(FEE.H_EEprom.Read_Point == 2)
        {
            FEE.H_USB.USB_Data_OUT[25] =  FEE.H_EEprom.Eeprom_Data[10] / 256;
            FEE.H_USB.USB_Data_OUT[26] =  FEE.H_EEprom.Eeprom_Data[10] % 256;
            FEE.H_USB.USB_Data_OUT[27] =  FEE.H_EEprom.Eeprom_Data[11] / 256;
            FEE.H_USB.USB_Data_OUT[28] =  FEE.H_EEprom.Eeprom_Data[11] % 256;
            FEE.H_USB.USB_Data_OUT[29] =  FEE.H_EEprom.Eeprom_Data[12] / 256;
            FEE.H_USB.USB_Data_OUT[30] =  FEE.H_EEprom.Eeprom_Data[12] % 256;
            FEE.H_USB.USB_Data_OUT[31] =  FEE.H_EEprom.Eeprom_Data[13] / 256;
            FEE.H_USB.USB_Data_OUT[32] =  FEE.H_EEprom.Eeprom_Data[13] % 256;
            FEE.H_USB.USB_Data_OUT[33] =  FEE.H_EEprom.Eeprom_Data[14] / 256;
            FEE.H_USB.USB_Data_OUT[34] =  FEE.H_EEprom.Eeprom_Data[14] % 256;
            FEE.H_USB.USB_Data_OUT[63] =  FEE.H_EEprom.Read_Point;
            FEE.H_EEprom.Read_Point = 3;
        }
        else if(FEE.H_EEprom.Read_Point == 3)
        {
            FEE.H_USB.USB_Data_OUT[25] =  FEE.H_EEprom.Eeprom_Data[15] / 256;
            FEE.H_USB.USB_Data_OUT[26] =  FEE.H_EEprom.Eeprom_Data[15] % 256;
            FEE.H_USB.USB_Data_OUT[27] =  FEE.H_EEprom.Eeprom_Data[16] / 256;
            FEE.H_USB.USB_Data_OUT[28] =  FEE.H_EEprom.Eeprom_Data[16] % 256;
            FEE.H_USB.USB_Data_OUT[29] =  FEE.H_EEprom.Eeprom_Data[17] / 256;
            FEE.H_USB.USB_Data_OUT[30] =  FEE.H_EEprom.Eeprom_Data[17] % 256;
            FEE.H_USB.USB_Data_OUT[31] =  FEE.H_EEprom.Eeprom_Data[18] / 256;
            FEE.H_USB.USB_Data_OUT[32] =  FEE.H_EEprom.Eeprom_Data[18] % 256;
            FEE.H_USB.USB_Data_OUT[33] =  FEE.H_EEprom.Eeprom_Data[19] / 256;
            FEE.H_USB.USB_Data_OUT[34] =  FEE.H_EEprom.Eeprom_Data[19] % 256;
            FEE.H_USB.USB_Data_OUT[63] =  FEE.H_EEprom.Read_Point;
            FEE.H_EEprom.Read_Point = 0;
        }
    }


//    FEE.H_USB.USB_Data_OUT[35] =  Compass1.xH;//FEE.H_GPIO.EXTI_Counter6 / 256;
//    FEE.H_USB.USB_Data_OUT[36] =  Compass1.xL;//FEE.H_GPIO.EXTI_Counter6 / 256;
//    FEE.H_USB.USB_Data_OUT[37] =  Compass1.yH;//FEE.H_GPIO.EXTI_Counter7 / 256;
//    FEE.H_USB.USB_Data_OUT[38] =  Compass1.yL;//FEE.H_GPIO.EXTI_Counter7 / 256;
//    FEE.H_USB.USB_Data_OUT[39] =  Compass1.zH;//FEE.H_GPIO.EXTI_Counter8 / 256;
//    FEE.H_USB.USB_Data_OUT[40] =  Compass1.zL;//FEE.H_GPIO.EXTI_Counter8 / 256;
//    FEE.H_USB.USB_Data_OUT[41] = (Compass1.fAngle + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[42] = (Compass1.fAngle + 32768) % 256;
    FEE_Send_Compass_USB(&Compass1);
    FEE.H_USB.USB_Data_OUT[43] =  FEE.H_Remote.rxBuffer[0];//
    FEE.H_USB.USB_Data_OUT[44] =  FEE.H_Remote.rxBuffer[1];
    FEE.H_USB.USB_Data_OUT[45] =  FEE.H_Remote.rxBuffer[2];
    FEE.H_USB.USB_Data_OUT[46] =  FEE.H_Remote.rxBuffer[3];//
    FEE.H_USB.USB_Data_OUT[47] =  FEE.H_Remote.rxBuffer[4];
    FEE.H_USB.USB_Data_OUT[48] =  FEE.H_Remote.rxBuffer[5];//
    FEE.H_USB.USB_Data_OUT[49] =  FEE.H_Remote.rxBuffer[6];
    FEE.H_USB.USB_Data_OUT[50] =  FEE.H_Remote.rxBuffer[7];
//    FEE.H_USB.USB_Data_OUT[51] =  (Compass1.x_offset + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[52] =  (Compass1.x_offset + 32768) % 256;
//    FEE.H_USB.USB_Data_OUT[53] =  (Compass1.y_offset + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[54] =  (Compass1.y_offset + 32768) % 256;
//    FEE.H_USB.USB_Data_OUT[55] =  (Compass1.z_offset + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[56] =  (Compass1.z_offset + 32768) % 256;
//    FEE.H_USB.USB_Data_OUT[57] =  (Compass1.x_Axis + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[58] =  (Compass1.x_Axis + 32768) % 256;
//    FEE.H_USB.USB_Data_OUT[59] =  (Compass1.y_Axis + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[60] =  (Compass1.y_Axis + 32768) % 256;
//    FEE.H_USB.USB_Data_OUT[61] =  (Compass1.z_Axis + 32768) / 256;
//    FEE.H_USB.USB_Data_OUT[62] =  (Compass1.z_Axis + 32768) % 256;

    //FEE.H_USB.USB_Data_OUT[63] =  FEE.H_EEprom.Read_Point;

    USBD_CUSTOM_HID_SendReport(pdev1, FEE.H_USB.USB_Data_OUT, 64);

    //		if(Process_done==1) Process_done=0;
    //if(PID_struct._PID_Uart_OK == 1) PID_struct._PID_Uart_OK = 0;

}





/********************* HID_Read_Packet : nhan 64 byte data USB_Custom_HID **********************************/

void HID_Read_Packet(void)
{
    // luu tru 63 byte du lieu
    for(pj = 0; pj < 63; pj++)
    {
        FEE.H_USB.USB_Data_IN[pj] = hhid1->Report_buf[pj + 1];
    }

    FEE.H_EEprom.Read_Start = hhid1->Report_buf[3];
    FEE.H_EEprom.PageNum = hhid1->Report_buf[4];

    for(pj = 0; pj < 20; pj++)
    {
        FEE.H_EEprom.USB_Data[pj] = hhid1->Report_buf[pj * 2 + 5] * 256 + hhid1->Report_buf[pj * 2 + 6];
    }

    if(FEE.H_EEprom.Read_Start == 2)
    {
        FEE.H_EEprom.Counter++;
        uint8_t *data;

        data = (uint8_t*)&FEE.H_EEprom.USB_Data[0];
        EEPROM_Write(FEE.H_EEprom.PageNum,0,data,40);
        FEE.H_EEprom.Write_Done = 1;
        FEE.H_EEprom.Read_Done = 0;

        HAL_Delay(10);

        data = (uint8_t*)&FEE.H_EEprom.Eeprom_Data[0];
        EEPROM_Read(FEE.H_EEprom.PageNum,0,data,40);
        FEE.H_EEprom.Read_Done = 1;
        FEE.H_EEprom.Write_Done = 0;
    }
}
void send_50b()
{
		FEE.H_UART7.txBuffer[0]=0xFE;
    FEE.H_UART7.txBuffer[1]=0xEE;
		FEE.H_UART7.txBuffer[2]=0xEE;																																								// 20 : clear do thi 
																																																																		// [1, 20) : ve do thi 
		FEE.H_UART7.txBuffer[3]=1;																																											// 0 : xoa do thi 
    FEE.H_UART7.txBuffer[4]=(FEE.H_GPIO.EXTI_Counter8+32768)/256;
    FEE.H_UART7.txBuffer[5]=(FEE.H_GPIO.EXTI_Counter8+32768)%256;
    FEE.H_UART7.txBuffer[6]=(Compass1.zAngle + 32768)/256;
    FEE.H_UART7.txBuffer[7]=(Compass1.zAngle + 32768)%256;
    FEE.H_UART7.txBuffer[8]=(SWR1.en_xoay_result+ 32768)/256;
    FEE.H_UART7.txBuffer[9]=(SWR1.en_xoay_result+ 32768)%256;
    FEE.H_UART7.txBuffer[10]=(SWR2.en_xoay_result+ 32768)/256;
    FEE.H_UART7.txBuffer[11]=(SWR2.en_xoay_result+ 32768)%256;
    FEE.H_UART7.txBuffer[12]=(SWR3.en_xoay_result+ 32768)/256;
    FEE.H_UART7.txBuffer[13]=(SWR3.en_xoay_result+ 32768)%256;
    FEE.H_UART7.txBuffer[14]=(SWR4.en_xoay_result+ 32768)/256;
    FEE.H_UART7.txBuffer[15]=(SWR4.en_xoay_result+ 32768)%256;
    FEE.H_UART7.txBuffer[16]=FEE.H_ADC.adc_value_Raw[1]/256;
    FEE.H_UART7.txBuffer[17]=FEE.H_ADC.adc_value_Raw[1]%256;
    FEE.H_UART7.txBuffer[18]=FEE.H_ADC.adc_value_Raw[2]/256;
    FEE.H_UART7.txBuffer[19]=FEE.H_ADC.adc_value_Raw[2]%256;
    FEE.H_UART7.txBuffer[20]=FEE.H_ADC.adc_value_Raw[3]/256;
    FEE.H_UART7.txBuffer[21]=FEE.H_ADC.adc_value_Raw[3]%256;
    FEE.H_UART7.txBuffer[22]=FEE.H_ADC.adc_value_Raw[4]/256;
    FEE.H_UART7.txBuffer[23]=FEE.H_ADC.adc_value_Raw[4]%256;
    FEE.H_UART7.txBuffer[24]=(SWR1.en_xoay_dc+ 32768)/256;
    FEE.H_UART7.txBuffer[25]=(SWR1.en_xoay_dc+ 32768)%256;
    FEE.H_UART7.txBuffer[26]=(SWR2.en_xoay_dc+ 32768)/256;
    FEE.H_UART7.txBuffer[27]=(SWR2.en_xoay_dc+ 32768)%256;
    FEE.H_UART7.txBuffer[28]=(SWR3.en_xoay_dc+ 32768)/256;
    FEE.H_UART7.txBuffer[29]=(SWR3.en_xoay_dc+ 32768)%256;
    FEE.H_UART7.txBuffer[30]=(SWR4.en_xoay_dc+ 32768)/256;
    FEE.H_UART7.txBuffer[31]=(SWR4.en_xoay_dc+ 32768)%256;
		FEE.H_UART7.txBuffer[32]= 0;			// step_number
    FEE.H_UART7.txBuffer[33]= 10;
    FEE.H_UART7.txBuffer[34]=0;
    FEE.H_UART7.txBuffer[35]=0;
    FEE.H_UART7.txBuffer[36]=0;
    FEE.H_UART7.txBuffer[37]=0;
    FEE.H_UART7.txBuffer[38]=0;
    FEE.H_UART7.txBuffer[39]=0;
    FEE.H_UART7.txBuffer[40]=0;
    FEE.H_UART7.txBuffer[41]=0;
    FEE.H_UART7.txBuffer[42]=0;
    FEE.H_UART7.txBuffer[43]=0;
    FEE.H_UART7.txBuffer[44]=0;
    FEE.H_UART7.txBuffer[45]=0;
    FEE.H_UART7.txBuffer[46]=0;
    FEE.H_UART7.txBuffer[47]=0;
    FEE.H_UART7.txBuffer[48]=0;
    FEE.H_UART7.txBuffer[49]=0;
		
    HAL_UART_Transmit_IT(&huart7,&FEE.H_UART7.txBuffer[0],60);
}


