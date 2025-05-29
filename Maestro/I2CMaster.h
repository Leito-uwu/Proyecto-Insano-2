#ifndef I2CMASTER_H
#define I2CMASTER_H

#include <Arduino.h>

// Inicializa la interfaz I2C del ESP32
void iniciarComunicacionI2C();

// Solicita y devuelve una cadena de texto desde el esclavo I2C
String leerDesdeEsclavoI2C(uint8_t direccion, uint8_t cantidad);

// Procesa los datos leídos (IR y distancia), aplica promedio móvil y los muestra por serial
void procesarLecturaFiltrada(uint8_t direccion, uint8_t cantidad);

#endif
