#pragma once

#include "Declaraciones.h"

inline void desplegarParacaidas() // llamado en estado = 2
{
	if (!Flags.paracaidas_desplegado)
	{
		Paracaidas.write(ANGULO_DESPLIEGUE);
		Flags.paracaidas_desplegado = true;
	}
}