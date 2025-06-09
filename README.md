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
## Laboratorio 2

#### Código utilizado
El código utilizado para la configuración de sensores, lectura de datos y la implementación del algoritmo de navegación autónoma se encuentra en los siguientes archivos:

- [Lab 2/ultrasonic_read_distance/ultrasonic_read_distance.ino](Lab%202/ultrasonic_read_distance/ultrasonic_read_distance.ino)
  Este archivo contiene el código para realizar la lectura de distancias utilizando el sensor ultrasónico HC-SR04. Las mediciones se muestran en el monitor serial, permitiendo validar el funcionamiento básico del sensor en condiciones controladas. Fue utilizado en la etapa de pruebas iniciales para verificar la precisión a diferentes distancias y con distintas superficies.
- [Lab 2/ultrasonic_threshold_detect/ultrasonic_threshold_detect.ino](Lab%202/ultrasonic_threshold_detect/ultrasonic_threshold_detect.ino)
  Este script aplica umbralización al sensor ultrasónico, generando una respuesta lógica si se detecta un obstáculo a menos de 10 cm. Es una base fundamental para la navegación autónoma del robot, ya que permite detener el movimiento o modificar la dirección al identificar objetos cercanos. La detección se prueba en tiempo real y se muestra en el monitor serial.
- [Lab 2/servo_sweep_test/servo_sweep_test.ino](Lab%202/servo_sweep_test/servo_sweep_test.ino)
  Este archivo permite probar el movimiento de un servo motor mediante un barrido angular (sweep). Se utiliza para validar la conexión, el control y el rango de giro del servo, el cual puede ser parte de un sistema de exploración activa o direccionamiento de sensores. El ángulo del servo es mostrado en el monitor serial durante el barrido.
- [Lab 2/color_sensor_detect/color_sensor_detect.ino](Lab%202/color_sensor_detect/color_sensor_detect.ino)
  Este script implementa la lectura de valores RGB a partir de un sensor de color y clasifica los colores detectados según umbrales definidos para rojo, verde y azul. El color identificado se muestra en el monitor serial, y el sistema fue probado bajo diferentes condiciones de iluminación y tipos de superficie para ajustar la precisión del reconocimiento.

### Parte 1: Configuración del Hardware y pruebas iniciales

- Conectar los sensores ultrasónicos HC-SR04 y RGB en Arduino.
- Programar Arduino para leer la distancia con HC-SR04 y mostrarla en el monitor serie.(Video listo)
- Programar Arduino para leer los valores RGB y mostrar el color detectado.
- Analizar la precisión de los sensores en diferentes condiciones (luz, superficie, distancia).

### Videos de demostración
- Lectura de distancia con sensor ultrasónico, medición de distancia utilizando el sensor HC-SR04, mostrando los valores en el monitor serial para validar su funcionamiento.
Ver video: https://youtube.com/shorts/zzdRjlIhOuk?feature=share

- Detección de obstáculos mediante umbralización, aplicación de un umbral de 10 cm para identificar la presencia de obstáculos y generar una respuesta lógica en tiempo real.
Ver video: https://youtube.com/shorts/xhiVeXC0McM?feature=share

- Detección de color con sensor RGB, clasificación de colores rojo, verde y azul mediante el uso de umbrales en los valores RGB capturados por el sensor.
Ver video: https://youtu.be/XJEscTwzXKM

#### Preguntas
**1. ¿Qué es la percepción en robótica y por qué es fundamental en los sistemas autónomos?**
    
  Es la capacidad que tiene un robot de adquirir, interpretar y procesar la información del entorno mediante el uso de los sensores. Al obtener esta información, le permite al sistema tener una visión del mundo que lo rodea, lo cual facilita la toma de decisiones y la interacción autónoma con su ambiente.
  
  Esto es fundamental para los sistemas autónomos porque si no se tiene percepción, el robot no puede adaptarse a los cambios que se producen en el entorno, por ejemplo detectar obstáculos, seguir rutas o interactuar con objetos. Por lo que, la percepción es el intermediario entre el ambiente y el sistema de control del robot, lo cual permite una navegación segura y eficiente.
  
