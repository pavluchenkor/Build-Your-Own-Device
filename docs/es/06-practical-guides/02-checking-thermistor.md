# Verificación de una termistancia

Una termistancia es un sensor de temperatura que cambia de resistencia cuando se calienta o enfría.

En impresoras 3D, secadores y calentadores de cámara, el tipo más común es una termistancia NTC clasificada en `100K`. NTC significa que la resistencia disminuye a medida que la temperatura aumenta.

Debe verificar una termistancia si:

- las lecturas de temperatura son irreales;
- la temperatura oscila;
- el calentador entra en estado de error;
- el firmware reporta `MINTEMP`, `MAXTEMP`, `Thermal runaway` o similar;
- la termistancia fue reemplazada, movida o recrimped;
- el dispositivo fue ensamblado por primera vez.

## Primero, apague la energía

La resistencia se mide solo en circuitos desenergizados.

Antes de verificar:

1. Apague el dispositivo.
2. Desconecte la alimentación de la red o fuente de alimentación.
3. Espere a que el calentador se enfríe.
4. Desconecte la termistancia de la placa si necesita medir el sensor mismo.

Si mide la resistencia mientras la termistancia está conectada a la placa, las lecturas pueden estar distorsionadas por otros componentes del circuito. Si mide la resistencia con la energía encendida, puede dañar el multímetro o la placa.

## Qué debe tener una NTC 100K

Una NTC típica `100K` tiene una resistencia de aproximadamente `100 kOhm` a `25°C`.

Esto no significa que el multímetro siempre mostrará exactamente `100.0 kOhm`.

Es normal que la lectura difiera ligeramente a la temperatura ambiente:

- en una habitación fría, la resistencia será más alta;
- en una habitación cálida, la resistencia será más baja;
- diferentes tipos de termistancias tienen diferentes tablas;
- los cables largos y los malos contactos pueden afectar la medición.

La verificación principal es simple: una NTC 100K a temperatura ambiente debe leer decenas o alrededor de cien kiloohmios, no `OL` u `OL`.

## Medición con un multímetro

Establezca su multímetro en modo de resistencia `Ohm`.

Si su multímetro no es automático, seleccione un rango superior a `100 kOhm`, como `200 kOhm` o `2 MOhm`.

Luego:

1. Desconecte la termistancia de la placa.
2. Toque las sondas del multímetro a los dos hilos de termistancia.
3. No sostenga los extremos metálicos de las sondas e hilos simultáneamente: su cuerpo puede agregar resistencia paralela.
4. Espere a que la lectura se estabilice.
5. Registre el valor.

