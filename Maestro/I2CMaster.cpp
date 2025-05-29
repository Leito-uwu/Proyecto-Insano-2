#include "I2CMaster.h"
#include <Wire.h>

// Tamaño de la ventana para el filtro de promedio móvil
#define WINDOW_SIZE 5

// Arreglos para almacenar los últimos valores
int irWindow[WINDOW_SIZE] = {0};
int distWindow[WINDOW_SIZE] = {0};

int indexFiltro = 0;
bool ventanaLlena = false;

void iniciarComunicacionI2C() {
  Wire.begin(); // En ESP32: SDA = GPIO 21, SCL = GPIO 22 por defecto
}

String leerDesdeEsclavoI2C(uint8_t direccion, uint8_t cantidad) {
  String datos = "";
  Wire.requestFrom(direccion, cantidad);
  while (Wire.available()) {
    char caracter = Wire.read();
    if (isPrintable(caracter)) {
      datos += caracter;
    }
  }
  return datos;
}

void procesarLecturaFiltrada(uint8_t direccion, uint8_t cantidad) {
  String datos = leerDesdeEsclavoI2C(direccion, cantidad);

  // Separar IR y distancia si hay coma
  int coma = datos.indexOf(',');
  if (coma > 0) {
    int ir = datos.substring(0, coma).toInt();
    int dist = datos.substring(coma + 1).toInt();

    // Guardar valores en ventana circular
    irWindow[indexFiltro] = ir;
    distWindow[indexFiltro] = dist;

    indexFiltro++;
    if (indexFiltro >= WINDOW_SIZE) {
      indexFiltro = 0;
      ventanaLlena = true;
    }

    // Calcular promedios
    int irProm = 0, distProm = 0;
    int n = ventanaLlena ? WINDOW_SIZE : indexFiltro;

    for (int i = 0; i < n; i++) {
      irProm += irWindow[i];
      distProm += distWindow[i];
    }

    irProm /= n;
    distProm /= n;

    // Mostrar datos filtrados
    Serial.print("IR filtrado: ");
    Serial.print(irProm);
    Serial.print("\tDistancia filtrada: ");
    Serial.println(distProm);
  }
}
