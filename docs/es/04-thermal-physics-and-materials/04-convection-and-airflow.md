# Convección y Flujo de Aire

La convección es la transferencia de calor por corriente de aire. En una secadora, cámara de impresora, filtro calentado o dispositivo como iHeater, el aire a menudo determina si el calor llega donde es necesario.

Un calentador por sí solo solo convierte potencia eléctrica en calor. El ventilador y el conducto de aire determinan si este calor se distribuye uniformemente por toda la cámara o permanece como un pequeño punto caliente peligroso.

## Tres Modos de un Calentador

El mismo calentador de `100 W` puede funcionar completamente diferente.

![Celdas de convección: el aire cálido sube, el aire frío baja](../../../img/04-thermal-physics-and-materials/04-convection-cells.svg)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Convection_cells.svg), McSush, CC BY-SA 3.0*

Sin flujo de aire:

- el calentador se calienta fuertemente en la zona local;
- el aire cercano se calienta, pero se mezcla mal;
- la parte lejana de la cámara puede mantenerse fría;
- el plástico, terminales o aislamiento cercano pueden sobrecalentarse;
- el sensor de temperatura puede no mostrar lo que sucede cerca del calentador.

Con flujo de aire débil o inadecuado:

- algo de calor entra en la cámara;
- ocurre la mezcla;
- pero el flujo puede eludir el calentador;
- el filtro, pantalla o canal estrecho pueden reducir mucho el flujo de aire;
- los puntos calientes aún persisten.

Con flujo normal:

- el aire pasa a través de la zona caliente;
- el calor escapa del calentador a la cámara;
- la temperatura se vuelve más uniforme;
- el control PID funciona más predeciblemente;
- las piezas cercanas se sobrecalientan menos localmente.

El flujo de aire no crea potencia adicional. Ayuda a eliminar el calor ya generado y transferirlo al lugar correcto.

## Convección Natural y Forzada

Hay dos modos útiles:

- convección natural - el aire cálido sube por sí solo;
- convección forzada - el flujo se crea mediante un ventilador, soplador o ventilador centrífugo.

Para dispositivos pequeños calentados, la convección natural a menudo es insuficiente. Es lenta, depende de la forma del alojamiento y fácilmente crea zonas de temperatura.

La convección forzada generalmente es mejor si necesita:

- quitar rápidamente el calor del calentador;
- calentar la cámara uniformemente;
- pasar aire a través de un filtro;
- secar filamento;
- enfriar electrónica de potencia;
- mantener el sensor de temperatura en un flujo de aire significativo.

## Ventilador No Es Solo Tamaño

La frase "voy a poner un ventilador de 40 mm" te dice casi nada sobre el resultado.

Para un dispositivo real, son importantes:

- flujo de aire;
- presión estática;
- punto de funcionamiento después de la instalación en la carcasa;
- dirección del flujo;
- resistencia de pantallas, filtros y conductos de aire;
- temperatura del aire en el ventilador;
- ruido y vibración;
- recurso bajo carga;
- corriente de arranque;
- tacómetro o control de rotación.

El catálogo a menudo enumera el flujo máximo y la presión estática máxima. En un dispositivo real, el ventilador no funciona en estos puntos ideales. El filtro, pantalla, canal estrecho, vuelta del conducto de aire y calentador denso crean resistencia, por lo que el flujo real puede ser mucho menor.

Si el aire debe pasar a través de un filtro, radiador, panal o canal estrecho, a menudo necesita no solo "más CFM" sino un ventilador o soplador centrífugo con presión estática apropiada.

## Ruta del Aire

El buen diseño responde cuatro preguntas:

1. ¿De dónde se extrae el aire?
2. ¿Qué pasa a través de?
3. ¿Dónde libera el calor?
4. ¿Dónde regresa?

Para cámara o secadora, la circulación en circuito cerrado es útil:

```text
cámara -> ventilador -> calentador -> corriente caliente -> cámara -> retorno
```

Para un filtro, puede aplicarse una lógica diferente:

```text
cámara -> filtro -> ventilador -> escape o retorno
```

Lo principal es que el flujo no toma la ruta inútil más fácil alrededor del calentador o filtro. El aire siempre elige la ruta con menor resistencia.

## El Sensor de Temperatura Debe Ver el Lugar Correcto

Opciones malas:

- sensor justo en el calentador y ve sobrecalentamiento local;
- sensor en zona muerta y ve esquina fría;
- sensor toca pared de metal y mide la pared, no el aire;
- sensor se encuentra antes del calentador, aunque la temperatura después importa;
- sensor es soplado por una corriente que no refleja la temperatura de la cámara.

