# Lista de verificación de diagnóstico

Esta lista de verificación es necesaria cuando el dispositivo no funciona o se comporta extrañamente.

La idea es simple: primero elimina el peligro, luego verifica potencia y cableado y solo después muévete a firmware, sensores y cargas.

## 1. Detén y apaga el poder

Primero, apaga el dispositivo.

Especialmente si hay:

- olor;
- cable calentándose;
- terminal calentándose;
- humo;
- sonido extraño;
- chisporroteando;
- el calentador no se apagará;
- el disyuntor o fusible disparan.

No cambies cables bajo potencia.

## 2. Desconecta carga de potencia

Antes del diagnóstico es mejor desconectar temporalmente:

- calentador;
- tira LED poderosa;
- servo;
- motor;
- carga de potencia externa.

Primero verifica que controlador y lógica están vivos sin carga peligrosa.

Si el dispositivo tiene 110-230V AC, no sostengas abierta parte de mains bajo potencia en el banco.

## 3. Verifica fuente de alimentación

Con multímetro verifica:

- ¿hay voltaje en salida de fuente de alimentación?
- ¿es voltaje correcto?
- ¿es polaridad correcta?
- ¿baja el voltaje bajo carga?

Por ejemplo:

- línea 24V debería ser aproximadamente 24V;
- línea 12V debería ser aproximadamente 12V;
- línea 5V debería ser aproximadamente 5V;
- línea 3.3V debería ser aproximadamente 3.3V.

La desviación aceptable depende de fuente de alimentación y dispositivo, pero un error obvio como 24V en lugar de 12V debería encontrarse antes de conectar carga.

## 4. Verifica polaridad

Verifica dónde está plus y dónde está minus.

No confíes solo en color de cable.

Verifica:

- marcas de placa;
- marcas de fuente de alimentación;
- pinout del módulo;
- multímetro;
- diagrama de conexión.

La polaridad invertida a menudo mata módulo instantáneamente.

## 5. Verifica GND común

Si hay módulo externo o potencia separada, verifica `GND` común.

Esto es importante para:

- módulo MOSFET;
- servo;
- ventilador PWM;
- HX711;
- RFID;
- sensores externos;
- DC-DC separado.

Si las señales van entre dispositivos, deben tener un nivel de referencia común, a menos que el circuito use aislamiento especial.

## 6. Verifica terminales y conectores

Inspecciona:

- cable insertado todo el camino;
- conductor apretado, no aislamiento;
- sin hilos expuestos;
- sin oscurecimiento;
- sin olor;
- el terminal no se sacude;
- el conector no sostiene "por fe";
- la cubierta de caso no pellizca cable.

Mueve cables con poder off. Si el contacto claramente cae mecánicamente, arregla cableado primero.

## 7. Verifica controlador sin carga

Conecta controlador sin carga de potencia.

Verifica:

- ¿se detecta vía USB?
- ¿inicia firmware?
- ¿hay comunicación con host?
- ¿no se calienta microcontrolador?
- ¿no parpadea potencia?
- ¿son visibles los logs?

Si el controlador no se detecta incluso sin carga, no reconectes calentador y módulos de potencia hasta que encuentres la causa.

## 8. Verifica firmware y configuración

Verifica:

- firmware construido para placa correcta;
- ruta serial/CAN/USB correcta seleccionada;
- los pines en config coinciden con pinout;
- `sensor_type` correcto;
- `min_temp` y `max_temp` razonables;
- salidas no accidentalmente invertidas;
- sin conflictos de pin.

Si el calentador se comporta opuestamente después del cambio de configuración, por ejemplo "off", pero la temperatura sube, apaga poder y verifica config y circuito de potencia.

## 9. Verifica sensores

Antes de calentar verifica sensores.

Para termistor:

- temperatura como temperatura ambiente;
- sin `MINTEMP`;
- sin `MAXTEMP`;
- las lecturas no saltan;
- resistencia como se espera;
- cuando se calienta con mano las lecturas cambian correctamente.

Para otros sensores:

- potencia correcta;
- interfaz seleccionada correctamente;
- dirección o pines coinciden con config;
- cables cortos y no colgando.

