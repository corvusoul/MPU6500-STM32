/*
 * MPU6500.h
 *
 *  Created on: Feb 18, 2024
 *      Author: S Vedram
 */

#ifndef INC_MPU6500_H_
#define INC_MPU6500_H_

#define RAD2DEG                   57.2957795131

//Includes
#include <stm32f4xx_hal.h>
#include <i2c.h>

//Defines
#define MPU6500_I2C_ADDRESS       (0x68 << 1) //Page 44 of Register Map

#define MPU6500_WHOAMI_Value      0x70
#define MPU6500_Reg_WHOAMI        0x75 //Page 44 of Register Map

#define MPU6500_Reg_PWR_MGMT_1    0x6B //Page 47 of Register Map

//Raw Data Register - Page 31 of Register Map
#define MPU6500_Reg_ACCEL_XOUT_H  0x3B


struct rawData
{
	int16_t ax, ay, az, t, gx, gy, gz;
};

struct scaledData
{
	float ax, ay, az, t, gx, gy, gz;
};

HAL_StatusTypeDef MPU6500_Init(I2C_HandleTypeDef *I2Cx);
struct rawData MPU6500_ReadRawData(I2C_HandleTypeDef *I2Cx);
struct scaledData MPU6500_ScaledData(struct rawData rawData);

#endif /* INC_MPU6500_H_ */