Para cámara, generalmente es útil medir el aire donde la temperatura debe ser controlable, pero no directamente en el calentador. Para proteger contra sobrecalentamiento cerca del calentador, se necesita un sensor separado o termostato independiente/corte térmico.

Un sensor para control y un elemento de emergencia independiente es mucho mejor que un sensor responsable de todo.

## Filtros y Pantallas Pueden Matar el Flujo

Un filtro, pantalla, rejilla decorativa o brecha estrecha agrega resistencia.

Errores típicos:

- poner filtro denso en ventilador axial débil;
- bloquear parcialmente la entrada con pantalla decorativa;
- hacer un giro agudo justo después del ventilador;
- posicionar el calentador para que el aire lo rodee;
- olvidar que el filtro se obstruye con polvo y la resistencia crece;
- no dejar acceso para mantenimiento del filtro.

Si el dispositivo depende del flujo, verifique no solo "el ventilador está girando" sino también que el aire realmente pasa por la ruta correcta.

## Qué Sucede Si Falla el Ventilador

Escenario más peligroso para calentador con flujo de aire:

```text
ventilador detenido -> calentador sigue funcionando -> la temperatura local aumenta rápidamente
```

Por lo tanto, calentador que depende de la corriente de aire necesita medidas:

- protección de sobrecalentamiento independiente cerca de la zona caliente;
- limitación de potencia;
- material con margen de temperatura;
- distancia del calentador al plástico e aislamiento;
- control de tacómetro de ventilador si el ventilador es crítico;
- verificación de firmware de calentamiento si usa Klipper o similar;
- primera prueba bajo observación.

El firmware ayuda pero no reemplaza la protección física. MOSFET, SSR o relé pueden fallar en estado encendido.

## Verificación Mínima Después del Ensamblaje

Después de construir un dispositivo calentado, verifique:

- dirección del flujo;
- ¿hay flujo en la salida, no solo rotación del ventilador?
- temperatura en calentador;
- temperatura después del calentador;
- temperatura en la parte lejana de la cámara;
- temperatura de cables, terminales y piezas impresas;
- temperatura del ventilador;
- comportamiento con filtro parcialmente bloqueado;
- ¿se apaga el calentamiento si el sensor falla?
- ¿se activa la protección de sobrecalentamiento independiente en escenario peligroso?

Haga el primer calentamiento bajo observación. Las mediciones se hacen mejor después de la estabilización y después de la operación prolongada, porque la carcasa, sujetadores y aislamiento se calientan más lentamente que el aire.

## Conexión a Klipper

En Klipper, varios mecanismos son útiles:

- `heater_fan` - el ventilador se enciende con el calentador o cuando se alcanza la temperatura;
- `temperature_fan` - el ventilador es controlado por sensor de temperatura separado;
- `verify_heater` - verifica que el calentador se comporte como se espera;
- `tachometer_pin` para ventilador - permite ver RPM si el ventilador soporta señal de tacómetro.

Este no es un esquema de seguridad completo, pero un buen nivel de control para dispositivo donde la temperatura y el flujo son importantes.

## Conclusión Principal

En un dispositivo calentado, lo que importa no es solo la potencia del calentador sino la ruta del aire. El buen flujo elimina el calor del calentador y lo transfiere a la cámara. El flujo pobre deja un punto caliente, engaña al sensor y aumenta el riesgo de sobrecalentamiento de material.

Si el calentador depende del ventilador, la falla del ventilador debe ser un escenario de emergencia separado, no una sorpresa.

## Materiales sobre el Tema

- [Engineering ToolBox: Convective Heat Transfer](https://www.engineeringtoolbox.com/amp/convective-heat-transfer-d_430.html) - explicación de convección natural y forzada.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - por qué el flujo máximo y la presión máxima del catálogo no equivalen a la operación de dispositivo real.
- [SANYO DENKI: Guideline in Selecting a Fan](https://products.sanyodenki.com/info/sanace/en/technical_material/select.html) - enfoque práctico para elegir ventilador por potencia térmica, aumento de temperatura y pruebas reales.
- [DigiKey: Selecting a Fan](https://www.digikey.com/en/articles/selecting-a-fan) - diferencia entre ventiladores axiales y centrífugos, impacto de alojamiento y resistencia del flujo.
- [Klipper Documentation: Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - parámetros para `heater_fan`, `temperature_fan`, `verify_heater` y tacómetro de ventilador.

## Ver También

- [iDryer docs: Connecting a Fan](../05-practical-guides/01-connecting-a-fan.md) - instrucción local sobre potencia del ventilador, MOSFET, GND común y ejemplos de Klipper.
