/*
 * MPU6500.c
 *
 *  Created on: Feb 18, 2024
 *      Author: S Vedram
 */


#include <MPU6500.h>

HAL_StatusTypeDef MPU6500_Init(I2C_HandleTypeDef *I2Cx)
{
	uint8_t check;
	HAL_StatusTypeDef statuscheck = HAL_I2C_Mem_Read(I2Cx, MPU6500_I2C_ADDRESS, MPU6500_Reg_WHOAMI, 1, &check, 1, 1000);

	if (statuscheck == HAL_OK && check == MPU6500_WHOAMI_Value)
	{
		//Power on the Sensor
		uint8_t poweron = 0x00;
		HAL_StatusTypeDef status = HAL_I2C_Mem_Write(I2Cx, MPU6500_I2C_ADDRESS, MPU6500_Reg_PWR_MGMT_1, 1, &poweron, 1, 1000);

		return status;
	}
	return HAL_ERROR;
}

struct rawData MPU6500_ReadRawData(I2C_HandleTypeDef *I2Cx)
{
	uint8_t serial_buffer[14];
	struct rawData atgraw;

	HAL_I2C_Mem_Read(I2Cx, MPU6500_I2C_ADDRESS, MPU6500_Reg_ACCEL_XOUT_H, 1, serial_buffer, 14, 1000);
	atgraw.ax = serial_buffer[0] << 8 | serial_buffer[1];
	atgraw.ay = serial_buffer[2] << 8 | serial_buffer[3];
	atgraw.az = serial_buffer[4] << 8 | serial_buffer[5];
	atgraw.t = serial_buffer[6] << 8 | serial_buffer[7];
	atgraw.gx = serial_buffer[8] << 8 | serial_buffer[9];
	atgraw.gy = serial_buffer[10] << 8 | serial_buffer[11];
	atgraw.gz = serial_buffer[12] << 8 | serial_buffer[13];

	return atgraw;
}

struct scaledData MPU6500_ScaledData(struct rawData raw)
{
	struct scaledData atgscaled;
	atgscaled.ax = ((raw.ax * 9.81) / 16384.0);
	atgscaled.ay = ((raw.ay * 9.81) / 16384.0);
	atgscaled.az = ((raw.az * 9.81) / 16384.0);

	atgscaled.t = (raw.t / 340) + 36.53; //TEMP_degC = ((TEMP_OUT – RoomTemp_Offset)/Temp_Sensitivity) + 21degC (Page 33 of Register Map)

	atgscaled.gx = (raw.gx * 0.0174) / 131.0;
	atgscaled.gy = (raw.gy * 0.0174) / 131.0;
	atgscaled.gz = (raw.gz * 0.0174) / 131.0;

	return atgscaled;
}
