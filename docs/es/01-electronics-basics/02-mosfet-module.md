# Módulo MOSFET

Un módulo MOSFET es una pequeña placa lista para usar que funciona como un conmutador de potencia controlado para cargas CC. El controlador suministra una señal de control débil, y el módulo MOSFET activa o desactiva la corriente desde la fuente de alimentación a la carga.

En dispositivos similares a iDryer y periféricos de impresora 3D, un módulo MOSFET se usa para ventiladores, tiras LED, calentadores de bajo voltaje y otras cargas `12V`/`24V`, cuando la salida estándar de la placa es débil, está ocupada o es incómoda.

## MOSFET y módulo MOSFET

Un MOSFET es un transistor de efecto de campo. Tiene tres pines principales:

- `Gate` - entrada de control;
- `Drain` - salida de potencia;
- `Source` - salida de potencia.

La puerta no alimenta la carga. Solo controla. La corriente de carga principal fluye a través de la parte de potencia del MOSFET entre `Drain` y `Source`.

Un módulo MOSFET no es solo un transistor simple. Generalmente es una placa con un MOSFET, terminales, entrada de control y a veces resistencias adicionales, indicadores, disipador de calor o diodo de protección.

La placa es conveniente para un prototipo, pero sus especificaciones deben verificarse tan cuidadosamente como cualquier nodo de potencia.

## Por qué es necesario

GPIO del controlador no debe alimentar una carga pesada.

GPIO puede controlar:

- entrada del módulo MOSFET;
- entrada del relé;
- entrada del SSR;
- entrada del controlador.

Pero GPIO no debe alimentar directamente:

- ventilador;
- tira LED;
- calentador;
- motor;
- solenoide;
- accionamiento servo.

Si conecta la carga directamente a GPIO, puede dañar el controlador, obtener reinicios, sobrecalentar pistas u obtener una operación inestable.

## Conmutación de lado bajo

La variante más común para el módulo MOSFET de canal N es la conmutación de lado bajo, es decir, conmutación a través de la línea negativa.

