#include <Arduino.h>
#include "I2CMaster.h"

// Dirección del esclavo I2C
#define SLAVE_ADDRESS 0x08

void setup() {
  Serial.begin(115200);         // Inicia el monitor serial
  iniciarComunicacionI2C();     // Configura el bus I2C
}

void loop() {
  procesarLecturaFiltrada(SLAVE_ADDRESS, 32);
  delay(200);
}
