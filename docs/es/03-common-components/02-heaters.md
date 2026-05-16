# Calentadores

Un calentador es una carga que convierte energía eléctrica en calor. En un dispositivo DIY simple, es el componente más peligroso: un error en un ventilador generalmente resulta en pobre flujo de aire, pero un error en un calentador puede causar sobrecalentamiento, carcasa fundida, cableado dañado, o riesgo de incendio.

En impresoras 3D y dispositivos tipo iDryer, los calentadores se encuentran en el hotend, cama, cámara, secador de filamento, conducto de aire, o módulo de calentamiento separado.

## Dónde Se Usa

Tareas típicas:

- calentar el hotend;
- calentar la cama;
- precalentar la cámara de la impresora;
- secar filamento;
- precalentar aire antes de un filtro o conducto;
- mantener temperatura en un pequeño volumen de proceso.

Estas son tareas diferentes. Un calentador para un hotend de metal, una almohadilla de cama de silicona, y un módulo PTC de aire no son intercambiables sin recalcular potencia, montaje, flujo de aire y protección.

## Tipos de Calentadores

Opciones comunes:

- calentador de cartucho;
- almohadilla de silicona;
- calentador PTC;
- elemento de calentamiento cerámico;
- módulo calentador con ventilador listo;
- placa de calentamiento;
- cama de calentamiento de red;
- ensamblaje de nicromo o resistivo en enclosure terminado.

Un calentador de cartucho generalmente se inserta en un bloque de metal. Necesita buen contacto térmico con el metal y montaje confiable del sensor de temperatura.

Una almohadilla de silicona generalmente se pega o presiona contra una superficie plana. Necesita una superficie plana, buena adhesión, un sensor de temperatura y protección contra despegue.

Un calentador PTC limita parcialmente el aumento de temperatura debido a sus propiedades, pero esto no reemplaza el controlador, sensor, fusible, enclosure y verificación de flujo de aire. PTC no automatiza hace un dispositivo seguro.

Un módulo calentador con ventilador listo combina calentador y flujo de aire, pero aún necesita ser verificado para voltaje, potencia, temperatura, materiales de alojamiento y protección de emergencia.

## Voltaje, Potencia y Corriente

Antes de conectar, necesitas encontrar:

- voltaje de operación;
- potencia;
- corriente;
- tipo de corriente: DC o AC;
- temperatura máxima;
- temperatura de operación del cable;
- método de montaje;
- requisitos de flujo de aire;
- método de control permitido.

La corriente se calcula por la fórmula:

```text
corriente = potencia / voltaje
```

