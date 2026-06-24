# Relé de estado sólido

Un relé de estado sólido o SSR es un relé sin contactos mecánicos. Aplica una débil señal de control desde el controlador a la entrada SSR, y la salida SSR enciende o apaga una carga.

En dispositivos simples para impresoras 3D, SSR se utiliza principalmente para un calentador de red: cámara, secadora, mesa o módulo de calentamiento separado. Es una forma conveniente de controlar una carga `110-230V AC` desde electrónica de bajo voltaje, pero no es una forma de hacer que la red sea segura.

Si el proyecto tiene `110-230V AC`, la sección de potencia debe montarse en una carcasa, con fusible, terminales normales, aislamiento, protección de tensión del cable y comprensión de la seguridad eléctrica.

## Diferencia entre SSR y relé ordinario

Un relé electromagnético ordinario hace clic porque los contactos se mueven físicamente en el interior. La bobina del relé necesita energía, a menudo necesita un controlador de transistor, diodo de protección, y los contactos pueden chisporrotear, vibrar y desgastarse.

SSR cambia la carga usando semiconductores. Por lo tanto, no hay clic, no hay desgaste de contactos mecánicos y es mejor para ciclos frecuentes de encendido/apagado del calentador.

Pero SSR no es "relé sin desventajas".

SSR tiene sus propias limitaciones:

- se calienta;
- a menudo requiere disipador de calor;
- puede tener pequeña fuga de corriente en estado apagado;
- tolera peor sobrecargas y picos que un contactor correctamente elegido;
- puede fallar en estado "encendido";
- debe elegirse para carga AC o DC;
- no reemplaza fusible, carcasa y protección térmica de emergencia.

Para ciclos de conmutación poco frecuentes, un relé ordinario o contactor puede ser más apropiado. Para control frecuente de calentador resistivo, SSR a menudo es más práctico.

## Qué hay dentro del SSR AC

Un SSR AC generalmente contiene:

- circuito de entrada de señal de control;
- aislamiento óptico;
- circuito de disparo;
- TRIAC de potencia o par de tiristores;
- circuito amortiguador u otra protección contra picos;
- terminales de potencia para la carga.

En términos simples, es un circuito TRIAC listo para usar en una carcasa. Por lo tanto, SSR es conveniente cuando no desea calcular optoacoplador TRIAC, TRIAC, amortiguador, espaciados de placa y sección de red usted mismo.

Una carcasa lista para usar no elimina la necesidad de verificación. Especialmente si el SSR es barato, no tiene especificación técnica o tiene una clasificación de corriente sospechosamente alta en la carcasa.

## SSR AC y SSR DC

SSR debe elegirse según el tipo de carga:

- **SSR AC** - para corriente alterna, por ejemplo calentador de red `110-230V AC`;
- **SSR DC** - para corriente continua, por ejemplo carga DC `12V` o `24V`.

Estos son dispositivos diferentes. SSR AC no puede ponerse automáticamente en un calentador DC `24V`: puede no apagarse. SSR DC no puede considerarse apropiado para `230V AC`: puede ser peligroso y no estar clasificado para tal circuito.

Debe verificar no solo la etiqueta `AC` o `DC`, sino también el rango de voltaje de salida.

Ejemplos de etiquetado:

```text
Entrada: 3-32V DC
Salida: 24-380V AC
```

Esto significa:

- la entrada es controlada por señal DC de bajo voltaje;
- la salida cambia carga AC en el rango especificado;
- no necesita alimentar la carga desde el lado entrada a través del SSR.

Antes de comprar, verifique las líneas `Input`, `Output`, `Load voltage`, `Load current` y el diagrama de conexión del fabricante.

## Diagrama de conexión típica

SSR generalmente se coloca en la ruptura de la línea de potencia de la carga. El controlador se conecta solo a la entrada SSR, mientras que el circuito de carga pasa a través de la salida SSR.

![Estructura interna del relé de estado sólido SSR](../../img/01-electronics-basics/04-ssr-internal-structure.png)

