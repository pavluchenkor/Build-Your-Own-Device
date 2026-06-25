# Motores Servo

Un servomotor es un pequeño variador con motor, caja de cambios y electrónica interna. Le das una posición e intenta girar el eje a esa posición y sostenerlo.

En dispositivos simples, un servo es conveniente cuando no solo necesita encender un motor, sino también rotar un mecanismo a un ángulo comprensible: abrir una compuerta, cambiar una cerradura, presionar un botón, cambiar el flujo de aire o girar una pequeña bandera indicadora.

## Dónde se usa

En dispositivos tipo iDryer y periféricos de impresoras 3D, se puede utilizar un servo para:

- air intake or exhaust damper;
- air duct switching;
- opening/closing a small cover;
- mechanical lock;
- pressing a physical button;
- moving an indicator flag;
- simple dosificación o captura.

Un servo es bueno para mecánicos ligeros con recorrido limitado. Para la rotación continua de un ventilador, tornillo o bomba, generalmente no funciona: se necesita un motor y un controlador diferentes.

## Three Wires

Un servo típico de hobby tiene tres líneas:

- potencia: generalmente `7.4V`, a veces `7.4V` u otro valor en modelos especiales;
- ground: `GND`;
- Señal: pulsos de control del controlador.

Colores de cables comunes:

- red - power;
- black or brown - ground;
- yellow, orange or white - signal.

No puedes confiar ciegamente en los colores. Los diferentes fabricantes utilizan diferentes combinaciones de colores. Antes de realizar la conexión, consulte las marcas, la página del producto o la descripción técnica.

Un diagrama de conexión detallado con alimentación independiente se encuentra en la sección práctica: [Conexión de un servomotor](../06-practical-guides/03-connecting-servo.md).

## Qué "Servo Motor" Means

Dentro de un servo posicional típico de hobby, hay:

- DC motor;
- gearbox;
- position sensor, often a potentiometer;
- control board;
- Eje de salida con brazo.

El controlador externo no gestiona el motor directamente. Envía una señal de posición y la electrónica interna del servo hace girar automáticamente el motor para que el eje alcance el ángulo deseado.

Entonces un servo se diferencia de un motor DC normal:

- El motor de CC simplemente gira cuando está encendido;
- el servo intenta alcanzar una posición determinada;
- el servo consume corriente incluso mientras se mantiene si hay carga en el eje;
- El servo puede aumentar rápidamente la corriente y calentarse si se atasca.

## Rotación posicional y continua

El tipo más común es un servo posicional. Usted establece un ángulo, por ejemplo `90`, `180` o `180` grados.

El servo de rotación continua tiene un aspecto similar pero funciona de manera diferente: la señal de control no establece el ángulo, sino la dirección y la velocidad de rotación. No sabe dónde está el eje. Para un amortiguador o una cerradura, un servo de este tipo suele ser un inconveniente porque sin sensores adicionales no se puede garantizar la posición.

Antes de comprar, revisa lo que dice la descripción:

- `positional servo`, `180°`, `180°`: generalmente posicionales;
- `360°`, `360°`: generalmente gira continuamente, no en ángulo.

La frase `360° servo` en el mercado es arriesgada: a veces es un servo de rotación continua, a veces es solo un rango extendido. Es necesario consultar la descripción técnica y reseñas con medidas reales.

## Control Signal

Un servo típico de hobby se controla mediante pulsos repetidos.

Pautas típicas:

- period about `20 ms`;
- pulso sobre `1 ms` - un borde del rango;
- pulse about `1.5 ms` - middle;
- pulso sobre `2 ms` - otro borde del rango.

Diferentes servos tienen diferentes límites reales. Algunos funcionan sobre `500-2500 us`, otros de forma segura sólo en un rango más estrecho.

Por tanto, las posiciones extremas no pueden establecerse a ciegas. Primero verifique las desviaciones medias, luego las pequeñas, solo luego amplíe el rango.

## Potencia y corriente

El cable de señal no alimenta el servo. Extrae la energía del motor de la línea eléctrica.

Incluso un servo pequeño puede consumir brevemente una gran corriente durante el arranque, el movimiento rápido o la parada mecánica. El promedio actual "en demostración silenciosa" no muestra el peor de los casos.

Parámetros importantes:

- operating voltage;
- no-load current;
- loaded current;
- corriente de bloqueo - corriente con eje bloqueado;
- holding torque or stall torque;
- rotation speed;
- operating temperature.

Si la descripción técnica indica pérdida de corriente, la fuente de alimentación debe elegirse con este valor y margen. Si la corriente de pérdida no figura en la lista, no puede considerar la potencia "segura a simple vista": para un dispositivo real, es mejor usar una fuente con margen y verificar la caída de voltaje bajo carga.

