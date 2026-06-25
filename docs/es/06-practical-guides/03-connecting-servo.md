# Conectar un Servo

Un servo es un motor pequeño con caja de cambios y electrónica de control. Puede decirle a qué posición girar el eje.

En dispositivos similares a iDryer, un servo puede abrir un amortiguador, mover un pestillo pequeño, presionar un interruptor mecánico o redirigir el flujo de aire.

El principal error con los servos: pensar que es una "cosa pequeña" y puede alimentarlo desde cualquier pin de 5V en el controlador. Un servo puede extraer corriente significativa, especialmente al inicio, movimiento repentino o cuando el mecanismo se bloquea.

## Tres Cables

Un servo de afición típico tiene tres cables:

- potencia: generalmente `5V` o `6V`;
- tierra: `GND`;
- señal: pulsos de control del controlador.

Colores comunes:

- rojo - potencia;
- negro o marrón - tierra;
- amarillo, naranja o blanco - señal.

Pero no puede confiar ciegamente en los colores. Diferentes fabricantes pueden usar esquemas de color diferentes. Antes de conectar, verifique el marcado, la página del producto o la hoja de datos.

## Potencia Separada, Señal Separada

El cable de señal no alimenta el servo. Solo dice al servo hacia dónde girar.

El servo extrae energía del cable de potencia.

La lógica correcta es:

- el controlador proporciona solo la señal de control;
- el servo es alimentado por una fuente de 5V/6V que puede manejar su corriente;
- la tierra del controlador y la tierra de potencia del servo están conectadas juntas.

![Código de color de cable de servo](../../img/03-common-components/06-servo-color-code.jpg)

*Fuente: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## Por Qué No Puede Alimentar Desde 5V Débil

Muchas placas tienen un pin de 5V. Esto no significa que un servo pueda ser alimentado de forma segura desde él.

Cuando se mueve, un servo puede extraer mucha más corriente de la que sugiere su tamaño. Si la potencia es insuficiente, aparecen síntomas típicos:

- el controlador se reinicia;
- la pantalla parpadea;
- la conexión USB se cae;
- el servo se sacude;
- Wi-Fi en ESP32 se cae;
- el servo zumba pero no se mueve;
- caída de potencia al inicio del movimiento.

Para un servo pequeño, la potencia suministrada por la placa a veces funciona si la placa y la fuente están explícitamente clasificadas para esa corriente. Pero para un dispositivo real con amortiguador, pestillo o mecanismo, es mejor usar una fuente de alimentación de CC DC-DC o 5V/6V separada con margen.

## Tierra Común

Si el servo es alimentado por una fuente separada, se necesita una tierra común.

Sin una tierra común, el controlador y el servo no tienen un nivel de señal común. El servo puede no responder, puede sacudirse o comportarse aleatoriamente.

Conexión sencilla:

1. `+5V` o `+6V` de la fuente de potencia va a la potencia del servo.
2. `GND` de la fuente de potencia va a la tierra del servo.
3. El `GND` del controlador está conectado a la misma tierra.
4. El pin PWM/GPIO del controlador va al cable de señal del servo.

La potencia del servo y la potencia del controlador pueden ser diferentes, pero la tierra debe ser común.

## Qué Señal se Necesita

Un servo de posición de afición típico se controla mediante pulsos.

Señal típica:

- pulso aproximadamente cada `20 ms`;
- aproximadamente `1 ms` - un extremo del rango;
- aproximadamente `1.5 ms` - en el medio;
- aproximadamente `2 ms` - otro extremo del rango.

Este no es PWM típico para brillo LED o velocidad de ventilador. Aquí, el ancho de pulso en microsegundos importa.

Los límites reales de un servo específico pueden diferir. Algunos funcionan de forma segura no de 0 a 180 grados sino menos. Entonces las posiciones extremas necesitan pruebas cuidadosas.

## No Bloquee un Servo Contra el Mecanismo

Un servo intenta mantener la posición ordenada.

Si un amortiguador golpea la carcasa, un brazo se bloquea o el mecanismo alcanza un tope físico antes de que termine el comando, el servo sigue empujando. En ese punto, la corriente sube, el motor se calienta, la caja de cambios se desgasta.

Esto es especialmente crítico para amortiguadores y pestillos.

Antes de la operación permanente, verifique:

- el mecanismo se mueve libremente en todo el rango;
- sin desalineación;
- sin bloqueo de eslabones;
- el servo no zumba en posición final;
- los ángulos extremos en firmware no fuerzan el mecanismo a un tope;
- con potencia apagada, el dispositivo permanece seguro o regresa a través de resorte, según lo deseado.

