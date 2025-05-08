# Laboratorios Robótica y Sistemas Autónomos - ICI4150

Repositorio para el desarrollo y documentación de los laboratorios del curso **Robótica y Sistemas Autónomos (ICI4150)** de la **PUCV**, semestre 2025-01.

## Integrantes del grupo

- Cesár Cristobal Anabalón Navarrete
- Ulysses Edward Barreto  Horn
- Felipe Jesus Andres Bravo Romo
- Matias Ignacio Guerrero  Castillo
- Fabiana Andrea Piña Vera

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

#### Código utilizado

El código utilizado para implementar los movimientos básicos del robot y realizar pruebas de sensores se encuentra en los siguientes archivos:

- [Lab 1/basic_move/basic_move.ino](Lab%201/basic_move/basic_move.ino)  
  Este archivo contiene las funciones para avanzar, retroceder, girar y detenerse utilizando control PWM sobre ambos motores. El robot fue probado en distintas direcciones a una velocidad configurable.

- [Lab 1/imu_basic_test/imu_basic_test.ino](Lab%201/imu_basic_test/imu_basic_test.ino)  
  Este archivo realiza pruebas básicas del sensor IMU MPU9250 para leer los valores de acelerómetro y giroscopio, mostrando los datos en el monitor serial para la validación del sensor.

- [Lab 1/imu_read_angles/imu_read_angles.ino](Lab%201/imu_read_angles/imu_read_angles.ino)  
  Este script mide y muestra los ángulos de inclinación del robot (pitch y roll) utilizando el acelerómetro del sensor IMU, permitiendo analizar la inclinación del robot en tiempo real.

- [Lab 1/imu_gyro_calibration/imu_gyro_calibration.ino](Lab%201/imu_gyro_calibration/imu_gyro_calibration.ino)  
  Este archivo calibra el giroscopio del sensor IMU, calculando el sesgo (bias) de cada eje y corrigiendo las lecturas de los giroscopios para mejorar la precisión en las mediciones de movimiento.

- [Lab 1/ultrasonic_distance_test/ultrasonic_distance_test.ino](Lab%201/ultrasonic_distance_test/ultrasonic_distance_test.ino)  
  Este script prueba el sensor ultrasónico HC-SR04, midiendo distancias y mostrando los resultados en el monitor serial, permitiendo verificar el funcionamiento del sensor.

Cada uno de estos archivos ha sido probado individualmente para validar el funcionamiento de los sensores y los movimientos del robot.
### Parte 1: Identificación de Componentes y Configuración
- Conectar Arduino UNO con el driver de motores y programar el movimiento básico de los motores (adelante, atrás, giro) sin controlar la velocidad.
- Verificar el funcionamiento del sensor ultrasónico HC-SR04 midiendo distancias.
- Analizar los datos del IMU MPUC6050 para medir inclinación o giros
del robot.

### Videos de demostración

- Movimientos básicos de los motores,
demostración de avance, retroceso y giros controlados con PWM.
Ver video: https://youtube.com/shorts/A4MSk1yM4Hs

- Control y Estimación de Movimiento en Robot Móvil con Cinemática Diferencial y Sensor IMU,
aplicación de la ecuación de cinemática diferencial, corrección con IMU y control de velocidad por PWM.
Ver video: https://youtu.be/SARl8lrz6Mw

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



### Parte 2: Cinemática y Dinámica de Robots Móviles Usando un IMU

- Aplicar la ecuación de cinemática diferencial para estimar la posición del robot usando tiempo y velocidad de motores
- Hacer que el robot se mueva en línea recta y registrar desviaciones usando el sensor IMU para detectar la inclinación y giro del robot.
- ﻿﻿Usar el sensor IMU MPU6050 para medir la inclinación del robot y ajustar su dirección en tiempo real, realizando correcciones en el movimiento de acuerdo a su orientación.
- Programar el PWM para controlar la velocidad de los motores y hacer que el robot se mueva a diferentes velocidades sin IMU, variando el tiempo de activación de los motores.


#### Preguntas

**1. ¿Cómo se calcula la velocidad del robot sin encoders usando PWM?**

   Dado que el PWM no permite medir directamente la velocidad del robot, esta se puede estimar de forma indirecta estableciendo una relación empírica entre los valores de PWM aplicados a los motores y la velocidad resultante. Para ello, se debe realizar una calibración previa, en la cual el robot avanza con distintos valores de PWM mientras se mide el tiempo que tarda en recorrer una distancia conocida. Con estos datos, se calcula la velocidad utilizando la fórmula:
velocidad = distancia / tiempo.

Una vez obtenidas múltiples mediciones, es posible construir una tabla o función que relacione cada nivel de PWM con una velocidad aproximada. Aunque esta estimación no es tan precisa como la que se obtendría con encoders, permite lograr un control básico de la velocidad del robot durante su operación.

**2. ¿Cómo factores afectan la trayectoria y velocidad del robot al cambiar los intervalos de tiempo?**

   Al modificar los intervalos de tiempo durante los cuales se activa el movimiento del robot, se afecta directamente la distancia recorrida, y por ende, su trayectoria y velocidad. Además del tiempo de activación, influyen otros factores como la duración total del movimiento, las diferencias en el rendimiento de los motores, el tipo de superficie, el peso del robot y el estado de la batería, los cuales pueden alterar el resultado final.
   
Por ejemplo, si un motor permanece activo más tiempo que el otro, o si existe una ligera diferencia en las velocidades de las ruedas, el robot puede desviarse de su trayectoria prevista. Asimismo, en superficies con fricción variable o con desniveles, un mismo intervalo de tiempo no garantiza que se recorra siempre la misma distancia.

**3. ¿Cuáles son las ventajas y desventajas de usar un IMU para ajustar la dirección en lugar de encoders?**

   Las ventajas de utilizar una IMU para ajustar la dirección, en lugar de encoders, incluyen su capacidad para detectar cambios de orientación, como giros e inclinaciones, incluso cuando las ruedas no giran correctamente. Esto resulta útil en situaciones donde hay derrapes o pérdida de tracción. Además, la IMU no requiere contacto mecánico directo con las ruedas, lo que reduce el desgaste físico del sistema.

Por otro lado, entre las desventajas se encuentra que los datos del giroscopio suelen acumular errores con el tiempo (deriva), lo que disminuye la precisión en trayectorias largas. Además, una IMU no proporciona información sobre la distancia recorrida, algo que sí pueden ofrecer los encoders.

**4. ¿Qué efecto tiene la inclinación o el giro en el movimiento del robot, y cómo se corrige con el IMU?**

   La inclinación o el giro del robot puede alterar significativamente su movimiento, ya que modifica la distribución del peso y afecta la trayectoria sobre las ruedas. Esto puede provocar desvíos no deseados, inestabilidad o movimientos erráticos. Por ejemplo, si el robot se inclina hacia un lado, podría perder tracción en una rueda o desviarse de su trayectoria prevista.

Una IMU permite detectar estos cambios mediante la medición de los ángulos de inclinación (pitch y roll) y la rotación (yaw). Con esta información, el controlador del robot puede ajustar el comportamiento de los motores, corrigiendo la trayectoria mediante un sistema de control activo; por ejemplo, reduciendo la velocidad de uno de los motores para compensar un giro.


---

> Este archivo será actualizado a medida que avancemos con las entregas.
