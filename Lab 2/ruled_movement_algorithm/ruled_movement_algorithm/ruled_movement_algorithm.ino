// -------------- Librerías--------------------
#include <HCSR04.h> // Sensor Ultrasónico
#include <Wire.h> 
#include "Adafruit_TCS34725.h" // Sensor Color
#include <Servo.h> // Servo motor

// -------------- Configuración de pines ----------------- 

// == Pines ultrasónico ==
  byte triggerPin = 12;
  byte echoPin = 11;
  // Umbral de distancia para detección de obstáculos (en cm)
    const int DIST_MIN = 10;

// == Pines motores == 
  const int IN1 = 3;  // Motor izquierdo
  const int IN2 = 4;
  const int IN3 = 5;  // Motor derecho
  const int IN4 = 6;
  // Pines de velocidad PWM
  const int ENA = 9;  // PWM motor izquierdo
  const int ENB = 10; // PWM motor derecho
// == Servo motor
  Servo servoMotor;
//== Sensor de Color == 
  uint16_t r, g, b, c;
  // Crear objeto del sensor con integración larga y ganancia baja (más estable)
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup(){
  // Servo 
  servoMotor.attach(8);
  //Ultrasónico
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  // Motores
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  //Sensor Color
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor TCS34725.");
    while (1); // Se detiene si no encuentra el sensor
  }
}

// --------------- LOOP -------------------

void loop() {
  float distancia = medirDistancia();

  // Mientras no haya obstáculo
  if (distancia > DIST_MIN) {
    avanzar(500, 200);
  } else {
    // Obstáculo detectado: leer color
    detenerse(500);
    
    // Medir color debajo del robot
    tcs.getRawData(&r, &g, &b, &c);
    if (c == 0) c = 1; // evitar división por cero

    float fr = (float)r / c;
    float fg = (float)g / c;
    float fb = (float)b / c;

    String color = detectarColor(fr, fg, fb, c);
    Serial.print("Color detectado: ");
    Serial.println(color);

    // Acciones según el color detectado
    if (color == "Rojo") {
      girarDerecha(500, 200);
      detenerse(500);
      // Avanzar hasta siguiente obstáculo
      while (medirDistancia() > DIST_MIN) {
        avanzar(500, 200);
      }

    } else if (color == "Azul") {
      girarIzquierda(500, 200);
      detenerse(500);
      // Avanzar hasta siguiente obstáculo
      while (medirDistancia() > DIST_MIN) {
        avanzar(500, 200);
      }

    } else if (color == "Negro") {
      detenerse(500);
      retroceder(500, 200);
      detenerse(500);
      girarDerecha(500, 200);
      detenerse(500);
      girarDerecha(500, 200);
      detenerse(500);
      // Avanzar hasta siguiente obstáculo
      while (medirDistancia() > DIST_MIN) {
        avanzar(500, 200);
      }

    } else {
      // Color desconocido o no válido: solo detenerse por seguridad
      detenerse(500);
    }
  }
}

//-------------------- Funciones --------------------------

// == Movimiento Motores

// Avanzar
 void avanzar(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Retroceder
void retroceder(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Detenerse
void detenerse(int tiempo) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(tiempo);
}

// Girar a la derecha
void girarDerecha(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Girar a la izquierda
void girarIzquierda(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// == Sensor ultrasónico
// Medir distancia
float medirDistancia() {
  double* distances = HCSR04.measureDistanceCm();
  return distances[0];  // devuelve la distancia en centímetros
}

// == Servo motor
// Mirar a la derecha
void mirarDerecha() {
  servoMotor.write(0);   // 0 grados
  delay(500);
}
// Mirar al frente
void mirarFrente() {
  servoMotor.write(90);  // 90 grados
  delay(500);
}

// Mirar a la izquierda
void mirarIzquierda() {
  servoMotor.write(180); // 180 grados
  delay(500);
}

// == Sensor Color 

// Detectar Color
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
