# Conectar una Célula de Carga

Una célula de carga mide la fuerza o el peso a través de la pequeña deformación de una viga de metal, botón o plataforma.

En dispositivos similares a iDryer, una célula de carga puede estimar el peso del carrete, el filamento restante o la carga del mecanismo.

Punto principal: una célula de carga casi nunca se conecta directamente a un controlador. Su señal es demasiado pequeña. Por lo general, se coloca un módulo HX711 o amplificador/ADC similar entre el sensor y el controlador.

## Qué Necesita

Conjunto mínimo:

- célula de carga del rango de peso necesario;
- módulo HX711;
- controlador: Arduino, ESP32, RP2040, STM32 u otra placa;
- montaje mecánico rígido;
- masa conocida para calibración;
- cables cortos y limpios.

Si la mecánica es pobre, el circuito no ayudará. Una célula de carga puede estar cableada perfectamente pero dar lecturas sin sentido debido a desalineación, juego o carga aplicada en el punto equivocado.

## Cómo Se Organiza la Conexión

La célula de carga se conecta a HX711 con cables analógicos.

HX711 se conecta al controlador con cables digitales.

Cadena típica:

```text
célula de carga -> HX711 -> controlador
```

HX711 generalmente tiene dos lados:

- entrada de célula de carga: `E+`, `E-`, `A+`, `A-` o similar;
- conexión al controlador: `VCC`, `GND`, `DT`/`DOUT`, `SCK`/`CLK`.

