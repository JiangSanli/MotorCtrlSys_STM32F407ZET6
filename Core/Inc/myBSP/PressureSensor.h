
#ifndef __PRESSURESENSOR_H
#define __PRESSURESENSOR_H


#include "main.h"
#include "i2c.h"

#define	SUCCESS_1		1
#define FAIL_0			0

extern uint16_t Pressure_Data_Digit ;
extern float	Pressure_Data_Float ;

#define SSCDANT250K_Address		0x28
#define SSCDANT250K_Write		SSCDANT250K_Address<<1
#define SSCDANT250K_Read		((SSCDANT250K_Address<<1)+1)
#define IIC_address				0x0000

uint8_t Init_SSCDANT250K_Pressure(void);
uint16_t Read_Pressure_Digital(void);
float Read_Pressure_Print_Float(void);
float Read_Pressure_Average_ntimes(uint8_t ntimes);



#endif
