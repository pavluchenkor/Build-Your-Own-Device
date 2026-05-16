# Herramientas

Esta sección no trata sobre la colección de herramientas.

Se trata del conjunto mínimo que te ayuda a montar un dispositivo de forma segura, verificar conexiones y encontrar errores simples sin adivinar.

En dispositivos caseros alrededor de iDryer e impresoras 3D, las herramientas se necesitan para tareas prácticas:

- comprobar si hay 24V en la fuente de alimentación;
- entender si los polos positivo y negativo están invertidos;
- verificar continuidad en un cable;
- probar un termistor;
- ver si la señal UART llega;
- flashear un controlador;
- hacer un conector apropiado;
- encontrar caída de voltaje en la fuente;
- entender por qué un ventilador o calefactor no se enciende.

## Conjunto mínimo

Para la mayoría de construcciones simples, las herramientas útiles incluyen:

- multímetro;
- adaptador USB-UART o USB-TTL;
- soldador;
- herramienta de crimping;
- cortador de cables y pelador;
- tubo termorretráctil;
- terminales y conectores apropiados;
- ST-Link si trabajas con STM32;
- osciloscopio o al menos un multímetro con contador de frecuencia para diagnósticos más complejos.

No necesitas comprar todo a la vez. Pero un multímetro y herramientas de cable adecuadas normalmente se amortizan rápidamente.

## Las herramientas no reemplazan la comprensión

Un multímetro no hace segura la parte de la red eléctrica.

Un soldador no arregla un esquema deficiente.

Un osciloscopio no se necesita si los polos positivo y negativo están invertidos.

Así que el orden es:

1. Entiende qué debe estar conectado.
2. Verifica la fuente de alimentación.
3. Verifica el cableado.
4. Verifica sensores y señales.
5. Solo entonces busca problemas complejos.

## Qué habrá en esta sección

- `02-multimeter.md` - medir voltaje DC, continuidad, resistencia, fusibles y por qué la medición de corriente es más peligrosa.
- `03-usb-ttl-adapter.md` - adaptadores USB-UART, TX/RX/GND, niveles lógicos 3.3V/5V, flashing y registros.
- `04-soldering.md` - soldar cables, pads, módulos, soldaduras frías, tubo termorretráctil y alivio de tensión.
- `05-crimping-connectors.md` - Dupont, JST, terminales, Faston, terminales y verificación de calidad de crimping.
- `06-st-link.md` - ST-Link, STM32, SWD, recuperación de placa después de flashing fallido.
- `07-oscilloscope.md` - PWM, UART, caída de voltaje, ruido y advertencia de seguridad crítica sobre voltaje de red.

## Qué vale la pena comprar adecuadamente

Hay cosas en las que no debes ahorrar:

- un multímetro con sondas apropiadas y modo de continuidad;
- un soldador con control de temperatura;
- soldadura y flux de calidad;
- herramienta de crimping para terminales específicos;
- conectores y terminales clasificados para la corriente necesaria;
- tubo termorretráctil;
- cables de calibre correcto.

El crimping deficiente o los terminales débiles pueden causar más problemas que el firmware deficiente.

## Qué no puedes hacer

No puedes:

- medir resistencia en un circuito energizado;
- medir corriente de la misma manera que mides voltaje;
- introducir un multímetro en 110-230V AC sin entender la seguridad;
- soldar la parte de potencia "de cualquier forma";
- usar Dupont para un calefactor;
- cambiar cables mientras la alimentación está encendida;
- dejar partes de la red abiertas en la mesa;
- pensar que si un cable "sostiene", el contacto es bueno.

## Lo esencial

- El multímetro es la primera herramienta de diagnóstico.
- USB-UART se necesita para registros, flashing y comunicación con dispositivos UART.
- Soldar y crimping son tareas diferentes, y para conectores, crimping a menudo es mejor.
- ST-Link se necesita cuando trabajas con STM32 y SWD.
- El osciloscopio no se necesita para todos, pero rápidamente muestra señales, caída y ruido.
- Para la parte de potencia, la calidad del contacto, el calibre del cable y la seguridad importan más que la apariencia del ensamblaje.

## Materiales de referencia

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - fundamentos del multímetro: voltaje, corriente, resistencia, continuidad.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - verificaciones de hardware para potencia, conexiones y calor.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - lógica de comunicación UART y serial básica.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - guía práctica de soldadura y calidad de conexión.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - documentación oficial de ST-Link y SWD/SWIM.
