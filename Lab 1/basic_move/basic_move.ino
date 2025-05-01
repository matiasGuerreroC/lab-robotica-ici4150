// Pines de dirección
const int IN1 = 3;  // Motor izquierdo
const int IN2 = 4;
const int IN3 = 5;  // Motor derecho
const int IN4 = 6;

// Pines de velocidad PWM
const int ENA = 9;  // PWM motor izquierdo
const int ENB = 10; // PWM motor derecho

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
}

// Función para avanzar
void avanzar(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Función para retroceder
void retroceder(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Función para detenerse
void detenerse(int tiempo) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(tiempo);
}

// Función para girar a la derecha
void girarDerecha(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

// Función para girar a la izquierda
void girarIzquierda(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void loop() {
  avanzar(500, 200);
  detenerse(1000);
  retroceder(500, 200);
  detenerse(1000);
  girarDerecha(500, 200);
  detenerse(1000);
  girarIzquierda(500, 200);
  detenerse(1000);
}