![MOSFET canal N en modo de conmutación de lado bajo](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Lógica típica:

1. `+24V` desde la fuente de alimentación va directamente al positivo de la carga.
2. El negativo de la carga va a la salida de potencia del módulo MOSFET.
3. El módulo MOSFET conecta o rompe el camino desde el negativo de la carga a `GND`.
4. `GND` de la fuente de alimentación y `GND` del controlador están conectados juntos.
5. El pin de control del controlador va a la entrada `Signal`, `IN`, `Gate` o similar del módulo.

El `GND` común / negativo común es obligatorio. Sin esto, el controlador y el módulo MOSFET no tienen un nivel de referencia común para la señal de control.

La conmutación de lado bajo tiene una limitación: MOSFET rompe el negativo de la carga. Mientras el interruptor está apagado, el negativo de la carga no es igual al `GND` común. Para un simple ventilador de 2 pines, tira o calentador, esto generalmente está bien. Para una carga con tacómetro, cable de señal separado, sensor interno o conexión adicional a otra placa, debe verificar el esquema: a veces es mejor controlar la entrada estándar o usar un método de conmutación diferente.

## Dónde usarlo

El módulo MOSFET es adecuado para cargas CC si se clasifica para su voltaje y corriente:

- ventilador `12V`/`24V`;
- tira LED de un solo color;
- canal de tira RGB estándar;
- calentador `12V`/`24V`;
- pequeño motor CC, si está protegido de picos;
- solenoide, si hay diodo de retorno u otra protección.

Para la tira LED direccionable, MOSFET generalmente no controla los datos. Puede desconectar la potencia de toda la tira, pero los LED individuales se controlan a través de la línea de datos.

Para un accionamiento servo, generalmente no se necesita un módulo MOSFET para controlar la posición: el servo necesita una señal PWM de control separada y alimentación normal.

## Qué verificar al elegir

Antes de comprar o conectar, verifique:

- clasificación de voltaje de carga;
- clasificación de corriente máxima;
- corriente real de su carga;
- ¿funciona la entrada desde `3.3V`;
- ¿es `Rds(on)` en la especificación técnica en el voltaje de puerta necesario;
- ¿necesita lógica activa `HIGH` o `LOW`;
- ¿hay `GND` común;
- ¿hay diodo de retorno para motores/solenoides;
- tamaño del terminal y corriente máxima del terminal;
- espesor de pista del tablero y enfriamiento;
- ¿se necesita disipador de calor;
- ¿hay esquema, especificación técnica o documentación normal.

Si la descripción solo dice "módulo MOSFET para Arduino" sin voltaje, corriente, esquema y tipo MOSFET, no puede elegir un módulo así para un calentador o tira LED larga.

## MOSFET de nivel lógico 3.3V

Muchos controladores modernos funcionan con lógica `3.3V`: ESP32, RP2040, muchos STM32.

No todos los MOSFET se abren completamente desde `3.3V`. Si no se abre completamente, su resistencia permanece alta y se calienta.

Términos importantes:

- `Vgs(th)` - umbral donde MOSFET comienza a abrirse;
- `Rds(on)` - resistencia del canal abierto;
- MOSFET de nivel lógico - MOSFET clasificado para control desde niveles lógicos.

Error común: ver en la especificación técnica `Vgs(th) = 2V` y decidir que el MOSFET funciona bien desde `3.3V`. Eso no es así. `Vgs(th)` no significa "completamente abierto". Debe verificar `Rds(on)` en `2.5V`, `3.3V`, `4.5V` o `5V`, según el controlador.

Para ESP32/RP2040, es mejor elegir un módulo que explícitamente indique compatibilidad de control `3.3V`, o donde el circuito de entrada lo proporcione. Si la tabla tiene `Rds(on)` solo en `10V`, y no hay datos en `2.5V`/`3.3V`/`4.5V`, ese módulo es sospechoso para un controlador `3.3V`.

## Corriente y calentamiento

Un MOSFET en estado abierto aún tiene resistencia. Se genera calor en él.

Cuanto mayor sea la corriente, más importante:

- bajo `Rds(on)`;
- área de cobre normal en la placa;
- terminales de tamaño apropiado;
- disipador de calor, si es necesario;
- ventilación de la carcasa;
- margen de corriente;
- verificación de temperatura después de operación real.

La marca "100A MOSFET" en el paquete de transistores no significa que un pequeño módulo con pistas delgadas y terminales baratos aguantará `100A`. El límite real es a menudo la placa, bloque de terminales, cable, unión de soldadura y enfriamiento.

Si el módulo MOSFET está tan caliente que es difícil de sostener en la mano, esa es una razón para detenerse y recalcular la corriente, el enfriamiento y la calidad de la conexión.

## Motores, ventiladores y solenoides

Las cargas inductivas pueden producir picos de voltaje cuando se apagan.

Tales cargas incluyen:

- motores CC;
- ventiladores;
- solenoides;
- relés;
- electroimanes.

A menudo necesitan protección:

- diodo de retorno;
- diodo TVS;
- controlador listo para usar con protección;
- módulo donde la protección ya está instalada.

Si el módulo solo se clasifica para tira LED o carga resistiva, no puede asumir automáticamente que es seguro para un motor o solenoide.

Para un calentador, generalmente no se necesita diodo de retorno, porque el calentador es cercano a una carga resistiva. Pero para un calentador, la corriente, los terminales, el fusible y la protección térmica independiente son más importantes.

## Control PWM

Un módulo MOSFET se puede usar no solo para encendido/apagado, sino también para regulación de potencia PWM.

Ejemplos típicos:

- brillo de tira LED;
- velocidad de ventilador CC simple;
- potencia de calentador de bajo voltaje.

Pero PWM no siempre es lo mismo:

- el ventilador PWM de 4 pines se controla mejor con un pin PWM separado del ventilador, no cortando potencia;
- el calentador generalmente no requiere frecuencia PWM alta;
- una frecuencia demasiado alta puede aumentar el calentamiento del MOSFET;
- una frecuencia demasiado baja puede causar parpadeo LED o ruido del motor.

La elección de la frecuencia depende de la carga, el módulo y el firmware.

## El módulo MOSFET no es para 110-230V AC

Los módulos MOSFET estándar para Arduino/ESP32 están diseñados para cargas CC: `5V`, `12V`, `24V`, a veces más si se especifica explícitamente.

No se pueden usar como interruptor para voltaje de la red `110-230V AC`.

Para carga de red necesita soluciones diferentes:

- relé o SSR clasificado específicamente para carga AC;
- terminales normales;
- fusible;
- carcasa;
- aislamiento;
- conexión a tierra donde sea necesario;
- comprensión de la seguridad eléctrica.

Si no está seguro de que el módulo esté destinado al voltaje de la red, no lo conecte a la red.

## Qué verificar después de conectar

Antes de la operación a largo plazo, verifique:

- la carga obtiene el voltaje correcto;
- el controlador y la fuente de alimentación tienen `GND` común;
- la señal de control realmente enciende y apaga la carga;
- el módulo MOSFET no se calienta excesivamente;
- los terminales no se calientan;
- los cables son adecuados para la corriente;
- PWM funciona sin ruido extraño, parpadeo o reinicios;
- la carga realmente está apagada cuando el comando está apagado;
- para motor/solenoide hay protección contra picos;
- para calentador hay fusible y protección térmica independiente.

Haga la primera prueba de carga pesada brevemente y bajo observación.

## Errores comunes

- alimentación de carga desde GPIO;
- olvidar tierra común;
- elegir módulo solo por el bonito número de corriente en el nombre;
- no verificar operación desde lógica `3.3V`;
- usar MOSFET que no se abre completamente;
- conectar motor o solenoide sin protección de retorno;
- conectar tira LED larga a través de terminales débiles;
- usar módulo MOSFET CC para `110-230V AC`;
- no verificar calentamiento del módulo en carcasa cerrada;
- pensar que el módulo MOSFET mismo limita la corriente de carga.

## La idea principal

Un módulo MOSFET es un conmutador de potencia controlado para cargas CC. No crea potencia ni alimenta la carga desde el controlador. Solo abre o cierra el camino de la corriente desde la fuente de alimentación.

Verifique voltaje, corriente, compatibilidad con lógica `3.3V`/`5V`, `GND` común, calentamiento, terminales y protección para cargas inductivas. Para voltaje de la red, el módulo MOSFET estándar Arduino/ESP32 no es adecuado.

## Materiales de referencia

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - ejemplo de módulo MOSFET listo para usar de lado bajo, conexión de carga, límites térmicos del tablero y diodo de retorno.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - ejemplo de cómo el fabricante especifica voltaje, corriente, circuito de lado bajo, MOSFET y limitaciones del tablero.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - explicación práctica de por qué los motores, solenoides y LED potentes no se pueden conectar directamente a GPIO y por qué se necesita protección contra picos.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - selección de MOSFET por `Vgs`, `Rds(on)` y nivel de control lógico.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - explicación de MOSFET de nivel lógico y control desde microcontrolador.
