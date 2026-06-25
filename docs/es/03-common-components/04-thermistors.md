# Termistores

Un termistor es un sensor de temperatura cuya resistencia cambia cuando se calienta o se enfría. En impresoras 3D, secadores y pequeños dispositivos de calefacción, a menudo se utiliza como retroalimentación para controlar el calentador.

La opción más común en la comunidad de impresión 3D es el termistor NTC `100K`. NTC significa que cuando aumenta la temperatura, la resistencia disminuye. `100K` generalmente significa alrededor de `100 kOhm` a `25°C`.

## Dónde se Utiliza

Los termistores se utilizan para medir la temperatura de:

- hotend;
- heated bed;
- printer chamber;
- filament dryer;
- air duct;
- heating module;
- área de electrónica, si se necesita protección simple contra sobrecalentamiento.

En un dispositivo con un calentador, un termistor no es un sensor decorativo. Determina cuándo el controlador reduce la potencia, desactiva la calefacción o se detiene con un error.

## NTC 100K, Beta y Tablas de Búsqueda

Los termistores diferentes pueden verse iguales pero tienen características diferentes.

Parámetros importantes:

- resistencia en `100 kOhm`, por ejemplo `100 kOhm`;
- type: NTC or PTC;
- Beta, for example `3950K`;
- resistance/temperature lookup table;
- operating temperature range;
- accuracy;
- package: glass bead, cartridge, screw sensor, sheath;
- wire insulation.

Si el firmware selecciona el tipo de sensor incorrecto, la temperatura se mostrará incorrectamente. El error puede ser pequeño a temperatura ambiente y peligroso a temperatura de funcionamiento.

Por lo tanto, la frase "termistor 100K" no siempre es suficiente. Para el firmware, importa un modelo específico o al menos la Beta/tabla correcta.

## Cómo el Controlador Mide la Temperatura

Un termistor se conecta normalmente a una entrada analógica a través de un divisor de voltaje con una resistencia pull-up. El controlador mide voltaje, lo convierte a resistencia, luego usa una tabla de búsqueda o fórmula para obtener la temperatura.

![Divisor de voltaje con termistor para medición de temperatura](../../img/03-common-components/04-thermistor-voltage-divider.svg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Thermistor_potential_divider.svg), Sjlegg, Public Domain*

En Klipper, esto se establece a través de `sensor_type`, `sensor_pin`, a veces `pullup_resistor` o una sección `[thermistor]` personalizada.

En Marlin, el tipo de termistor se selecciona a través de parámetros de configuración de sensor y límites de temperatura.

Para el usuario, lo importante es simple: el firmware debe conocer exactamente el tipo de sensor que está instalado en el dispositivo.

## Circuito Abierto y Cortocircuito

Un termistor y su cableado pueden fallar.

Síntomas típicos:

- broken wire;
- poor connector contact;
- wires short together;
- damaged insulation;
- el sensor se salió de la funda;
- alambre desgastado en una parte móvil;
- El sensor muestra la temperatura ambiente aunque se esté calentando.

El firmware generalmente tiene protecciones como `MINTEMP`, `MAXTEMP`, verificación de calefacción y protección contra fuga térmica. Pero estas protecciones solo funcionan si el sensor y el firmware se configuran correctamente, y la parte de potencia realmente se puede desconectar.

Si un sensor se cae del calentador pero permanece eléctricamente conectado, esto es especialmente peligroso: el firmware puede ver "temperatura baja" y seguir calentando.

## Contacto Térmico

El montaje del termistor es a menudo más importante de lo que parece.

El sensor debe medir la temperatura del lugar que realmente necesitas controlar. Para un hotend, es el bloque de calefacción. Para una cama, es la superficie o un lugar relacionado con la temperatura real de la cama. Para un calentador de aire, es un punto elegido por lógica de seguridad y control.

El contacto térmico se ve afectado por:

- sensor pressure;
- thermal paste;
- mounting hole;
- sheath;
- screw mounting;
- gap;
- material alrededor del sensor;
- wire condition;
- contamination or dried paste;
- vibraciones y montaje flojo.

Si un termistor apenas toca una parte de lado, puede responder lentamente y mostrar la temperatura incorrecta. El controlador PID recibe información retrasada, y la temperatura puede excederse o exceder el objetivo.

