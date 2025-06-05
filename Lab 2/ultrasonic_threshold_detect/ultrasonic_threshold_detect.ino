#include <HCSR04.h>

// Pines del sensor ultrasónico
byte triggerPin = 12;
byte echoPin = 11;

// Umbral de distancia para detección de obstáculos (en cm)
const int DIST_MIN = 10;

void setup() {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop() {
  // Medir distancia
  double* distances = HCSR04.measureDistanceCm();
  float distance = distances[0];

  // Mostrar la distancia
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm -> ");

  // Aplicar umbralización
  if (distance <= DIST_MIN) {
    Serial.println("¡Obstáculo detectado!");
  } else {
    Serial.println("Sin obstáculo.");
  }

  delay(500);
}