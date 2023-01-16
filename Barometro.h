#pragma once

#include "Declaraciones.h"

void inicializarBarometro() // llamado en setup()
{
	if (!Bmp.begin(0x76))
	{
		imprimirln("No se encontró sensor BMP280");
		digitalWrite(LED_AMARILLO, HIGH);
		while (1)
			;
	}
	Bmp.setSampling(
		Adafruit_BMP280::MODE_NORMAL,  /* Operating Mode. */
		Adafruit_BMP280::SAMPLING_X16, /* Temp. oversampling */
		Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
		Adafruit_BMP280::FILTER_X16,   /* Filtering. */
		Adafruit_BMP280::STANDBY_MS_1);/* Standby time. */ // puesto a X1 según datasheet
	presion_inicial = Bmp.readPressure() / 100;
}

//==================================================================================================================//

inline float devolverAltura(float Apresion_base)
{
	return Bmp.readAltitude(Apresion_base);
}

//==================================================================================================================//

inline float devolverTemperatura()
{
	return Bmp.readTemperature();
}