Ejemplos:

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> aproximadamente 1.3A
```

Un calentador de bajo voltaje y alta potencia es más seguro para voltaje, pero requiere corrientes grandes. Las corrientes grandes requieren una fuente de alimentación adecuada, cables, terminales, MOSFET/SSR y fusible.

Un calentador de red en `110-230V AC` puede entregar alta potencia con corriente menor, pero el riesgo de choque es mucho mayor. Para la parte de red necesitas conocimiento de seguridad eléctrica, enclosure, terminales, aislamiento, toma de tierra donde sea requerido, fusibles y aislamiento galvánico del control.

## Control del Calentador

El controlador no debe alimentar el calentador directamente desde GPIO. GPIO solo proporciona una señal de control.

Opciones típicas de control de potencia:

- MOSFET - para calentadores DC `12V`/`24V`;
- DC SSR - para calentadores DC si están correctamente clasificados para DC;
- AC SSR - para calentadores AC de red;
- relé mecánico - para apagado/encendido raro, pero no para PID/PWM frecuente;
- salida de potencia lista - solo si está clasificada para la corriente y voltaje necesarios.

AC SSR y DC SSR son dispositivos diferentes. El tipo incorrecto puede no apagar el calentador o funcionar de manera insegura.

Un módulo MOSFET típico para Arduino/ESP32 no puede usarse como interruptor `110-230V AC`. Si el módulo no está diseñado para carga de red, no puede conectarse a la red.

## Capas de Seguridad

Un calentador no puede ser diseñado como "controlador lo enciende - controlador lo apaga". Necesitas múltiples capas de protección.

![Capas de control seguro del calentador](../../../img/03-common-components/02-heater-safety-stack.svg)

Lógica mínima:

- fuente de alimentación está clasificada para la corriente;
- fusible está seleccionado para cableado y carga;
- interruptor de potencia coincide con el tipo de carga;
- sensor de temperatura está montado en el lugar correcto;
- firmware tiene `min_temp`, `max_temp` y verificación de calentamiento;
- hay protección térmica de hardware independiente: fusible térmico, termostato o interruptor bimetálico;
- enclosure y materiales soportan la temperatura real;
- la primera prueba se realiza bajo supervisión.

La protección térmica de hardware debe funcionar independientemente del controlador. En el caso simple, se coloca en serie en el circuito de potencia del calentador para romper físicamente la potencia. Esto no es solo otro sensor para el firmware.

Si el controlador se cuelga, el sensor se cae, un MOSFET hace cortocircuito o un SSR se queda atascado, la protección debe cortar la potencia del calentador.

## Sensor de Temperatura

Un calentador no conoce su propia temperatura. El controlador toma la decisión basada en el sensor.

Si el sensor:

- está presionado mal;
- está en la ubicación incorrecta;
- se cae;
- es el tipo incorrecto en el firmware;
- tiene pobre contacto térmico;
- mide aire en lugar de la pieza crítica;

el controlador puede continuar calentando aunque la temperatura real ya sea peligrosa.

Para un hotend, el contacto del sensor de temperatura con el bloque de metal importa. Para un calentador de aire, es importante entender qué se está midiendo: la temperatura del elemento, la temperatura del aire después del elemento, la temperatura de la cámara, o la temperatura cerca de la bobina. Estos son puntos diferentes, y pueden diferir significativamente.

## Flujo de Aire y Transferencia de Calor

Un calentador libera potencia, pero esa potencia debe ir de manera segura a donde es prevista.

Para un calentador de aire, el flujo de aire es crítico:

- sin flujo, el elemento puede sobrecalentarse localmente;
- ventilación débil no remueve el calor;
- un filtro obstruido cambia el modo de calentamiento;
- los conductos de plástico pueden ablandarse;
- un sensor de temperatura puede no ver qué está sucediendo en el elemento.

Para un calentador de cámara, es importante verificar no solo la temperatura de aire objetivo, sino también la temperatura cerca del calentador, cables, SSR/MOSFET, terminales y piezas de plástico.

## Cables, Terminales y Conectores

Un calentador a menudo funciona durante largos períodos y consume corriente significativa. El pobre contacto se convierte en una fuente de calor.

Verifica:

- calibre del cable;
- clase de temperatura de aislamiento;
- clasificación de corriente del terminal;
- calidad del crimpado;
- apriete del tornillo;
- herrajes en cables trenzados;
- alivio de tensión;
- distancia de piezas calientes;
- ausencia de conductores expuestos.

Si un terminal se oscurece, huele, ablanda plástico o se calienta, la potencia debe apagarse y la causa encontrada. No solo aumentes el fusible o aprietes más tarde.

## Qué Verificar Antes de Comprar

Antes de comprar un calentador, verifica:

- qué medio debe calentar: metal, aire, cama, cámara;
- voltaje y tipo de corriente;
- potencia;
- corriente;
- temperatura de operación;
- temperatura máxima de superficie;
- requisitos de flujo de aire;
- método de montaje;
- material de cable y aislamiento;
- interruptor de potencia compatible;
- lugar para sensor de temperatura;
- lugar para protección térmica independiente;
- enclosure y materiales circundantes;
- disponibilidad de descripción técnica o documentación clara.

Si la página del producto carece de voltaje, potencia, temperatura e información de aplicación, tal calentador no es adecuado para un primer proyecto seguro.

## Primera Prueba

El primer calentamiento se realiza brevemente y bajo supervisión.

Procedimiento:

1. Verifica resistencia del calentador y compara con cálculo `R = U^2 / P` si voltaje y potencia son conocidos.
2. Verifica cortocircuitos donde sea aplicable.
3. Si hay enclosure metálico o tierra de protección `PE`, verifica que el calentador no haga cortocircuito al enclosure.
4. Verifica voltaje de suministro sin el calentador.
5. Verifica que el interruptor de control apague la carga.
6. Verifica que el sensor de temperatura lea un valor razonable.
7. Para calentador `12V`/`24V`, si es posible, comienza a través de una fuente de alimentación de laboratorio con limitación de corriente o fusible temporal.
8. Habilita calentamiento a baja potencia o brevemente.
9. Observa si la temperatura sube en el lugar correcto.
10. Verifica que el comando de apagado realmente detiene el calentamiento.
11. Verifica calentamiento de cables, terminales, MOSFET/SSR y enclosure.
12. Verifica protección de emergencia por un escenario que puedas simular de manera segura.

No dejes un nuevo calentador desatendido en el primer arranque.

## Errores Típicos

- conectado calentador a voltaje incorrecto;
- no calculé corriente;
- alimentar calentador a través de conector débil;
- usar MOSFET para calentador AC de red;
- mezclé AC SSR y DC SSR;
- instalé SSR sin disipador de calor cuando fue necesario;
- olvidé fusible;
- sin protección térmica independiente;
- pobre montaje del sensor de temperatura;
- hice enclosure de PLA cerca del calentador;
- no consideré flujo de aire y filtro obstruido;
- probé en banco pero no en enclosure;
- dejé parte de red expuesta;
- aumenté fusible en lugar de encontrar por qué se activó.

## Punto Principal

Un calentador es elegido por la tarea, voltaje, potencia, método de transferencia de calor y seguridad. No puedes tratarlo como una simple "carga de dos cables".

Primero calcula corriente, selecciona interruptor de potencia, cableado y fusible. Luego asegura sensor de temperatura, protección de firmware, protección térmica de hardware independiente, un enclosure adecuado y pruebas en el mundo real.

## Materiales de Referencia

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - configuración de calentador, sensores de temperatura, `min_temp`, `max_temp` y verificación de calentamiento en Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - límites de temperatura, `MINTEMP`, `MAXTEMP` y protección térmica en Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - explicación básica de SSR, tipos, aplicación y medidas térmicas.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - por qué SSR necesita un disipador de calor y cómo el régimen térmico se relaciona con la corriente de carga.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - notas prácticas sobre aplicación de calentador de cartucho, contacto térmico y selección de potencia.
