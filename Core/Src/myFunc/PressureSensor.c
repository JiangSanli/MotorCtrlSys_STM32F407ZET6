

#include <PressureSensor.h>

uint16_t 	Pressure_Data_Digit ;
float		Pressure_Data_Float ;

uint8_t Init_SSCDANT250K_Pressure(void)
{
	uint8_t 	temp_data[2];
	if ( HAL_I2C_Mem_Read(&hi2c2,SSCDANT250K_Read,IIC_address,I2C_MEMADD_SIZE_8BIT,temp_data,2,100) == HAL_OK ){
		printf("Pressure_S init successful \r\n");
		return SUCCESS_1 ;
	}else{
		printf("[FAIL]Pressure_S init FAIL! \r\n");
		return FAIL_0 ;
	}
}


// 读取数字值
uint16_t Read_Pressure_Digital(void)
{
	uint8_t 	temp_data[2];
	uint16_t 	pres_d ;
	if ( HAL_I2C_Mem_Read(&hi2c2,SSCDANT250K_Read,IIC_address,I2C_MEMADD_SIZE_8BIT,temp_data,2,100) == HAL_OK ){
		pres_d = ( (temp_data[0]<<8) + temp_data[1] );
		return pres_d ;
	}else{
		return FAIL_0 ;
	}
}

// 读取并转化为真实气压，单位kPa
float Read_Pressure_Print_Float(void)
{
	uint8_t 	temp_data[2];
	uint16_t 	pres_d ;
	float		pres_f ;
	if ( HAL_I2C_Mem_Read(&hi2c2,SSCDANT250K_Read,IIC_address,I2C_MEMADD_SIZE_8BIT,temp_data,2,100) == HAL_OK ){
		pres_d = ( (temp_data[0]<<8) + temp_data[1] );
		pres_f = ( (pres_d/163.83)-10 ) *250/80;
		return pres_f ;
	}else{
		return FAIL_0 ;
	}
}

float Read_Pressure_Average_ntimes(uint8_t ntimes)
{
	uint8_t 	temp_data[2];
	uint16_t	pres_temp = 0;
	uint32_t 	pres_d_av = 0 ;
	float		pres_f ;
	for(uint16_t j=0 ; j<ntimes ; j++){
		if ( HAL_I2C_Mem_Read(&hi2c2,SSCDANT250K_Read,IIC_address,I2C_MEMADD_SIZE_8BIT,temp_data,2,100) == HAL_OK ){
			pres_temp = ( (temp_data[0]<<8) + temp_data[1] );
			pres_d_av = pres_d_av + pres_temp ;
			HAL_Delay(5);
		}else{
			printf("IIC WRONG!!! \r\n");
			return FAIL_0 ;
		}
	}
	pres_f = ( (pres_d_av/163.83/ntimes)-10 ) *250/80;
	return pres_f;
}