*Fuente: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SSR.png), Thomas Verdyck, CC BY-SA 3.0*

Puntos importantes:

- la entrada SSR y la salida SSR son lados diferentes del dispositivo;
- el lado de bajo voltaje no debe conectarse al lado de red;
- SSR se coloca en la ruptura de la línea de potencia de carga, generalmente `Line`;
- la puesta a tierra de protección `PE` no se interrumpe a través del SSR;
- el fusible debe proteger el cableado y la carga;
- el calentador necesita protección térmica independiente;
- toda la sección de red debe estar cerrada al tacto.

SSR no se considera un desconectador de servicio. Para mantenimiento, necesita una forma física de cortar energía: interruptor, disyuntor, conector u otra interrupción de circuito estándar. En la práctica, puede haber diferentes esquemas según reglas locales, tipo de energía, puesta a tierra de protección y carcasa. Si no está seguro, una persona calificada debe verificar el circuito.

## Cruce por cero, encendido aleatorio y control

SSR AC viene con diferentes métodos de encendido.

**SSR de cruce por cero** enciende la carga cerca del cruce por cero del voltaje de red. Esta es una buena opción para encendido/apagado simple de un calentador resistivo: menos ruido y conmutación más suave.

**SSR de encendido aleatorio** enciende la salida casi inmediatamente después de aplicar la señal de control. Este tipo se utiliza cuando se necesita lógica diferente, control de fase o requisitos específicos de carga.

Para una cámara, secadora o calentador simple, generalmente no se necesita control rápido del atenuador. A menudo, el control lento es suficiente: por ejemplo, encender el calentador durante segundos, no cientos de veces por segundo.

No todos los SSR son adecuados para control de fase. Si necesita específicamente un regulador de potencia de fase, ese es un tipo de dispositivo separado y un tema separado con ruido, calentamiento y requisitos de carga.

## Fuga de corriente

SSR puede pasar una pequeña corriente incluso cuando está "apagado". Esto se llama corriente de fuga.

Para un calentador potente, tal corriente generalmente no crea calentamiento perceptible, pero para una pequeña lámpara, controlador LED, fuente de alimentación o carga muy pequeña, puede ser perceptible: el indicador puede brillar débilmente, la entrada de fuente de alimentación puede comportarse de manera extraña.

Por lo tanto, SSR no debe considerarse un cortacircuitos ideal. Antes del primer encendido del calentador, verifique que la carga no se calienta cuando se quita la señal de control. Es mejor probar primero la salida SSR con una pequeña carga segura, una lámpara o multímetro, no inmediatamente con el calentador principal.

Para mantenimiento, parada de emergencia e aislamiento completo, necesita un interruptor, disyuntor, fusible, conector u otro medio físico de corte de energía.

## Calentamiento y disipador de calor

SSR se calienta durante la operación. En estado encendido, hay una caída de voltaje en el elemento de potencia, lo que significa que se genera calor.

Debe verificar:

- corriente de carga;
- corriente máxima SSR a temperatura real;
- caída de voltaje en salida;
- requisitos de disipador de calor;
- temperatura dentro de la carcasa;
- orientación del disipador de calor y flujo de aire;
- calidad del contacto térmico entre SSR y disipador de calor;
- temperatura de terminales e hilos después de la prueba.

La etiqueta `25A` o `40A` no significa que el SSR soportará esa corriente sin disipador de calor en una carcasa cerrada y caliente junto a un calentador. Los fabricantes generalmente especifican corriente en condiciones específicas de refrigeración.

Regla práctica para un proyecto simple: no elija SSR exactamente para corriente de carga. Plan margen, use disipador de calor, lea la especificación técnica y verifique la temperatura en la carcasa real. El margen del `50%` es el límite inferior para una estimación inicial, no una garantía para ninguna instalación.

## SSR no protege el calentador

SSR es un interruptor de potencia, no un sistema de seguridad.

Un calentador necesita capas independientes:

- fusible o disyuntor para cableado y carga;
- sensor de temperatura correcto;
- límites de temperatura de software;
- verificación de calentamiento en firmware;
- termostato independiente, fusible térmico o interruptor bimetálico;
- carcasa hecha de material que resiste temperaturas reales;
- primera prueba bajo observación.

