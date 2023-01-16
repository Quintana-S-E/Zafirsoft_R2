#pragma once

#include "Declaraciones.h"

void inicializarMPU6050()
{
	Wire.beginTransmission(0x68); // I2C address of the MPU
	Wire.write(0x6B);			  // Accessing the register 6B - Power Management (Sec. 4.28)
	Wire.write(0b00000000);		  // Setting SLEEP register to 0. (Required; see Note on p. 9)
	Wire.endTransmission();
	Wire.beginTransmission(0x68); // I2C address of the MPU
	Wire.write(0x1B);			  // Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
	Wire.write(0b00011000);		  // Setting the gyro to +/- 2000deg./s
	Wire.endTransmission();
	Wire.beginTransmission(0x68);	 // I2C address of the MPU
	Wire.write(0x1C);				 // Accessing the register 1C - aceleracion_ccelerometer Configuration (Sec. 4.5)
	Wire.write(RANGO_ACELERACIONES); // Setting the accel to +/- 16g.
	Wire.endTransmission();
}

//==================================================================================================================//

void leerIMU()
{
	Wire.beginTransmission(0x68);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(0x68, 12, true);
	aceleracion_x_raw = Wire.read() << 8 | Wire.read();
	aceleracion_y_raw = Wire.read() << 8 | Wire.read();
	aceleracion_z_raw = Wire.read() << 8 | Wire.read();
	gyro_x = Wire.read() << 8 | Wire.read();
	gyro_y = Wire.read() << 8 | Wire.read();
	gyro_z = Wire.read() << 8 | Wire.read();

	// Convertimos aceleracion_x_raw a aceleracion_x en m/s^2
	aceleracion_x = ( (float) aceleracion_x_raw * 9.81F )	/	2048.0F;
	aceleracion_x -= 0.3F; // restamos 0,30 para corregir
}