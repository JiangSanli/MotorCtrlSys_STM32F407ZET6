
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "ScheduleTable.h"
#include "stdlib.h"
#include "FDC2112.h"

/* ****************
 * 函数名：FDC2112_Write_Reg_I2C2
 * 描述：写FDC2112的寄存器数据，写入数据格式为uint16_t
 ******************/
void FDC2112_Write_Reg_I2C(uint16_t MemAddress,uint16_t data)
{
	uint8_t temp_data[2];
	temp_data[0] = (data>>8);
	temp_data[1] = (data & 0xff);
	HAL_I2C_Mem_Write(&hi2c2,FDC2112_W,MemAddress,I2C_MEMADD_SIZE_8BIT,temp_data,2,1000);
	HAL_Delay(10);
}

/* ****************
 * 函数名：FDC2112_Read_Reg_I2C2
 * 描述： 读寄存器数据，返回值为16bit的寄存器数据值
 ******************/
uint16_t FDC2112_Read_Reg_I2C(uint16_t MemAddress)
{
	uint16_t reg_data ;
	uint8_t temp_data[2];
	HAL_I2C_Mem_Read(&hi2c2,FDC2112_R,MemAddress,I2C_MEMADD_SIZE_8BIT,temp_data,2,1000);
	reg_data = ( (temp_data[0]<<8) + temp_data[1] );
	return reg_data;
}

/* ****************
 * 函数名：FDC2112_Read_Data_I2C
 * 描述： 读取某个地址范围的数据，数量总长度32bit
 ******************/
#ifdef FDC2112
uint32_t FDC2112_Read_Data_I2C(uint16_t ADDR_MSB)   //FDC2112只有MSB的12bit为有效数据，获取MSB的12bit进行计算
{
	uint32_t data_temp;
	uint8_t temp[2];
	if ( HAL_I2C_Mem_Read_IT(&hi2c2,FDC2112_R,ADDR_MSB,I2C_MEMADD_SIZE_8BIT,&temp[0],2) == HAL_OK){
	//if ( HAL_I2C_Mem_Read_DMA(&hi2c2,FDC2112_R,ADDR_MSB,I2C_MEMADD_SIZE_8BIT,&temp[0],2) == HAL_OK){    // DMA模式有问题
		HAL_Delay(1);
		temp[0] = temp[0]<<4;
		temp[0] = temp[0]>>4;
		data_temp = (unsigned int)( (temp[0]<<8) + temp[1] ) ;
		return data_temp;
	}
	else{
		printf("[WRONG]HAL_NotOK get\r\n");
	}
	return 0;
}
#else
uint32_t FDC2112_Read_Data_I2C(uint16_t ADDR_MSB , uint16_t ADDR_LSB)   //FDC2214分辨率为28bit，需要获取MSB和LSB的数据
{
	uint32_t data_temp;
	uint8_t temp_MSB[2];
	uint8_t temp_LSB[2];
	if ( HAL_I2C_Mem_Read_IT(&hi2c2,FDC2112_R,ADDR_MSB,I2C_MEMADD_SIZE_8BIT,&temp_MSB[0],2) == HAL_OK){
	//if ( HAL_I2C_Mem_Read_DMA(&hi2c2,FDC2112_R,ADDR_MSB,I2C_MEMADD_SIZE_8BIT,&temp[0],2) == HAL_OK){    // DMA模式有问题
		HAL_Delay(1);
		temp_MSB[0] = temp_MSB[0]<<4;
		temp_MSB[0] = temp_MSB[0]>>4;
	}
	else{
		printf("[WRONG]HAL_NotOK get\r\n");
		return 0;
	}
	if ( HAL_I2C_Mem_Read_IT(&hi2c2,FDC2112_R,ADDR_LSB,I2C_MEMADD_SIZE_8BIT,&temp_LSB[0],2) == HAL_OK){
	//if ( HAL_I2C_Mem_Read_DMA(&hi2c2,FDC2112_R,ADDR_MSB,I2C_MEMADD_SIZE_8BIT,&temp[0],2) == HAL_OK){    // DMA模式有问题
		HAL_Delay(1);
	}
	else{
		printf("[WRONG]HAL_NotOK get\r\n");
		return 0;
	}
	data_temp = (unsigned int)( (temp_MSB[0]<<24) | (temp_MSB[1]<<16)| (temp_LSB[0]<<8) |  temp_LSB[1] ) ;
	return data_temp;
}
#endif

