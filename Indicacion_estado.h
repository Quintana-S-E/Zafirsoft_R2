#pragma once

#include "Declaraciones.h"

inline void pitidosIniciales() // llamado en setup()
{
	for (int n = 0; n < PITIDOS; n++)
	{
		digitalWrite(BUZZER, HIGH);
		digitalWrite(LED_AZUL_ROJO, HIGH);
		digitalWrite(LED_AMARILLO, HIGH);
		delay(80);
		digitalWrite(BUZZER, LOW);
		digitalWrite(LED_AZUL_ROJO, LOW);
		digitalWrite(LED_AMARILLO, LOW);
		delay(25);
	}
}

//==================================================================================================================//

void indicacionEstado0()
{
	analogWrite(LED_AZUL_ROJO, cuentaStateInd);

	switch (LedesBuzzerBrillo)
	{
	case SubiendoSinPitido:
		cuentaStateInd++;
		if (cuentaStateInd == 255)
			LedesBuzzerBrillo = BajandoSinPitido;
		break;

	case BajandoSinPitido:
		cuentaStateInd--;
		if (cuentaStateInd == 20)
			LedesBuzzerBrillo = SubiendoConPitido;
		break;

	case SubiendoConPitido:
		cuentaStateInd++;
		if (cuentaStateInd == 255)
		{
			LedesBuzzerBrillo = BajandoConPitido;
			digitalWrite(BUZZER, HIGH);
		}
		break;

	case BajandoConPitido:
		cuentaStateInd--;
		if (cuentaStateInd == 233)
			digitalWrite(BUZZER, LOW);
		//else if(cuentaStateInd == 211)
		//	digitalWrite(BUZZER, HIGH); //descomentar para hacer dos pitidos
		//else if(cuentaStateInd == 89)
		//	digitalWrite(BUZZER, LOW);
		if (cuentaStateInd == 20)
			LedesBuzzerBrillo = SubiendoSinPitido;
		break;
	}
}

//==================================================================================================================//

void indicarEstado()
{
	switch (estado)
	{
	case 0: // dimmear led y pitido
		if (tiempo_actual - ultima_vez_indicacion_estado_0 >= DELAY_ACTUALIZACION_BRILLO_LEDES)
		{
			ultima_vez_indicacion_estado_0 = tiempo_actual;
			indicacionEstado0();
		}
		break;

	case 1:
		digitalWrite(LED_AZUL_ROJO, HIGH);
		digitalWrite(LED_AMARILLO, HIGH);
		break;

	case 2:
		digitalWrite(LED_AMARILLO, LOW);
		break;

	case 3:
		cuentaStateInd++;
		delay(5);
		// cuentaStateInd = 0 en void ejecutarConfiguracionDespegue()
		if (cuentaStateInd >= 100)
		{
			digitalWrite(BUZZER, !digitalRead(BUZZER));
			digitalWrite(LED_AZUL_ROJO, !digitalRead(LED_AZUL_ROJO));
			cuentaStateInd = 0;
		}
		break;
	}
}