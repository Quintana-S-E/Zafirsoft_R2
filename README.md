# Zafirsoft_R2

English clarification: all contents in this repository, including comments, function and variable names, and any documentation are (mostly) in Spanish. And they will continue to be.

___
### Introducción
Este es el código basado en el entorno Arduino de la computadora de vuelo Zafir, para cohetería experimental y modelista. El mismo controla tres salidas visuales, una auditiva, una de movimiento, otra eléctrica de potencia (MOSFET), y un sistema de datalog hasta a 181 Hz en tarjeta SD.

### Computadora de vuelo
#### Componentes
+ Arduino Nano (ATmega328p U-TH @16 MHz. 2 KB RAM, 30 KB FLASH usable) **(NRFND)**. [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
+ Módulo sensor MPU6050; protocolo I2C **(NRFND)**. [datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
+ Módulo sensor BMP280; protocolo I2C. [datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)
+ Módulo lector microSD HW-125; protocolo SPI.
+ N channel MOSFET 2SK3533-01 (7 Amperes continuos). [datasheet](https://pdf1.alldatasheet.com/datasheet-pdf/view/422439/FUJI/2SK3533-01.html)
+ Servomotor 9 g.
+ Ledes X3: rojo y azul (juntos), y amarillo (independiente).
+ Buzzer activo.

#### Capacidades
+ Detección de despegue, apogeo y aterrizaje.
+ Despliegue de paracaídas (doble, programable).
+ Medición de:
  + Aceleración en los tres ejes, hasta ±16 g.
  + Velocidades de precesión (giroscopios) en los tres ejes, hasta ±2000 ${deg} \over {s}$.
  + Altitud relativa y absoluta, desde -500 hasta 9000 m s. n. m.
+ Recopilación rápida (hasta de 181 Hz: 5,52 ms promedio entre escrituras) de datos csv en tarjeta SD de hasta 32 GB.
+ Alta velocidad del loop en vuelo (~250 Hz sin datalog [3,42-3,8 ms por leer sensores], y ~181 Hz con datalog [5,52 ms totales]).
+ Alimentación desde 6 hasta 20 V no regulados.

### Próximos cambios
+ [ ] Control de buzzer pasivo.
+ [ ] Implementar un sistema para la creación de nuevos nombres para cada archivo de datalog.
+ [ ] Mover todos los mensajes del código a un archivo en la SD para ahorrar memoria.

### Changelog
+ [v1.0.0 Separación en headers](https://github.com/Quintana-S-E/Zafirsoft_R2/releases/tag/v1.0.0) ¡primera versión!
