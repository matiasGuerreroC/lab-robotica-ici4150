#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu;

// Sesgo del giroscopio
float gyroBiasZ = 0.0;
const int N = 500; // Muestras para calibración

// Pines motores
const int IN1 = 3, IN2 = 4; // Izquierdo
const int IN3 = 5, IN4 = 6; // Derecho
const int ENA = 9, ENB = 10;

unsigned long lastTime = 0;
float x = 0.0, y = 0.0, theta = 0.0;
const float velocity = 0.2; // m/s aprox.

void setup() {
  Serial.begin(9600);
  Wire.begin();

  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();
  delay(1000);

  // Pines de motor
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  calibrarGiroscopio();
  lastTime = millis();
}

void calibrarGiroscopio() {
  Serial.println("Calibrando giroscopio...");
  float sumZ = 0;

  for (int i = 0; i < N; i++) {
    mpu.gyroUpdate();
    sumZ += mpu.gyroZ();
    delay(5);
  }

  gyroBiasZ = sumZ / N;
  Serial.print("Sesgo Z: ");
  Serial.println(gyroBiasZ, 6);
}

void loop() {
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  mpu.gyroUpdate();
  mpu.accelUpdate();

  // Corregir giro
  float gyroZ_corr = mpu.gyroZ() - gyroBiasZ;
  theta += gyroZ_corr * dt;

  // Estimar posición
  x += velocity * cos(theta) * dt;
  y += velocity * sin(theta) * dt;

  // Calcular inclinación (pitch)
  float accX = mpu.accelX();
  float accY = mpu.accelY();
  float accZ = mpu.accelZ();
  float pitch = atan2(accY, sqrt(accX * accX + accZ * accZ)) * 180.0 / PI;

  // Mostrar info
  Serial.print("X: "); Serial.print(x, 2);
  Serial.print(" m | Y: "); Serial.print(y, 2);
  Serial.print(" m | θ: "); Serial.print(theta * 180 / PI, 1);
  Serial.print("° | Pitch: "); Serial.println(pitch, 1);

  // Umbral de inclinación
  float umbral = 10;

  if (abs(pitch) < umbral) {
    avanzar(0, 100); // Sigue avanzando
  } else {
    Serial.println("⚠️ Inclinación detectada, retrocediendo...");
    detenerse(500);
    retroceder(1000, 100);
    detenerse(500);
  }

  delay(50);
}

// FUNCIONES DE MOVIMIENTO

void avanzar(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void retroceder(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void detenerse(int tiempo) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(tiempo);
}