![Multímetro digital para medir la resistencia de termistancia](../../img/05-tools/02-digital-multimeter.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Electricista jubilado, CC0 Dominio público*

## Prueba de calor rápida con su dedo

Después de medir a temperatura ambiente, puede calentar cuidadosamente el sensor con los dedos.

Para una termistancia NTC, la resistencia debe comenzar a disminuir.

Por ejemplo:

- fue alrededor de `100 kOhm` a temperatura ambiente;
- se hizo más baja después del calentamiento del dedo.

Los números exactos no importan aquí. La dirección del cambio importa.

Si la resistencia no cambia en absoluto, salta aleatoriamente o desaparece cuando el hilo se mueve, el problema puede estar en el sensor, hilo, crimp o conector.

## Ruptura y cortocircuito

Un multímetro ayuda a distinguir rápidamente un sensor normal de una falla evidente.

Signos típicos:

- `OL`, `sobre límite`, `1` en el lado izquierdo de la pantalla, o resistencia infinita - circuito abierto;
- casi `0 Ohm` - cortocircuito;
- el valor salta significativamente cuando el hilo se mueve - mal contacto o conductor roto;
- valor alrededor de `100 kOhm` a temperatura ambiente y disminuye con calentamiento - se parece a una NTC 100K sana.

Diferentes multímetros usan diferentes designaciones para circuito abierto. Generalmente es `OL` o un valor más allá del rango seleccionado.

## Verificación del cableado

La termistancia puede estar bien mientras el problema está en el cableado.

Verificar:

- el conector está completamente insertado;
- los pines no han salido de la carcasa del conector;
- los hilos no están deshilachados;
- sin daño de aislamiento cerca del calentador;
- sin tensión de alambre cuando los ejes o la cubierta se mueven;
- el cable no corre directamente junto a los hilos de potencia del calentador sin razón;
- la ubicación del crimp es segura.

Si las lecturas cambian cuando mueve el hilo, esto no es una "característica del sensor". Este es un problema de contacto que debe repararse antes de encender el calentador.

## Verificación en Klipper

En Klipper, el tipo de sensor se establece en la configuración.

Ejemplo para un sensor de temperatura de cámara típico:

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

Ejemplo para un calentador de cámara:

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

Los nombres de pin aquí son típicos. En un dispositivo real, verifique la disposición de su placa.

Importante: `sensor_type` debe coincidir con el sensor real. Dos termistancias pueden parecer idénticas pero tener diferentes tablas. Si elige el tipo incorrecto, la temperatura puede ser notoriamente inexacta, especialmente en el rango de calentamiento de trabajo.

## Qué observar en la interfaz

Después de conectar, verifique la temperatura en la interfaz Klipper, Mainsail, Fluidd u otra interfaz de usuario.

A temperatura ambiente, la lectura debería estar cerca de la temperatura real de la habitación.

Signos sospechosos:

- lee significativamente más bajo que la realidad;
- lee significativamente más alto que la realidad;
- la temperatura salta por docenas de grados;
- la temperatura cambia cuando mueve el hilo;
- la temperatura no sube cuando la calefacción está encendida;
- la temperatura sube muy lentamente;
- la temperatura sube aunque el calentador está apagado.

Si el sensor está en el calentador, no inicie calentamiento prolongado hasta que las lecturas parezcan razonables.

## Errores de firmware

En el firmware de la impresora 3D, los errores de temperatura no son un problema menor sino parte de la seguridad.

Para un circuito típico con una NTC y pull-up en placa:

- la rotura del sensor a menudo parece demasiada baja temperatura o `MINTEMP`;
- el cortocircuito a menudo parece demasiada alta temperatura o `MAXTEMP`;
- el mal contacto térmico puede causar `Heating failed` o `Thermal runaway`;
- el fuerte enfriamiento del bloque de calentamiento puede causar un error porque la temperatura sube demasiado lentamente o no se mantiene.

Los nombres de error dependen del firmware, pero el significado es el mismo: el controlador ya no confía en la temperatura o ve que la calefacción no funciona como se esperaba.

No deshabilite la protección térmica solo para "verificar". Si la protección se activa, busque primero la causa en el sensor, cableado, montaje, calentador, configuración PID y enfriamiento.

## Contacto térmico

Una termistancia funcionalmente eléctrica no garantiza una temperatura correcta.

El sensor debe transferir bien el calor de la parte que está midiendo.

Verificar:

- el sensor se asienta completamente en la manga o agujero;
- sujeción normal del heno;
- sin espacio entre sensor y superficie;
- la pasta térmica no se ha secado ni descamado si se usa;
- los sujetadores no están sueltos;
- el sensor no ha salido de su asiento;
- los hilos no tiran del sensor.

El mal contacto es peligroso porque el sensor lee una temperatura más baja que la realidad. El controlador continúa calentando mientras la parte real puede ya estar sobrecalentada.

## Mini-lista de verificación

Antes del primer calentamiento:

- la resistencia de la termistancia se ve como se esperaba;
- la resistencia NTC disminuye con calentamiento de dedos;
- sin circuito abierto o cortocircuito;
- los hilos no reaccionan con saltos cuando se mueven;
- el conector está insertado correctamente;
- el `sensor_type` correcto está elegido en el firmware;
- la temperatura en la interfaz parece temperatura ambiente;
- el sensor está montado de forma segura en la ubicación correcta;
- `min_temp` y `max_temp` se establecen razonablemente para el dispositivo.

## Errores comunes

- medir resistencia con la placa bajo tensión;
- no desconectar el sensor de la placa y obtener valores extraños;
- confundir una termistancia `100K` con otro tipo de sensor;
- elegir el `sensor_type` incorrecto;
- ver `OL` y pensar que significa "100K";
- asumir que cualquier NTC 100K es idéntica;
- dejar la termistancia suelta junto al calentador;
- apretar demasiado una termistancia de vidrio con un tornillo;
- tirar del hilo para que el sensor salga de la manga;
- deshabilitar la protección térmica en lugar de corregir la causa del error.

## Puntos clave

- La resistencia se mide solo en circuitos desenergizados.
- Una NTC 100K típica es aproximadamente `100 kOhm` a `25°C`.
- Cuando se calienta, la resistencia NTC disminuye.
- `OL` generalmente significa circuito abierto, casi `0 Ohm` significa cortocircuito.
- El firmware debe tener el tipo de sensor correcto seleccionado.
- El buen contacto térmico es tan importante como el cableado funcional.
- No inicie el calentador si las lecturas de temperatura se ven mal.

## Lecturas relacionadas

- [Referencia de configuración de Klipper: Sensores de temperatura](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - parámetros oficiales `sensor_type`, `sensor_pin`, `pullup_resistor` y lista de termistancias comunes.
- [Configuración de Marlin: Rangos de temperatura y protección térmica](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - explicación de `MINTEMP`, `MAXTEMP` y protección contra descontrol térmico.
- [Solución de problemas de Marlin: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - causas típicas de errores de calentamiento: termistancia, subida lenta de temperatura, descontrol térmico.
- [RepRap Wiki: Termistancia](https://reprap.org/wiki/Thermistor) - descripción básica de termistancias NTC/PTC y verificación de resistencia a temperatura ambiente.
- [Fluke: Cómo medir la resistencia con un multímetro digital](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - procedimiento seguro para medir la resistencia con un multímetro digital.
