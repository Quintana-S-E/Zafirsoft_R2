#pragma once

#include "Declaraciones.h"

void inicializarSDCard() // llamado en setup()
{
	if (!SD.begin(SD_CS))
	{
		imprimirln("Falta tarjeta SD");
		digitalWrite(LED_AMARILLO, HIGH);
		while (1)
			;
	}
	ArchivoSD = SD.open("vuelo.txt", FILE_WRITE); //("vuelo.txt", O_CREAT | O_APPEND | O_WRITE);
	if (!ArchivoSD)
	{
		imprimirln("No se pudo abrir o modificar el archivo SD");
		digitalWrite(LED_AMARILLO, HIGH);
		while (1)
			;
	}
}

//==================================================================================================================//

inline void asegurarSDCard() // llamado en estado = 2
{
	if (!Flags.SD_card_asegurada)
	{
		ArchivoSD.flush();
		Flags.SD_card_asegurada = true;
	}
}

//==================================================================================================================//

inline void finalizarSDCard() // llamado en estado = 3
{
	if (Flags.SD_card_cerrada)
		return;
	ArchivoSD.close();
	Flags.SD_card_cerrada = true;
}