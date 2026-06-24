# Interfaz CAN

CAN es una interfaz de comunicación para múltiples dispositivos en una línea diferencial común. Expansión: `Controller Area Network`.

CAN proviene de la electrónica automotriz e industrial, pero en las impresoras 3D se popularizó para placas de cabezal, MCU remotas y módulos donde se necesita una comunicación más larga y confiable que I2C/SPI.

## Dónde es útil CAN

En impresoras y periféricos similares a iDryer, CAN se usa para:

- placas de cabezal en el extrusor;
- MCU adicional en un bloque remoto;
- reducir el número de cables en el mazo;
- comunicación con filtro CAN, cámara o placas de secador;
- sistema distribuido de múltiples controladores;
- casos donde USB o I2C/SPI largo resultan inconvenientes.

CAN es especialmente útil cuando un nodo está lejos del host o la placa principal, y hay motores, calentadores y otras fuentes de ruido cerca.

## CANH, CANL y GND

Un bus CAN físico típicamente utiliza:

- `CANH`;
- `CANL`;
- a veces `GND` o cable de referencia común;
- alimentación del módulo por separado, si es necesario.

La señal se transmite como la diferencia entre `CANH` y `CANL`. Por eso CAN maneja mejor el ruido que las líneas de señal individual.

Diagrama simplificado:

![Bus CAN de alta velocidad ISO 11898-2 con múltiples nodos y terminadores](../../img/02-controllers/09-can-iso11898-2-network.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png), EE JRW, CC BY-SA 4.0*

Para el cableado, a menudo se usa un par trenzado para `CANH`/`CANL`. `GND` depende del circuito específico, las placas y la documentación, pero en sistemas DIY pequeños, suele ser necesaria una referencia común para un funcionamiento estable y la seguridad de la interfaz.

## Se requiere transceptor CAN

Importante: la compatibilidad con CAN en el microcontrolador y la presencia de CAN en la placa no son lo mismo.

Para que CAN funcione, se necesita:

- microcontrolador con controlador CAN o soporte de firmware adecuado;
- transceptor CAN en la placa;
- conectores `CANH`/`CANL` correctos;
- alimentación del transceptor;
- terminadores;
- firmware compilado para CAN.

Si la hoja de datos del microcontrolador menciona CAN, pero la placa no tiene transceptor, no se puede conectar directamente al bus CAN.

## Topología y terminadores

CAN es un bus. Una buena topología se parece a una línea con nodos conectados mediante ramas cortas.

Normalmente se necesitan dos terminadores de `120 Ohm`:

- uno en un extremo físico del bus;
- otro en el otro extremo físico.

No uno, no tres, ni "en cada placa". Exactamente dos en los extremos.

Si está apagado, en un bus correctamente terminado, un multímetro entre `CANH` y `CANL` suele mostrar alrededor de `60 Ohm`, porque dos resistencias de `120 Ohm` están en paralelo.

Muchas placas tienen un jumper de terminador. Algunas tienen un terminador integrado sin desactivación conveniente. Por eso, antes del montaje, revisa los esquemas de todas las placas del bus.

## Velocidad de transmisión

La velocidad CAN debe coincidir en todos los nodos. En Klipper, CAN suele usar `1000000`, es decir, `1 Mbit/s`, pero el valor específico depende del firmware, la configuración y la longitud del bus.

Si la velocidad de transmisión es diferente, los nodos no podrán comunicarse normalmente.

Para cableado largo o problemático, la velocidad puede ser crítica. Cuanto mayor sea la velocidad, más exigente es el bus respecto a la topología, los terminadores y la calidad del cable.

## CAN en Klipper

En Klipper, CAN se usa como método de comunicación con la MCU.

Un dispositivo en CAN normalmente no se especifica mediante `serial:`. En cambio, la configuración usa `canbus_uuid`:

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

En el lado de Linux, normalmente se necesita una interfaz `can0`. El host debe tener un adaptador CAN:

- adaptador USB-CAN;
- placa en modo puente USB-to-CAN;
- HAT/adaptador para SBC;
- otro circuito compatible.

Klipper tiene una herramienta para encontrar el `canbus_uuid` de nuevos dispositivos no inicializados. Importante entender: si un dispositivo ya está configurado por Klipper, puede que ya no aparezca en la lista como "nuevo".

## Puente USB-to-CAN

Algunas placas pueden flashearse en modo puente USB-to-CAN. Entonces la placa se conecta al host por USB y aparece en Linux como un adaptador CAN.

