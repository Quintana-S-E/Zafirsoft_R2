/*------------------------------------------------------------------------------------------------------------------*\
	Nombre:				Zafirsoft_R2
	Desarrollo: 		enero - marzo de 2022 / enero 2023 - presente
	Primer lanzamiento:	12 de marzo de 2022
	Creado por:			Quintana Santiago Esteban

	Esta es una versión del código de Zafir la cual no usa delay (excepto en estado 3, donde no perjudica al vuelo,
	para parpadear ledes y buzzer). El loop tiene un delay de 3,42-3,8 ms por leer sensores, mas otros 1,8 ms cuando
	hace datalog. La datalog rate es de 181 Hz (5,52 ms entre registros), aunque cada 7 registros hay uno que tarda
	8,5 ms (y que rara vez puede tardar más).
\*------------------------------------------------------------------------------------------------------------------*/

#include "Declaraciones.h"
#include "Activaciones.h"
#include "Barometro.h"
#include "Datos.h"
#include "GNC.h"
#include "IMU.h"
#include "Indicacion_estado.h"
#include "SD_manejo.h"
#include "Tiempo.h"

void setup()
{
	delay(2000);
#ifdef DEBUGserial
	Serial.begin(9600);
#endif
	Wire.begin();
	pinMode(PYRO1, OUTPUT);
	digitalWrite(PYRO1, LOW);
	pinMode(LED_AZUL_ROJO, OUTPUT);
	pinMode(LED_AMARILLO, OUTPUT);
	pinMode(BUZZER, OUTPUT);
	pitidosIniciales();

	inicializarMPU6050();
	// Serial.println("¡Zafir se ha iniciado! Comenzando comprobaciones de los sistemas a bordo...");

	inicializarSDCard();
	// Serial.println("Tarjeta SD configurada con éxito! Calibrando el barómetro BMP280...");
	
	delay(2480);

	inicializarBarometro();
	// Serial.println("BMP280 configurado con éxito! Estableciendo sistema de liberación...");

	ArchivoSD.print("Temp: ");
	ArchivoSD.print( devolverTemperatura() );
	ArchivoSD.println(" °C");
	ArchivoSD.println("t(s),t_v(s),Estado,AcXr,AcYr,AcZr,gyroX,gyroY,gyroZ,Alt,AcX(m/s2)");

	Paracaidas.attach(PIN_SERVO, PULSOMIN, PULSOMAX);
	Paracaidas.write(ANGULO_APERTURA);
	// Serial.println("Sistema de liberación listo");

	delay(20); // tarda 4,5 segundos en terminar el setup.
	// Serial.println("¡Zafir está lista para el vuelo!");
}

//=================================================fin del setup()==================================================//

void loop()
{
	indicarEstado();
	leerIMU();
	altura_actual = devolverAltura(presion_inicial);
	actualizarTiempo();
	
	switch (estado)
	{
	case 0: // plataforma
		registrarDatosMilisegundos(1000);
		detectarLanzamiento();
		break;

	case 1: // volando
		detectarApogeo();
		registrarDatosMilisegundos(0);
		break;

	case 2: // caída segura en paracaídas
		desplegarParacaidas();
		asegurarSDCard();
		detectarAterrizaje();
		registrarDatosMilisegundos(10);
		break;

	case 3: // tierra firme, tomar datos finales y terminar procesos
		registrarUltimosDatos(500);
		finalizarProcesos();
		break;
	}
}