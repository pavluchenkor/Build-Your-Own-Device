# Multímetro

Un multímetro es la principal herramienta de diagnóstico de primera línea.

Puede verificar con él:

- si hay potencia presente;
- si el voltaje es correcto;
- dónde están más y menos;
- si un cable está roto;
- si un fusible está intacto;
- si un termistor parece funcional;
- si hay caída de voltaje bajo carga.

Pero es fácil cometer errores con un multímetro si confunde los modos. Los errores más peligrosos involucran medir corriente y voltaje de corriente alterna.

## Sondas y Puertos

Un multímetro típicamente tiene:

- `COM` - puerto común, donde casi siempre inserta la sonda negra;
- `V/Ohm/mA` o similar - para voltaje, resistencia, continuidad y pequeñas corrientes;
- `10A` o `A` - puerto separado para corriente grande.

Antes de medir, siempre verifique:

- a qué puerto está inserto la sonda roja;
- qué modo está seleccionado;
- exactamente qué está a punto de medir.

Un error muy común: después de medir corriente, olvida mover la sonda de `A` de vuelta a `V/Ohm`, luego intenta medir voltaje. Esto puede causar un cortocircuito.

## Medir Voltaje DC

DC es voltaje directo (constante). En nuestros dispositivos, esto es generalmente:

- `3.3V`;
- `5V`;
- `12V`;
- `24V`.

Procedimiento:

1. Sonda negra en `COM`.
2. Sonda roja en el puerto `V`.
3. Seleccione modo de voltaje DC: generalmente `V` con una línea recta.
4. Sonda negra en negativo o `GND`.
5. Sonda roja en positivo.
6. Lea la pantalla.

Si aparece un signo menos antes del número en la pantalla, las sondas están intercambiadas. Esto es útil: puede determinar la polaridad de esta manera.

