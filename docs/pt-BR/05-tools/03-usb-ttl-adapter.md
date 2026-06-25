# USB-TTL

Um adaptador USB-TTL, ou adaptador USB-UART, permite que seu computador se comunique com um microcontrolador via UART através de USB.

Você precisa dele para:

- programar algumas placas;
- ler logs;
- depurar comunicação UART;
- configurar módulos;
- recuperar uma placa quando USB normal não funciona;
- conectar a um dispositivo sem USB-UART integrado.

Os adaptadores comuns usam chips como CH340, CP2102, FT232 e similares.

## USB-TTL ou USB-UART

As descrições do consumidor frequentemente dizem USB-TTL.

Tecnicamente geralmente significa um adaptador USB-UART com níveis lógicos TTL.

A coisa principal a compreender:

- O lado USB conecta ao computador;
- O lado UART conecta ao microcontrolador;
- o adaptador não é um programador para todas as placas;
- o adaptador não substitui ST-Link se você precisar programar STM32 através de SWD.

## Pinos principais

Tipicamente há:

- `GND`;
- `TX`;
- `RX`;
- `VCC` ou `3V3`/`5V`;
- às vezes `DTR`;
- às vezes `CTS`, `RTS`.

Mínimo para comunicação:

- `GND`;
- `TX`;
- `RX`.

A energia só é conectada se você tiver certeza de que o adaptador deve alimentar a placa.

## TX e RX são interconectados

UART é conectado assim:

```text
adapter TX -> board RX
adapter RX -> board TX
adapter GND -> board GND
```

`TX` é transmissão.

`RX` é recepção.

O transmissor de um dispositivo deve conectar ao receptor do outro.

Se você conectar `TX` a `TX`, a comunicação geralmente não funcionará.

![TX/RX interconectados em conexão UART](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Fonte: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## Terra comum

O `GND` do adaptador e `GND` da placa devem estar conectados.

Sem uma terra comum, UART pode não funcionar ou funcionará instável.

Mesmo que a placa seja alimentada por uma fonte de alimentação separada, a terra ainda é necessária como o nível de sinal comum.

## Níveis lógicos 3.3V e 5V

Este é um dos pontos mais importantes.

O adaptador pode funcionar com lógica em:

- `3.3V`;
- `5V`;
- comutável `3.3V/5V`.

Muitas placas e módulos modernos usam lógica 3.3V: ESP32, RP2040, muitos STM32.

Se você aplicar um sinal UART 5V a uma entrada 3.3V, você pode danificar o pino ou toda a placa.

Antes de conectar, verifique:

- que nível lógico a placa usa;
- que nível lógico o adaptador usa;
- o que o jumper 3.3V/5V faz;
- se o jumper altera apenas a energia `VCC` ou também os níveis `TX/RX`.

Alguns adaptadores fornecem potência 5V, mas sinais lógicos 3.3V. Outros mudam tanto potência quanto níveis. Verifique a documentação específica do adaptador.

## Energia do adaptador

Nem sempre é necessário conectar `VCC`.

Frequentemente é mais seguro conectar apenas:

- `GND`;
- `TX`;
- `RX`.

Alimentar a placa a partir de sua fonte normal.

Você pode conectar `VCC` do adaptador se:

- a placa é classificada para essa tensão;
- a corrente da placa está dentro da capacidade do adaptador;
- não há outra energia ao mesmo tempo;
- a documentação da placa permite alimentação através deste pino.

Um erro perigoso é fornecer energia do adaptador USB-UART e de uma fonte de alimentação separada ao mesmo tempo, causando conflito das fontes.

## DTR e auto-reset

Algumas placas usam `DTR` para reset automático durante a programação.

Por exemplo, Arduino Pro Mini e placas semelhantes podem usar DTR através de um capacitor para auto-reset.

Se a programação não começar automaticamente, pode ser porque:

- DTR não está conectado;
- reset manual é necessário;
- o adaptador errado é selecionado;
- o bootloader errado é selecionado;
- a velocidade ou placa no IDE é selecionada incorretamente.

Para leitura de logs simples, DTR geralmente não é necessário.

## Como verificar se o adaptador é visível para o sistema

Em macOS e Linux, o adaptador geralmente aparece como um dispositivo em `/dev`.

Exemplos:

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

No Windows, aparece como uma porta `COM`.

Se a porta não aparecer:

- verifique o cabo USB;
- tente uma porta USB diferente;
- verifique o driver;
- verifique se não é apenas um cabo de carregamento;
- veja qual chip está no adaptador: CH340, CP2102, FT232.

Adaptadores baratos às vezes requerem um driver separado, especialmente no Windows.

## Teste de loopback

Forma simples de verificar o adaptador:

1. Conecte `TX` e `RX` do adaptador juntos.
2. Abra um terminal série.
3. Selecione a porta e velocidade.
4. Digite texto.

Se os caracteres que você digita voltarem, o adaptador e a porta provavelmente funcionam.

Após o teste, remova o jumper entre `TX` e `RX`.

## Erros comuns

- `TX` conectado a `TX` e `RX` a `RX`;
- esqueceu `GND` comum;
- selecionou nível 5V para uma placa 3.3V;
- conectou `VCC` mesmo que a placa já esteja alimentada separadamente;
- cabo USB virou ser apenas de carregamento;
- driver CH340/CP210x/FTDI não instalado;
- porta COM errada selecionada;
- velocidade UART não corresponde;
- esperava USB-UART para programar STM32 através de SWD;
- confundiu modo de boot ou reset durante a programação.

## Os essenciais

- Adaptador USB-UART é necessário para comunicação UART entre computador e placa.
- Mínimo para comunicação: `GND`, `TX`, `RX`.
- `TX` do adaptador vai para `RX` da placa, `RX` do adaptador vai para `TX` da placa.
- Verifique os níveis lógicos 3.3V/5V antes de conectar.
- `VCC` só é conectado se você definitivamente precisa de energia do adaptador.
- Se o adaptador não é visível, verifique o cabo, driver e porta USB.

## Materiais de referência

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - adaptador USB-para-série, TX/RX/GND, VCC, DTR e comutação 3.3V/5V.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - adaptador USB-UART CH340C moderno, pinos, LEDs e seleção de tensão.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - noções básicas de UART, TX/RX e comunicação série.
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - drivers oficiais CP210x Virtual COM Port.
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - cabo de exemplo com potência 5V e lógica 3.3V, mostrando por que potência e níveis de sinal precisam ser lidos separadamente.
