#include <SD.h>

// SÓLO CAMBIAR LOS SIGUIENTES DOS VALORES:
#define PIN_SPI_CS 10
#define CANTIDAD_MENSAJES_SD 6




File Archivo_mensajes;
File Archivo_mensaje_actual;

String obtenerMensaje(int Anumero_mensaje);


void setup()
{
  Serial.begin(9600);
  delay(3000);

  if (!SD.begin(PIN_SPI_CS))
  {
    Serial.println("No se encontró tarjeta SD");
    while (1)
      ;
  }

  
  for (int i = 0; i < CANTIDAD_MENSAJES_SD; i++)
  {
    Archivo_mensajes = SD.open("msj/mensajes.txt", FILE_READ);
    if (!Archivo_mensajes)
    {
      Serial.print("No se pudo abrir el archivo de mensajes. i vale: ");
      Serial.println(i);
      continue;
    }

    
    String mensaje = obtenerMensaje(i);
    Serial.print("Mensaje de mensajes.txt: ");
    Serial.println(mensaje);
    Archivo_mensajes.close();

    
    String archivo_mensaje_nombre = "msj/";
    archivo_mensaje_nombre += String(i);
    archivo_mensaje_nombre += ".txt";
    
    int buffer_size = 11;//archivo_mensaje_nombre.length() + 1;
    Serial.print("El nombre del archivo en String es: ");
    Serial.print(archivo_mensaje_nombre);
    Serial.print(", tamaño: ");
    Serial.println(buffer_size);
    char archivo_mensaje_nombre_char[buffer_size];
    archivo_mensaje_nombre.toCharArray(archivo_mensaje_nombre_char, buffer_size);
    Serial.print("El nombre del archivo en Char array es: ");
    Serial.println(archivo_mensaje_nombre_char);

    
    Archivo_mensaje_actual = SD.open(archivo_mensaje_nombre_char, FILE_WRITE);
    if (Archivo_mensaje_actual)
    {
      Archivo_mensaje_actual.print(mensaje);
      Serial.println("Escrito");
    }
    else
    {
      Serial.print("Error al crear el archivo Número ");
      Serial.println(archivo_mensaje_nombre);
    }
    Archivo_mensaje_actual.close();
  }

  Serial.print("Hecho");
}


String obtenerMensaje(int Anumero_mensaje)
{
  String mensaje;
  
  for (int j = 0; j <= Anumero_mensaje; j++)
    mensaje = Archivo_mensajes.readStringUntil('\n');

  return mensaje;
}

void loop()
{
}
