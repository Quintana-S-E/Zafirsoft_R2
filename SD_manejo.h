#pragma once

#include "Declaraciones.h"

void inicializarSDCard() // llamado en setup()
{
	if (!SD.begin(SD_CS))
	{
		imprimirln(mensajeSD(FALTA_SD));
		digitalWrite(LED_AMARILLO, HIGH);
		while (1)
			;
	}
	ArchivoSD = SD.open("vuelo.txt", FILE_WRITE); //("vuelo.txt", O_CREAT | O_APPEND | O_WRITE);
	if (!ArchivoSD)
	{
		imprimirln(mensajeSD(ERROR_ARCHIVO_SD));
		digitalWrite(LED_AMARILLO, HIGH);
		while (1)
			;
	}
}

//==================================================================================================================//

String mensajeSD(MensajesSD Amensaje)
{
	char nombre_archivo[15];
	sprintf(nombre_archivo, "msj/%u.txt", Amensaje);

	File ArchivoMensaje = SD.open(nombre_archivo, FILE_READ);
	if (ArchivoMensaje)
		return ArchivoMensaje.readStringUntil('\n');
	return "";
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