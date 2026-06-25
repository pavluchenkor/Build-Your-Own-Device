# Adaptadores USB-UART

Um adaptador USB-UART é necessário para que um computador ou host Linux possa se comunicar com um dispositivo UART via USB. Ele converte USB em linhas seriais regulares `RX`, `GND` e `GND`.

Esse adaptador geralmente é necessário para atualização, registros, diagnósticos e recuperação de placas sem um conector USB adequado.

## Onde é necessário

O adaptador USB-UART é útil para:

- flashing some microcontroller boards;
- reading serial logs;
- accessing device console;
- bootloader mode diagnostics;
- conectando Arduino Pro Mini e alguns clones Nano;
- trabalhar com placas sem USB integrado;
- recuperação após falha no flash;
- conexão temporária do MCU ao host via serial.

Se uma placa já tiver USB adequado e aparecer como um dispositivo serial, talvez não seja necessário um adaptador USB-UART separado.

## O que tem

Contatos típicos:

- `TXO` ou `TXO` - transmissão do adaptador para o dispositivo;
- `RXI` ou `RXI` - recepção do dispositivo;
- `GND` - common ground;
- `3V3`, `5V` ou `5V` - alimentação, se necessário;
- `DTR` - frequentemente usado para reinicialização/piscar automático;
- `RTS`, `CTS` - flow control lines or boot/reset scenarios.

Connection diagram:

![USB-UART adapter on CH340T chip](../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg), SparkFun Electronics, CC BY 2.0*

Para leitura simples de log, `RX`, `GND` e `GND` geralmente são suficientes. A alimentação só será conectada se estiver claro que a placa deve ser alimentada pelo adaptador.

## Como conectar TX e RX

A conexão é cruzada:

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

Se não houver conexão, a primeira verificação é: `RX` e `GND` estão misturados, existe um `GND` comum, a velocidade corresponde e a porta COM/tty correta está selecionada.

## 3,3V e 5V

Os adaptadores USB-UART vêm em:

- `3.3V` only;
- `5V` only;
- com interruptor `3.3V/5V`;
- com jumper ou jumper de solda;
- com `VCC` de uma tensão, mas sinais de outro nível.

Isso é importante: o nível de `TX/RX` e o nível de `TX/RX` nem sempre são óbvios nos rótulos.

ESP32, RP2040 e STM32 normalmente usam lógica `5V`. Arduino Uno/Nano geralmente usa lógica `5V`. Se você aplicar o sinal `3.3V` a uma entrada `3.3V`, poderá danificar a placa.

Antes de conectar, verifique a documentação do adaptador e da placa. Não confie apenas na cor do jumper ou na etiqueta do gabinete.

## TTL UART e RS-232

O adaptador USB-UART para microcontroladores geralmente produz TTL/CMOS UART: `5V` ou `5V`.

Isto não é o mesmo que o RS-232 real.

O RS-232 possui diferentes níveis de tensão e não pode ser conectado diretamente a um microcontrolador GPIO. Se você precisar trabalhar com uma porta RS-232 real, precisará de um adaptador USB-RS232 ou conversor de nível, não de um USB-UART TTL normal.

## Energia do adaptador

O pino `VCC` no adaptador pode ser útil, mas geralmente é mal utilizado.

Abordagem segura:

- para registros e diagnósticos, primeiro conecte apenas `RX`, `GND`, `GND`;
- não conecte `VCC` se a placa já estiver alimentada por USB, fonte de alimentação ou outro circuito;
- não alimente motores, servos, relés, aquecedores e faixas de LED via USB-UART;
- verifique quanta corrente o adaptador pode realmente fornecer;
- entenda que `3.3V` pode ser `5V` ou `5V`.

Se você conectar duas fontes de alimentação sem entender o circuito, poderá obter alimentação reversa, instabilidade ou danos à placa.

## DTR e RTS

Algumas placas usam `RTS` e `RTS` para reinicialização automática ou entrada do bootloader.