## 10. Verifica salida sin carga

Si necesitas verificar MOSFET, relé o salida de placa, hazlo primero sin carga peligrosa.

Opciones:

- ventilador de prueba pequeño;
- LED con resistencia;
- multímetro;
- carga segura débil.

No comiences diagnóstico con calentador poderoso.

Para calentador, antes del primer encendido la verificación numérica es útil: mide resistencia y compara con `R = U^2 / P` esperado. Si hay carcasa de metal o `PE`, verifica sin cortocircuito a carcasa. Para calentador `12V`/`24V` la primera ejecución es mejor a través de fuente de laboratorio con límite de corriente o fusible temporal.

## 11. Verifica interruptor de potencia por separado

Para MOSFET/SSR/relé verifica:

- tipo de carga correcto: AC o DC;
- voltaje correcto;
- terminales correctos;
- entrada de control;
- `GND` común si se necesita;
- disipador de calor si se necesita;
- entrada y salida no mezcladas.

AC SSR y DC SSR no pueden ser intercambiados.

Para SSR por separado verifica estado "off": con señal de control removida la carga no debe calentarse. La primera es mejor usar carga segura pequeña, lámpara o multímetro, no calentador principal.

## 12. Conecta carga con breve prueba

Cuando las verificaciones básicas pasaron, conecta carga brevemente y bajo supervisión.

Verifica:

- carga enciende;
- carga apaga;
- terminales no se calientan;
- cables no se calientan;
- MOSFET/SSR no se sobrecalienta;
- sensor muestra temperatura realista;
- controlador no se reinicia;
- fusible no dispara.

La primera prueba de calentador no debería ser larga e desatendida.

## 13. Verifica después de pocos minutos de operación

Después de pocos minutos verifica:

- terminales;
- cables;
- fuente de alimentación;
- MOSFET;
- SSR;
- carcasa cerca del calentador;
- lecturas del sensor;
- estabilidad del controlador.

Si algo inesperadamente se calentó, apaga el poder y regresa a verificar potencia, cableado e interruptor de potencia.

## Qué no hacer

No puedes:

- repetidamente encender dispositivo si algo se calienta u huele;
- sostener 110-230V AC abierto en el banco;
- cambiar cables bajo potencia;
- aumentar fusible "para que no dispare";
- deshabilitar protección térmica para prueba;
- cortocircuitar termostato de emergencia;
- probar calentador poderoso sin sensor de temperatura;
- dejar primera prueba desatendida.

## Orden muy corto

Si necesitas orden muy corto:

1. Apaga el poder.
2. Desconecta carga de potencia.
3. Verifica voltaje de fuente de alimentación.
4. Verifica polaridad.
5. Verifica `GND` común.
6. Verifica terminales y cables.
7. Verifica controlador sin carga.
8. Verifica firmware y pinout.
9. Verifica sensores.
10. Verifica salida sin carga peligrosa.
11. Verifica MOSFET/SSR/relé.
12. Conecta carga con breve prueba.
13. Verifica calentamiento de cables, terminales y partes de potencia.

## Puntos clave

- El diagnóstico comienza apagando poder y reduciendo riesgo.
- La carga de potencia mejor desconectada para verificaciones básicas.
- Potencia, polaridad, `GND` y terminales verificados antes del firmware.
- El calentador no puede ser usado como primer indicador de prueba.
- Si protección dispara, encuentra la causa, no deshabilites protección.

## Referencias

- [SparkFun: Consejos de resolución de problemas](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - secuencia básica de verificación de conexiones, potencia y problemas de hardware.
- [SparkFun: Cómo alimentar un proyecto](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - cómo pensar en voltaje, corriente y potencia del proyecto.
- [Fluke: Cómo medir resistencia con multímetro digital](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - medición de resistencia segura en circuito desenergizado.
- [Tom's Hardware: Cómo arreglar thermal runaway de impresora 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - verificaciones prácticas de termistor, calentador, ventilador, potencia y cableado.
- [Referencia de configuración de Klipper: min_temp, max_temp y verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - verificaciones de software de temperatura, sensor y subida de temperatura de calentador esperada.
