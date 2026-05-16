# Conductividad Térmica

La conductividad térmica muestra qué tan fácilmente un material transfiere calor a través de sí mismo.

Para una secadora casera, cámara, filtro, conducto de aire o carcasa, esto no es física abstracta. La conductividad térmica determina si el calor escapará hacia afuera, si aparecerá un punto caliente cerca del calentador, cuánto se calentará la pared exterior y si una pieza impresa se ablandará.

## Idea Simple

El calor siempre tiende a escapar de una zona más caliente a una más fría. Cuanto mayor sea la conductividad térmica de un material, más fácilmente pasa el calor a través de él.

La velocidad de transferencia de calor se ve afectada por:

- material;
- espesor de la pared;
- área de contacto;
- diferencia de temperatura;
- calidad del contacto entre partes;
- presencia de aire, espacios e aislamiento.

Una placa de aluminio delgada puede distribuir rápidamente el calor por toda la carcasa. Una capa gruesa de lana mineral o aislamiento de espuma, por el contrario, evita que el calor escape.

## Valores de Referencia de Materiales

Los valores a continuación son solo para entender órdenes de magnitud. Para una construcción real, consulte la hoja de datos del material específico.

| Material | Conductividad Térmica Aproximada, `W/(m*K)` | Lo Que Significa en la Práctica |
| --- | ---: | --- |
| Cobre | alrededor de `400` | excelente conductor de calor, adecuado para disipar calor, pero transfiere rápidamente el calor donde no siempre es necesario |
| Aluminio | alrededor de `200-240` | distribuye bien el calor, útil como placa, radiador o disipador de calor |
| Acero | alrededor de `15-60` | conduce el calor peor que el aluminio, pero los tornillos y postes aún pueden ser puentes térmicos |
| Vidrio | alrededor de `1` | conduce el calor mucho peor que el metal, pero no es aislamiento en el sentido convencional |
| Plásticos comunes | alrededor de `0.1-0.5` | conducen el calor mal, pero pueden reblandecerse y ser inflamables |
| Lana mineral, fibra de vidrio | alrededor de `0.04` | reduce efectivamente la pérdida de calor, pero requiere protección contra polvo, humedad y daño mecánico |
| Poliestireno expandido / espuma de poliuretano | alrededor de `0.03` | buen aislamiento, pero cerca del calor son importantes la temperatura de funcionamiento y las propiedades de fuego |
| Aire | alrededor de `0.026` | conduce el calor mal por sí solo, pero transfiere calor por convección cuando se mueve |

La conclusión principal: el metal y el aislamiento no difieren por un factor de dos, sino por órdenes de magnitud. Por lo tanto, incluso una pequeña pieza metálica puede cambiar significativamente el panorama térmico.

## Puente Térmico

Un puente térmico es una vía a través de la cual el calor escapa más fácilmente que a través del resto de la estructura.

![Puente térmico clásico a través de un recinto](../../../img/04-thermal-physics-and-materials/02-thermal-bridge-classic.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pont_thermique_classique.png), AmisDeLaThermique, CC BY-SA 3.0*

Puentes térmicos típicos:

- tornillo de metal a través de una pared aislada;
- placa de aluminio conectada a la carcasa exterior;
- poste de metal entre la cámara caliente y el panel exterior;
- bloque de terminales o sujetador cerca del calentador;
- conducto de aire que toca directamente una pieza caliente.

Un puente térmico no siempre es malo. A veces es necesario para disipar calor de un interruptor de potencia, radiador o nodo caliente. El problema comienza cuando el puente es accidental: la cámara pierde calor, la superficie exterior se calienta y el plástico cerca del puente se calienta más de lo esperado.

## Metal: Disipador de Calor o Calentamiento Accidental

El metal es conveniente de usar en dispositivos calentados:

- como pantalla entre calentador y plástico;
- como placa de distribución de calor;
- como base para montaje del calentador;
- como radiador para electrónica de potencia;
- como superficie interior no inflamable.

Pero el metal no hace que un dispositivo sea seguro automáticamente. Si una placa de metal toca una zona caliente y la carcasa exterior, puede conducir calor hacia afuera. Si el plástico está atornillado a él, ese plástico puede calentarse a través del sujetador. Si los cables pasan por él, cerca del borde necesita pasamuros, protección contra abrasión y margen de temperatura para el aislamiento.