## Paquete de Sensor

Los termistores vienen en diferentes paquetes.

Glass bead:

- cheap;
- tiny;
- requires careful mounting;
- Fácil de dañar el cable o el aislamiento.

Cartridge thermistor:

- más fácil de insertar en el orificio del bloque calefactor;
- normalmente mecánicamente más estable;
- importante hacer coincidir el diámetro y la longitud.

Screw thermistor:

- se monta fácilmente en una superficie metálica;
- puede dar un buen contacto si se instala correctamente;
- No debe apretar demasiado ni dañar el cable.

Sensor in sheath:

- conveniente para aire, líquido o recinto;
- responde más lentamente si la vaina es masiva;
- El punto de instalación adecuado es importante.

La elección del paquete depende de lo que se mida y cómo se servirá el sensor.

## Comprobación con Multímetro

La verificación básica se puede hacer con un multímetro en modo de resistencia. El procedimiento detallado se encuentra en el artículo práctico: [Checking a thermistor](../06-practical-guides/02-checking-thermistor.md).

Para un NTC típico `100K` a temperatura ambiente alrededor de `25°C`, esperas alrededor de `100 kOhm`. El valor exacto depende de la temperatura y la tolerancia.

Cuando se calienta con los dedos, la resistencia NTC debe disminuir. Si el multímetro muestra circuito abierto, cortocircuito, o el valor salta cuando mueves el cable, primero revisa el conector y el cableado.

La comprobación con multímetro no reemplaza la calibración y no prueba precisión a `200°C`, pero muestra rápidamente un circuito abierto, cortocircuito o tipo de sensor incorrecto obvio.

## Qué Verificar Antes de Comprar

Antes de comprar un termistor, verifica:

- resistance at `25°C`;
- Beta or exact model;
- compatibilidad con firmware;
- operating temperature range;
- sensor package;
- longitud y material del cable;
- connector type;
- mounting method;
- whether you need a cartridge, screw, sheath or glass bead;
- si el sensor se adapta a su bloque calefactor o al lugar de instalación;
- Disponibilidad de descripción técnica o información clara.

Para un hotend, es mejor obtener un sensor que se ajuste mecánicamente al bloque específico. Para una cámara o secador, la ubicación de instalación, la protección del cable y la estabilidad de la medición en el flujo de aire son más importantes.

## Típicos Errores

- Se seleccionó `sensor_type` incorrecto;
- pensar que cualquier termistor `100K` es igual;
- el sensor está mal presionado;
- no proper thermal contact;
- el sensor se salió de la funda;
- cable rozado o roto en el cuerpo del sensor;
- el contacto del conector es deficiente;
- cableado innecesario junto a líneas eléctricas;
- el termistor mide el aire pero el controlador cree que mide el calentador;
- firmware configurado sin `max_temp` y `max_temp` razonables;
- calentador encendido sin protección de hardware independiente.

## Punto Principal

Un termistor es retroalimentación para un calentador. Es importante no solo comprar "100K NTC", sino seleccionar el tipo correcto en el firmware, montar el sensor en el lugar correcto y verificar el cableado.

El contacto térmico deficiente o el `sensor_type` incorrecto pueden ser más peligrosos que un sensor completamente muerto, porque el sistema sigue funcionando pero toma decisiones sobre temperatura incorrecta.

## Materiales de Referencia

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - official `sensor_type`, `pullup_resistor`, custom `[thermistor]` and temperature sensors in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - temperature limits, `MINTEMP`, `MAXTEMP` and thermal protection.
- [Vishay: NTC Thermistors](https://www.vishay.com/en/thermistors/ntc/) - NTC thermistor parameters: resistance at `25°C`, Beta, tolerance and operating range.
- [RepRap Europe: Thermistor NTC100K](https://www.reprap-3d-printer.com/product/335-thermistor-ntc100k) - example of typical 3D printer NTC `100K` with Beta `3950` and `100 kOhm` at `25°C`.
- [RepRap Europe: Thermistor Cartridge 100k HT-NTC B3950](https://reprap.eu/produto/?id=1245&nome=Thermistor+Cartridge+100k+HT-NTC+B3950) - example of cartridge thermistor for heating block and mechanical mounting.