/* ****************
 * 函数名：FDC2112_Read_Data_I2C_CH
 * 描述： 读取通道0或1的寄存器数据
 ******************/
uint32_t FDC2112_Read_Data_I2C_CH(uint8_t index)
{
	uint32_t result;
	switch(index)
#ifdef FDC2112
	{
		case 0:
			result = FDC2112_Read_Data_I2C(DATA_CH0);
			break;
		case 1:
			result = FDC2112_Read_Data_I2C(DATA_CH1);
			break;
	}
#else
	{
		case 0:
			result = FDC2112_Read_Data_I2C(DATA_CH0 , DATA_LSB_CH0);
			break;
		case 1:
			result = FDC2112_Read_Data_I2C(DATA_CH1 , DATA_LSB_CH1);
			break;
	}
#endif
	return result;
}


// 初始化FDC2112单通道CH0采集
void Init_SingleChannel_FDC2212_CH0(void)
{
	FDC2112_Write_Reg_I2C(0x08,0x2089);	//设置转换时间10ms
	FDC2112_Write_Reg_I2C(0x10,0x000A);	//FDC2214_SETTLECOUNT_CH0 计数 不用改
#ifdef FDC2112
	FDC2112_Write_Reg_I2C(0x14,0x2002); //设置fREF0和fIN0均为2分频，即时钟频率为43.4/2=21.7MHz
#else
	FDC2112_Write_Reg_I2C(0x14,0x2001); //设置fREF0和fIN0均为2分频，即时钟频率为43.4/2=21.7MHz
#endif
	FDC2112_Write_Reg_I2C(0x19,0x0000); //ERROE_CONFIG
	FDC2112_Write_Reg_I2C(0x1B,0xC20D); //通道配置
	FDC2112_Write_Reg_I2C(0x1E,0xF800); //配置驱动电流
	FDC2112_Write_Reg_I2C(0x1A,0x1481); //参数配置
}

void Init_DoubleChannel_FDC2212(void)
{
	FDC2112_Write_Reg_I2C(0x08,0x34FB); //转换时间10ms
	FDC2112_Write_Reg_I2C(0x09,0x34FB);

	FDC2112_Write_Reg_I2C(0x10,0x001B);//作用时间 CH1 //转换之前的稳定时间(T=(SETTLECOUNT_CHx*16)/Frefx)
	FDC2112_Write_Reg_I2C(0x11,0x001B);

	FDC2112_Write_Reg_I2C(0x14,0x2002);//选择在0.01MHz~10MHz的传感器频率
	FDC2112_Write_Reg_I2C(0x15,0x2002);//Frefx =Fclk =43.4MHz/2  二分频

	FDC2112_Write_Reg_I2C(0x19,0x0000); //ERROE_CONFIG
	FDC2112_Write_Reg_I2C(0x1B,0xC20D); //通道配置

	FDC2112_Write_Reg_I2C(0x1E,0x7800); //CH0 驱动电流  0.146mA
	FDC2112_Write_Reg_I2C(0x1F,0x7800); //CH1

	FDC2112_Write_Reg_I2C(0x1A,0x1401); //参数配置
}

// 计算通道index的电容
#ifdef FDC2112
float Cap_Calculate(uint8_t index)
{
	uint32_t Data_FDC;
	float Cap;
	Data_FDC = FDC2112_Read_Data_I2C_CH(index);
	Cap = 3540.4144 / ( (float)(Data_FDC) );
	return (Cap*Cap-33);
}
#else
float Cap_Calculate(uint8_t index)
{
	uint32_t Data_FDC;
	float Cap;
	Data_FDC = FDC2112_Read_Data_I2C_CH(index);
	Cap = 232021045.248 / ( (float)(Data_FDC) );
	return (Cap*Cap);
}
#endif




