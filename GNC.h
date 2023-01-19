#pragma once

#include "Declaraciones.h"
#include "Datos.h"

inline void detectarLanzamiento()// llamado en estado = 0
{
	// Medir 2 g por 0,5 segundos me parece mejor
	if (aceleracion_x > 15)
	{
		estado++;
		ejecutarConfiguracionDespegue();
	}
}

//==================================================================================================================//

void ejecutarConfiguracionDespegue() // llamado en estado = 0, en detectarLanzamiento()
{
	t0_vuelo = tiempo_actual;
	altura_anterior = altura_actual;
	digitalWrite(BUZZER, LOW);
	escribirDatos();
}

//==================================================================================================================//

void detectarApogeo() // llamado en estado = 1
{
	// si pasaron los milisegundos correspondientes a la lectura
	if (tiempo_vuelo >= DELAY_APOGEO * cuenta_comprobaciones_apogeo)
	{
		cuenta_comprobaciones_apogeo++;
		if (altura_actual < altura_anterior)
			estado++; // pasar a estado 2
		else
			altura_anterior = altura_actual;
	}
}

//==================================================================================================================//

inline void detectarAterrizaje()
{
	if (altura_actual < ALTURA_ATERRIZAJE)
	{
		estado++;
		tiempo_aterrizaje = tiempo_actual;
	}
}

//==================================================================================================================//

inline void finalizarProcesos(unsigned long Aespera_despues_de_aterrizar)
{
	if (tiempo_actual - tiempo_aterrizaje > Aespera_despues_de_aterrizar)
	{
		finalizarSDCard(); // tiene una flag y se ejecuta una sola vez
		// finalizar flashchip
		indicarProcesosFinalizados();
	}
}