# Laboratorios Robótica y Sistemas Autónomos - ICI4150

Repositorio para el desarrollo y documentación de los laboratorios del curso **Robótica y Sistemas Autónomos (ICI4150)** de la **PUCV**, semestre 2025-01.

## Integrantes del grupo

- Cesar Anabalón  
- Ulysses Barreto  
- Felipe Bravo  
- Matias Guerrero  
- Fabiana Piña  

## Contenidos

Este repositorio contendrá el desarrollo y entregas de los siguientes laboratorios:

- **Laboratorio 1**: Ensamblar y programar un robot básico  
- **Laboratorio 2**: Sensores, percepción y planificación básica  

## Tecnologías y herramientas

- Arduino UNO  
- Sensores: ultrasónico (HC-SR04), infrarrojo, RGB, IMU (MPU6050)  
- Driver de motores L298N  
- Chasis impreso en 3D con motores DC  
- Protoboard y cables de conexión

---

## Laboratorio 1

### Parte 1: Identificación de Componentes y Configuración
- Conectar Arduino UNO con el driver de motores y programar el movimiento básico de los motores (adelante, atrás, giro) sin controlar la velocidad.
- Verificar el funcionamiento del sensor ultrasónico HC-SR04 midiendo distancias.
- Analizar los datos del IMU MPUC6050 para medir inclinación o giros
del robot.

Video: 
[Movimientos básicos de los motores](https://www.youtube.com/shorts/A4MSk1yM4Hs)



#### Preguntas
**1. ¿Qué función cumplen los sensores, actuadores y controladores en el robot?**
   
   Los sensores tienen la función de recoger información del entorno o del propio robot. Por ejemplo, el sensor ultrasónico HC-SR04 mide la distancia a los obstáculos. Los actuadores, por su parte, se encargan de ejecutar acciones físicas, un ejemplo de ello son los motores, los que permiten el movimiento del robot. Finalmente, los controladores procesan los datos recibidos por los sensores y toman decisiones. Un ejemplo de controlador es el Arduino UNO, que interpreta las lecturas de los sensores y envía señales a los actuadores para ejecutar las acciones correspondientes
   
**2. ¿Cómo se puede estimar la velocidad sin encoders?**

   Existen tres métodos para estimar la velocidad sin utilizar encoders:
   
  **a. Tiempo y distancia:** Consiste en medir cuánto se mueve el robot en un cierto tiempo. Estos datos se pueden obtener utilizando un sensor ultrasónico y un cronómetro. Luego, se aplica la fórmula de la velocidad: velocidad = ditancia / tiempo
  
  **b. Datos de la IMU (MPU6050):** Se puede estimar la velocidad integrando la aceleración medida por la IMU. Sin embargo, este método es poco preciso a largo plazo debido a la acumulación de errores (deriva).

  **c. Calibración previa:** Se realizan pruebas experimentales para correlacionar el valor del PWM aplicado con la velocidad real del robot en diferentes condiciones. A partir de estas pruebas, se generan tablas de referencia que permiten estimar la velocidad según el PWM aplicado.

   
**3. ¿Cómo afecta la falta de encoders a la precisión del movimiento?** 
    Sin el uso de encoders, el robot no puede saber con exactitud cuánto ha girado una rueda ni cuánta distancia ha recorrido. Lo cual genera errores que se acumulan durante el movimiento, dificultando mantener una trayectoria recta y limitando la capacidad de realizar movimientos precisos o repetibles, como avanzar exactamente un metro o girar 90°.

**4. ¿Qué es PWM y cómo ayuda a controlar la velocidad de los motores?**
    El Pulse Width Modulation (PWM) o Modulación por Ancho de Pulso es una técnica que consiste en enviar pulsos digitales a un motor con una frecuencia fija pero con un ciclo de trabajo variable (duty cycle). Al variar el duty cycle, se modifica el tiempo durante el cual el motor recibe corriente en cada ciclo. Esto simula una tensión promedio menor, lo que permite controlar la velocidad del motor sin necesidad de variar el voltaje de alimentación.

**5. ¿Cómo afecta el control de velocidad a la precisión de la navegación sin encoders?**
    Si no se controla la velocidad de los motores, estos pueden girar a diferentes velocidades debido a variaciones mecánicas o de fricción. Esto provoca desviaciones en la trayectoria, especialmente al intentar avanzar en línea recta, lo que reduce la precisión de la navegación.


---

> Este archivo será actualizado a medida que avancemos con las entregas.
