# Interface SPI

SPI é uma interface de comunicação serial rápida entre um controlador e dispositivos periféricos. Expansão: `Serial Peripheral Interface`.

O SPI é frequentemente usado onde os dados precisam ser transmitidos mais rapidamente que o I2C ou onde o dispositivo é projetado para SPI: display, cartão SD, módulo RFID, sensor, driver ou chip de memória.

## Onde o SPI é usado

Em impressoras 3D e dispositivos semelhantes ao iDryer, o SPI pode aparecer em:

- RFID/NFC modules like RC522;
- OLED/TFT displays;
- SD cards;
- acelerômetros para modelador de entrada;
- drivers de passo, por exemplo TMC2130/TMC5160;
- memory chips;
- ADC/DAC e placas de expansão;
- alguns sensores e módulos especializados.

O SPI geralmente é mais rápido que o I2C, mas requer mais fios e uma seleção de pinos mais cuidadosa.

## Basic lines

Um SPI típico usa:

- `SCK` or `CLK` - clock signal;
- `MOSI` - dados do controlador para o dispositivo;
- `MISO` - dados do dispositivo para o controlador;
- `CS`, `SS`, or `NSS` - select specific device;
- `GND` - common ground;
- module power.

Diagrama com dois dispositivos:

![SPI: basic exchange operation between master and slave device](../../img/02-controllers/08-spi-basic-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`MOSI`, `MISO` e `CS` podem ser compartilhados por vários dispositivos. Mas cada dispositivo geralmente precisa de seu próprio `CS`.

## CS em vez de endereços

No I2C, os dispositivos são diferenciados por endereços. No SPI, geralmente não há endereços. O controlador seleciona o dispositivo com uma linha `CS` separada.

Exemplo:

```text
SCK  -> common to all SPI devices
MOSI -> common
MISO -> common
CS1  -> RFID module
CS2  -> display
CS3  -> SD card
```

Quando o controlador deseja falar com o módulo RFID, ele ativa o `CS2`. Quando quiser falar com o display, ele ativa `CS2`.

Mais comumente, `HIGH` está ativo em nível baixo: em repouso a linha é `LOW`, para selecionar um dispositivo - `LOW`. Mas isso precisa ser verificado na ficha técnica.

## MOSI/MISO e novos nomes

Em esquemas antigos e muito comuns, os nomes são:

- `MOSI` - Master Out Escravo In;
- `MISO` - Master In Slave Out;
- `SS` - Slave Select.

Na documentação mais recente, você poderá ver nomes neutros:

- `PICO` - Peripheral In Controller Out, equivalente a MOSI;
- `POCI` - Entrada do Controlador de Saída Periférica, equivalente a MISO;
- `CS` - Chip Select.

Na eletrônica de impressoras 3D, `MISO`, `SCK`, `CS`, `CS` ainda são muito comuns. O principal é entender a direção do sinal e verificar a pinagem do módulo específico.

## MISO pode não ser necessário

Nem todo dispositivo SPI realmente envia dados de volta.

Por exemplo, um display simples só pode receber comandos e pixels. Então a linha `MISO` pode estar faltando ou não ser utilizada.

Mas para dispositivos que leem dados, é necessário `MISO`:

- RFID module;
- SD card;
- sensor;
- motorista com diagnóstico;
- memory chip.

Se o módulo deveria responder e `MISO` não estiver conectado ou misturado, a inicialização poderá falhar.

## Velocidade e modo SPI

SPI tem uma velocidade. Pode ser muito maior que I2C, mas isso não significa que você precise definir o máximo imediatamente.

O trabalho é afetado por:

- wire length;
- ground quality;
- módulo e sua ficha técnica;
- noise level;
- controller frequency;
- chosen SPI mode.

O modo SPI é definido pelos parâmetros de polaridade e fase do relógio: `CPHA` e `CPHA`. O modo 0 é frequentemente usado, mas nem sempre. Se o modo estiver errado, o dispositivo poderá não responder ou retornar dados incorretos.

Na maioria das bibliotecas prontas, o modo já está definido. Mas se você estiver conectando um módulo incomum ou escrevendo uma configuração de baixo nível, será necessário verificar a folha de dados.

## 3,3V e 5V

Assim como outras interfaces, o SPI não garante níveis de tensão seguros.

ESP32, RP2040, STM32 e muitos módulos modernos operam com lógica `5V`. Arduino Uno/Nano geralmente usa `5V`.

Antes de conectar, verifique:

- module power;
- nível lógico de `MOSI`, `MISO`, `CS`, `CS`;
- se há correspondência de nível;
- se o módulo tolera `5V` nas entradas de sinal;
- se a entrada do controlador tolerar `5V`.

Por exemplo, RC522 normalmente requer energia e lógica `5V`. Conectá-lo a um Arduino `5V` sem correspondência de nível é uma má ideia.

## SPI in Klipper

No Klipper, o SPI é usado para vários dispositivos: drivers TMC, acelerômetros, alguns monitores e sensores.

Configuration may include:

- `cs_pin` - device select pin;
- `spi_bus` - hardware SPI bus;
- `spi_speed` - speed in Hz;
- `spi_software_sclk_pin`;
- `spi_software_mosi_pin`;
- `spi_software_miso_pin`.

Se o dispositivo estiver conectado a um MCU adicional, os pinos deverão pertencer a esse MCU. Tal como acontece com outras seções do Klipper, a pinagem específica da placa é mais importante do que suposições.

Rough idea:

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

Esta não é uma configuração pronta para um dispositivo específico, mas uma ilustração: todos os pinos SPI devem estar no MCU ao qual o módulo está realmente conectado.

## Comprimento do fio e interferência

O SPI pode funcionar rápido, mas não gosta de fiação longa e desleixada.

Practical rules:

- keep `SCK`, `MOSI`, `MISO`, `CS` short;
- route near `GND`;
- não passe paralelamente aos fios do aquecedor e do motor;
- reduza `spi_speed` se houver erros;
- use conectores adequados;
- não aplique SPI em toda a impressora sem motivo;
- para nós remotos, escolha com mais frequência CAN, UART/RS-485 ou um MCU separado próximo ao módulo.

A linha `SCK` é especialmente sensível: é um sinal de clock. Se estiver sujo, toda a comunicação pode ficar instável.

## SPI e RC522

RC522 é um bom exemplo de módulo SPI com confusão de nomenclatura.

Em muitas placas RC522, o pino `SS` é realmente usado como `CS`/`SDA` para SPI. Este não é I2C `SDA`.

Para RC522, normalmente você precisa de:

- `3.3V`;
- `GND`;
- `SCK`;
- `MOSI`;
- `MISO`;
- `SDA`/`SS`/`CS`;
- `RST`;
- às vezes `IRQ`, mas em projetos simples geralmente não é usado.

Um diagrama detalhado está no artigo prático: [Conectando um leitor RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## O que verificar antes de conectar

Antes de conectar um módulo SPI, verifique:

- module power;
- logic level;
- pinagem da placa específica;
- onde estão `MOSI`, `MISO`, `CS`, `CS`;
- se `DC`, `IRQ`, `IRQ` ou outros pinos forem necessários;
- qual `CS` está atribuído ao dispositivo;
- se `CS` não entrar em conflito com outro módulo;
- se for necessário SPI de hardware ou SPI de software;
- qual velocidade a documentação recomenda;
- se o firmware suportar este módulo.

## Erros típicos

- misturou `MISO` e `MISO`;
- forgot `CS`;
- conectou dois dispositivos a um `CS`;
- não conectou `GND` comum;
- aplicou `3.3V` a um módulo SPI `3.3V`;
- confundiu `SDA` em RC522 com I2C `SDA`;
- selected too high a speed;
- made wires too long;
- conectou o módulo a um MCU, mas especificou os pinos de outro;
- acho que SPI é uma interface de energia para impulsionar a carga.

## Key takeaway

SPI é uma interface rápida para módulos próximos ao controlador. Normalmente você precisa de `MOSI`, `MISO`, `CS`, `GND`, potência e `GND`.

A principal diferença do I2C: o SPI geralmente não possui endereços e cada dispositivo é selecionado por um `CS` separado. Antes de conectar, verifique a pinagem, os níveis lógicos, a velocidade, o comprimento do fio e o suporte de firmware.

## Related materials

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - practical explanation of SPI, data lines, new PICO/POCI names, and basic exchange logic.
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - why `CS` is needed and how to connect multiple SPI devices.
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - SPI vs I2C comparison, separate `CS`, speed, polarity/phase, and limitations.
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - options for connecting multiple SPI devices and role of `CS`.
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - `spi_speed`, `spi_bus`, software SPI, and `cs_pin` parameters in Klipper.
