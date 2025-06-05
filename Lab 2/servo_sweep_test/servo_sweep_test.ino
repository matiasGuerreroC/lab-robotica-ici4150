#include <Servo.h>

Servo servoMotor;

void setup() {
  servoMotor.attach(8); // Conectar al pin 8 
}

void loop() {
  servoMotor.write(0);   // Ir a 0 grados
  delay(1000);
  servoMotor.write(90);  // Ir a 90 grados
  delay(1000);
  servoMotor.write(180); // Ir a 180 grados
  delay(1000);
}