Modo de falla importante: SSR puede degradarse y permanecer encendido. Por lo tanto, la protección térmica de emergencia debe poder cortar la energía del calentador independientemente del controlador y SSR.

## Qué cargas son apropiadas

SSR es más fácil de usar con cargas AC resistivas:

- calentador;
- almohadilla térmica de silicona;
- bombilla incandescente;
- carga térmica simple sin electrónica integrada.

Tenga cuidado con:

- motores;
- ventiladores AC;
- transformadores;
- solenoides;
- fuentes de alimentación;
- controladores electrónicos;
- cargas con corriente de irrupción alta.

Las cargas inductivas y electrónicas pueden requerir un tipo SSR diferente, amortiguador, varistor, contactor o circuito separado. No puede elegir SSR solo por la etiqueta "40A".

## Qué verificar antes de comprar

Antes de comprar SSR, verifique:

- carga AC o DC;
- voltaje de carga;
- corriente y potencia de carga;
- voltaje de entrada de control;
- compatibilidad de entrada con controlador: `3.3V`, `5V`, `12V` u otro nivel;
- tipo de encendido: cruce por cero o aleatorio;
- corriente máxima con refrigeración necesaria;
- ¿se necesita disipador de calor?;
- ¿hay especificación técnica?;
- ¿hay diagrama de conexión normal?;
- terminales y distancias de aislamiento;
- calidad del fabricante;
- dónde se coloca el fusible;
- dónde estará la protección térmica independiente.

Si no hay documentación y el SSR debe controlar un calentador de red, esa es una mala opción.

## Errores comunes

- confundido entrada y salida SSR;
- comprado SSR DC en lugar de SSR AC o viceversa;
- no verificado rango de voltaje de salida;
- conectado SSR AC a calentador DC y sorprendido de que no se apaga;
- elegido SSR exactamente para corriente de carga;
- instalado SSR sin disipador de calor;
- instalado SSR en carcasa cerrada y caliente;
- no considerado fuga de corriente;
- usar SSR como única forma para parada de emergencia;
- olvidado fusible;
- no instalado protección térmica independiente;
- dejado terminales de red accesibles;
- controlar SSR con PWM demasiado rápido sin entender tipo SSR y carga.

## El punto principal

SSR es conveniente para control de carga frecuente y silencioso, especialmente calentador de red. Pero SSR debe elegirse para tipo de carga, voltaje, corriente, método de encendido y punto operativo térmico.

Para carga `110-230V AC`, SSR no elimina la seguridad eléctrica. Necesita carcasa, fusible, cableado normal, disipador de calor si es necesario y protección térmica independiente del calentador.

## Materiales de referencia

- [Omron: Descripción general de relés de estado sólido](https://www.ia.omron.com/support/guide/18/introduction.html) - diseño SSR, aislamiento óptico, tipos y principios de aplicación general.
- [Omron: Glosario SSR y notas de instalación](https://www.ia.omron.com/support/guide/18/further_information.html) - definiciones de `load voltage`, `leakage current`, `output ON voltage drop`, cruce por cero, amortiguador y notas sobre disipación térmica.
- [Panasonic: Principio de operación SSR](https://industry.panasonic.com/global/en/products/control/relay/solid-state/principle_operation) - diferencia entre SSR cruce por cero y aleatorio, comportamiento con cargas AC resistivas e inductivas.
- [Sensata/Crydom: Disipadores de calor serie HS](https://www.sensata.com/products/relays/solid-state-relays/ssr-accessories/hs-series-heat-sinks) - por qué SSR genera calor y por qué disipador debe coincidir con corriente y temperatura.
- [DigiKey: Relés de estado sólido - Una descripción general básica](https://www.digikey.com/en/blog/solid-state-relays-a-basic-overview) - breve descripción general de tipos de salida SSR, cruce por cero, encendido aleatorio y limitaciones en comparación con relés mecánicos.
