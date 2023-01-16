#pragma once

#include "Declaraciones.h"

inline void actualizarTiempo()
{
	tiempo_actual = millis();
	tiempo_vuelo = tiempo_actual - t0_vuelo;
	if (estado == 0)
		tiempo_vuelo = 0;
}