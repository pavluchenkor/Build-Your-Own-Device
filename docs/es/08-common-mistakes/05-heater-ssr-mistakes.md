# Errores de calentador y SSR

El calentador es la carga más peligrosa en un dispositivo DIY simple.

Un ventilador podría no inicia. Un sensor podría dar lecturas incorrectas. Pero un calentador con un error puede sobrecalentar la carcasa, derretir plástico, dañar cableado o crear riesgo de fuego.

Si el dispositivo tiene 110-230V AC y no entiendes seguridad eléctrica, la acción correcta es detener y pedir ayuda a un especialista.

## Síntomas

Signos peligrosos:

- SSR se calienta significativamente;
- el calentador no se apagará;
- la temperatura sube aunque el comando es off;
- la temperatura sube demasiado rápido o de forma irracional;
- el sensor de temperatura muestra valor incorrecto;
- terminal oscurecido;
- cable o conector se calientan;
- el disyuntor o fusible disparan;
- la carcasa huele a plástico o quemado;
- el dispositivo es peligroso al toque;
- el calentamiento continúa después de error del controlador.

Si el calentador no se comporta como se espera, apaga el poder.

## AC SSR y DC SSR mezclados

Los SSRs vienen para diferentes tipos de carga.

AC SSR es para corriente alterna. DC SSR es para corriente directa.

Error:

- AC SSR puesto en calentador DC;
- DC SSR puesto en 230V AC;
- comprado "SSR 40A" sin entender qué está escrito en la carcasa.

El tipo SSR incorrecto podría no apagar la carga o funcionar peligrosamente.

Antes de conectar verifica:

- tipo de salida: AC o DC;
- voltaje de carga permitido;
- corriente permitida;
- voltaje de entrada de control;
- diagrama de conexión del fabricante;
- si se necesita disipador de calor.

## SSR sin disipador de calor

El SSR se calienta durante la operación.

Incluso si la carcasa dice corriente grande, no significa que el relé lo aguantará sin disipador de calor en una carcasa cerrada.

Verifica:

- corriente de carga;
- caída de voltaje a través de SSR;
- potencia disipada;
- requisitos del disipador de calor;
- temperatura de carcasa de SSR después de operación;
- ¿hay flujo de aire?

Si SSR está tan caliente que es difícil sostener a mano, esta es razón para detener y averiguar.

## MOSFET para 110-230V AC

Los módulos MOSFET normales para Arduino/ESP32 son usualmente para cargas DC: 12V o 24V.

No pueden ser usados como simple interruptor para AC mains 110-230V.

Para carga de mains necesitas componentes diferentes, aislamiento diferente, terminales diferentes, conexión a tierra, fusibles y entendimiento de seguridad eléctrica.

Si no estás seguro de que el módulo seleccionado está diseñado para carga de mains, no lo conectes a mains.

## Sin fusible

Un fusible no hace el dispositivo completamente seguro, pero limita las consecuencias de algunas fallas.

Malas ideas:

- "Lo agregaré después";
- "la fuente de alimentación se protegerá a sí misma";
- "mi calentador es pequeño";
- "si el fusible se quema pondré uno más grande".

El fusible se selecciona para el circuito, cableado y carga. No puede ser aumentado solo porque dispara.

Si el fusible dispara, encuentra la causa.

## Sin protección térmica independiente

Firmware y sensor de temperatura no son la única protección.

Para calentador, protección de hardware independiente es útil:

- termostato;
- fusible térmico;
- interruptor bimetálico;
- corte de potencia de calentador de emergencia separado.

Tal protección debe funcionar independientemente del controlador y firmware.

Si el controlador se cuelga, pin se cuelga en estado on, SSR falla o sensor se desconecta, la protección de hardware podría ser la última línea de defensa.

## Sensor de temperatura mal montado

El calentador se controla por retroalimentación del sensor.

Si el sensor:

- se desconecta;
- está mal presionado;
- está en lugar incorrecto;
- sin contacto térmico;
- muestra temperatura de aire en lugar de calentador;
- tipo incorrecto seleccionado en firmware;

el controlador podría continuar calentando porque ve temperatura incorrecta.

El contacto térmico pobre es uno de los errores más peligrosos en sistemas de calefacción.

## Potencia incorrecta del calentador

La potencia del calentador debe ser calculada antes de conectar.

Ejemplo:

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> aproximadamente 1.3A
```

Para calentadores de bajo voltaje poderosos la corriente rápidamente se hace grande. Esto requiere cables apropiados, terminales, MOSFET/SSR y fuente de alimentación.

Para calentadores de mains la corriente es menor pero el peligro de choque es mucho mayor.

## Terminales y cables débiles

Un terminal que "de alguna forma sostiene" puede calentarse bajo corriente.

Razones:

- contacto pobre;
- aislamiento apretado;
- cable demasiado delgado;
- terminal no clasificado para corriente;
- cable trenzado sin ferrule deshilachado;
- tornillo aflojado por calor y vibración.

Terminal oscurecido, olor, calentamiento o plástico ablandándose alrededor es razón para apagar dispositivo.

## Qué no hacer

No puedes:

- sostener abierta parte de mains bajo potencia;
- cambiar cables bajo potencia;
- usar módulo MOSFET de Arduino para 230V AC;
- usar SSR sin disipador de calor si se requiere;
- deshabilitar protección térmica;
- cortocircuitar el termostato de emergencia;
- aumentar fusible "para que no dispare";
- dejar calentador desatendido en primera prueba;
- usar montaje PLA cerca del calentador.

## Qué verificar

Antes del primer calentamiento:

1. Voltaje del calentador.
2. Potencia y corriente.
3. Tipo de interruptor de potencia: MOSFET, AC SSR, DC SSR, relé.
4. Margen de corriente.
5. Disipador de calor de SSR o MOSFET, si se necesita.
6. Fusible.
7. Conexión a tierra, si se requiere.
8. Terminales y cables.
9. Montaje del sensor de temperatura.
10. `sensor_type` correcto en firmware.
11. `min_temp` y `max_temp`.
12. Protección térmica de hardware independiente.
13. Comportamiento cuando el controlador está off.
14. Temperatura terminal y SSR después de breve prueba.

## Puntos clave

- El calentador no puede ser probado como una carga ordinaria pequeña.
- AC SSR y DC SSR son dispositivos diferentes.
- SSR a menudo requiere disipador de calor.
- Módulo MOSFET para cargas DC no funciona para 110-230V AC.
- El sensor de temperatura debe ser montado firmemente en lugar correcto.
- La protección térmica de hardware debe ser independiente del firmware.
- Si hay olor, calentamiento terminal o comportamiento de calentador inusual, apaga el poder.

## Referencias

- [Referencia de configuración de Klipper: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - verificación oficial de calentador y sensor de temperatura verificando tasa de subida y error acumulado.
- [Tom's Hardware: Cómo arreglar thermal runaway de impresora 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - verificar termistor, cartucho de calentamiento, ventilador, potencia y cableado durante thermal runaway.
- [Configuración de Marlin: Rangos de temperatura y protección térmica](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`, `MAXTEMP` y protección térmica como parte de seguridad.
- [Selección de disipador de calor SSR de Sensata/Crydom](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - por qué SSR requiere cálculo térmico y disipador de calor a corrientes significativas.
- [Omron: Fundamentos de relé de estado sólido](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - información básica sobre SSR, aplicación, calentamiento y diferencias de relés mecánicos.
