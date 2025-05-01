#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu;

unsigned long lastTime = 0;
float angleGyroZ = 0; // Acumulador del ángulo con giroscopio

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();
  delay(1000);

  if (!mpu.accelUpdate() || !mpu.gyroUpdate()) {
    Serial.println("No se detecta el MPU-9250/6500");
  } else {
    Serial.println("Sensor detectado correctamente");
  }

  lastTime = millis();
}

void loop() {
  mpu.accelUpdate();
  mpu.gyroUpdate();

  // ---- Calcular pitch y roll desde el acelerómetro ----
  float accX = mpu.accelX();
  float accY = mpu.accelY();
  float accZ = mpu.accelZ();

  float pitch = atan2(accY, sqrt(accX * accX + accZ * accZ)) * 180 / PI;
  float roll  = atan2(-accX, accZ) * 180 / PI;

  // ---- Calcular giro acumulado con el giroscopio ----
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0; // Delta time en segundos
  lastTime = currentTime;

  float gyroZ = mpu.gyroZ(); // °/s
  angleGyroZ += gyroZ * dt;  // Integración simple

  // ---- Mostrar datos ----
  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("° | Roll: ");
  Serial.print(roll, 2);
  Serial.print("° | Giro acumulado Z: ");
  Serial.print(angleGyroZ, 2);
  Serial.println("°");

  delay(100); // Ajusta para mayor precisión si es necesario
}
