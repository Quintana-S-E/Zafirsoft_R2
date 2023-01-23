#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// CAMBIAR LA SIGUIENTE DEFINICIÓN PARA DEBUGGING
//#define DEBUGserial
#ifdef DEBUGserial
	#define imprimir(x) Serial.print(x)
	#define imprimirln(x) Serial.println(x)
	// #define imprimir2Paramts(x,y) Serial.print(x,y)
	// #define imprimirln2Paramts(x,y) Serial.println(x,y)
#else
	#define imprimir(x)
	#define imprimirln(x)
	// #define imprimir2Paramts(x,y)
	// #define imprimirln2Paramts(x,y)
#endif

// Constantes de funcionamiento generales
#define COMA ","
#define ALTURA_ATERRIZAJE 3.0F
#define TIEMPO_REGISTRO_DESPUES_ATERRIZAR 10000UL

// Pines
#define PIN_SERVO 6
#define LED_AZUL_ROJO 5
#define LED_AMARILLO 4
#define BUZZER 8
#define PYRO1 2
#define SD_CS 10

// Variables generales
uint8_t estado = 0;
unsigned long tiempo_actual;
unsigned long t0_vuelo = 0;
unsigned long tiempo_vuelo;
unsigned long tiempo_aterrizaje;
float altura_actual;
float aceleracion_x;
int16_t aceleracion_x_raw, aceleracion_y_raw, aceleracion_z_raw;
int16_t gyro_x, gyro_y, gyro_z;

// Flags de estado generales
struct FlagsDeEstado
{
	uint8_t paracaidas_desplegado	: 1;
	uint8_t SD_card_asegurada		: 1;
	uint8_t SD_card_cerrada			: 1;
} Flags;

// Indicacion_estado.h
inline void pitidosIniciales();
void indicacionEstado0();
void indicarEstado();
inline void indicarProcesosFinalizados();
unsigned long ultima_vez_indicacion_estado_0 = 0;
uint8_t cuentaStateInd = 0;
#define PITIDOS 3
#define DELAY_ACTUALIZACION_BRILLO_LEDES 4UL
enum LedesBuzzerBrilloEstados
{
	SubiendoSinPitido,
	BajandoSinPitido,
	SubiendoConPitido,
	BajandoConPitido
};
LedesBuzzerBrilloEstados LedesBuzzerBrillo = SubiendoSinPitido;

// GNC.h
inline void detectarLanzamiento();
void ejecutarConfiguracionDespegue();
void detectarApogeo();
inline void detectarAterrizaje();
inline void finalizarProcesos(unsigned long Aespera_despues_de_aterrizar);
float altura_anterior;
unsigned long cuenta_comprobaciones_apogeo = 0;
#define DELAY_APOGEO 250UL

// IMU.h
void inicializarMPU6050();
void leerIMU();
#define _2G		0b00000000
#define _4G		0b00001000
#define _8G		0b00010000
#define _16G	0b00011000
#define RANGO_ACELERACIONES _16G
// 2g = 16384, 4g = 4096, 8g = 8192, 16g = 2048 son los valores crudos del DAC que deberían corresponder a 1g

// Activaciones.h
inline void desplegarParacaidas();
#define PULSOMAX			1500
#define PULSOMIN			500
#define ANGULO_APERTURA		85
#define ANGULO_DESPLIEGUE	175
Servo Paracaidas;
// Todo lo de pyro channels

// Barometro.h
void inicializarBarometro();
inline float devolverAltura(float Apresion_base = 1013.25);
inline float devolverTemperatura();
float presion_inicial;
Adafruit_BMP280 Bmp;

// SD_manejo.h
void inicializarSDCard();
inline void asegurarSDCard();
inline void finalizarSDCard();
File ArchivoSD;

// Datos.h
void registrarDatosMilisegundos(unsigned long Adelay_escrituras);
void escribirDatos();
inline void registrarUltimosDatos(unsigned long Adelay, unsigned long Atiempo_registro);
unsigned long ultima_vez_escritura_datos = 0;

// Tiempo.h
inline void actualizarTiempo();