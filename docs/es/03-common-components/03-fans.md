---
title: "Ventiladores y flujo de aire en un secador de filamento"
description: "Por qué importa el flujo de aire en un secador de filamento y una cámara calefactada: elección del ventilador, caudal, presión estática, ruido y calentamiento uniforme."
---

# Ventiladores y flujo de aire en un secador de filamento

Un ventilador no solo mueve aire: reparte el calor, reduce puntos calientes y ayuda a secar el filamento de forma uniforme. Esta página ayuda a elegir un ventilador y entender su efecto en la carcasa, el calentador y el sensor.

Un ventilador es un motor con un impulsor que mueve aire. En dispositivos alrededor de una impresora 3D, lo necesitas no solo para "soplar", sino para empujar aire a través de la zona correcta: un calentador, bobina, filtro, radiador, cámara o compartimento de electrónica.

Los ventiladores del mismo tamaño pueden funcionar de manera muy diferente. Uno empuja aire bien en espacio abierto, otro empuja aire mejor a través de un filtro o conducto, un tercero es más silencioso pero más débil bajo resistencia.

## Dónde se usa

En proyectos tipo iDryer, los ventiladores se utilizan para:

- circulación de aire dentro de la secadora;
- transferir calor desde el calentador a la cámara;
- extraer aire de la cámara de la impresora;
- filtering through HEPA/carbon filter;
- cooling electronics;
- cooling a radiator;
- Temperatura de nivelación dentro del recinto.

Para calentar la cámara es especialmente importante un ventilador. El calentador libera calor y el flujo de aire elimina ese calor del elemento y lo transporta más lejos. Sin un flujo de aire adecuado, el calentador puede sobrecalentarse localmente mientras que la cámara no calienta bien.

## Flujo de aire y presión estática

En la descripción técnica de un ventilador se suelen ver dos parámetros importantes:

- flujo de aire, a menudo en `m3/h` o `m3/h`;
- presión estática, a menudo en `Pa`, `inch H2O` o `inch H2O`.

El flujo de aire muestra cuánto aire puede bombear un ventilador en condiciones ideales con poca resistencia.

La presión estática muestra qué tan bien un ventilador puede empujar el aire a través de una resistencia: un filtro, una parrilla, un radiador, un conducto estrecho o un tubo de aire largo.

Practical rule:

- para la circulación abierta, el flujo de aire es más importante;
- para filtros, radiadores, rejillas densas y conductos, la presión estática importa más;
- para un gabinete real, el punto de operación importa, no solo el número máximo en la especificación.

Si coloca un ventilador de caja silencioso sobre un filtro denso, es posible que apenas impulse el aire, aunque el flujo de aire parezca fuerte en un espacio abierto.

## Ventiladores axiales y radiales

Un ventilador axial empuja el aire a lo largo del eje de rotación. Estos son los típicos ventiladores cuadrados `60x60`, `80x80`, `120x120 mm`, `120x120 mm`.

Un ventilador radial toma aire desde un lateral y lo expulsa a través de una salida estrecha. A menudo funciona mejor para conductos, boquillas, filtros y lugares donde se necesita presión.

Para la libre circulación dentro de una cámara, suele ser conveniente un ventilador axial. Para un conducto compacto, filtro o flujo dirigido, a veces es mejor un ventilador radial.

## 2 pines, 3 pines y 4 pines

Los fanáticos a menudo difieren en la cantidad de cables.

![3-pin connector on a computer fan](../../img/03-common-components/03-fan-3pin-connector.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Three-pin_connector_on_a_computer_fan.jpg), Dsimic, CC BY-SA 4.0*

2-pin:

- `+V`;
- `GND`.

Un ventilador así simplemente obtiene poder. Puede controlar la velocidad cambiando el voltaje de suministro o PWM en la línea eléctrica si la placa y el ventilador lo admiten.

3-pin:

- `+V`;
- `GND`;
- tachometric signal (`tach`/`sense`).

El tercer cable suele emitir una señal de velocidad. No controla la velocidad por sí solo.

4-pin PWM:

- `GND`;
- `+V`;
- tachometric signal (`tach`/`sense`);
- PWM control signal.

En un ventilador PWM de 4 pines, la energía generalmente se suministra constantemente y la velocidad se establece mediante una línea PWM separada. Esto no es lo mismo que encender y apagar rápidamente el ventilador.

## PWM y tacómetro

PWM es una señal de control que establece la velocidad deseada. Los ventiladores PWM de 4 pines de las computadoras suelen tener una frecuencia cercana a `25 kHz` y la potencia se mantiene constante.

Si el cable PWM no está conectado, muchos ventiladores de 4 pines funcionan a máxima velocidad.

La señal taquimétrica muestra RPM. Es necesario si el dispositivo debe comprender:

- si el ventilador está girando o parado;
- si la velocidad coincide con el comando;
- whether a filter or duct creates too much resistance;
- si el ventilador está atascado.

El tacómetro no reemplaza el control de temperatura. En un dispositivo con calentador, es necesario controlar tanto la temperatura como el estado del flujo de aire si la falla del ventilador es peligrosa.

## Voltaje y corriente

Antes de conectar, verifique:

