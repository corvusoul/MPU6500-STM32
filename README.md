<h1>MPU 6500 I2C Driver for STM32 using HAL</h1>

These 2 files constitute an extremely simple and rudimentary I2C driver for MPU6500 with an STM32 MCU using the STM HAL Driver.
The only argument that is required is the I2C_HandleTypeDef that you choose while initializing the .ioc file.

I am aware that this does not even initialize the accelerometer or gyroscope scaling but the default ones worked good enough for me so I did not implement it.

Maybe later.
