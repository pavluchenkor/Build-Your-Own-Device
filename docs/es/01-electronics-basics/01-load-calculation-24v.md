# Corriente, voltaje y potencia de carga

Antes de conectar un calentador, ventilador, tira LED, accionamiento de servo o cualquier otro módulo, debe entender tres cosas:

- voltaje;
- corriente;
- potencia.

Sin esto, es fácil comprar la fuente de alimentación incorrecta, sobrecalentar el cable, derretir el conector, quemar un módulo MOSFET o conectar la carga al controlador de forma que funcione inestablemente.

## Dónde encontrar los parámetros

El voltaje, la corriente y la potencia generalmente se encuentran:

- en la carcasa del componente;
- en la etiqueta de la fuente de alimentación;
- en la página del producto;
- en la especificación técnica;
- en el manual;
- en el esquema del circuito o diagrama de pines.

Si el parámetro no se especifica, no es un problema menor. Es una razón para detenerse y averiguar exactamente qué está conectando.

Para componentes de periféricos de impresoras 3D, los parámetros típicos se ven así:

- ventilador: `24V 0.2A`;
- calentador: `24V 100W`;
- tira LED: `24V 9.6W/m`;
- accionamiento de servo: `5V`, la corriente depende de la carga;
- placa del controlador: la corriente máxima para cada salida se especifica por separado.

## El voltaje debe coincidir

Una carga está diseñada para un voltaje específico.

Ejemplos:

- el ventilador puede ser `5V`, `12V` o `24V`;
- la tira LED puede ser `5V`, `12V` o `24V`;
- el accionamiento de servo a menudo se clasifica como `5V` o `6V`;
- el calentador puede ser `12V`, `24V` o `110-230V AC`.

Si conecta un ventilador `24V` a `12V`, es posible que no se inicie o funcione débilmente. Si conecta un ventilador `12V` a `24V`, puede fallar rápidamente.

La regla principal:

**el voltaje de la fuente de alimentación debe coincidir con el voltaje de la carga.**

No conecte un dispositivo a un voltaje más alto solo porque el conector se ajusta físicamente.

## La potencia muestra el tamaño de la carga

La potencia muestra cuánta energía consume la carga o convierte en trabajo, calor, luz o movimiento.

La potencia se mide en vatios: `W`.

Ejemplos:

- `24V 5W` - carga pequeña;
- `24V 24W` - aproximadamente `1A`;
- `24V 120W` - aproximadamente `5A`;
- `24V 240W` - aproximadamente `10A`.

Los calentadores generalmente consumen mucha potencia. Los ventiladores consumen menos, pero pueden tener una corriente de arranque alta. Las tiras LED pueden ser una carga pequeña si son cortas, o una carga seria si son largas y brillantes.

## La corriente carga los cables y los elementos de potencia

La corriente muestra cuánta electricidad fluye a través de cables, terminales, conectores y elementos de potencia.

La corriente a menudo crea problemas prácticos:

- los cables se calientan;
- los terminales se oscurecen;
- los conectores se derriten;
- MOSFET se sobrecalienta;
- la fuente de alimentación no es suficiente;
- el dispositivo se reinicia cuando se enciende la carga;
- el fusible se activa no por casualidad, sino debido a sobrecarga real o error.

Por lo tanto, no es suficiente conocer solo el voltaje. Debe calcular la corriente.

## Fórmula de cálculo

Para la mayoría de los cálculos simples, necesita la fórmula de potencia:

```text
P = U * I
```

Donde:

- `P` - potencia en vatios `W`;
- `U` - voltaje en voltios `V`;
- `I` - corriente en amperios `A`.

Para encontrar la corriente:

```text
I = P / U
```

