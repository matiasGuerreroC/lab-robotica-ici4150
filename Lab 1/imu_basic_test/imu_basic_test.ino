#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 

  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();
  delay(1000);

  if (!mpu.accelUpdate() || !mpu.gyroUpdate()) {
    Serial.println("No se detecta el MPU");
  } else {
    Serial.println("MPU detectado correctamente");
  }
}

void loop() {
  mpu.accelUpdate();
  mpu.gyroUpdate();

  Serial.print("Accel X: ");
  Serial.print(mpu.accelX());
  Serial.print(" | Gyro Z: ");
  Serial.println(mpu.gyroZ());

  delay(500);
}