﻿﻿**2. En el sensor ultrasónico HC-SR04 ¿ Qué parámetro se mide para calcular la distancia?**
  
  Lo que mide el sensor ultrasónico HC-SR04 es el tiempo que tarda una onda sonora en ir desde el emisor hasta el objeto y regresar al receptor, para lo cual se utiliza la siguiente fórmula:
  
  Distancia = (Tiempo x VelocidadDeSonido)/2
  
  Como la onda sonora realiza un viaje de ida y vuelta, se divide por 2 para así obtener el tiempo medio. Hay que considerar que la velocidad del sonido se aproxime a 343 m/s a temperatura ambiente, la cual es 20°C

**3. ¿Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo podría reducirse?**

  El ruido en las mediciones del sensor ultrasónico se debe a múltiples factores como lo son las interferencias acústicas, superficies irregulares, materiales que absorben el sonido o ecos múltiples. Lo cual puede generar valores poco precisos, en especial en ambientes no controlados.
  
  Para reducir el ruido en las mediciones se puede aplicar un filtro de medida móvil o mediana para suavizar los datos, también se puede realizar varias mediciones consecutivas y tomar un promedio, otra opción es filtrar valores fuera de un rango esperado o totalmente diferentes a la lectura anterior, otra alternativa es usar materiales reflectantes frente al sensor para obtener mejores ecos, y la última posibilidad es evitar superficies con ángulos que desvíen el sonido 


### Parte 2: Procesamiento de datos y Algoritmo de Navegación

- Aplicar umbralización al sensor ultrasónico para detectar si hay un obstáculo a menos de 10cm.
- ﻿﻿Definir umbrales para detectar colores, rojo, verde y azul usando el sensor RGB.
﻿﻿- Implementar un algoritmo en Arduino que detenga el robot ante obstáculos y cambie de dirección según el color detectado.
- ﻿﻿Probar navegación en un circuito con obstáculos y superficies de diferentes colores.
- ﻿﻿Ajustar parámetros para mejorar la detección y estabilidad del sistema.
- ﻿﻿Implementación de estrategias de navegación basadas en reglas.



### Videos de demostración


#### Preguntas

**1. Si el robot detecta el color rojo en el suelo ¿ Qué acción debería tomar?¿ Por qué?**

  Al momento que el robot detecta el color rojo, se puede detener inmediatamente o realizar una acción específica que ya esté programada, como lo es cambiar de dirección o retroceder. También el color rojo, puede usarse como una señal de advertencia o peligro, lo que indica al robot que no debe continuar por esa zona, por ejemplo, una zona de fin de recorrido o una zona prohibida o restringida.
  
  Ya que esta respuesta se basa en un acuerdo de señales visuales que ayuda a integrar reglas reactivas simples para la toma de decisiones basadas en la percepción del entorno.
  
**2. ﻿﻿Si el sensor ultrasónico detecta valores erráticos ¿ Qué estrategias podrías aplicar para mejorar la precisión?**

  Al momento de detectar valores erráticos, se pueden utilizar las siguientes estrategias:
  1. Filtrado de señales: donde se puede usar un filtro de media móvil para suavizar las fluctuaciones rápidas, o aplicar los filtros de Kalman si se requiere un mayor nivel de precisión y predicción.
  2. Umbralización: Se establece un rango válido de mediciones y descartar aquellas que estén fuera de este rango.
  3. Mediciones múltiples: Realizar de 3 a 5 mediciones y tomar la mediana o promedio para mayor confiabilidad.
  4. Rediseñar el montaje del sensor: Donde hay que asegurar que esté bien alineado y que no tenga interferencias físicas.
  5. Ajustar el entorno: Donde se evitan los obstáculos móviles o superficies irregulares que interfieran con el eco.