![Ley de Ohm: circuito con fuente de voltaje, corriente y resistencia](../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Esta fórmula no es para un examen. Se necesita para entender si la fuente de alimentación, el cable, el terminal, el módulo MOSFET, el relé, el SSR o la salida del tablero lo aguantarán.

## Tabla rápida para 24V

En impresoras 3D y periféricos, `24V` es común. Para una evaluación rápida, es útil recordar:

| Potencia | Corriente a 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Estos son valores aproximados, pero para la primera selección de fuente de alimentación, cable y conmutador de potencia son muy útiles.

## Ejemplo: calentador 24V 100W

Tiene un calentador:

```text
24V 100W
```

Calcule la corriente:

```text
I = 100W / 24V = 4.17A
```

Esto significa que lo siguiente debe soportar más de `4.17A`:

- fuente de alimentación;
- cable;
- terminales;
- conector;
- MOSFET o SSR;
- fusible y portafusibles;
- pistas del tablero, si el calentador está conectado al tablero.

Si la fuente de alimentación se clasifica como `24V 5A`, formalmente se acerca a la carga, pero casi sin margen. Para un dispositivo real, es mejor tomar más.

## Ejemplo: cargas múltiples

Suponga que un dispositivo `24V` tiene:

- calentador `100W`;
- ventilador `24V 0.2A`;
- tira LED `24V 1A`;
- otro ventilador `24V 0.15A`.

Calcule el calentador:

```text
100W / 24V = 4.17A
```

Súmelos:

```text
4.17A + 0.2A + 1A + 0.15A = 5.52A
```

Una fuente de alimentación mínima "ajuste estrecho" sería alrededor de `24V 6A`, pero esa no es una buena opción para operación a largo plazo. Con `50%` de margen:

```text
5.52A * 1.5 = 8.28A
```

Prácticamente debe buscar una fuente de alimentación `24V 9A`, `24V 10A` o mayor, si la carcasa, el enfriamiento y la seguridad lo permiten.

## El margen es obligatorio

La fuente de alimentación, el cableado, los terminales y los módulos de potencia no se pueden seleccionar exactamente de acuerdo con la corriente calculada.

Para esta guía, una regla simple para la evaluación inicial aproximada:

**planifique al menos 50% de margen**, a menos que la documentación de un componente específico requiera más. Esta no es una garantía universal, sino una estimación inicial. La selección final se realiza de acuerdo con las especificaciones técnicas, la temperatura dentro de la carcasa, el enfriamiento, la reducción de escala y el calentamiento real de terminales/cables.

El margen es necesario porque:

- la fuente de alimentación se calienta;
- la temperatura dentro de la carcasa puede ser más alta que la temperatura ambiente;
- los ventiladores y motores tienen corriente de arranque;
- los contactos envejecen y se aflojan;
- los terminales tienen límites de corriente y temperatura;
- SSR y MOSFET generan calor;
- la fuente de alimentación puede tener reducción de escala - reducción de potencia máxima a temperatura alta o ventilación deficiente.

Las fuentes de alimentación industriales a menudo tienen una curva de reducción de escala en la especificación técnica — una curva de potencia máxima reducida a medida que sube la temperatura. La reducción de escala significa que el fabricante reduce la potencia máxima permitida a temperatura alta o ventilación deficiente. Por lo tanto, la etiqueta `240W` en una fuente de alimentación no siempre significa que entregará con seguridad `240W` en una carcasa caliente y cerrada.

## El punto débil puede no ser la fuente de alimentación

Incluso si la fuente de alimentación es poderosa, el circuito puede ser débil en otra parte.

Debe verificar todo el circuito:

- salida de la fuente de alimentación;
- cable;
- bloque de terminales;
- conector;
- fusible;
- módulo MOSFET;
- relé o SSR;
- pistas del tablero;
- la carga misma.

Por ejemplo, una fuente de alimentación puede soportar `10A`, pero un conector pequeño o un terminal de tornillo deficiente puede calentarse ya a corriente más baja. Esto es especialmente importante para calentadores y tiras LED.

## Qué es un conmutador de potencia

Un conmutador de potencia es un conmutador controlado.

El controlador no alimenta directamente una carga pesada. Da una señal de control débil, y el conmutador de potencia enciende o apaga la corriente de la carga.

Ejemplos:

- módulo MOSFET para cargas DC `12V`/`24V`;
- relé;
- SSR;
- controlador de carga listo para usar;
- salida de potencia estándar del tablero, si se clasifica para la carga necesaria.

Para calentadores, ventiladores, tiras LED y motores, la regla casi siempre se aplica:

**GPIO del controlador no alimenta la carga. GPIO solo controla.**

## Un poco sobre la ley de Ohm

La ley de Ohm relaciona el voltaje, la corriente y la resistencia:

```text
U = I * R
```

Para este artículo, la idea simple es importante: si aplica voltaje a una carga, la corriente fluirá a través de ella. Cuánta corriente fluye depende de la carga misma.

Pero no todas las cargas se comportan igual:

- el calentador es cercano a una carga resistiva;
- el ventilador y el motor tienen corriente de arranque;
- el accionamiento de servo aumenta bruscamente la corriente cuando se bloquea;
- la tira LED consume corriente por longitud y brillo;
- el módulo electrónico puede tener corriente transitoria cuando se enciende.

Por lo tanto, para un dispositivo real, es mejor obtener datos de las especificaciones técnicas o medir la corriente con un multímetro / fuente de alimentación de laboratorio si es seguro.

## Qué verificar antes de conectar

Antes de conectar la carga, responda:

1. ¿Para qué voltaje se clasifica la carga?
2. ¿Es una carga CC o CA?
3. ¿Qué potencia o corriente se especifica?
4. ¿Qué corriente obtendrá de la fórmula `I = P / U`?
5. ¿Qué otras cargas hay en la misma fuente de alimentación?
6. ¿Hay al menos `50%` de margen?
7. ¿Los cables, terminales, conectores y tablero lo soportan?
8. ¿Qué controla la carga: MOSFET, relé, SSR o salida estándar?
9. ¿Se necesita un fusible?
10. ¿Qué sucede si hay un cortocircuito, bloqueo del motor o falla del ventilador?

Si se trata de un calentador o voltaje principal `110-230V AC`, los requisitos de seguridad son más altos. La sección de alimentación no se puede ensamblar adivinando: necesita una carcasa adecuada, fusible, aislamiento, tierra de protección `PE`, alivio de tracción para cables y verificación por una persona calificada.

## Lo esencial

- El voltaje de la fuente de alimentación debe coincidir con el voltaje de la carga.
- La potencia muestra el tamaño de la carga.
- La corriente muestra la carga en cables, terminales, conectores y elementos de potencia.
- Fórmula básica: `I = P / U`.
- En un sistema `24V`, `24W` es aproximadamente `1A`, `120W` es aproximadamente `5A`, `240W` es aproximadamente `10A`.
- Las corrientes de todas las cargas en una fuente de alimentación se suman.
- Necesita un margen de al menos `50%` para una estimación inicial aproximada; la selección precisa se realiza de acuerdo con las especificaciones técnicas, la temperatura, el enfriamiento y la reducción de escala.
- El punto débil puede no ser la fuente de alimentación, sino un terminal, conector, cable, MOSFET o pista del tablero.
- GPIO del controlador no alimenta una carga pesada, solo controla un conmutador de potencia.

## Materiales de referencia

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - explicación clara y fundamental de voltaje, corriente, resistencia y ley de Ohm.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - calculadora para calcular relaciones de voltaje, corriente, resistencia y potencia.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - por qué la potencia máxima de una fuente de alimentación depende de la temperatura, ventilación y voltaje de entrada.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - selección de una fuente de alimentación teniendo en cuenta la temperatura, reducción de escala, cables y tipo de carga.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - por qué la corriente máxima de terminales y conectores depende de la temperatura y el diseño.
