# Primeros pasos

Ya está imprimiendo en una impresora 3D y desea construir un secador de filamentos. Pero cuando abre el esquema, las preguntas aparecen inmediatamente: qué fuente de alimentación, dónde va la masa, MOSFET o SSR, por qué necesita un disipador de calor. Esta sección responde estas preguntas paso a paso — desde el primer cálculo de corriente hasta un dispositivo funcional.

Después de esta sección, entenderá qué está construyendo, por qué exactamente de esta manera, dónde podrían estar los peligros y cómo revisar el dispositivo antes de encenderlo.

La sección lo guía gradualmente desde conceptos simples hasta resultados reales.

El camino aquí va de lo simple a lo complejo:

1. Primero comprenda la potencia, la corriente, la carga y la seguridad básica.
2. Luego, descubra qué controladores existen y cuál elegir.
3. Luego, comprenda los componentes básicos: calentador, ventilador, sensores, pantallas, RFID y celdas de carga.
4. Luego, aprenda a usar herramientas mínimas: multímetro, USB-UART, soldador, prensa de terminales.
5. Luego, pase a las conexiones prácticas.
6. Luego, piense en la carcasa y las piezas impresas en 3D.
7. Al final, tenga a mano una lista de errores comunes y una lista de verificación de diagnóstico.

La idea principal:

No necesita entender toda la electrónica a la vez. Es suficiente proceder paso a paso y cada vez entender el siguiente paso pequeño.

Lo que esta sección debería proporcionar:

- comprensión de cómo los circuitos de bajo voltaje `12V`/`24V DC` difieren del suministro principal `110-230V AC`;
- capacidad de calcular aproximadamente la corriente de carga;
- comprensión de cuándo necesita MOSFET, SSR o relé;
- comprensión de cómo ESP32, Arduino, RP2040 y STM32 difieren en la práctica;
- comprensión de por qué para Klipper MCU es mejor buscar RP2040 o STM32;
- comprensión básica de sensores, ventiladores, calentadores y pantallas;
- habilidades mínimas de diagnóstico con multímetro;
- comprensión de qué piezas impresas se pueden colocar cerca del calor;
- lista de errores que es mejor no repetir.

Lo que esta sección no hace:

- no reemplaza a un electricista cuando trabaja con `110-230V AC`;
- no enseña diseño profundo de circuitos;
- no intenta explicar toda la física;
- no da permiso para ensamblar dispositivos peligrosos sin entender la seguridad.

Cómo leer:

- si el tema es nuevo — proceda en orden;
- si ya ha construido dispositivos — abra la sección requerida como referencia;
- si el dispositivo no funciona — primero mire `08-common-mistakes`;
- si trabaja con `110-230V AC` — primero lea todo lo relacionado con seguridad, SSR, cables, terminales y puesta a tierra de protección.

## Materiales de referencia

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - conceptos básicos de voltaje, corriente, resistencia, circuito cerrado y ley de Ohm.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - orden práctico del diagnóstico inicial: alimentación, conexiones, polaridad, uniones de soldadura, cables y caídas de voltaje.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - por qué las mediciones de resistencia se realizan con la alimentación desconectada y por qué se necesita un multímetro para comprobar componentes.
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - por qué se necesita la puesta a tierra de protección y por qué trabajar con voltaje principal requiere disciplina de seguridad separada.

## Ver también

- [Cálculo de carga 24V](../01-electronics-basics/01-load-calculation-24v.md) - primer tema práctico sobre voltaje, corriente, potencia y margen de la fuente de alimentación.
- [Componentes comunes](../03-common-components/01-overview.md) - mapa de las piezas que se encuentran con mayor frecuencia en dispositivos simples.
- [Herramientas](../05-tools/01-overview.md) - lo que necesita para verificar, flashear, soldar y diagnosticar.
- [Guías prácticas](../06-practical-guides/01-connecting-fan.md) - ejemplo de la primera conexión de carga segura a través del controlador.
- [Errores comunes](../08-common-mistakes/01-overview.md) - lo que debe buscar si el dispositivo no se enciende, se calienta, hace ruido o se comporta de manera inestable.