﻿﻿**3. Si tuvieras que integrar un nuevo sensor para mejorar la navegación del robot ¿Cuál eligirías y por qué?**
  
  Si hay que integrar un nuevo sensor, sería el sensor LIDAR (Light Detection and Ranging), dado que este permite obtener mapas más precisos del entorno mediante el uso de láseres. A diferencia del sensor ultrasónico, el LIDAR tiene mayor resolución y rango de detección, también tiene menor susceptibilidad al ruido ambiental y por último su capacidad de generar mapas en 2D o 3D del entorno en tiempo real. Lo cual permitiría una navegación más precisa y robusta, sobre todo en entornos complejos o donde hay múltiples obstáculos.  

﻿﻿**4. ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?**
  
  El tiempo de respuesta que tiene el robot al detectar un cambio de color depende de varios factores como lo son la frecuencia de lectura del sensor RGB, la velocidad de procesamiento del Arduino y la ejecución del algoritmo de control. En condiciones ideales, el tiempo de respuesta del robot al detectar un cambio de color suele estar en un rango de decenas a cientos de milisegundos, por ejemplo entre 100 y 300 ms. Por lo que el tiempo depende del rendimiento del código, la eficiencia  en la lectura de sensores y la carga de procesamiento.


### Posibles mejoras

En la siguiente sección se plantea un análisis de posibles mejoras contemplando ambas partes del laboratorio 2.

**1. Promediado inteligente de lecturas del sensor ultrasónico**
Actualmente, el sensor HC-SR04 puede entregar valores erráticos debido a ruido ambiental, superficies irregulares o interferencias. Una mejora práctica sería implementar una técnica de medición múltiple seguida de un filtrado por mediana o promedio desechando valores extremos. Esto implicaría una mejora de la estabilidad y confiabilidad de los datos entregados. Por otro lado, fortalece el control reactivo del robot al detectar obstáculos de forma más precisa.

```cpp
// Sugerencia de implementación
int readFilteredDistance() {
  long readings[5];
  for (int i = 0; i < 5; i++) {
    readings[i] = readUltrasonic(); // función que entrega una medición puntual
    delay(20); // pequeño retardo entre lecturas
  }
  // Ordenar y devolver la mediana
  sort(readings, 5); 
  return readings[2]; // mediana
}
```

**2. Calibración dinámica del sensor de color según la luz ambiente**
El sensor RGB puede verse afectado por la intensidad de luz ambiental o el tipo de superficie. Implementar una fase de calibración automática al iniciar el sistema permitiría ajustar los umbrales de color a las condiciones reales del entorno. Para poder mejorarlo, se sugiere leer valores RGB de una superficia conocida al inicio, y calcular un factor de corrección multiplicativo sobre los umbrales definidos.

Realizar lo anterior, aplicaría los conceptos de percepción adaptativa mencionados en la Parte 1. Aumentaría la confiabilidad en la decisión basada en colores, clave para que el robot actúe correctamente ante rojo, azul o negro. Y por último, mejoraría el tiempo de respuesta descrito en la pregunta 4 (Parte 2) al reducir errores de lectura por condiciones externas.

**3. Integración de sensores infrarrojos para lectura de superficie (complemento del RGB)**
Los sensores RGB pueden tener limitaciones al distinguir colores oscuros (como el negro) sobre superficies con brillo o textura. Integrar sensores infrarrojos (IR) de reflexión ayudaría a reforzar la detección de cambios bruscos en la reflectancia (como líneas negras). Para incorporar esta mejora, se sugiere añadir un sensor IR adicional bajo el robot, combinando la lógica RGB + IR, de forma que, si el RGB no puede distinguir el color pero el IR detecta baja reflexión, se asuma color negro. Aplicar lo anterior, respalda la lógica del algoritmo de navegación con una redundancia que reduce falsos positivos/negativos, complementa la detección en circuitos con colores mal iluiminados o superficies no mates. y por útlimo, mejora la robustez general del sistema perceptivo, lo cual es una recomendación alineada con la pregunta 1 de percepción.


---

> Este archivo será actualizado a medida que avancemos con las entregas.