Esto es conveniente, pero tiene una limitación importante: el modo puente es necesario para comunicarse con un bus CAN real y otros nodos CAN. Si solo tienes una placa cerca del host y no hay un bus CAN real, normalmente es más sencillo usar el modo USB/serial normal.

Además, el puente USB-to-CAN no será visible como `/dev/serial/by-id/...`. Se configura como interfaz CAN y usa `canbus_uuid`, no `serial:`.

## Cuándo está justificado CAN

Vale la pena considerar CAN si:

- necesitas conectar una placa de cabezal;
- necesitas llevar comunicación por un mazo de cables largo;
- necesitas varias MCU remotas;
- quieres reducir cables entre las partes móviles y el gabinete;
- ya tienes infraestructura CAN;
- la placa elegida está bien documentada para Klipper CAN.

CAN puede ser innecesario si:

- la placa está cerca del host;
- solo necesitas una MCU adicional;
- USB funciona de forma estable;
- no tienes experiencia con flasheo, `can0`, terminadores y redes de Linux;
- la placa elegida está poco documentada.

Para un primer controlador adicional simple, USB suele ser más rápido y claro. CAN tiene sentido cuando resuelve un problema real de cableado o distribución de placas.

## CAN no alimenta cargas

CAN es solo comunicación.

Si una placa CAN controla un ventilador, calentador, SSR o servo, aún necesita:

- alimentación de la placa;
- alimentación de la carga;
- MOSFET/driver/SSR;
- fusibles;
- terminales adecuados;
- protección térmica para calentadores;
- carcasa segura.

CAN no reemplaza la electrónica de potencia ni hace que un calentador sea seguro.

## Qué verificar antes de comprar

Antes de comprar una placa CAN, verifica:

- qué microcontrolador se usa;
- si la placa es compatible con Klipper CAN;
- si hay transceptor CAN;
- dónde están `CANH` y `CANL`;
- si hay terminador y cómo habilitarlo;
- qué conector se usa;
- cómo se alimenta la placa;
- cómo se flashea la placa;
- si hay instrucciones para `canbus_uuid`;
- si se necesita un adaptador USB-CAN separado;
- si hay esquema y pinout;
- qué pines y salidas de alimentación están disponibles.

Si el vendedor escribe "CAN" solo porque el chip lo soporta teóricamente, pero la placa no tiene transceptor ni documentación, es una mala elección.

## Errores típicos

- confundido `CANH` y `CANL`;
- olvidado que se requiere transceptor CAN;
- puesto un terminador en lugar de dos;
- habilitados terminadores en cada placa;
- no verificada la resistencia entre `CANH` y `CANL`;
- elegida velocidad de transmisión diferente en los nodos;
- esperado `/dev/serial/by-id` de un puente USB-to-CAN;
- flasheada la placa para USB, pero conectada como CAN;
- flasheada para CAN, pero sin configurar `can0`;
- creada una estrella con ramas largas en lugar de un bus;
- creer que CAN es una forma de alimentar cargas.

## Conclusión clave

CAN es una buena interfaz para MCU remotas, placas de cabezal y sistemas distribuidos dentro de una impresora. Usa un par diferencial `CANH`/`CANL`, requiere transceptores CAN, topología correcta y dos terminadores en los extremos del bus.

Para Klipper, CAN es útil pero más complejo que USB: hay que flashear la placa para CAN, configurar el adaptador/`can0`, encontrar el `canbus_uuid` y verificar el bus físico. Usa CAN donde realmente simplifique el cableado o mejore la robustez de la conexión.

## Materiales relacionados

- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) - documentación oficial de Klipper para CAN: hardware, adaptador de host, `can0`, `canbus_uuid`, terminadores y puente USB-to-CAN.
- [Klipper: CANBUS protocol](https://www.klipper3d.org/CANBUS_protocol.html) - cómo Klipper asigna el ID de nodo CAN y usa `canbus_uuid`.
- [CAN Bus Debugger: CAN Bus Termination Explained](https://www.canbusdebugger.com/articles/can-bus-termination) - explicación práctica de los dos terminadores de `120 Ohm`, la medición de `60 Ohm` y los errores comunes.
- [DigiKey: CAN Bus explained](https://www.digikey.com/en/blog/can-bus-explained) - descripción general de CAN bus, comunicación diferencial y aplicación en sistemas distribuidos.
- [Texas Instruments: Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - descripción básica de la capa física CAN, transceptores y red típica.
