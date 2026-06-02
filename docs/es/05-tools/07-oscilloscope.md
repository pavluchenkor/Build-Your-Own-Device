# Osciloscopio

Un osciloscopio muestra cómo cambia una señal con el tiempo.

Un multímetro puede mostrar "alrededor de 3.3V" o "hay frecuencia". Un osciloscopio muestra la forma de la señal: pulsos, bordes, caída, ruido, rebote, paquetes UART, PWM.

![Pantalla de un osciloscopio digital](../../../img/05-tools/07-digital-oscilloscope.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

Una señal PWM en la pantalla del osciloscopio se ve así:

![Animación de PWM: cambio de ciclo de trabajo y forma de onda de señal](../../../img/05-tools/07-pwm-signal-waveform.gif)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

No necesita uno para cada construcción simple. Pero cuando un dispositivo se comporta inestablemente, un osciloscopio puede revelar en minutos lo que un multímetro no puede ver.

## Lo Que Puede Ver

En dispositivos similares a iDryer, un osciloscopio es útil para ver:

- PWM del ventilador;
- PWM del módulo MOSFET;
- UART `TX/RX`;
- caída de 5V o 3.3V al inicio del servo;
- ruido de la fuente de alimentación;
- rebote del botón;
- señal del tacómetro del ventilador;
- breves parpadeos que un multímetro promedia.

Un osciloscopio responde no solo "¿hay voltaje?" sino "¿qué sucede con la señal a lo largo del tiempo?".

## La Advertencia Más Importante

La mayoría de los osciloscópios de escritorio tienen la tierra de la sonda conectada a la tierra protectora de la red.

Esto significa: el clip de tierra de la sonda no es "solo otro cable".

Si fija el clip de tierra a un punto que no es `GND` del circuito de bajo voltaje, puede crear un cortocircuito a través del osciloscopio.

Es especialmente peligroso entrar en la sección de corriente alterna 110-230V, SSR, fuente de alimentación o alta tensión con una sonda normal.

No puede:

- desconectar la tierra del osciloscopio para medición "flotante";
- conectar la tierra de la sonda a fase u otro punto de voltaje;
- medir voltaje de corriente alterna con una sonda normal sin comprender el circuito;
- asumir que los dos canales son completamente independientes: las tierras de canales a menudo están conectadas.

Para mediciones flotantes, mediciones de alto lado y mediciones de alto voltaje, necesita métodos adecuados: sonda diferencial, dispositivo aislado u otro enfoque seguro.

## Cómo Conectar una Sonda

Para circuitos de bajo voltaje:

1. Conecte la sonda al osciloscopio.
2. Conecte la tierra de la sonda a `GND` del dispositivo.
3. Conecte la punta de la sonda a la señal.
4. Seleccione la configuración correcta de la sonda: `1x` o `10x`.
5. Asegúrese de que el osciloscopio esté configurado con el mismo factor.

Para la mayoría de señales digitales, use `10x`: la sonda carga menos el circuito y generalmente muestra mejor la forma de la señal.

## PWM

PWM es una señal de pulso.

El osciloscopio muestra:

- frecuencia;
- ciclo de trabajo;
- nivel lógico alto;
- nivel lógico bajo;
- bordes;
- jitter;
- ruido.

Para un ventilador o MOSFET esto ayuda a entender:

- si el pin emite una señal en absoluto;
- si el nivel 3.3V o 5V es suficiente;
- si la frecuencia coincide con la configuración;
- si el ciclo de trabajo cambia a comando;
- si la señal no cae cuando se conecta la carga.

## UART

UART en el osciloscopio se parece a una secuencia de pulsos.

El osciloscopio ayuda a ver:

- si hay actividad en `TX`;
- si los niveles lógicos no están invertidos;
- cuál es el nivel inactivo;
- si hay ruido fuerte;
- si la velocidad de baudios aproximadamente coincide.

Para decodificar texto, un analizador lógico o adaptador USB-UART es más conveniente. Pero un osciloscopio muestra rápidamente si la señal está físicamente viva.

## Caída de Fuente de Alimentación

Un multímetro puede no ver una breve caída.

Por ejemplo, cuando un servo comienza, una línea de 5V podría caer durante unos milisegundos. El multímetro muestra casi 5V normal, pero el controlador ya se reinició.

Un osciloscopio le permite ver:

- cuánto cae el voltaje;
- cuánto dura la caída;
- si hay picos;
- si un capacitor ayuda;
- si la situación cambia con una fuente de alimentación diferente o cables.

Esto es especialmente útil para ESP32, servos, ventiladores y DC-DC.

## Ruido e Interferencia

El ruido en líneas de potencia o señal puede romper sensores y comunicación.

Un osciloscopio ayuda a ver:

- ondulación de DC-DC;
- picos de motor;
- ruido cerca del calentador;
- rebote del botón;
- interferencia en un cable largo.

Pero comprenda los límites: una conexión pobre de la tierra de la sonda puede agregar ruido a la pantalla misma. Un resorte de tierra de sonda corto o cable de tierra corto a menudo da una imagen más honesta que un clip largo.

## Multímetro con Medición de Frecuencia

A veces un osciloscopio no es necesario para verificaciones iniciales.

Algunos multímetros pueden medir la frecuencia de la señal. En las especificaciones esto podría llamarse `Hz`, `frequency` o `frequency counter`.

Esto es útil si necesita entender rápidamente:

- si una señal PWM existe en absoluto;
- si la frecuencia cambia con el ajuste;
- si la salida del controlador funciona;
- si hay actividad en una línea digital simple.

Por ejemplo, si un controlador debe enviar PWM a un ventilador o módulo MOSFET, un multímetro de medición de frecuencia puede mostrar que la señal existe y su frecuencia aproximadamente coincide con el valor esperado.

Pero un multímetro no muestra la forma de la señal. No mostrará:

- nivel lógico alto;
- ancho de pulso;
- ciclo de trabajo de PWM;
- bordes de señal;
- breves caídas;
- ruido e interferencia;
- distorsión de línea.

Entonces un multímetro de medición de frecuencia es una buena herramienta para verificaciones rápidas, pero no un reemplazo del osciloscopio completo.

## Qué Verificar Antes de Medir

Antes de conectar una sonda:

1. ¿Cuál es `GND` en el circuito?
2. ¿Está este punto conectado a la tierra protectora de la red?
3. ¿No hay voltaje de corriente alterna?
4. ¿Está la sonda clasificada para el voltaje?
5. ¿Se selecciona `10x` si es necesario?
6. ¿Están la sonda y el canal configurados de la misma manera?
7. ¿No conectan las tierras de canales diferentes puntos de circuito?
8. ¿Puede verificar primero la señal en el lado de bajo voltaje?

Si tiene dudas sobre 110-230V AC, no conecte el osciloscopio.

## Errores Comunes

- clip de tierra fijado a un punto de voltaje, no `GND`;
- intentando "desconectar" la tierra del osciloscopio de la red;
- midiendo voltaje de corriente alterna con una sonda normal sin diferencial;
- olvidando que las tierras de canales están conectadas;
- sonda configurada en `10x`, osciloscopio configurado en `1x`;
- usando tierra de sonda larga y viendo ruido adicional;
- solo mirando con multímetro y faltando una breve caída;
- pensando que un problema de UART es software cuando no hay señal física en la línea.

## Lo Esencial

- Un osciloscopio muestra la forma de la señal a lo largo del tiempo.
- Es útil para PWM, UART, caída de potencia, ruido y parpadeos breves.
- La tierra de un osciloscopio de escritorio normal está conectada a la tierra protectora de la red.
- No puede conectar la tierra de la sonda a un punto de circuito arbitrario.
- Para mediciones de corriente alterna y flotantes, se necesitan métodos seguros especiales.
- Un multímetro de medición de frecuencia es útil, pero no un reemplazo del osciloscopio.

## Materiales de Referencia

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - introducción práctica básica a osciloscópios, señales y controles.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - conexión a tierra, configuración, controles y uso básico del osciloscopio.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - advertencias sobre tierra de sonda, tierra de corriente alterna y peligro de mediciones flotantes con osciloscopio normal.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - por qué desconectar la tierra de corriente alterna del osciloscopio es peligroso y qué alternativas seguras existen.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight no recomienda eludir la conexión a tierra y sugiere sondas diferenciales.
