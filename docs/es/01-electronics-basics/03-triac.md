# TRIAC

Un TRIAC, o tiristor, es un semiconductor de potencia para corriente alterna. Se utiliza cuando se necesita activar o controlar una carga de CA: por ejemplo, un calentador de red eléctrica, una lámpara incandescente u otro dispositivo simple con `110-230V AC`.

Para dispositivos caseros, este es un tema de alto riesgo. El TRIAC por sí mismo no hace que la tensión de red sea segura. Solo proporciona una forma de controlar una carga de CA sin contactos mecánicos.

## Cómo difiere el TRIAC del MOSFET

El módulo MOSFET del artículo anterior se usa generalmente para cargas de CC: `5V`, `12V`, `24V`.

El TRIAC se usa para cargas de CA. Se activa mediante un pulso de control y conduce corriente hasta que la corriente a través de él cae por debajo del valor de mantenimiento. En la red de CA esto suele ocurrir cerca del cruce por cero de la onda sinusoidal.

En la práctica:

- MOSFET - elección típica para ventilador de `12V`/`24V`, tira LED o calentador de CC;
- TRIAC - elemento típico dentro de los reguladores de potencia de CA y muchos SSR de CA;
- SSR - relé de estado sólido listo para usar, que puede contener un optoacoplador, TRIAC/tiristor, carcasa, terminales y a veces disipador de calor.

Para un principiante, para una carga de red eléctrica, a menudo es más seguro considerar un SSR listo para usar o un módulo certificado que ensamblar su propio circuito TRIAC en una protoboard.

## Por qué se usa para cargas de CA

Una carga potente de baja tensión requiere alta corriente.

Por ejemplo:

```text
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> about 1.3A
```

A `24V` se necesitan cables gruesos, fuente de alimentación potente, MOSFET fuerte, terminales adecuados y refrigeración. A `230V AC` la corriente es menor, pero hay tensión de red peligrosa y todos los requisitos de seguridad eléctrica.

El enfoque TRIAC no es "mejor" ni "más simple". Es un compromiso diferente: menos corriente en el circuito de potencia, pero requisitos mucho mayores para el aislamiento, la carcasa, el fusible, las distancias y las calificaciones.

## Arquitectura típica

El controlador generalmente no se conecta directamente al TRIAC.

Una arquitectura segura típica tiene este aspecto:

