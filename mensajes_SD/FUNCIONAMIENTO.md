# Funcionamiento de la lectura de mensajes desde la SD

### Introducción
Mediante este escrito se pretende documentar el funcionamiento, mantenimiento y modo de uso de la nueva funcionalidad del código Zafirsoft_R2 en su versión [v1.1.1-mensajes-SD](https://github.com/Quintana-S-E/Zafirsoft_R2/releases/tag/v1.1.1-mensajes-SD): el almacenamiento y acceso a cadenas de texto guardadas en la tarjeta SD.  
Siendo el ahorro de memoria (especialmente FLASH) la mayor preocupación durante el desarrollo de la funcionalidad, se implementó en la computadora un sistema de lectura minimalista, que permitiese trasladar la mayor parte de los procesos y complejidad del problema a la "etapa 0" y los preparativos anteriores al vuelo.  
Por ello, para efectuar el mantenimiento del código de tierra y la modificación de las cadenas de texto, se debe llevar a cabo una cuidadosa y específica serie de pasos, detallada aquí.

## Lectura (Zafir)
La lectura de los mensajes por parte de la computadora se lleva a cabo desde una carpeta de nombre "msj" en la tarjeta SD. En ella, los distintos mensajes se encuentran separados en archivos .txt propios, identificados simplemente por un número. Por ej: "0.txt" se encuentra dentro de la carpeta "msj", y contiene el texto "No se ha encontrado tarjeta SD".

### Enum `MensajesSD`
Cada mensaje de la computadora es identificado mediante uno de los enumeradores definidos en [Declaraciones.h](https://github.com/Quintana-S-E/Zafirsoft_R2/blob/8f13b2e4816df921160812402d2953c4189182b5/Declaraciones.h#L48):  
```
enum MensajesSD : unsigned int
{
	FALTA_SD,
	ERROR_ARCHIVO_SD,
	ERROR_BMP280,
	SD_TEMP_IGUAL,
	SD_GRADO_CENT,
	SD_CSV_NOMBRES_DATOS,
	CANTIDAD_MENSAJES_SD
};
```
El valor de cada enumerador (en este caso desde 0U hasta 5U [más el contador]) corresponde así con el nombre del archivo .txt que contiene su mensaje. Por ej: `ERROR_BMP280` tiene un valor de 2U, y el archivo que contiene el mensaje de error del BMP280 se llama "2.txt".  
De este modo, puede accederse a cada mensaje dando uno de estos enumeradores como argumento a la función `mensajeSD()`, la cual devuelve el mensaje solicitado.

### Función `mensajeSD()`
Esta función de tipo `String` se encarga de acceder y devolver el mensaje correspondiente al solicitado en su argumento, y se encuentra definida en [SD_manejo.h](https://github.com/Quintana-S-E/Zafirsoft_R2/blob/8f13b2e4816df921160812402d2953c4189182b5/SD_manejo.h#L26):
```
String mensajeSD(MensajesSD Amensaje)
{
	char nombre_archivo[15];
	sprintf(nombre_archivo, "msj/%u.txt", Amensaje);

	File ArchivoMensaje = SD.open(nombre_archivo, FILE_READ);
	if (ArchivoMensaje)
		return ArchivoMensaje.readStringUntil('\n');
	return "";
}
```
Ya que cada mensaje se encuentra identificado por un número, esta función llama a `SD.open()`, dando como dirección un char array del estilo "msj/n.txt" creado con `sprintf()`, siendo "n" el número correspondiente al mensaje (y enviado en la llamada como argumento). Si la apertura del archivo es exitosa, la función devuelve la `String` devuelta por `readStringUntil('\n')`. De no ser exitosa, la función devuelve una cadena vacía.

## Creación de las cadenas de texto (Etapa 0)
### Generación de los archivos
Para que cada mensaje se encuentre en su propio archivo con nombre enumerado, no es necesaria la edición de cada archivo individual. En lugar de ello, cada mensaje debe guardarse en renglones individuales ordenados en el archivo [mensajes.txt](https://github.com/Quintana-S-E/Zafirsoft_R2/blob/v1.1.1-mensajes-SD/mensajes_SD/msj/mensajes.txt), guardado también en la carpeta "msj" de la SD.  
Luego, en la propia Zafir, puede subirse el código del sketch [Generador_de_mensajes_txt_Zafir.ino](https://github.com/Quintana-S-E/Zafirsoft_R2/blob/v1.1.1-mensajes-SD/mensajes_SD/Generador_de_mensajes_txt_Zafir/Generador_de_mensajes_txt_Zafir.ino), modificando en él solamente la constante `CANTIDAD_MENSAJES_SD`, con el mismo valor del último enumerador del enum `MensajesSD`, que describe la cantidad de archivos a generar.
Este sketch se encarga de abrir mensajes.txt, y una vez por cada mensaje leer la línea correspondiente y generar un archivo en donde escribir su contenido (_aunque el código no es muy legible ni tiene las mejores prácticas_).  
El resultado luego de ejecutar la tarea es la creación, dentro de la carpeta "msj" contenida en la tarjeta SD, de la cantidad configurada de nuevos archivos de texto enumerados, tal como puede verse en la carpeta [msj](https://github.com/Quintana-S-E/Zafirsoft_R2/tree/v1.1.1-mensajes-SD/mensajes_SD/msj) incluida en el repositorio. 

### Organización de los mensajes
Para lograr una mejor organización y coordinación ente el archivo modificable "mensajes.txt" y el código de Zafir, se encuentra en la carpeta [mensajes_SD](https://github.com/Quintana-S-E/Zafirsoft_R2/tree/v1.1.1-mensajes-SD/mensajes_SD) un excel con cada frase ordenada y enumerada.