- fan voltage: `5V`, `12V`, `24V`;
- operating current;
- startup current;
- connector type;
- pinout;
- whether it has PWM;
- whether it has a tachometer;
- operating temperature;
- airflow direction;
- noise level;
- vida útil y tipo de rodamiento.

No se puede alimentar un ventilador desde el GPIO del controlador. GPIO es una señal, no una salida de energía. La corriente del ventilador debe provenir de la fuente de alimentación, una salida de alimentación de la placa o un módulo MOSFET.

Al arrancar, un ventilador puede consumir brevemente más corriente que en funcionamiento normal. Si se conectan varios ventiladores a una salida, sus corrientes se suman.

## Ruido, vibración y rodamiento

El ruido depende de algo más que las RPM.

Sound is affected by:

- blade shape;
- balancing;
- bearing type;
- mounting;
- grill;
- duct;
- filter;
- enclosure resonance;
- multiple fans nearby.

Las descripciones técnicas enumeran el ruido en `dB(A)`, pero en un recinto real el ventilador puede sonar diferente. Una parrilla con una geometría deficiente, una pared cercana o un montaje rígido en un panel delgado pueden hacer que un buen ventilador sea ruidoso.

Para un dispositivo que funciona durante horas, es mejor elegir un ventilador no sólo por el precio y el tamaño, sino también por la vida útil, el rodamiento y la temperatura.

## Temperatura y ubicación de instalación

Un ventilador que funciona bien en un banco puede degradarse rápidamente en una cámara caliente.

Comprobar:

- fan operating temperature;
- temperatura del aire cerca del calentador;
- distancia del elemento calefactor;
- si el flujo caliente llega directamente al motor;
- si el montaje se ablanda;
- whether wires dry out;
- si el ventilador se obstruye con polvo o fibras.

Si el ventilador es responsable del flujo de aire del calentador, su falla debe considerarse en la lógica de seguridad. No se puede diseñar un calentador de modo que un ventilador detenido genere inmediatamente una temperatura peligrosa sin un apagado de emergencia.

## Filtros y Conductos

Un filtro, una rejilla y un conducto pueden reducir significativamente el flujo de aire útil.

Signos típicos:

- el ventilador hace ruido pero el flujo de aire es débil;
- filter barely gets any air through;
- el aire pasa por alto el filtro a través de los huecos;
- la temperatura cerca del calentador aumenta más rápido que la temperatura de la cámara;
- Después de montar la cubierta, el flujo de aire es peor que en el banco.

Para filtrar una cámara de manera efectiva, no solo es necesario colocar un ventilador, sino también asegurar un paso de aire a través del filtro. Si al aire le resulta más fácil pasar por un hueco, lo hará.

## Qué comprobar antes de comprar

Antes de comprar un ventilador, revisa:

- tamaño y espesor;
- voltage;
- current;
- type: axial or radial;
- airflow;
- static pressure;
- noise;
- RPM;
- bearing type;
- 2-pin/3-pin/4-pin;
- operating temperature;
- lifetime;
- airflow direction;
- conector y distribución de pines;
- whether it suits a filter, duct or free circulation.

Para un filtro y un conducto estrecho, no elija un ventilador sólo por CFM. Mire la presión estática y pruebe en un montaje real.

## Típicos Errors

- connected 12V fan to 24V;
- conecté el ventilador de 24 V a 12 V y pensé que estaba roto;
- ventilador de alimentación de GPIO;
- no estableció puntos en común para MOSFET/PWM externos;
- no tuvo en cuenta la corriente de inicio;
- conectó varios ventiladores a una salida débil;
- ventilador seleccionado solo por tamaño;
- instaló un ventilador de flujo libre en un filtro denso;
- piense que el cable del tacómetro es un cable de control;
- piense que el PWM de 4 pines es lo mismo que el de 2 pines;
- controle el ventilador PWM de 4 pines encendiendo/apagando la alimentación;
- ventilador instalado en zona caliente sin control de temperatura;
- No revisé el flujo de aire después de instalar la cubierta, el filtro y el conducto.

## Principal Point

Se elige un ventilador para la tarea: libre circulación, filtro, conducto, radiador, calentador o refrigeración de componentes electrónicos. Para espacios abiertos, el flujo de aire es importante; Para filtros y conductos, la presión importa.

Verifique el voltaje, la corriente, el tipo de cable, el PWM/tacómetro, la temperatura de funcionamiento y la resistencia real del sistema. En un dispositivo con calentador, el ventilador debe ser parte de un sistema térmico seguro, no un componente decorativo.

## Referencia Materials

- [Noctua: Microcontroller guide for PWM and RPM monitoring](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - practical explanation of 4-pin PWM, tachometer, power and PWM frequency around 25 kHz.
- [Noctua: Fan pin configuration](https://www.noctua.at/faq-redirects/en/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-) - standard 4-pin fan pinout and behavior when only power is connected.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - explanation of airflow, static pressure, operating point and system resistance.
- [DigiKey: Selecting A Fan](https://www.digikey.ca/en/articles/selecting-a-fan) - fan type selection, fan curve, system resistance and difference between axial and radial fans.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - official Klipper sections for fans: `fan`, `heater_fan`, `temperature_fan`, `controller_fan` and `fan_generic`.
