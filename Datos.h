#pragma once

#include "Declaraciones.h"

void crearArchivosDatalog()
{
	char nombre_archivo[] = NOMBRE_BASE_ARCHIVO_DATALOG;

	// probamos si existen archivos numerados, hasta llegar a un nombre que no exista
	// i = 2 porque 2 es el siguiente número de vuelo a probar
	for (uint8_t i = 2; i <= 99; i++)
	{
		if (SD.exists(nombre_archivo))
		{
			// el nombre base existe, incrementar el índice de 2 dígitos
			nombre_archivo[6] = i/10 + '0';
			nombre_archivo[7] = i%10 + '0';
		}
		else
			// el nombre no existe, por lo que salimos del for() y creamos los archivos
			break;
	}

	crearArchivoDatalogSD(nombre_archivo);
	//crearArchivoDatalogFlash(nombre_archivo);
}

//==================================================================================================================//

void registrarDatosMilisegundos(unsigned long Adelay_escrituras)
{
	unsigned long tiempo_transcurrido = tiempo_actual - ultima_vez_escritura_datos;
	if (tiempo_transcurrido >= Adelay_escrituras)
	{
		if (Adelay_escrituras == 0)
			Adelay_escrituras = 1;
		// if (tiempo_transcurrido >= 2 * Adelay_escrituras) vamos a saltar una lectura, mucho retraso
		unsigned short retraso = tiempo_transcurrido % Adelay_escrituras;
		ultima_vez_escritura_datos = tiempo_actual - retraso;
		escribirDatos();
	}
}

//==================================================================================================================//

void escribirDatos()
{
	String str_d = "";
	str_d += String((float) tiempo_actual / 1000, 3);		str_d += COMA;
	str_d += String((float) tiempo_vuelo  / 1000, 3);		str_d += COMA;
	str_d += String(estado);			str_d += COMA;
	str_d += String(aceleracion_x_raw);	str_d += COMA;
	str_d += String(aceleracion_y_raw);	str_d += COMA;
	str_d += String(aceleracion_z_raw);	str_d += COMA;
	str_d += String(gyro_x);			str_d += COMA;
	str_d += String(gyro_y);			str_d += COMA;
	str_d += String(gyro_z);			str_d += COMA;
	str_d += String(altura_actual);		str_d += COMA;
	str_d += String(aceleracion_x);

	imprimirln(str_d);
	ArchivoSD.println(str_d);
}

//==================================================================================================================//

inline void registrarUltimosDatos(unsigned long Adelay, unsigned long Atiempo_registro) // llamado en estado = 3
{
	if (tiempo_actual - tiempo_aterrizaje <= Atiempo_registro)
		registrarDatosMilisegundos(Adelay);
}