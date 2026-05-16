# Errores de fuente de alimentación

La fuente de alimentación es lo primero que se verifica cuando el dispositivo se comporta extrañamente.

Una fuente de alimentación débil, cable delgado o terminal pobre puede parecer un problema de firmware, Wi-Fi, sensor o controlador.

## Síntomas

Signos típicos de problemas de fuente de alimentación:

- el controlador se reinicia;
- la pantalla parpadea;
- Wi-Fi en ESP32 se cae;
- el ventilador inicia y se detiene;
- el servo se sacude;
- el calentador calienta débilmente;
- USB desaparece cuando la carga se activa;
- MOSFET, terminal o cable se calientan;
- los sensores muestran valores inestables;
- el dispositivo funciona sin carga pero se rompe cuando se conecta calentador o motor.

Si un síntoma aparece exactamente cuando la carga se activa, casi siempre la fuente de alimentación y el cableado necesitan ser verificados.

## Fuente de alimentación sin margen

No puedes seleccionar una fuente de alimentación exactamente igualando la potencia de carga.

Si la carga consume `100W`, una fuente de alimentación de `100W` funcionará en su límite. Puede sobrecalentarse, bajar de voltaje y manejar mal corrientes de inrush.

Regla práctica para esta sección:

**el margen mínimo de potencia es 50%, a menos que la documentación de un componente específico requiera más.**

Ejemplo:

```text
calentador: 24V 120W
corriente: 120W / 24V = 5A
margen mínimo 50%: 7.5A
```

Así que la fuente de alimentación es mejor elegir al menos `24V 7.5A`, y en la práctica a menudo más grande, si hay ventiladores, controlador, iluminación y otras cargas.

## Corriente total no calculada

Debes calcular no un componente, sino todo el dispositivo.

Por ejemplo:

- calentador;
- ventiladores;
- servo;
- tira LED;
- controlador;
- pantalla;
- sensores;
- convertidor DC-DC.

Las corrientes se suman. Las corrientes de inrush y picos breves también necesitan ser contabilizados.

Un servo o ventilador puede brevemente dibujar más que en modo normal. Si el margen es pequeño, exactamente este momento causará que el controlador se reinicie.

## 12V y 24V confundidos

El error más simple y más peligroso:

- ventilador 12V enchufado a 24V;
- módulo 5V enchufado a 12V;
- calentador 24V se espera que funcione normalmente de 12V;
- módulo 3.3V alimentado de 5V sin verificar.

Antes de conectar verifica:

- clasificación de carga;
- clasificación de fuente de alimentación;
- voltaje con multímetro;
- diagrama de conexión;
- clasificación de voltaje del controlador y módulo.

No confíes solo en el color del cable o tipo de conector similar.

## Caída de voltaje en cables

El cable tiene resistencia.

Cuanto más largo es el cable y mayor la corriente, mayor la caída de voltaje y calentamiento.

Síntomas:

- la fuente de alimentación produce 24V, pero la carga recibe menos;
- el calentador calienta más débilmente que lo esperado;
- el ventilador inicia mal;
- el servo se sacude;
- el cable notablemente cálido;
- el terminal se calienta.

Verifica voltaje no solo en la salida de la fuente de alimentación, sino también en la carga misma durante la operación.

Si el voltaje cae significativamente bajo carga, el problema podría estar en el cable, terminal, conector, fuente de alimentación o carga demasiado grande.

## Sin tierra común

Si un controlador conduce un módulo externo o carga, a menudo se necesita una tierra común.

Por ejemplo:

- controlador conduce módulo MOSFET;
- controlador configura PWM a ventilador de 4-pin;
- controlador conduce servo con potencia separada;
- HX711, RFID u otro módulo alimentado separadamente.

Sin `GND` común la señal podría no tener el nivel correcto. El dispositivo podría no responder, sacudirse o funcionar inestablemente.

La tierra común no significa que toda la carga deba ser alimentada a través del controlador. Es solo el nivel de referencia común para la señal.

## Controlador alimentado de línea ruidosa

Motores, ventiladores, servos, calentadores y tiras LED pueden crear bajadas de voltaje y ruido.

Si el controlador se alimenta de la misma línea sin DC-DC apropiado, filtrado y margen, puede reiniciarse.

Soluciones comunes:

- DC-DC separado y apropiado para controlador;
- cables de potencia cortos del controlador;
- `GND` común en un punto claro;
- capacitor cerca de la carga, si es apropiado;
- separación de cableado de potencia y lógica;
- fuente de alimentación apropiada con margen.

## Qué verificar con un multímetro

Como mínimo:

1. Voltaje de fuente de alimentación sin carga.
2. Voltaje de fuente de alimentación bajo carga.
3. Voltaje en terminales de carga bajo carga.
4. Polaridad.
5. Presencia de tierra común.
6. Calentamiento de cable y terminal después de una breve prueba.

Si el dispositivo funciona solo sin carga, mídelo bajo carga. El voltaje sin carga podría verse normal.

## Qué no hacer

No puedes:

- usar una fuente de alimentación "al límite";
- aumentar clasificación de fusible porque dispara;
- usar cables Dupont delgados para carga de potencia;
- retorcer cables de potencia sin terminal apropiado;
- alimentar calentador a través de conector débil;
- conectar carga directamente a GPIO;
- repetidamente encender dispositivo si el cable o terminal se calienta.

Si algo se calienta, primero apaga el poder y encuentra la causa.

## Errores típicos

- no calcular corriente de carga;
- elegir fuente de alimentación sin margen;
- olvidar corriente de inrush de ventilador o servo;
- confundir 12V y 24V;
- alimentar controlador 5V desde línea inestable;
- sin `GND` común;
- cable demasiado delgado;
- cable demasiado largo para la corriente;
- terminal no apretado bien;
- carga funciona pero el voltaje cae significativamente.

## Puntos clave

- La fuente de alimentación se verifica primero.
- Calcula corriente para todas las cargas, no solo una pieza.
- Necesita al menos margen de 50% de potencia.
- El voltaje debe ser medido bajo carga.
- `GND` común es a menudo obligatorio para controlar módulos externos.
- Cable delgado o largo puede causar caída de voltaje y calentamiento.

## Referencias

- [SparkFun: Cómo alimentar un proyecto](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - consideraciones básicas sobre voltaje, corriente y potencia para proyectos de microcontrolador.
- [SparkFun: Consejos de resolución de problemas](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - verificar fuente de alimentación, conexiones y calentamiento al resolver problemas.
- [ProdataKey: Cómo afecta el calibre de cable a la pérdida de línea?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss?) - por qué longitud, sección transversal y corriente afectan caída de voltaje y pérdidas.
- [WiringCalcs: Caída de voltaje explicada](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - explicación práctica de caída de voltaje, resistencia de cable y efecto de corriente.
- [Guía de medidor de potencia Qwiic de SparkFun](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - ejemplo de `GND` común al medir/controlar carga externa.
