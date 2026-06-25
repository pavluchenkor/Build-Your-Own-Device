# Erros de Fiação

A fiação geralmente quebra mais o dispositivo do que os próprios componentes eletrônicos.

Mau contato, polaridade invertida ou terminal fraco podem parecer um erro de firmware, sensor ou controlador.

## Symptoms

Sinais típicos de problemas de fiação:

- o dispositivo funciona às vezes e depois não;
- placa detectada somente quando o cabo é movido;
- sensors show garbage;
- temperature jumps;
- fan starts intermittently;
- USB drops off;
- terminal heats up;
- wire darkens or smells;
- módulo funciona na bancada mas não funciona no case;
- depois de fechar a tampa o dispositivo para de funcionar.

Se um sintoma mudar quando o fio for movido, verifique primeiro a fiação.

## Mais e menos invertidos

A polaridade não pode ser verificada “por cor”.

O fio vermelho geralmente é positivo, o fio preto geralmente é negativo, mas isso não é uma garantia. Em um dispositivo DIY, o construtor anterior ou você mesmo pode ter misturado as cores.

Antes de conectar:

- check board markings;
- check module pinout;
- medir a tensão com multímetro;
- verifique onde `GND` e onde `GND`;
- não conecte o módulo se a pinagem não estiver clara.

Reversed polarity can instantly destroy a board, sensor, fan, or DC-DC.

## No Common Ground

O aterramento comum é necessário quando um módulo é alimentado separadamente e o sinal vem do controlador.

Exemplos:

- servo com alimentação separada de 5V;
- MOSFET module for fan;
- 4-pin PWM fan;
- HX711;
- RFID module;
- external sensor.

Sem o `GND` comum o sinal pode não fazer sentido. O dispositivo pode não responder, sacudir ou funcionar de forma instável.

## Mau contato no terminal

O terminal pode parecer preso, mas segura mal o fio.

Reasons:

- fio não inserido completamente;
- isolamento preso em vez de condutor;
- stranded wire frayed;
- screw loosened;
- terminal não classificado para corrente;
- fio muito fino ou muito grosso para terminal;
- sem ponteira onde necessário.

Mau contato causa aquecimento. O aquecimento piora o contato. Este é um ciclo perigoso.

Após um breve teste sob carga, verifique se os terminais e conectores estão aquecendo.

## Dupont não para carga de energia

Os fios Dupont são convenientes para placas de ensaio e sinais fracos.

Mas eles não podem ser considerados cabos de alimentação normais para:

- heaters;
- powerful fans;
- LED strips;
- servos com grande corrente;
- device power;
- 110-230V AC.

O Dupont pode ter uma má aderência, ter uma pequena área de contato e aquecer em correntes para as quais não foi projetado.

Para a parte de alimentação, você precisa de terminais, conectores, seção transversal de fio e alívio de tensão adequados.

## TX e RX

Para UART, muitas vezes é necessária fiação cruzada:

- `RX` de um dispositivo para `RX` de outro;
- `TX` de um dispositivo para `TX` de outro;
- common `GND`.

Erros típicos:

- connected `TX` to `TX`;
- connected `RX` to `RX`;
- forgot `GND`;
- escolheu a velocidade errada;
- os níveis lógicos não coincidem: 5V e 3,3V.

Se o UART não funcionar, primeiro verifique `TX/RX/GND`, depois a velocidade e as configurações.

## I2C e SPI

Para I2C:

- `SDA` deve ir para `SDA`;
- `SCL` deve ir para `SCL`;
- need common `GND`;
- o endereço do dispositivo não deve entrar em conflito;
- os fios devem ser curtos.

Para SPI:

- `MISO`, `SCK`, `CS`, `CS` devem corresponder à pinagem;
- each device has its own `CS`;
- need common `GND`;
- fios longos podem interromper a conexão.

RFID RC522 muitas vezes confunde as pessoas: o pino `SS/CS` na placa pode significar `SDA` para SPI, não I2C `SDA`.

## Fios principais e de sinal

Fios de 110-230 V CA, carga de alimentação CC e sinais fracos não devem ser colocados aleatoriamente em um pacote.

Problems:

- interference;
- heating;
- insulation damage;
- risco de tocar na parte da rede elétrica;
- difficult diagnostics;
- user danger.

A parte principal deve ser separada fisicamente. Sensores de baixa tensão, UART/I2C/SPI e fios de termistor funcionam melhor separadamente dos fios de alimentação do aquecedor.

## Exposed Strands

Um fio exposto fora de um terminal é um mau sinal.

Pode:

- touch a neighboring terminal;
- encurte o caso;
- fique sob a capa;
- bata no ventilador;
- create a danger during maintenance.

Após a fixação no terminal, nenhum fio longo e desencapado deverá sobressair.

## O que verificar

Mini-checklist:

1. Power supply polarity.
2. Common `GND`.
3. Pinout correspondence.
4. Terminal quality.
5. Nenhum isolamento fixado em vez de condutor.
6. No exposed strands.
7. Wires not taut.
8. A tampa não comprime o cabo.
9. Fios de alimentação e sinal separados.
10. Conector classificado para corrente.
11. O dispositivo não altera o comportamento quando o fio é movido.

## O que não fazer

Você não pode:

- change wires under power;
- segure a parte aberta da rede elétrica na bancada;
- use Dupont como aquecedor;
- clamp stranded wire so some strands stick out;
- torcer os fios de alimentação sem conexão adequada;
- ignore a heating terminal;
- considere "às vezes funciona" normal.

## Key Points

- Se o dispositivo responder ao movimento do fio, isso é um problema de fiação.
- A polaridade é verificada com multímetro, não por cor.
- O `GND` comum é necessário para a maioria dos módulos externos com alimentação separada.
- Dupont é adequado para protoboards e sinais, mas não para carga de energia.
- Os fios da rede elétrica e de baixa tensão devem ser separados.
- O terminal de aquecimento é motivo para parar e não continuar o teste.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic checking of connections, continuity, power cycle, and heating.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX, and serial communication.
- [SparkFun: I2C](https://learn.sparkfun.com/tutorials/i2c) - `SDA`, `SCL` lines, addresses, and I2C typical mistakes.
- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI lines, `MOSI`, `MISO`, `SCK`, `SS/CS`.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - practical advice on electronics cases: wire holes, ventilation, port access, and component service removal.
