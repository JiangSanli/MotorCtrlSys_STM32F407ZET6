
#ifndef __FDC2112_H__
#define __FDC2112_H__

#include "main.h"
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"

#define Cap0_Sample_State	11
extern 	uint8_t DetectionTask_STATE ;
#define I2C_Read_Delay		1
extern 	float Cap_Value_Calibrated[2] ;
extern 	uint8_t Follow_state ;

// FDC2x1x Internal master clock frequency range : 35 - 55MHz  Typical fclk : 43.4MHz
#define FDC2112_Address 	0x2A	// ADDR->low: 0x2A , ADDR->high: 0x2B
#define FDC2112_W 			FDC2112_Address<<1		// 0:Write
#define FDC2112_R 			(FDC2112_Address<<1)+1	// 1:Read
#define DATA_CH0 			0x00    //通道0数据的高12位
#define DATA_LSB_CH0 		0x01	//通道0数据的低16位,FDC2112中没有使用
#define DATA_CH1 			0x02
#define DATA_LSB_CH1 		0x03
//#define DATA_CH2 			0x04
//#define DATA_LSB_CH2 		0x05
//#define DATA_CH3 			0x06
//#define DATA_LSB_CH3 		0x07
#define RCOUNT_CH0 			0x08 	//Conversion Time Configuration Registers-转换时间配置寄存器. CONVERSION TIME=(CH0_RCOUNT*16)/fREF0
//#define RCOUNT_CH1 			0x09
//#define RCOUNT_CH2 			0x0A
//#define RCOUNT_CH3 			0x0B
#define OFFSET_CH0 			0x0C	//Frequency Offset Registers-fOFFSET0 = CH0_OFFSET * (fREF0/(2^16))
//#define OFFSET_CH1 			0x0D
//#define OFFSET_CH2 			0x0E
//#define OFFSET_CH3 			0x0F
#define SETTLECOUNT_CH0 	0x10	//Settling Time Register Configuration-通道建立时间配置寄存器.CONVERSION TIME=(CH0_SETTLECOUNT*16)/fREF0
//#define SETTLECOUNT_CH1		0x11
//#define SETTLECOUNT_CH2 	0x12
//#define SETTLECOUNT_CH3 	0x13
#define CH0_FREF_DIVIDER 	0x14	//Clock Configuration Registers-时钟频率配置寄存器. CH0_FREF_DIVIDER [9:0] fREF0 = fCLK / CH0_FREF_DIVIDER
//#define CH1_FREF_DIVIDER 	0x15	//fIN0 : CH0_FIN_SEL [13:12]  fIN0 = fSENSOR0 / CH0_FIN_SEL
//#define CH2_FREF_DIVIDER 	0x16
//#define CH3_FREF_DIVIDER 	0x17
#define STATUS 0x18				//Refer to Register Maps section for a description of the individual status bits.
#define ERROR_CONFIG 0x19		//Refer to Register Maps section for a description of the individual error configuration bits.
#define CONFIG 0x1A				//选择时钟源、通道、休眠、INTB使能、驱动电流模式等等 see page 34,Table 38
#define MUX_CONFIG 0x1B			//see page 35,Table 39
#define RESET_DEV 0x1C
#define DRIVE_CURRENT_CH0 0x1E	//[15:11] Channel 0 Sensor drive current
//#define DRIVE_CURRENT_CH1 0x1F
//#define DRIVE_CURRENT_CH2 0x20
//#define DRIVE_CURRENT_CH3 0x21
#define MANUFACTURER_ID 0x7E	//[15:0]  Manufacturer ID = 0x5449
#define DEVICE_ID 0x7F			//[7:0]Device ID 0x3054 (FDC2112, FDC2114 only)

void FDC2112_Write_Reg_I2C(uint16_t MemAddress,uint16_t data);
uint16_t FDC2112_Read_Reg_I2C(uint16_t MemAddress);
int16_t FDC2112_Read_Data_I2C_CH(uint8_t index);
void Init_SingleChannel_FDC2212_CH0(void);
void Init_DoubleChannel_FDC2212(void);
float Cap_Calculate(uint8_t index);

#endif
