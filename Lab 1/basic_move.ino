#include <Wire.h>
#include <MPU6050.h>

// Pines del motor
const int IN1 = 3, IN2 = 4, ENA = 9;
const int IN3 = 5, IN4 = 6, ENB = 10;

// Parámetros del robot
const float R = 0.03; // radio de rueda en metros
const float L = 0.15; // distancia entre ruedas (eje) en metros
float x = 0, y = 0, theta = 0; // posición y orientación del robot
unsigned long lastTime = 0;

// Control de velocidad
int velIzq = 150; // PWM motor izquierdo (0-255)
int velDer = 150; // PWM motor derecho (0-255)

// IMU
MPU6050 imu;
float gyroBiasZ = 0;
const int N = 500; // muestras para calibración

void setup() {
  Serial.begin(115200);

  // Pines motores
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Inicializar IMU
  Wire.begin();
  imu.initialize();

  // Calibración giroscopio Z
  Serial.println("Calibrando giroscopio...");
  for (int i = 0; i < N; i++) {
    gyroBiasZ += imu.getRotationZ();
    delay(5);
  }
  gyroBiasZ /= N;
  Serial.print("Bias Z: "); Serial.println(gyroBiasZ);

  lastTime = millis();
}

// Movimiento hacia adelante con control de dirección
void avanzarCorrigiendo() {
  // Leer giroscopio
  float gyroZ = imu.getRotationZ() - gyroBiasZ;

  // Calcular corrección simple: si se desvía a la derecha, reducir velocidad derecha
  float factorCorreccion = gyroZ / 200.0;
  int ajuste = constrain(factorCorreccion * 100, -50, 50);

  analogWrite(ENA, constrain(velIzq - ajuste, 0, 255));
  analogWrite(ENB, constrain(velDer + ajuste, 0, 255));

  // Dirección adelante
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

// Cinemática diferencial
void estimarPosicion() {
  unsigned long tiempoActual = millis();
  float dt = (tiempoActual - lastTime) / 1000.0;
  lastTime = tiempoActual;

  // Velocidades angulares aproximadas (PWM proporcional)
  float vL = velIzq / 255.0 * 5.0; // m/s arbitrario
  float vR = velDer / 255.0 * 5.0;

  float v = R * (vR + vL) / 2.0;
  float w = R * (vR - vL) / L;

  theta += w * dt;
  x += v * cos(theta) * dt;
  y += v * sin(theta) * dt;

  Serial.print("Posición -> X: "); Serial.print(x);
  Serial.print(" m | Y: "); Serial.print(y);
  Serial.print(" m | θ: "); Serial.println(theta);
}

// Detener motores
void detenerse() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void loop() {
  avanzarCorrigiendo();      // Mover y corregir orientación
  estimarPosicion();         // Estimar posición usando cinemática
  delay(100);                // Ciclo cada 100 ms
}