![Multímetro digital con sondas](../../img/05-tools/02-digital-multimeter.jpg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Dónde Medir Voltaje

No se limite a la salida de la fuente de alimentación.

Verificar:

- en los terminales de la fuente de alimentación;
- en la entrada de la placa;
- en los terminales de la carga;
- en un módulo DC-DC;
- en el ventilador;
- en un servo;
- en una tira LED.

Si la fuente de alimentación muestra 24V pero la carga muestra notablemente menos, busque caída en los cables, terminales o conectores.

Para diagnóstico de fuente de alimentación, es importante medir bajo carga, no solo en ralentí.

## Medir Voltaje AC

AC es voltaje alterno, como 110-230V de la corriente alterna.

El voltaje de la red es peligroso.

Si no entiende lo que está haciendo, no mida piezas abiertas de corriente alterna con un multímetro. Es mejor usar módulos seguros listos, terminales cerrados y ayuda de especialistas.

Si mide, necesita:

- multímetro con categoría de seguridad **CAT II** o **CAT III** — esto está escrito en el cuerpo del dispositivo junto al voltaje, por ejemplo `CAT II 600V`. CAT I no es adecuado para la red del hogar. CAT III y CAT IV proporcionan margen adicional para instalaciones más complejas;
- sondas que funcionen correctamente con una categoría no inferior a la del multímetro;
- manos secas;
- ensamblaje cerrado y estable;
- comprensión de dónde están la fase y el neutro;
- ningún punto de contacto abierto accidental.

Para la mayoría de tareas que involucran electrónica de bajo voltaje, las mediciones de CC son suficientes.

## Verificación de Continuidad

La continuidad muestra si dos puntos están eléctricamente conectados.

Es útil para verificar:

- si un cable está intacto;
- si `GND` está conectado;
- si un cable no está roto;
- si un botón funciona;
- si un fusible está intacto;
- si los contactos vecinos están cortocircuitados.

Procedimiento:

1. Apague la potencia.
2. Establezca el multímetro en modo de continuidad: generalmente un icono de sonido o símbolo de diodo.
3. Toque las sondas entre sí - debe haber un pitido.
4. Toque los dos puntos que desea verificar.
5. Si pita, hay una conexión conductora entre los puntos.

La verificación de continuidad se realiza en un circuito desenergizado.

## Resistencia

La resistencia se mide en ohmios.

Para nuestras tareas, esto es necesario para:

- verificar un termistor;
- verificar cable roto;
- verificar un fusible;
- determinar si hay un cortocircuito;
- verificar una resistencia.

Importante: la resistencia solo se mide en un circuito desenergizado.

Si mide resistencia en una placa energizada, puede obtener lecturas incorrectas o dañar el multímetro.

## Prueba de Termistor

Para un NTC típico de `100K` a temperatura ambiente, espere decenas o alrededor de `100 kOhm`.

Si el multímetro muestra:

- `OL` o infinito - probablemente circuito abierto;
- casi `0 Ohm` - probablemente cortocircuito;
- valor fluctuando mucho cuando mueve el cable - contacto pobre;
- la resistencia disminuye cuando se calienta con los dedos - parece un NTC vivo.

Los valores exactos dependen del tipo de termistor y la temperatura.

## Medir Corriente

Medir corriente es más peligroso que medir voltaje.

El voltaje se mide en paralelo: las sondas tocan dos puntos.

La corriente se mide en serie: debe romper el circuito y conectar el multímetro en línea para que la corriente fluya a través del dispositivo.

Error: coloque el multímetro en modo de corriente y toque las sondas al más y menos de la fuente de alimentación. Eso es casi un cortocircuito a través del multímetro.

Para un principiante es mejor:

- primero calcular la corriente a partir de la potencia;
- usar medidores de vatios listos/medidor de potencia USB/medidor de potencia DC;
- medir corriente solo si entiende cómo conectar el multímetro en serie;
- comenzar con el rango correcto y puerto correcto.

## Comprobación de Fusible

Verifique el fusible en un circuito desenergizado.

Métodos:

- continuidad;
- medición de resistencia.

Un buen fusible generalmente muestra continuidad y tiene resistencia muy baja.

Un fusible quemado generalmente no muestra continuidad.

Si un fusible se quemó, no puede simplemente instalar uno con clasificación más alta. Primero encuentre la causa.

## Cómo No Quemar el Multímetro

Reglas mínimas:

- verifique el modo antes de medir;
- verifique el puerto de sonda roja antes de medir;
- no mida resistencia en un circuito energizado;
- no mida corriente como voltaje;
- no ingrese a 110-230V AC sin comprender la seguridad;
- comience con un rango más alto si el multímetro no es autorango;
- use sondas que funcionen;
- no toque las puntas de metal con los dedos.

## Escenarios Prácticos

Verificar fuente de alimentación de 24V:

1. Modo de voltaje DC.
2. Sonda negra en negativo.
3. Sonda roja en positivo.
4. Debe leer alrededor de 24V.

Verificar un ventilador:

1. Mida voltaje en el conector del ventilador.
2. Verifique la polaridad.
3. Verifique voltaje durante el inicio.

Verificar cable roto:

1. Desconecte la potencia.
2. Modo de continuidad.
3. Sondas en ambos extremos del cable.
4. Sin pitido - posible circuito abierto.

Verificar cortocircuito entre `+` y `GND`:

1. Desconecte la potencia.
2. Verifique la continuidad entre `+` y `GND`.
3. Si pita donde no debería, busque un cortocircuito.

## Lo Esencial

- Para voltaje DC, use modo `V` con una línea recta.
- Resistencia y continuidad solo se realizan en circuitos desenergizados.
- La corriente se mide en serie, no en paralelo.
- Después de medir corriente, mueva la sonda de `A` de vuelta al puerto normal `V/Ohm`.
- El voltaje de red es peligroso; no mida piezas abiertas de 110-230V sin comprender la seguridad.
- Un multímetro bajo carga a menudo revela problemas invisibles cuando está en ralentí.

## Materiales de Referencia

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - guía práctica para voltaje, corriente, resistencia, continuidad y puertos de multímetro.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - medición segura de resistencia.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - medición de voltaje AC y orden de conexión de sondas.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - verificación de continuidad y búsqueda de circuito abierto.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - por qué los puertos de entrada de corriente necesitan fusibles adecuados con voltaje correcto y clasificación de interrupción.
