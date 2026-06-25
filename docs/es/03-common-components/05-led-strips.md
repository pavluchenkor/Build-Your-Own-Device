# Tiras LED

Una tira de LED es una placa flexible con LED y líneas de alimentación. En una impresora, secadora o pequeño dispositivo de bricolaje, generalmente se usa para iluminación de cámaras, indicación de estado, iluminación del área de trabajo o iluminación decorativa de recintos.

El principal error del principiante es tratar una tira de LED como un LED pequeño. Incluso una tira corta puede consumir más corriente que un ventilador, y una tira larga se convierte en una carga de máxima potencia.

## Dónde se usa

En dispositivos de bricolaje alrededor de una impresora 3D, las tiras de LED son útiles para:

- iluminar la cámara de la impresora;
- encender el secador de filamentos;
- status indication: heating, drying, error, waiting;
- iluminación del área de trabajo en el interior del recinto;
- iluminación nocturna suave sin luz principal;
- Señal visual cuando finaliza la impresión o se produce un error.

Para la iluminación de servicio, suele ser mejor una simple franja blanca. Para la indicación de modo, las tiras RGB o direccionables son convenientes, pero son más complejas en potencia y control.

## Voltage: 5V, 12V or 24V

Las tiras de LED vienen en diferentes voltajes:

- `5V` - often addressable strips like WS2812/NeoPixel;
- `12V`: tiras blancas y RGB comunes;
- `24V`: conveniente para secciones más largas y sistemas de 24 V.

El voltaje de la tira debe coincidir con la fuente de alimentación. No puede conectar una tira `24V` a `24V`. Una tira `12V` en `5V` puede atenuarse o no funcionar. Es casi seguro que una tira `12V` en `24V` o `24V` se dañará.

Si su impresora ya tiene `24V`, eso no significa que se pueda conectar cualquier tira. Necesitas comprar exactamente una tira `24V` o poner un convertidor DC-DC para el voltaje correcto.

## Tiras regulares y direccionables

Hay dos tipos principales de tiras de LED.

Una tira normal se enciende de repente. Esto podría ser:

- single-color white;
- warm/cold white;
- Tira RGB que cambia de color en toda su longitud;
- Tira RGBW con canal blanco independiente.

Una tira de este tipo no tiene microchip en cada LED. El brillo se controla mediante conmutación de energía o PWM a través de un MOSFET, un controlador LED o una salida de placa adecuada.

Una tira direccionable tiene un microchip de control para LED individuales o grupos de LED. Te permite iluminar diferentes secciones con diferentes colores. Ejemplos típicos: WS2812B, SK6812, tiras compatibles con NeoPixel.

Addressable strips require:

- potencia al voltaje correcto;
- común `GND` con controlador;
- data wire `DIN`;
- dirección correcta de los datos a lo largo de la flecha de la tira;
- often - 5V data signal level;
- Potencia cuidada y sin grandes caídas.

Para una iluminación de cámara sencilla, una tira direccionable suele ser excesiva. Para obtener indicaciones y efectos agradables, es conveniente, pero requiere más atención a la potencia.

## Corriente y potencia

Elija una tira de LED no solo por el color y la longitud. Necesitas conocer su poder.

Las páginas de productos suelen incluir:

- voltaje: por ejemplo `24V` o `24V`;
- potencia por metro: por ejemplo `9.6 W/m`, `14.4 W/m`, `14.4 W/m`;
- número de LED por metro;
- LED type: for example `3528`, `5050`, `2835`;
- strip width;
- protection degree: bare, silicone jacket, IP65/IP67;
- maximum length per section.

La corriente se calcula simplemente:

```text
current = power / voltage
```

Ejemplo: tienes `24V` de la tira `9.6 W/m` a la potencia `9.6 W/m`.

```text
total power = 2 m × 9.6 W/m = 19.2 W
current = 19.2 W / 24 V = 0.8 A
```

Para una tira de este tipo, la fuente de alimentación, el MOSFET, los cables y el conector deben manejarse cómodamente sobre `30-50%`. En la práctica, es mejor agregar al menos un margen `30-50%`, especialmente si la tira funciona durante períodos prolongados.