![Diagrama de conexión de HX711 y célula de carga](../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Fuente: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Cables de Célula de Carga

Una célula de carga típica de cuatro cables generalmente tiene:

- `E+` - más de suministro de puente;
- `E-` - menos de suministro de puente;
- `S+`, `A+` u `O+` - señal de medición positiva;
- `S-`, `A-` u `O-` - señal de medición negativa.

Esquema de color común:

- rojo - `E+`;
- negro - `E-`;
- verde o azul - `A+`;
- blanco - `A-`.

Pero los colores no son ley. Los sensores diferentes pueden diferir. Si hay una hoja de datos para la célula de carga específica, sígala.

Si el sensor tiene un quinto cable, lámina o escudo, a menudo es blindaje electromagnético. No lo confunda con un cable de medición de puente. Generalmente, el escudo se conecta a `GND` u alojamiento en un lado si la documentación lo dice, pero no a medición `A+`/`A-`.

Si no hay diagrama de cable, no conecte la célula de carga "al azar". Primero encuentre la hoja de datos del sensor o verifique el puente según guía del fabricante: los cables incorrectos fácilmente dan lecturas inestables u sobrecargan la entrada HX711.

## Conectando HX711 al Controlador

En el lado del controlador, generalmente necesita cuatro líneas:

- `VCC` - potencia del módulo;
- `GND` - negativo común;
- `DT`, `DOUT` o `DATA` - datos;
- `SCK`, `CLK` o `PD_SCK` - reloj.

Para muchos módulos HX711, la potencia puede ser `3.3V` o `5V`, pero verifique el módulo específico. Si el controlador funciona a 3.3V, es conveniente usar un módulo y potencia compatibles con lógica 3.3V.

Los pines `SCK` y `SCK` generalmente pueden conectarse a GPIO regular. Esta no es I2C o SPI en el sentido habitual, pero una interfaz HX711 simple de dos cables.

## La Mecánica Importa Más Que el Circuito

Una célula de carga debe deformarse como el fabricante tenía la intención.

Para un sensor de viga, un lado generalmente monta en una base fija, el otro lado soporta la carga. Si ambos lados están rígidamente montados en una parte, el sensor no flexionará normalmente.

Verificar:

- dónde está el lado de montaje del sensor;
- dónde debe aplicarse la carga;
- qué dirección debe ir la fuerza;
- si se necesitan espaciadores;
- si la parte móvil despeja el alojamiento;
- sin desalineación;
- sin carga lateral;
- los tornillos no están apretados en exceso;
- el carrete o plataforma no aterriza más allá de la zona de trabajo del sensor.

Para peso de carrete, es especialmente importante que toda la carga pase a través del sensor, no parcialmente a través de pared de alojamiento, eje, cable o cubierta cosmética.

## No Sobrecargue el Sensor

El rango de una célula de carga no es una recomendación sino un límite de medición.

Si un sensor de 1 kg se coloca donde un carrete y soporte pueden exceder esto, el sensor funcionará mal o se deformará permanentemente.

Elija el rango con margen:

- peso máximo de carrete;
- peso del soporte;
- posibles tirones;
- desalineación;
- margen de seguridad para error del usuario.

Pero un rango demasiado grande tampoco siempre es bueno. Un sensor de 100 kg sensirá un carrete pequeño peor que un sensor de 5 kg o 10 kg con mecánica e electrónica idénticas.

## Primer Inicio

Antes de instalar en el dispositivo, pruebe el sistema en el banco:

1. Conecte célula de carga a HX711.
2. Conecte HX711 a controlador.
3. Ejecute código de prueba o librería.
4. Asegúrese de que los valores brutos cambien cuando presiona el sensor.
5. Retire la carga y verifique que el valor sea bastante estable.
6. Coloque una masa conocida y verifique el cambio.

En esta etapa, no exija exactitud en gramos. Primero, necesita ver que el sensor está vivo, la dirección de carga es correcta y las lecturas cambian predeciblemente.

Si el valor disminuye cuando aumenta el peso, generalmente solo intercambie `A+` y `A-` o cuente el signo en código.

## Tara y Calibración

Una célula de carga sin calibración no sabe qué son los gramos.

Proceso típico:

1. Coloque plataforma vacía.
2. Tara: esto es cero contabilizando el peso de la plataforma.
3. Coloque una masa conocida.
4. Seleccione factor de calibración.
5. Verifique varios pesos diferentes.

Para carretes de filamento, decida qué cuenta como peso:

- carrete completo con plástico;
- solo plástico restante sin peso de carrete vacío;
- cambio de peso desde valor inicial.

Si carretes vacíos de diferentes fabricantes pesan diferente, el cálculo exacto del resto requiere conocer el peso específico del carrete vacío u trabajar con estimaciones aproximadas.

## Ruido y Lecturas Inestables

HX711 mide una señal muy pequeña, por lo que el sistema es sensible al ruido y problemas mecánicos.

Causas de lecturas inestables:

- cables largos del sensor a HX711;
- contactos pobres;
- cables de potencia del calentador junto a cables de señal;
- vibración del ventilador o impresora;
- base blanda;
- juego en montaje;
- desviación de temperatura;
- carga tocando el alojamiento eludiendo el sensor.

Medidas prácticas:

- mantenga HX711 cerca de célula de carga;
- no ejecute cables de señal junto a cables de potencia del calentador;
- asegure cables para que no tiren del sensor;
- utilice la mediación de medición;
- calibre después de montaje en alojamiento;
- tara después del calentamiento del dispositivo si la temperatura notablemente afecta las lecturas.

## Qué Verificar Después del Ensamblaje

Antes de usar:

- sensor está clasificado para el peso necesario;
- la carga va a través de la parte de trabajo del sensor;
- los sujetadores no bloquean deformación;
- HX711 recibe potencia correcta;
- `DT` y `SCK` están conectados a los GPIO correctos;
- existe tierra común;
- los valores brutos cambian bajo carga;
- sin carga, las lecturas no derivan demasiado rápidamente;
- la masa conocida muestra peso esperado después calibración;
- los cables no tiran de la plataforma;
- el carrete o soporte no toca el alojamiento más allá del sensor.

## Errores Comunes

- conectando célula de carga directamente a entrada analógica del controlador;
- confundiendo `E+`/`E-` y `A+`/`A-`;
- confiando en colores de cable sin hoja de datos;
- olvidando calibración;
- tarando antes de instalación mecánica final;
- montando sensor para que no pueda flexionar;
- sobrecargando el sensor;
- eligiendo rango demasiado grande y perdiendo sensibilidad;
- obteniendo inestabilidad de cables largos e interferencia;
- esperando exactitud en gramos de cuerpo de plástico flexible sin mecánica rígida.

## Puntos Clave

- La célula de carga generalmente se conecta a través de HX711, no directamente al controlador.
- Los cables del sensor van a `E+`, `E-`, `A+`, `A-`.
- HX711 se conecta al controlador vía potencia, tierra, `DT` y `SCK`.
- La mecánica importa más que el circuito: la carga debe pasar a través del sensor correctamente.
- Se requieren tara y calibración con masa conocida.
- Sin montaje rígido y mecánica adecuada, no sucederán lecturas precisas.

## Lecturas Relacionadas

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - conexión práctica de HX711 y célula de carga, colores de cable, `DT`/`SCK` y ejemplo de calibración.
- [SparkFun: Load Cell Amplifier HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - descripción de módulo HX711, propósito e interfaz de microcontrolador.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - hoja de datos técnica HX711: ADC de 24 bits, entrada diferencial de puente, ganancia e interfaz digital.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - ejemplos prácticos de instalación mecánica de célula de carga y dirección de aplicación de carga.
- [SparkFun retired HX711 guide: load cell mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - ilustraciones útiles de opciones de montaje de sensor de viga, botón y plataforma.
