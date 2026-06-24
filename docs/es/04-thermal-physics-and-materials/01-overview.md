# Física Térmica y Materiales

Esta sección es necesaria para dispositivos con calentador, cámara, secador de filamento, filtro con aire caliente, conductos de aire, ventiladores, aislamiento, o piezas impresas cerca de temperaturas altas.

No encontrarás un curso académico de física aquí. El objetivo es práctico: entender adónde va el calor, por qué la carcasa se calienta de manera desigual, por qué un material sirve para una pared de cámara mientras que otro puede ablandarse, humear, o convertirse en un riesgo de incendio.

## Por Qué Importa

En un dispositivo simple calentado, no puedes pensar solo de esta manera:

```text
coloqué un calentador -> se calentó
```

En la práctica, necesitas responder otras preguntas:

- adónde va el calor del calentador;
- dónde aparecerán puntos calientes;
- qué ve el sensor de temperatura;
- ¿soportará el material el calentamiento prolongado;
- qué sucede si el ventilador falla;
- qué sucede si un MOSFET/SSR se queda atascado;
- ¿terminarán el cable, terminal, o plástico en la zona de sobrecalentamiento;
- ¿hay protección independiente contra sobrecalentamiento.

Un dispositivo puede mostrar `45°C` en la pantalla, pero al lado del calentador, terminal, o dentro del conducto de aire puede ser mucho más caliente. Por lo tanto, no solo importa la temperatura de la cámara objetivo, sino también las temperaturas locales de las piezas.

## Tres Formas en que el Calor se Propaga

El calor se transfiere de tres formas principales:

![Tres mecanismos de transferencia de calor: conducción, convección y radiación](../../img/04-thermal-physics-and-materials/01-heat-transfer-kettle.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kettle-convection-conduction-radiation.png), P.wormer, CC BY-SA 3.0*

**Conducción térmica** - el calor pasa a través de un material. Por ejemplo, un soporte de metal transfiere rápidamente el calor de una zona caliente a la carcasa.

**Convección** - el calor es transportado por una corriente de aire. Por ejemplo, un ventilador toma el calor del calentador y lo dispersa por toda la cámara.

**Radiación** - una superficie caliente transfiere calor mediante radiación infrarroja. Por ejemplo, un elemento fuertemente calentado puede calentar plástico cercano incluso sin contacto directo.

En un dispositivo real, casi siempre funcionan los tres mecanismos simultáneamente.

## El Material es Parte del Sistema Térm ico

El material de la carcasa, pared, conducto de aire, o soporte afecta el régimen térmico.

Metal:

- conduce el calor bien;
- puede disipar calor de la zona caliente;
- puede hacer que la superficie exterior se caliente;
- no resuelve el problema de aislamiento y seguridad eléctrica por sí solo.

Plástico:

- conduce el calor mal;
- puede ser conveniente para una carcasa;
- puede ablandarse y perder resistencia;
- puede ser inflamable o humar cuando se sobrecalienta.

Aislamiento:

- reduce la pérdida de calor;
- ayuda a mantener la temperatura de la cámara;
- puede amplificar el sobrecalentamiento local;
- requiere capa de protección y verificación de seguridad contra incendios.

No hay un "mejor material" universal. Hay un material adecuado para una ubicación específica, temperatura, carga y escenario de fallo.

## Temperatura de Trabajo No es Temperatura de Fusión

Los principiantes a menudo miran solo la temperatura de fusión. Esto es un error.

El material puede volverse inadecuado antes:

- ablandarse;
- perder forma;
- encoger;
- perder resistencia;
- comenzar a oler;
- liberar productos de descomposición;
- volverse más inflamable.

Para carcasa, montaje, o conducto de aire, la temperatura de trabajo permisible, temperatura de ablandamiento, propiedades de fuego, y recomendaciones del fabricante importan más.

## El Aire Debe Moverse Correctamente

Un ventilador en un dispositivo calentado no está ahí "para mostrar". Determina cómo escapará el calor del calentador.

Sin flujo adecuado:

- el calentador puede sobrecalentarse localmente;
- la cámara se calentará de manera desigual;
- el sensor puede no mostrar la temperatura correcta;
- las piezas cercanas pueden volverse más calientes de lo esperado;
- el control PID se comportará peor.

Pero el ventilador también debe ser seleccionado e instalado correctamente: flujo, presión estática, dirección, filtro, pantalla, y conducto de aire pueden cambiar completamente el resultado.

## Qué Verificar en Cualquier Dispositivo Calentado

Antes del montaje y la primera prueba, verifica:

- potencia del calentador;
- temperatura al lado del calentador;
- temperatura del aire después del calentador;
- temperatura de terminales y cables;
- temperatura de carcasa y piezas impresas;
- si el material soporta la temperatura de trabajo con margen;
- si hay material inflamable cerca de la zona caliente;
- ¿hay fusible;
- ¿hay protección independiente contra sobrecalentamiento;
- qué sucede si el ventilador falla;
- qué sucede si el sensor de temperatura falla.

La primera prueba se realiza bajo observación y con la capacidad de cortar rápidamente la potencia.

## Cómo Leer Esta Sección

La sección consta de tres temas prácticos:

- [Conductividad Térmica](02-thermal-conductivity.md) - por qué metal, plástico, vidrio, y aislamiento se comportan diferentemente.
- [Materiales, Inflamabilidad y Emisiones Nocivas](03-material-safety.md) - cómo elegir material cerca del calor y qué leer en la hoja de datos.
- [Convección y Flujo de Aire](04-convection-and-airflow.md) - por qué el mismo calentador funciona diferentemente con diferentes flujos de aire.

## Conclusión Principal

Un dispositivo calentado no es solo un calentador y un sensor. Es un sistema térmico: calentador, aire, carcasa, materiales, cables, terminales, ventilador, sensores, y protección de emergencia.

Si un material es conveniente, barato, y fácil de cortar, eso no significa que pueda colocarse al lado de un calentador. Primero verifica la temperatura, transferencia de calor, propiedades de fuego, documentación, y escenarios de fallo.

## Materiales en el Tema

- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - explicación simple de conducción térmica, convección, y radiación.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - explicación básica de transferencia de calor de un cuerpo más caliente a uno más frío.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - conducción térmica, gradiente de temperatura, espesor de material, y paredes multicapa.
- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - por qué los materiales plásticos se comparan por comportamiento cuando arden, no solo por temperatura de fusión.

## Ver También

- [iDryer docs: Calentadores](../03-common-components/02-heaters.md) - artículo local sobre selección de calentador, interruptor de potencia, sensor, y protección independiente contra sobrecalentamiento.