Si un servo zumba en reposo, a menudo señala carga, un tope o geometría de palanca incorrecta.

## Corriente de Inicio y Bloqueo

Un servo tiene corriente de funcionamiento normal y corriente cuando el eje está bloqueado. Esta última a menudo se llama corriente de bloqueo.

La corriente de bloqueo aparece cuando el servo intenta moverse pero el eje está bloqueado o el mecanismo es demasiado pesado.

Este modo a menudo causa:

- caída de potencia;
- reinicio del controlador;
- calentamiento de cable;
- sobrecalentamiento de DC-DC;
- rotura de caja de cambios.

Si la hoja de datos lista la corriente de bloqueo, elija la fuente de alimentación considerando este valor y margen de seguridad. Si no hay hoja de datos, no puede asumir que un servo es seguro ejecutar "a simple vista".

## Capacitor Junto al Servo

A veces un capacitor electrolítico entre `GND` y `GND` junto al servo ayuda.

No reemplaza una fuente de alimentación adecuada, pero puede suavizar una breve caída al inicio del movimiento.

Para un servo pequeño: cientos de microfaradios, como `470 uF` o más, con clasificación de voltaje por encima del voltaje de suministro.

La polaridad del capacitor electrolítico importa:

- capacitor más a `+5V`;
- capacitor menos a `GND`.

Si el dispositivo necesita ser confiable, primero elija potencia adecuada y cableado, luego use un capacitor como medida adicional.

## Configuración de Ejemplo de Klipper

En Klipper, un servo se describe con una sección `[servo]`.

Ejemplo:

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

Comandos:

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

Los nombres de pin aquí son típicos. En un dispositivo real, verifique el pinout de su placa.

Para mecánica, no comience con `0` y `180` de inmediato. Primero pruebe un rango seguro como `60`, `90`, `120`, luego expanda los ángulos.

## Lógica de Ejemplo de Arduino/ESP32

El enfoque de Arduino típicamente usa la librería de Servo:

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

Este es solo un ejemplo de lógica de señal. La potencia del servo aún necesita ser diseñada por separado. Incluso si el cable de señal está conectado a Arduino o ESP32, el motor servo no debe sobrecargar la potencia del controlador.

## Qué Verificar Después de Conectar

Antes de montarse en la carcasa:

- servo recibe voltaje correcto;
- la fuente de alimentación puede manejar la corriente del servo;
- la tierra del controlador y la tierra del servo son comunes;
- el cable de señal está conectado al pin correcto;
- el servo se mueve en la dirección correcta;
- los ángulos extremos no rompen el mecanismo;
- el mecanismo no se bloquea;
- el servo no zumba continuamente;
- los cables no atrapan la palanca o engranajes;
- la potencia no cae después del movimiento;
- el controlador no se reinicia.

Pruebe mecánica sin carga y bajo carga real. Un amortiguador que se mueve fácilmente a mano puede bloquearse después de montarse en la carcasa.

## Errores Comunes

- alimentando servo desde GPIO;
- alimentando servo desde un débil pin 5V de placa;
- olvidando tierra común;
- confiando en colores de cable sin verificar;
- conectando potencia al revés;
- usando cables demasiado delgados;
- no contabilizar la corriente de inicio y bloqueo;
- forzando servo a empujar contra un tope mecánico;
- usando ángulo `0` o `180` cuando el mecanismo real funciona de forma segura solo en un rango más pequeño;
- montando servo cerca del calor sin verificar temperatura de funcionamiento;
- tratando un servo de rotación continua como un servo de posición regular.

## Puntos Clave

- Un servo tiene tres líneas: potencia, tierra y señal.
- La señal no alimenta el servo.
- Los dispositivos reales a menudo necesitan una fuente de alimentación de 5V/6V separada.
- La tierra del servo y la tierra del controlador deben ser comunes.
- La carga más peligrosa es el bloqueo o el bloqueo mecánico.
- Los ángulos extremos necesitan selección cuidadosa, no inmediatamente `0` y `180`.
- Si el controlador se reinicia cuando se mueve el servo, primero verifique la potencia y la tierra común.

## Lecturas Relacionadas

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - sección oficial `[servo]`, `SET_SERVO`, ángulos y ancho de pulso.
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - explicación básica de servo de afición, tres cables y control de pulso.
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - desglose de conexión eléctrica, colores de cable típicos y mecánica de servo de afición.
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - ejemplo práctico de conexión, comportamiento de caída de potencia y capacitor junto a servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - referencia oficial de librería Servo para enfoque de Arduino.
