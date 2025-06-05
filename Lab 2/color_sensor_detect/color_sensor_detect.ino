#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Crear objeto del sensor con integración larga y ganancia baja (más estable)
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
 
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor TCS34725.");
    while (1); // Se detiene si no encuentra el sensor
  }

  // Recomendado: encender el LED del sensor manualmente conectando LED a GND
}

void loop() {
  uint16_t r, g, b, c;

  // Obtener datos crudos
  tcs.getRawData(&r, &g, &b, &c);

  // Evitar división por cero
  if (c == 0) c = 1;

  // Normalización
  float fr = (float)r / c;
  float fg = (float)g / c;
  float fb = (float)b / c;

  // Mostrar datos crudos y normalizados
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" C: "); Serial.print(c);
  Serial.print(" | fr: "); Serial.print(fr, 2);
  Serial.print(" fg: "); Serial.print(fg, 2);
  Serial.print(" fb: "); Serial.print(fb, 2);

  // Detección del color
  String color = detectarColor(fr, fg, fb, c);
  Serial.print(" -> Color: "); Serial.println(color);

  delay(1000); // Tiempo entre lecturas
}

// Función para identificar el color según proporciones RGB normalizadas y claridad
String detectarColor(float fr, float fg, float fb, uint16_t c) {
  if (c < 30 && fr > 0.35 && fg > 0.30 && fb > 0.25) {
    return "Negro";
  } else if (fr > 0.60 && fg < 0.45 && fb < 0.45) {
    return "Rojo";
  } else if (fr > 0.33 && fr < 0.40 && fg > 0.43 && fg < 0.47 && fb < 0.30) {
    return "Verde";
  } else if (fb > 0.41 && fr < 0.42 && fg < 0.42 && c < 50) {
    return "Azul";
  } else if (fr > 0.34 && fr < 0.40 && fg > 0.36 && fg < 0.40 && fb > 0.28 && fb < 0.33 && c > 90) {
    return "Blanco";
  } else {
    return "Desconocido";
  }
}
