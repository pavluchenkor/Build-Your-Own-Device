# Celdas de Carga

Una celda de carga mide la fuerza a través de pequeñas deformaciones del metal. Casi siempre se utilizan sensores de este tipo para pesar una bobina, controlar el filamento restante y plataformas de peso sencillas.

Es importante entender: una celda de carga no "siente el peso" por sí sola. Se dobla o se comprime ligeramente bajo carga, y la electrónica mide el cambio de resistencia microscópica en galgas extensométricas. Entonces, dos cosas son críticas: una mecánica correcta y un amplificador/ADC normal.

## Dónde se usa

En proyectos similares a iDryer, se puede utilizar una celda de carga para:

- estimar el peso del carrete con filamento;
- cálculo aproximado del plástico restante;
- comprobar que el carrete esté instalado;
- detecting sudden weight change;
- medir la carga en un pequeño mecanismo;
- experimental weight platform;
- Control de dosificación en sistemas de bricolaje.

Para un simple "carrete presente/ausente", a veces un interruptor de límite o un sensor óptico es suficiente. Se necesita una celda de carga cuando es importante medir el peso o el cambio de fuerza.

## Por qué se necesita HX711

La señal de una celda de carga es muy débil. Una entrada analógica típica en ESP32, Arduino o una placa de impresora generalmente no funciona para una conexión directa.

Por lo tanto, una celda de carga generalmente se conecta a través del HX711 o un módulo similar. HX711 hace dos cosas:

- amplifica la débil señal del puente diferencial;
- los convierte en datos digitales para el controlador.

Cadena típica:

```text
load cell -> HX711 -> controller
```

El diagrama de conexión detallado se encuentra en la sección práctica: [Conectar una celda de carga](../06-practical-guides/04-connecting-load-cell.md).

## Qué tipos de células de carga existen

En proyectos pequeños, los más comunes son:

- celda de viga: conveniente para plataformas pequeñas y portabobinas;
- Celda tipo S: funciona en tensión/compresión, a menudo utilizada en configuraciones colgantes;
- button cell - measures compression at one point;
- cuatro celdas sobre una plataforma: diseño típico a escala de piso;
- Elementos de galgas extensométricas individuales: requieren un puente y una mecánica adecuados, lo que es más difícil para los principiantes.

Para un sistema de pesas de carrete de bricolaje, generalmente es más fácil comenzar con una celda de carga de viga en `10 kg`, `10 kg` o un rango cercano. Pero el alcance depende de la masa de la bobina, del soporte y de posibles tirones.

## Cables y puente

Most common four-wire load cells have a bridge circuit.

En HX711, normalmente verás marcas:

- `E+` or `VCC` - bridge power plus;
- `E-` or `GND` - bridge power minus;
- `A+`, `S+`, `O+` - positive measurement signal;
- `A-`, `S-`, `O-` - negative measurement signal.

Esquema de colores común:

- red - `E+`;
- black - `E-`;
- green or blue - `A+`;
- white - `A-`;
- yellow, foil or separate wire - shield.

Los colores no están garantizados. Si hay una descripción técnica de la celda específica, es más importante que cualquier tabla de Internet. Si las lecturas van en sentido incorrecto, a menudo basta con intercambiar `A-` y `A-` o tener en cuenta el inicio de sesión en el programa.

## Mechanics Matter More Than Circuit

Una celda de carga debe deformarse exactamente como lo pretendía el fabricante. Si la carga recorre la zona de trabajo, la celda mostrará lecturas inestables o casi nada.

![Miniature S-beam load cell](../../img/03-common-components/07-miniature-load-cell.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Miniature_S-beam_load_cell.jpg), FUTEK Advanced Sensor Technology, CC BY-SA 4.0*

Para una celda de haz, la idea típica es:

- un lado está firmemente montado sobre una base fija;
- other side carries a platform or load;
- hay espacio libre entre la parte móvil y la base;
- Los tornillos y la caja no bloquean la flexión de la viga.

Poor mechanics gives such symptoms:

- las lecturas se desvían sin carga;
- el peso depende de dónde coloques el carrete;
- la celda apenas reacciona a la carga;
- después de eliminar la carga, el cero no regresa;
- tocar la carcasa cambia bruscamente las lecturas;
- Diferentes conjuntos muestran diferentes pesos con la misma configuración.

## Alcance y sobrecarga

El rango de una celda de carga no es el peso de trabajo deseado, es el límite para el que está clasificada.