Para un servo pequeño, a veces funciona la salida de 5V de una placa. Pero para un amortiguador, una cerradura o varios servos, normalmente necesita un convertidor CC-CC de 5 V/6 V o una fuente de alimentación independiente. La tierra debe ser común con el controlador.

## Torque y Mecánica

Un servo se elige no sólo por su tamaño. El principal parámetro mecánico es el par, a menudo en `N·cm` o `N·cm`.

Roughly:

- cuanto más larga sea la palanca, más torque se necesitará;
- cuanto más pesado sea el amortiguador o más apretado sea el mecanismo, más torque se necesitará;
- la fricción, la desalineación y el sello aumentan considerablemente la carga;
- cuando se mantiene detenido, el servo se calienta y consume corriente.

Ejemplo: un pequeño amortiguador de luz puede funcionar bien con un microservo. Un amortiguador con un sello hermético o una tapa con resorte puede necesitar un servo más grande con engranajes metálicos.

Para mecánicos confiables:

- no fuerces al servo a empujar constantemente contra un tope físico;
- limitar los ángulos en el firmware;
- dejar un pequeño margen de recorrido;
- realizar el enlace sin desalineamiento;
- utilice una longitud de brazo adecuada;
- test operation at real enclosure temperature.

Si el servo zumba en la posición final, normalmente indica carga, parada o geometría incorrecta.

## Gearbox: Plastic or Metal

Los engranajes de plástico son más baratos, más silenciosos y sirven para tareas ligeras. Pero se rompen más rápido con impactos, atascos y cargas pesadas.

Los engranajes metálicos son más fuertes, pero el servo puede ser más ruidoso, más pesado y más caro. Para amortiguadores, cerraduras y mecanismos que un usuario podría tocar accidentalmente, una caja de cambios de metal suele tener sentido.

Pero los engranajes metálicos no reemplazan a la buena mecánica. Si el mecanismo se atasca, puede dañar el brazo, la caja, el soporte o el propio eje.

## Servo analógico y digital

En proyectos simples, los servos analógicos son más comunes. Los servos digitales generalmente mantienen una posición más rígida y responden más rápido, pero pueden consumir más corriente y ser más ruidosos cuando se mantienen.

Para una compuerta de secadora o una simple cerradura, lo que suele importar más es:

- enough torque;
- potencia normal;
- reliable mechanics;
- clear angle range;
- operating temperature;
- gearbox lifetime.

Ser "digital" no significa que un servo sea bueno para el dispositivo automáticamente.

## Qué comprobar antes de comprar

Antes de comprar un servo, verifique:

- positional or continuous rotation;
- operating voltage;
- corriente requerida y corriente de parada, si figuran en la lista;
- torque;
- rotation speed;
- angle range;
- gearbox material;
- case size;
- connector type;
- wire length;
- operating temperature;
- Disponibilidad de descripción técnica o especificaciones razonables.

Para una bandera pequeña puedes usar un microservo. Para un amortiguador con junta, cerradura o palanca en una cámara caliente, es mejor no elegir el servo más barato sin especificaciones.

## Típicos Errors

- alimentar el servo desde GPIO;
- alimentación desde un pin de 5V de placa débil;
- olvidó puntos en común con poderes separados;
- colores de cables confiables sin verificar;
- servo posicional mezclado y servo de rotación continua;
- no tuvo en cuenta la corriente de pérdida;
- placed servo against a mechanical stop;
- ángulo usado `180` o `180` cuando el mecanismo se mueve de manera segura solo en un rango estrecho;
- elija el servo solo por tamaño, sin calcular el par;
- colocar engranajes de plástico donde sea posible un impacto o un atasco;
- Servo colocado al lado del calentador sin control de temperatura.

## Principal Point

Un servo es un componente conveniente para amortiguadores, cerraduras y mecanismos pequeños, pero necesita energía normal y un cuidado mecánico. Una señal del controlador solo establece la posición y toda la corriente del motor pasa a través de la línea eléctrica.

Antes de usarlo, verifique el tipo de servo, voltaje, torque, corriente, rango de ángulo y comportamiento mecánico en las posiciones finales.

## Referencia Materials

- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial) - basic explanation of hobby servo structure, signal, power and typical problems.
- [SparkFun: Basic Servo Control for Beginners](https://learn.sparkfun.com/tutorials/basic-servo-control-for-beginners/servo-motor-basics) - table of typical wire colors, power, stall current and control signal range.
- [Pololu: Electrical characteristics of servos](https://www.pololu.com/blog/16/electrical-characteristics-of-servos-and-introduction-to-the-servo-control-interface) - useful explanation of servo currents and why stall current matters for power selection.
- [Adafruit: If the Servo Misbehaves](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves) - practical description of power drop and capacitor next to servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - official Servo library for Arduino approach and standard/continuous rotation servo description.