Para las tiras RGB, debes tener en cuenta la corriente máxima de todos los canales. El blanco en RGB generalmente significa que los canales rojo, verde y azul están encendidos simultáneamente.

Para tiras direccionables de 5 V, una estimación aproximada es de hasta `60 mA` por píxel RGB en blanco total. En efectos reales, la corriente puede ser menor, pero no se puede dimensionar la fuente de alimentación y el cableado para que "generalmente no tengan el brillo máximo".

## Por qué no se puede alimentar una regleta desde GPIO

El GPIO de un controlador es una salida de señal, no una fuente de alimentación.

No se puede conectar una tira de LED directamente a un pin de microcontrolador. GPIO no está clasificado para corriente de tira. Esto puede dañar la placa, provocar reinicios, funcionamiento inestable o rastros de sobrecalentamiento.

Correct logic:

- la corriente de tira proviene de la fuente de alimentación;
- el controlador solo gestiona el encendido/apagado, el brillo o los datos;
- un MOSFET, controlador LED, controlador LED o salida de alimentación de placa maneja la conmutación de energía;
- El controlador y las tierras de suministro están conectados si hay una señal de control.

## Conexión de una tira simple de un solo color

Para una tira blanca `24V` o `24V`, a menudo se usa un MOSFET de lado bajo: el plus de la tira está conectado al plus de alimentación y el módulo MOSFET conmuta el menos de la tira.

![Close-up of LED strip with SMD diodes](../../img/03-common-components/05-led-strip-closeup.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:LED_strip_closeup.jpg), Akbermamps, CC BY 4.0*

Circuito típico:

1. La fuente de alimentación `+` va a la tira de LED `+`.
2. La tira de LED `-` va a la salida de alimentación del módulo MOSFET.
3. La fuente de alimentación `GND` va al módulo MOSFET.
4. El controlador `GND` está conectado a la fuente de alimentación `GND`.
5. El pin de control del controlador va a la entrada del módulo MOSFET.

Si la placa de la impresora ya tiene una salida administrada para ventiladores o LED, puede usarla solo si está clasificada para el voltaje y la corriente necesarios. No puede conectar una tira larga a ningún conector aleatorio sin verificar el límite de salida.

## RGB Strip

Una tira RGB típica suele tener un plus común y tres menos controlados:

- `+V`;
- `R`;
- `G`;
- `B`.

Cada canal de color requiere un canal MOSFET separado o un controlador RGB listo para usar. Un MOSFET para toda la tira RGB solo puede encenderlo y apagarlo, no cambiar de color.

Al seleccionar un módulo MOSFET para una tira RGB, observe la corriente por canal y la corriente total. El conector, terminal y cable también deben soportar la carga.

## Addressable Strip

Una regleta direccionable suele tener:

- `+5V` u otra potencia si no es un modelo de 5V;
- `GND`;
- `DIN` - data input;
- a veces `DOUT`: salida de datos a la siguiente sección.

Reglas importantes:

- conecte los datos hacia la flecha de la tira;
- el controlador y la tira deben tener puntos en común;
- para tiras direccionables de 5 V en un controlador de 3,3 V, a menudo se necesita un convertidor de nivel;
- antes de una tira larga, es útil un condensador electrolítico de potencia;
- a menudo se coloca una resistencia alrededor de `300-500 Ohm` en la línea de datos cerca de la entrada de la tira;
- para una franja larga, es mejor suministrar energía no sólo al principio sino también en puntos adicionales.

Si una regleta direccionable se alimenta desde una fuente separada, no puede aplicar solo `GND` sin `GND` común. La señal de datos entonces no tiene un nivel de referencia adecuado y la tira parpadeará aleatoriamente o no funcionará.

## Caída de voltaje y potencia multipunto

Una tira de LED larga puede ser brillante al principio y notablemente más tenue al final. Esto no es un "mal controlador", es una caída de voltaje en los cables y las trazas de cobre de la tira.

Cuanto menor sea el voltaje y mayor la corriente, peor será el problema. Por lo tanto, las tiras `12V` y `24V` necesitan con más frecuencia energía de múltiples puntos que las tiras `24V` de la misma potencia.