## Aislamiento: Menor Pérdida, Mayor Responsabilidad

El aislamiento reduce la pérdida de calor, pero no elimina el control de temperatura.

Cuando aísla una cámara:

- es más fácil para el calentador elevar la temperatura;
- la carcasa puede enfriarse más en el exterior;
- el tiempo de enfriamiento aumenta;
- la temperatura local cerca del calentador puede aumentar;
- la falla del ventilador o el interruptor atascado se vuelven más peligrosos.

Por lo tanto, el aislamiento no se puede agregar como una "mejora" sin probar nuevamente. Después del aislamiento, debe volver a medir las temperaturas dentro de la cámara, en el calentador, en los cables, en los terminales y en la superficie exterior.

## La Brecha de Aire También Funciona

El aire estacionario conduce el calor mal. Por lo tanto, las brechas de aire, paredes dobles y materiales de espuma pueden reducir la transferencia de calor.

Pero si el aire comienza a moverse, interviene la convección. Entonces el calor es transferido por la corriente de aire, no solo por conducción térmica. Por lo tanto, una brecha a través de la cual fluye una corriente caliente puede calentar la carcasa más que una pared gruesa sin flujo.

En la práctica, esto significa:

- no dejar espacios accidentales cerca del calentador;
- no dirigir el flujo caliente directamente al plástico;
- no tratar los espacios de aire como protección si una corriente pasa a través de ellos;
- verificar la temperatura en modo de funcionamiento real, no solo en un dispositivo frío.

## Qué Buscar en la Hoja de Datos del Material

Para material cerca del calor, la conductividad térmica no es lo único que importa.

Verificar:

- temperatura máxima de funcionamiento continuo;
- temperatura de reblandecimiento o temperatura de deformación térmica;
- inflamabilidad y clase de comportamiento al fuego;
- permisibilidad del contacto con aire caliente;
- comportamiento de la capa de pegamento, lámina, recubrimiento o laminación;
- recomendaciones del fabricante para usar;
- disponibilidad de SDS/hoja de seguridad si el material puede calentarse o procesarse.

Si un material no tiene documentación clara, no lo coloque cerca del calentador y no lo use como única protección.

## Orden de Verificación Práctica

Para carcasa, cámara o secadora, es conveniente proceder de la siguiente manera:

1. Identifique la zona caliente: calentador, salida de aire, terminales, interruptor de potencia.
2. Separe la zona caliente del plástico con metal, cerámica u otro material apropiado.
3. Verifique dónde el metal conduce el calor.
4. Agregue aislamiento solo donde no cubre nodos calientes peligrosos.
5. Mida la temperatura en varios puntos después del calentamiento.
6. Verifique el modo de falla del ventilador si el calentador depende del flujo de aire.
7. Agregue protección de sobrecalentamiento independiente donde sea peligroso.

Un sensor de temperatura en la cámara no muestra todo el panorama térmico. Necesita mediciones cerca del calentador, en sujetadores, en cables, en la carcasa y en piezas impresas.

## Conclusión Principal

La conductividad térmica lo ayuda a entender dónde irá realmente el calor. El metal puede ser un disipador de calor útil o un puente térmico accidental. El aislamiento puede mejorar la eficiencia, pero al mismo tiempo amplifica las consecuencias de la falla.

Cualquier cambio en la carcasa, aislamiento, sujetadores o conducto de aire debe verificarse midiendo la temperatura en modo de funcionamiento real.

## Materiales sobre el Tema

- [Engineering ToolBox: Thermal Conductivity of Common Materials](https://www.engineeringtoolbox.com/thermal-conductivity-d_429.html) - valores de referencia de conductividad térmica para metales, plásticos, aire, vidrio y aislamiento.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - relación entre flujo de calor, material, espesor de pared, área y diferencia de temperatura.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - explicación básica de la transferencia de calor de un cuerpo caliente a uno frío.
- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - explicación simple de conducción térmica, convección, radiación y papel del aislamiento.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - referencia práctica para el comportamiento de temperatura de materiales populares de impresión 3D.
