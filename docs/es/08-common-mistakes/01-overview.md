# Errores comunes

Esta sección no está aquí para criticarte.

Está aquí para ayudarte a identificar rápidamente errores comunes en un dispositivo DIY: fuente de alimentación floja, cable suelto, sensor mostrando basura, controlador reiniciando, calentador comportándose extrañamente.

El formato de sección es directo:

- síntoma;
- causa probable;
- qué verificar;
- qué no hacer;
- cómo arreglarlo con seguridad.

## La regla principal de diagnóstico

Si el dispositivo se comporta extrañamente, no cambies inmediatamente firmware, resuelda todo o aumentes potencia.

Primero, verifica lo básico:

1. fuente de alimentación;
2. polaridad;
3. `GND` común;
4. terminales y conectores;
5. sensores;
6. interruptores de potencia;
7. firmware y configuración.

La mayoría de problemas en dispositivos simples resultan ser no "electrónica compleja", sino fuente de alimentación, cableado o conexiones incorrectas.

## Cuándo detener

Apaga el poder inmediatamente si:

- aparece olor a quemado;
- el cable se calienta;
- el terminal se calienta;
- el conector se oscurece;
- la carcasa se ha puesto caliente en un lugar inesperado;
- el calentador no se apagará;
- el disyuntor o fusible disparan;
- el sensor de temperatura muestra basura;
- el dispositivo funciona solo cuando mueves el cable.

No "enciéndelo una vez más para mirar". Si algo se está calentando, oliendo o chisporroteando, encuentra la causa primero sin potencia.

## Grupos principales de errores

En esta sección, los errores se dividen en grupos:

- `02-power-mistakes.md` - fuente de alimentación débil, voltaje incorrecto, floja, cables delgados, sin margen.
- `03-wiring-mistakes.md` - polaridad invertida, terminales pobres, sin tierra común, conectores malos.
- `04-controller-mistakes.md` - placa inadecuada, lógica 3.3V/5V, GPIO en lugar de salida de potencia, firmware incorrecto.
- `05-heater-ssr-mistakes.md` - calentadores, SSR, MOSFET, 110-230V AC, sensor de temperatura, disipadores de calor y protección.
- `06-diagnostic-checklist.md` - orden general de verificación cuando el dispositivo no funciona.

## Por qué la fuente de alimentación se verifica primero

La fuente de alimentación afecta casi todo.

Si la fuente de alimentación es débil o los cables son delgados, los síntomas pueden parecer un problema de firmware:

- el controlador se reinicia;
- Wi-Fi se cae;
- la pantalla parpadea;
- el servo se sacude;
- el ventilador no inicia;
- los sensores muestran valores aleatorios;
- el calentador calienta mal.

Hasta que la fuente de alimentación se verifique con un multímetro bajo carga, es difícil diagnosticar con confianza todo lo demás.

## Por qué el cableado es más importante de lo que parece

Una conexión pobre puede funcionar "casi normalmente".

Esto es exactamente lo que es peligroso:

- hoy funciona;
- cuando se vibra se desconecta;
- cuando se calienta, el contacto empeora;
- el terminal se oscurece gradualmente;
- el cable comienza a calentarse;
- el sensor aparece y desaparece.

Si el dispositivo cambia comportamiento cuando mueves el cable, esto no es un error de software. Esto es un problema de conexión.

## Por qué la protección no debe ser deshabilitada

Thermal runaway, `MINTEMP`, `MAXTEMP`, "heater not heating" y errores similares existen no para molestar al usuario.

Estas son señales de que el controlador ya no confía en la lectura de temperatura o ve comportamiento de calentamiento peligroso.

Mala idea:

- deshabilitar protección térmica;
- expandir límites de temperatura sin entender la razón;
- reemplazar el fusible con uno más grande;
- cortocircuitar el termostato directamente;
- cortocircuitar la protección "para prueba".

Idea correcta: encuentra la razón por la que la protección dispara.

## Cómo leer esta sección

Si el dispositivo no funciona en absoluto, comienza con la lista de verificación de diagnóstico.

Si el síntoma es claro, ve al artículo relevante:

- reinicios, parpadeo, calor débil - fuente de alimentación;
- funciona cuando mueves el cable - cableado;
- placa no detectada o pines que no responden - controlador;
- el calentador no se apagará o SSR se calienta - calentador y SSR;
- todo es unclear - lista general de verificación.

## Puntos clave

- La mayoría de errores comienzan con potencia, cableado y conexiones incorrectas.
- Si algo se calienta, huele u se oscurece, apaga el poder.
- El diagnóstico procede de simple a complejo.
- La protección de firmware y protección de hardware no debe ser deshabilitada por conveniencia.
- El AC mains 110-230V no puede ser diagnosticado "en el banco" sin entender seguridad eléctrica.

## Referencias

- [SparkFun: Consejos de resolución de problemas](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - enfoque básico para verificar conexiones, fuente de alimentación, calentamiento y problemas de hardware.
- [SparkFun: Cómo alimentar un proyecto](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - voltaje, corriente y selección de potencia para un proyecto electrónico.
- [Tom's Hardware: Cómo arreglar thermal runaway de impresora 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - análisis práctico de sensor de temperatura, calentador, ventilador, fuente de alimentación y cableado durante thermal runaway.
- [Referencia de configuración de Klipper: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - verificación oficial de calentador y sensor de temperatura verificando tasa de subida de temperatura esperada y error acumulado.
- [Guía de medidor de potencia Qwiic de SparkFun](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - ejemplo de la necesidad de `GND` común al medir/controlar carga externa.