![Circuito dimmer de CA con TRIAC](../../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Contiene:

- lado de baja tensión: controlador y resistencia de control;
- TRIAC optoacoplador: transmite el comando mediante aislamiento óptico;
- lado de red: TRIAC de potencia, carga de CA, fusible, terminales y carcasa;
- a veces circuito snubber y varistor/TVS para ruido y picos.

El TRIAC optoacoplador es necesario para el aislamiento galvánico. Esto significa que no hay conexión eléctrica directa entre el microcontrolador y la sección de red. El control se transmite a través de la luz dentro del optoacoplador.

El aislamiento galvánico reduce el riesgo de que la tensión de red llegue al controlador, USB y al ordenador. Pero no hace que la sección de red sea segura al tacto.

## Cruce por cero y control de fase

Los TRIAC optoacopladores vienen con cruce por cero y sin él.

Un TRIAC optoacoplador con cruce por cero activa la carga cerca del cruce por cero de la tensión de red. Esto es conveniente para el encendido/apagado simple de un calentador u otra carga resistiva: menos ruido y conmutación más suave.

Un TRIAC optoacoplador sin cruce por cero se usa donde se necesita el control de fase de la potencia, por ejemplo un dimmer. Este circuito es más complejo: hay que detectar el cruce por cero, contar el retardo y tener en cuenta el ruido.

Para un calentador en un secador o cámara, generalmente no se necesita control de nivel de dimmer. A menudo es suficiente un enfoque lento de encendido/apagado o control por ráfagas, si es compatible con el módulo elegido y seguro para la carga.

## Qué cargas son adecuadas

Un TRIAC es más fácil de usar con cargas resistivas de CA:

- calentador;
- lámpara incandescente;
- carga térmica simple sin electrónica interna.

Usar con precaución con:

- motores;
- ventiladores de CA;
- transformadores;
- solenoides;
- fuentes de alimentación;
- controladores electrónicos;
- cargas con alta corriente de irrupción.

La carga inductiva desplaza la fase de la corriente con respecto a la tensión y puede interferir con el apagado normal del TRIAC. Puede requerir otros tipos de TRIAC, circuito snubber, varistor o un método de conmutación diferente.

Una fuente de alimentación o un controlador electrónico no debe considerarse una carga resistiva normal. Si tiene su propia electrónica interna, el control TRIAC puede funcionar de forma deficiente o peligrosa.

## Circuito snubber

El snubber es un circuito RC (resistencia + condensador en paralelo con el TRIAC) que amortigua los cambios bruscos de tensión y evita la activación falsa del TRIAC.

Puede ayudar:

- con cargas inductivas;
- con ruido rápido en la red;
- con la activación falsa del TRIAC;
- con problemas de apagado.

Un punto de partida típico para una carga resistiva de 200–400 W a 230 V: **100 nF + 100 Ω**. El condensador debe ser de tipo X2 o equivalente, con clasificación para funcionamiento en circuito de red. Esta no es una solución universal, sino un valor de partida. Para otra carga, los valores se recalculan según la hoja de datos del TRIAC y las notas de aplicación del fabricante.

Si no tiene experiencia con circuitos de CA, es mejor usar un módulo listo para usar o SSR donde el snubber ya ha sido calculado por el fabricante.

## Calentamiento y disipador de calor

Un TRIAC se calienta durante el funcionamiento. No es un interruptor perfecto: hay una caída de tensión a través de él, lo que significa que se genera calor.

Debe verificar:

- corriente de carga;
- encapsulado del TRIAC;
- caída de tensión en estado de conducción;
- requisitos del disipador de calor;
- temperatura ambiente;
- temperatura dentro de la carcasa;
- distancia de plásticos y cables;
- margen de parámetros.

En la especificación técnica hay muchos parámetros. Para la primera elección, tres son suficientes:

- `IT(RMS)` — corriente RMS máxima a través del TRIAC. Debe ser mayor que la corriente de carga con margen, en las condiciones de refrigeración reales.
- `VDRM`/`VRRM` — tensión máxima en estado de corte. Para red de 230 V, elegir TRIAC con clasificación de 600 V o más.
- `IGT` — corriente de puerta. Debe coincidir con las capacidades del TRIAC optoacoplador.

Otros parámetros (`IH`, `dV/dt`, `Tj`, `Rth`) son importantes para cálculos precisos o cuando hay problemas en el circuito real.

La clasificación de corriente en la especificación técnica se da bajo ciertas condiciones de refrigeración. En una carcasa cerrada y cálida sin disipador de calor, la corriente máxima real es menor.

## TRIAC y SSR

Un SSR para una carga de CA a menudo usa internamente un optoacoplador y una etapa de potencia TRIAC o tiristor.

Ventajas de un SSR listo para usar:

- terminales cómodos;
- entrada de control clara;
- carcasa;
- parámetros declarados;
- a menudo más fácil de montar y refrigerar mecánicamente.

Desventajas:

- el SSR también se calienta;
- se necesita el tipo correcto: SSR de salida de CA para carga de CA;
- muchos SSR requieren disipador de calor;
- el mercado tiene muchas falsificaciones y módulos con especificaciones sobredimensionadas;
- el SSR no reemplaza el fusible, la carcasa y la seguridad eléctrica.

Si la tarea es controlar un calentador de red en un dispositivo real, un SSR de calidad listo para usar es a menudo más práctico que un circuito casero sobre un TRIAC separado.

## Lo que no se puede hacer

No se puede:

- ensamblar un circuito TRIAC de red en una protoboard sin soldadura;
- dejar la sección de red abierta bajo tensión;
- conectar el controlador directamente a la sección de red sin aislamiento;
- usar módulo MOSFET de baja tensión en lugar de TRIAC/SSR para `230V AC`;
- poner un condensador aleatorio en el circuito snubber de red;
- considerar la etiqueta "40A" en un módulo barato como verificación suficiente;
- prescindir de un fusible;
- colocar terminales de red junto a USB, botones y contactos de baja tensión abiertos;
- probar dicho circuito sin comprender la seguridad eléctrica.

Trabajar con `110-230V AC` requiere conocimientos, herramientas adecuadas, carcasa, verificación de aislamiento y comprensión de las normas locales. En caso de duda, una persona calificada debe ensamblar o inspeccionar la sección de potencia.

## Qué verificar antes de comprar

Antes de comprar un TRIAC, módulo o SSR, verifique:

- si es carga de CA o CC;
- tensión de red;
- corriente y potencia de carga;
- si es carga resistiva o inductiva;
- si se necesita cruce por cero;
- si se necesita snubber;
- corriente máxima con la refrigeración real;
- si se necesita disipador de calor;
- si hay optoacoplador;
- terminales y espaciado para red eléctrica;
- fusible y carcasa;
- si hay especificación técnica o documentación del fabricante.

Si no hay documentación y el módulo debe controlar un calentador de red, es una mala elección.

## Errores comunes

- usar TRIAC para carga de CC;
- confundir MOSFET, TRIAC y SSR;
- conectar carga de red sin aislamiento galvánico;
- usar TRIAC optoacoplador con cruce por cero y esperar una regulación suave de dimmer;
- usar TRIAC con motor sin snubber y verificación del tipo de carga;
- no instalar disipador de calor;
- no tener en cuenta la temperatura dentro de la carcasa;
- usar terminales aleatorios y cables delgados;
- pensar que el SSR o TRIAC reemplaza al fusible;
- dejar la sección de red abierta junto al controlador y USB.

## El punto principal

El TRIAC es un interruptor de potencia para cargas de CA. Es útil para cargas resistivas de red, como calentadores, pero requiere un diseño correcto de la sección de red.

Para un microcontrolador, se necesita aislamiento galvánico. Para la carga, se necesitan el TRIAC/SSR correcto, fusible, terminales, carcasa, disipador de calor si es necesario, y verificación de seguridad. Si no tiene experiencia con `110-230V AC`, no ensamble la sección de potencia usted mismo.

## Materiales de referencia

- [STMicroelectronics: Standard and snubberless triacs documentation](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - Selección de TRIAC, parámetros y notas de aplicación sobre TRIAC snubberless/estándar.
- [ST AN437: RC snubber circuit design for TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - explicación detallada de por qué se necesita el circuito RC de amortiguación y cómo afecta al apagado del TRIAC.
- [MOC3063 datasheet: zero-cross optoisolator TRIAC driver](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - ejemplo de TRIAC optoacoplador para interfaz de lógica con cargas de `115/240 VAC`.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - explicación básica del SSR como relé de estado sólido sin contactos mecánicos.
- [Omron SSR glossary: phototriac, zero-cross, snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - definiciones breves de fototriac, cruce por cero y circuito snubber.
