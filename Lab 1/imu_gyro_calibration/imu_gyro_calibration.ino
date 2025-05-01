#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu;

// Variables para almacenar el sesgo (bias) de los giroscopios
float gyroBiasX = 0.0, gyroBiasY = 0.0, gyroBiasZ = 0.0;
const int N = 500;  // Número de muestras para obtener un promedio

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();
  delay(1000);
  
  // Inicia el proceso de calibración del giroscopio
  calibrarGiroscopio();
}

void calibrarGiroscopio() {
  Serial.println("Calibrando giroscopio...");

  // Variables para acumular las lecturas
  float sumGyroX = 0, sumGyroY = 0, sumGyroZ = 0;

  // Tomamos N lecturas del giroscopio y sumamos los valores
  for (int i = 0; i < N; i++) {
    mpu.gyroUpdate();
    
    sumGyroX += mpu.gyroX();
    sumGyroY += mpu.gyroY();
    sumGyroZ += mpu.gyroZ();
    
    delay(5);  // Pequeño delay entre lecturas
  }

  // Calculamos el promedio para obtener el sesgo
  gyroBiasX = sumGyroX / N;
  gyroBiasY = sumGyroY / N;
  gyroBiasZ = sumGyroZ / N;

  Serial.print("Sesgo del giroscopio X: ");
  Serial.println(gyroBiasX);
  Serial.print("Sesgo del giroscopio Y: ");
  Serial.println(gyroBiasY);
  Serial.print("Sesgo del giroscopio Z: ");
  Serial.println(gyroBiasZ);
}

void loop() {
  // Actualizamos los valores de acelerómetro y giroscopio
  mpu.accelUpdate();
  mpu.gyroUpdate();

  // Aplicamos el sesgo para corregir las lecturas del giroscopio
  float gyroX_corr = mpu.gyroX() - gyroBiasX;
  float gyroY_corr = mpu.gyroY() - gyroBiasY;
  float gyroZ_corr = mpu.gyroZ() - gyroBiasZ;

  // Mostrar valores corregidos
  Serial.print("Giroscopio X corregido: ");
  Serial.print(gyroX_corr);
  Serial.print(" | Giroscopio Y corregido: ");
  Serial.print(gyroY_corr);
  Serial.print(" | Giroscopio Z corregido: ");
  Serial.println(gyroZ_corr);

  delay(100);  // Delay para no saturar la salida serial
}