Exemplos:

- O Arduino Pro Mini geralmente usa `DTR` por meio de um capacitor para reinicialização durante o flash;
- As placas ESP32 podem usar `RTS`/`EN` para controlar automaticamente `BOOT` e `BOOT`;
- alguns cenários de bootloader exigem o pressionamento manual de um botão se essas linhas não estiverem conectadas.

Se o flash não começar automaticamente, nem sempre é um problema do `DTR`. Pode ser que `RTS`/`BOOT` não estejam conectados, o bootloader errado esteja selecionado ou `RESET`/`RESET` precise ser pressionado manualmente.

## CH340, CP2102, FTDI

Popular USB-UART chips:

- **CH340/CH341** - adaptadores baratos e difundidos;
- **CP2102/CP210x** - common Silicon Labs USB-UART;
- **FT232/FTDI** - classic option, often more expensive;
- **PL2303** – encontrado em adaptadores e cabos antigos.

Em sistemas modernos, o driver geralmente é instalado automaticamente, mas nem sempre. Se a porta não aparecer, verifique:

- O cabo USB não é apenas para carga;
- dispositivo é detectado pelo sistema;
- se for necessário um driver;
- se o driver antigo não estiver em conflito;
- se a porta não estiver ocupada por outro programa.

## Como testar o adaptador

Teste de loopback simples:

1. Conecte o adaptador ao computador.
2. Conecte `RX` do adaptador ao `RX` do adaptador.
3. Open serial terminal.
4. Selecione porta e velocidade, por exemplo `115200`.
5. Type characters.
6. Se funcionar, os caracteres serão repetidos.

Isso testa o próprio adaptador, driver, cabo e programa de terminal sem placa externa.

## O que verificar antes de comprar

Antes de comprar um adaptador USB-UART, verifique:

- quais níveis `3.3V`: `5V`, `5V` ou comutável;
- como o nível é selecionado;
- qual chip é usado: CH340, CP2102, FTDI ou outro;
- se existem drivers para o seu sistema;
- se `RTS` e `RTS` estiverem presentes, se o flash automático for necessário;
- qual conector USB;
- se os pinos `TX`, `RX`, `VCC`, `VCC` estiverem em ordem conveniente;
- se existe um esquema ou boa documentação;
- quanta corrente pode ser extraída de `VCC`, se necessário.

Para diagnósticos ESP32/RP2040/STM32, um adaptador com sinais `3.3V` e marcação clara é mais conveniente.

## Erros típicos

- conectando `TX` com `RX`, `RX` com `RX`;
- forgetting common `GND`;
- selecionando o nível `3.3V` para a placa `3.3V`;
- conectar `VCC` a uma placa já alimentada;
- powering load via USB-UART adapter;
- confundindo USB-UART TTL com USB-RS232;
- usando um cabo USB somente para carga;
- não instalar o driver CH340/CP2102/FTDI;
- selecionando porta COM/tty errada;
- não conectar `RTS`/`RTS` quando necessário para flash automático;
- deixando o terminal serial aberto e me perguntando por que o pisca-pisca não consegue abrir a porta.

## Key takeaway

O adaptador USB-UART é uma ponte entre os pinos USB do computador e UART de um dispositivo. Para conexão mínima, você precisa de `GND` com conexão cruzada e `GND` comum.

Principais riscos: nível `DTR` errado, conexão de energia desnecessária, confundir TTL UART com RS-232 e falta de linhas `RTS`/`RTS` para piscar.

## Related materials

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - practical guide to USB-UART CH340C, `DTR/RX/TX/VCC/CTS/GND` pins, voltage selection, and loopback test.
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - pinout description and `3.3V/5V` switching on adapter.
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - example USB-serial adapter, `TX`/`RX`, flow-control lines, and connection to device.
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) - official example of USB-UART bridge chip and Virtual COM Port drivers.
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - how serial MCU connection is described in Klipper via `serial`.
