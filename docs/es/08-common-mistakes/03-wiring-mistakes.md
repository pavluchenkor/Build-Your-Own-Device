# Errores de cableado

El cableado a menudo rompe el dispositivo más que la electrónica misma.

El contacto pobre, polaridad invertida o terminal débil puede parecer un error de firmware, sensor o controlador.

## Síntomas

Signos típicos de problemas de cableado:

- el dispositivo funciona a veces, luego no;
- la placa se detecta solo cuando el cable se mueve;
- los sensores muestran basura;
- la temperatura salta;
- el ventilador inicia intermitentemente;
- USB se cae;
- el terminal se calienta;
- el cable se oscurece u huele;
- el módulo funciona en el banco pero no funciona en la carcasa;
- después de cerrar la cubierta el dispositivo deja de funcionar.

Si un síntoma cambia cuando el cable se mueve, primero verifica el cableado.

## Plus y menos invertidos

La polaridad no puede ser verificada "por color".

El cable rojo a menudo es plus, el cable negro a menudo es menos, pero esto no es una garantía. En un dispositivo DIY, el constructor anterior o tú mismo podrían haber mezclado los colores.

Antes de conectar:

- verifica marcas de placa;
- verifica pinout del módulo;
- mide voltaje con multímetro;
- verifica dónde está `+` y dónde está `GND`;
- no conectes módulo si el pinout no está claro.

La polaridad invertida puede destruir instantáneamente una placa, sensor, ventilador o DC-DC.

## Sin tierra común

La tierra común se necesita cuando un módulo se alimenta separadamente y la señal viene del controlador.

Ejemplos:

- servo con potencia 5V separada;
- módulo MOSFET para ventilador;
- ventilador PWM de 4-pin;
- HX711;
- módulo RFID;
- sensor externo.

Sin `GND` común la señal podría no tener sentido. El dispositivo podría no responder, sacudirse o funcionar inestablemente.

## Contacto pobre en terminal

El terminal podría parecer apretado, pero sostener el cable mal.

Razones:

- cable no insertado todo el camino;
- aislamiento apretado en lugar de conductor;
- cable trenzado deshilachado;
- tornillo aflojado;
- terminal no clasificado para corriente;
- cable demasiado delgado o demasiado grueso para terminal;
- sin ferrule donde se necesita.

El contacto pobre causa calentamiento. El calentamiento empeora el contacto. Este es un ciclo peligroso.

Después de una breve prueba bajo carga, verifica si los terminales y conectores se están calentando.

## Dupont no es para carga de potencia

Los cables Dupont son convenientes para breadboards y señales débiles.

Pero no pueden ser considerados cableado de potencia normal para:

- calentadores;
- ventiladores poderosos;
- tiras LED;
- servos con corriente grande;
- potencia del dispositivo;
- 110-230V AC.

Dupont podría sostener mal, tener área de contacto pequeña y calentarse a corrientes para las que no está diseñado.

Para la parte de potencia necesitas terminales apropiados, conectores, sección de cable y alivio de tensión.

## TX y RX

Para UART a menudo se necesita cableado cruzado:

- `TX` de un dispositivo a `RX` de otro;
- `RX` de un dispositivo a `TX` de otro;
- `GND` común.

Errores típicos:

- conectado `TX` a `TX`;
- conectado `RX` a `RX`;
- olvidó `GND`;
- eligió velocidad incorrecta;
- niveles de lógica no coinciden: 5V y 3.3V.

Si UART no funciona, primero verifica `TX/RX/GND`, luego velocidad y configuración.

## I2C y SPI

Para I2C:

- `SDA` debe ir a `SDA`;
- `SCL` debe ir a `SCL`;
- se necesita `GND` común;
- la dirección del dispositivo no debe entrar en conflicto;
- los cables deben ser cortos.

Para SPI:

- `MOSI`, `MISO`, `SCK`, `CS` deben coincidir con el pinout;
- cada dispositivo tiene su propio `CS`;
- se necesita `GND` común;
- cables largos pueden romper la conexión.

RFID RC522 a menudo confunde gente: el pin `SDA` en la placa podría significar `SS/CS` para SPI, no `SDA` de I2C.

## Cables de mains y señal

Los cables 110-230V AC, carga DC de potencia y señales débiles no deben ser colocados aleatoriamente en un haz.

Problemas:

- interferencia;
- calentamiento;
- daño de aislamiento;
- riesgo de tocar parte de mains;
- diagnóstico difícil;
- peligro del usuario.

La parte de mains debe estar separada físicamente. Los sensores de bajo voltaje, UART/I2C/SPI y cables de termistor son mejor corridos separadamente de cables de potencia del calentador.

## Hilos expuestos

Un cable expuesto fuera del terminal es un mal signo.

Puede:

- tocar un terminal vecino;
- cortocircuitar la carcasa;
- meterse bajo la cubierta;
- golpear el ventilador;
- crear peligro durante el mantenimiento.

Después de apretar en el terminal ningún hilo desnudo largo debería sobresalir.

## Qué verificar

Mini-checklist:

1. Polaridad de fuente de alimentación.
2. `GND` común.
3. Correspondencia de pinout.
4. Calidad del terminal.
5. Sin aislamiento apretado en lugar de conductor.
6. Sin hilos expuestos.
7. Los cables no están tensos.
8. La cubierta no pellizca cable.
9. Cables de potencia y señal separados.
10. Conector clasificado para corriente.
11. El dispositivo no cambia comportamiento cuando el cable se mueve.

## Qué no hacer

No puedes:

- cambiar cables bajo potencia;
- sostener abierta parte de mains en el banco;
- usar Dupont para calentador;
- apretar cable trenzado para que algunos hilos sobresalgan;
- retorcer cables de potencia sin conexión apropiada;
- ignorar un terminal calentándose;
- considerar "a veces funciona" normal.

## Puntos clave

- Si el dispositivo responde al movimiento de cable, esto es un problema de cableado.
- La polaridad se verifica con multímetro, no por color.
- `GND` común se necesita para la mayoría de módulos externos con potencia separada.
- Dupont es adecuado para breadboards y señales, pero no para carga de potencia.
- Los cables de mains y bajo voltaje deben estar separados.
- Terminal calentándose es razón para detener, no continuar la prueba.

## Referencias

- [SparkFun: Consejos de resolución de problemas](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - verificación básica de conexiones, continuidad, ciclo de potencia y calentamiento.
- [SparkFun: Comunicación serial](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX y comunicación serial.
- [SparkFun: I2C](https://learn.sparkfun.com/tutorials/i2c) - líneas `SDA`, `SCL`, direcciones y errores típicos de I2C.
- [SparkFun: Interfaz periférica serial](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - líneas SPI, `MOSI`, `MISO`, `SCK`, `SS/CS`.
- [FRC Design: Diseño para impresión 3D](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - consejos prácticos sobre carcasas de electrónica: agujeros de cable, ventilación, acceso de puerto y remoción de servicio de componente.