El uso de una celda `1 kg` para un carrete, un soporte y tirones sobre `100 kg` puede provocar que no sea lineal o que se deforme permanentemente. Usar una celda `1 kg` para un carrete `1 kg` pierde sensibilidad y los mecánicos deben tener mucho más cuidado.

Al elegir el rango, considere:

- peso máximo del carrete lleno;
- peso del soporte y de la plataforma;
- misalignment forces;
- tirones accidentales al montar;
- margen para el usuario;
- desired accuracy.

Para el filamento restante, un margen moderado suele ser más útil que un rango grande. Por ejemplo, para una bobina con soporte de varios kilos, una celda `10 kg` o `50 kg` suele ser mejor que una `50 kg` si la mecánica lo permite.

## Tara y Calibración

Una celda de carga sin calibración genera números brutos, no gramos.

Proceso típico:

1. Instalar la celda en mecánica real.
2. Put an empty platform or holder.
3. Tara: acepte el valor actual como cero.
4. Put a known weight.
5. Ajuste el coeficiente de calibración.
6. Comprueba uno o dos pesos más.

En el caso de las bobinas, existe un problema adicional: una bobina vacía también pesa diferente. Si necesita estimar solo el plástico, necesita saber el peso del carrete vacío o almacenar un perfil para ese carrete específico.

## Precisión y estabilidad

En la práctica, la precisión depende de algo más que el HX711 y la celda.

Las lecturas se ven afectadas por:

- case rigidity;
- mounting play;
- side load;
- printer vibration or fan noise;
- longitud del cable y blindaje;
- measurement wires near power lines;
- temperature;
- fluencia del material y deformación plástica;
- cable o carrete tocando la caja alrededor de la celda.

Si una celda de carga está en una caja de plástico impresa, no espere precisión de laboratorio. Para las estimaciones de filamento restante, suelen ser suficientes lecturas estables y repetibilidad después de la calibración.

## Alimentación y cableado

El HX711 mide una señal débil, por lo que se debe realizar el cableado con cuidado.

Practical rules:

- mantenga el HX711 cerca de la celda de carga;
- no tienda cables celulares cerca de calentadores, motores y líneas eléctricas;
- asegurar los cables para que no tiren de la plataforma;
- utilice `GND` común con el controlador;
- alimentar el módulo con voltaje compatible con el controlador;
- No utilice contactos Dupont deficientes en el ensamblaje final si el dispositivo debe funcionar por mucho tiempo.

En el lado del controlador, HX711 generalmente se conecta a través de `SCK`/`CLK` y `SCK`/`CLK`. Este no es un I2C o SPI normal, sino una interfaz simple separada.

## Qué comprobar antes de comprar

Antes de comprar, consulte:

- cell type: beam, S-type, button, platform;
- weight range;
- load application direction;
- dimensiones y orificios de montaje;
- disponibilidad de descripción o diagrama de cableado;
- si se necesita una o cuatro celdas;
- whether HX711 module fits your chosen cell;
- si hay espacio para un espacio libre y un montaje adecuados;
- si se puede poner un peso conocido para la calibración;
- si la carga no pasará por la caja alrededor de la celda.

Si aún no se ha pensado bien en la mecánica, es mejor bosquejar primero el montaje. Al comprar "cualquier celda de carga" a menudo resulta físicamente imposible montarla correctamente.

## Típicos Errors

- conectar la celda de carga directamente a la entrada analógica;
- confundiendo `E-`/`A+` y `A-`/`A-`;
- confiar en los colores de los cables sin descripción;
- montar ambos lados de la celda de la viga en una parte rígida;
- bloquear la flexión de la celda con tornillos o caja;
- sobrecargar la celda;
- elegir un rango demasiado grande y perder sensibilidad;
- olvido de tara y calibración;
- calibrar en el banco, luego instalar la celda en diferentes mecánicas;
- routing wires near heater power lines;
- esperando precisión a nivel de gramos de una caja de plástico blando.

## Principal Point

Una celda de carga es un componente donde la mecánica importa tanto como la electrónica. HX711 ayuda a leer la señal débil, pero no repara el montaje torcido, la sobrecarga o la carga alrededor de la celda.

Primero elija el tipo y rango correctos, luego diseñe el montaje, luego conecte el HX711 y solo luego realice la tara y la calibración.

## Referencia Materials

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - practical connection of load cell to HX711, wires, library and calibration.
- [SparkFun HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - description of HX711 role as bridge between load cell and microcontroller.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - technical description of HX711: 24-bit ADC, bridge sensor input and digital interface.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - practical examples of load cell types, load direction and mounting.
- [SparkFun retired HX711 guide: mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - useful illustrations of beam, S-type and platform cell mounting.