Signs of voltage drop:

- strip end is dimmer;
- el blanco en RGB cambia a amarillo o rojo;
- addressable strip flickers during bright effects;
- el controlador se reinicia cuando se ilumina;
- wires, connector or strip start become hot.

Solution:

- utilice una tira con el voltaje adecuado;
- utilice alambre con calibre suficiente;
- aplique energía al inicio y al final de secciones largas;
- dividir la tira larga en secciones;
- utilizar fusible en la línea eléctrica;
- don't route all current through weak connector or thin traces.

## Calor y montaje

Una tira de LED produce calor por sí misma. Esto es especialmente notable en el caso de tiras brillantes con cubierta de silicona y tiras montadas dentro de un recinto cerrado.

Bad mounting locations:

- next to a heater;
- en PLA blando dentro de una cámara cálida;
- sobre una superficie que no disipe el calor;
- donde la tira toca las partes móviles;
- en una cubierta que a menudo se retira sin conector.

Para una mayor duración, es mejor montar la tira sobre un perfil de aluminio u otra superficie que disipe el calor. Si la tira está dentro de la cámara de la impresora, tenga en cuenta la temperatura de la cámara y la temperatura de la capa adhesiva.

## Qué comprobar antes de comprar

Antes de comprar una tira de LED, comprueba:

- strip voltage;
- power per meter;
- total length;
- color: white, RGB, RGBW, addressable;
- control type;
- ancho de la tira y ubicación de montaje;
- installation location temperature;
- whether you need an aluminum profile;
- whether you need a MOSFET module or LED controller;
- si la fuente de alimentación puede soportar la carga adicional;
- si hay un conector adecuado para el servicio.

Para una cámara de impresora, una tira blanca `24V` suele ser más práctica si todo el sistema ya es `5V`. Para un indicador ESP32 pequeño, una tira direccionable `5V` corta podría ser conveniente. Para una iluminación RGB decorativa prolongada, es mejor calcular la corriente de antemano y pensar en la potencia multipunto.

## Típicos Errors

- tira conectada a voltaje incorrecto;
- regleta de alimentación de GPIO;
- no calculó la corriente para toda la longitud;
- módulo MOSFET seleccionado sin margen;
- tira larga conectada con un cable delgado;
- olvidé puntos en común entre el controlador y la tira;
- datos de tira direccionables conectados a `DIN` en lugar de `DIN`;
- no instalé un convertidor de nivel para la tira direccionable de 5 V desde el controlador de 3,3 V cuando fue necesario;
- alimentado solo un extremo de una tira larga;
- tira instalada en zona caliente sin control de temperatura;
- Regleta izquierda sin conector sobre funda extraíble.

## Principal Point

Una tira de LED no es un LED de señal, es una carga. Primero verifique el voltaje y la potencia, luego calcule la corriente, seleccione el cable, MOSFET o controlador, y solo luego conéctelo a la placa.

Para una iluminación sencilla, elija una tira blanca normal al voltaje del sistema. Para efectos e indicaciones, puede utilizar una regleta direccionable, pero la alimentación, la tierra común, el nivel de señal y la protección contra caídas de voltaje son especialmente importantes.

## Referencia Materials

- [Adafruit NeoPixel Überguide: Best Practices](https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices) - practical rules for addressable strips: common ground, data line resistor, capacitor and signal level.
- [Adafruit NeoPixel Überguide: Powering NeoPixels](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels) - detailed explanation of addressable strip power, voltage drop and multi-point power.
- [Adafruit RGB LED Strips: Usage](https://learn.adafruit.com/rgb-led-strips/usage) - example of managing regular RGB strips through power transistors/MOSFET, not directly from microcontroller.
- [SparkFun WS2812 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide/addressable-led-strips) - introduction to addressable WS2812 strips and their variants.
- [QuinLED: 12V vs 24V LED strip and voltage drop](https://quinled.info/2018/08/24/12v-vs-24v-led-strip-or-voltage-drop/) - practical explanation of why long strips suffer from voltage drop and why 24V is often better for long sections.
