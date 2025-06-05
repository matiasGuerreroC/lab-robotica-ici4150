#include <HCSR04.h>

// Pines del sensor ultrasónico
byte triggerPin = 12;
byte echoPin = 11;

void setup() {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop() {
  // Medir distancia en centímetros
  double* distances = HCSR04.measureDistanceCm();
  float distance = distances[0];

  // Mostrar la distancia en el monitor serie
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(250); // Pequeño retardo para evitar lecturas excesivas
}
