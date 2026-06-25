# Interface CAN

CAN é uma interface de comunicação para vários dispositivos em uma linha diferencial comum. Expansão: `Controller Area Network`.

CAN veio da eletrônica automotiva e industrial, mas em impressoras 3D ele se tornou popular para placas de cabeçote de ferramentas, MCUs remotos e módulos onde você precisa de comunicação mais longa e confiável do que I2C/SPI.

## Onde o CAN é útil

Em impressoras e periféricos semelhantes ao iDryer, o CAN é usado para:

- placas de cabeçote de ferramentas no cabeçote da impressora;
- MCU adicional em um bloco remoto;
- reduzindo a contagem de fios no feixe de cabos;
- comunicação com filtro CAN, câmera ou placas secadoras;
- sistema distribuído de múltiplos controladores;
- casos em que USB ou I2C/SPI longo são inconvenientes.

CAN é especialmente útil quando um nó está longe do host ou da placa principal e há motores, aquecedores e outras fontes de ruído próximos.

## CANH, CANL e GND

Um barramento CAN físico normalmente usa:

- `CANH`;
- `CANL`;
- sometimes `GND` or common reference wire;
- alimentação do módulo separadamente, se necessário.

O sinal é transmitido como a diferença entre `CANL` e `CANL`. É por isso que o CAN lida melhor com o ruído do que linhas de sinal único.

Simplified diagram:

![High-speed CAN ISO 11898-2 bus with multiple nodes and terminators](../../img/02-controllers/09-can-iso11898-2-network.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png), EE JRW, CC BY-SA 4.0*

Para fiação, um par trançado é frequentemente usado para `CANL`/`GND`. `GND` depende do circuito, placas e documentação específicos, mas em pequenos sistemas DIY, muitas vezes é necessária uma referência comum para operação estável e segurança de interface.

## É necessário um transceptor CAN

Importante: Suporte CAN no microcontrolador e presença CAN na placa não são a mesma coisa.

Para que o CAN funcione, você precisa de:

- microcontrolador com controlador CAN ou suporte de firmware adequado;
- CAN transceptor na placa;
- correct `CANH`/`CANL` connectors;
- transceiver power;
- terminators;
- firmware construído para CAN.

Se a folha de dados do microcontrolador mencionar CAN, mas a placa não tiver transceptor, você não poderá conectar diretamente ao barramento CAN.

## Topologia e terminadores

CAN é um ônibus. Uma boa topologia se parece com uma linha com nós conectados por meio de ramificações curtas.

Normalmente são necessários dois terminadores `120 Ohm`:

- um em uma extremidade física do barramento;
- segundo na outra extremidade física.

Nem um, nem três, e nem "em cada tabuleiro". Exatamente dois nas extremidades.

Se a energia estiver desligada, em um barramento com terminação adequada, um multímetro entre `CANL` e `60 Ohm` geralmente mostra cerca de `120 Ohm`, porque dois resistores `120 Ohm` estão em paralelo.

Muitas placas possuem um jumper terminador. Alguns possuem um terminador integrado sem desativação conveniente. Portanto, antes da montagem, verifique os esquemas de todas as placas do barramento.

## Bitrate

A velocidade CAN deve corresponder em todos os nós. No Klipper, o CAN geralmente usa `1 Mbit/s`, que é `1 Mbit/s`, mas o valor específico depende do firmware, das configurações e do comprimento do barramento.

Se a taxa de bits for diferente, os nós não conseguirão se comunicar normalmente.

Para cabeamento longo ou problemático, a velocidade pode ser crítica. Quanto maior a velocidade, mais exigente será o barramento em relação à topologia, aos terminadores e à qualidade do fio.

## CAN in Klipper

No Klipper, o CAN é usado como forma de comunicação com o MCU.

Um dispositivo em CAN geralmente não é especificado via `canbus_uuid`. Em vez disso, a configuração usa `canbus_uuid`:

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

No lado Linux, você geralmente precisa de uma interface `can0`. O host deve ter um adaptador CAN:

- USB-CAN adapter;
- placa em modo ponte USB para CAN;
- HAT/adapter for SBC;
- other supported circuit.

Klipper possui uma ferramenta para localizar `canbus_uuid` de novos dispositivos não inicializados. Importante entender: se um dispositivo já estiver configurado pelo Klipper, ele poderá não aparecer mais na lista como “novo”.

## USB-to-CAN bridge

Algumas placas podem ser atualizadas no modo ponte USB para CAN. Em seguida, a placa se conecta ao host via USB e aparece no Linux como um adaptador CAN.

Isso é conveniente, mas há uma limitação importante: o modo ponte é necessário para se comunicar com um barramento CAN real e outros nós CAN. Se você tiver apenas uma placa próxima ao host e nenhum barramento CAN real, geralmente é mais simples usar o modo USB/serial normal.

Além disso, a ponte USB para CAN não será visível como `canbus_uuid`. Ele é configurado como interface CAN e usa `serial:`, não `serial:`.

## Quando o CAN é justificado

Vale a pena considerar o CAN se:

- você precisa conectar uma placa de cabeçote;
- você precisa executar a comunicação por meio de um longo feixe de cabos;
- you need multiple remote MCUs;
- você deseja reduzir os fios entre as peças móveis e o gabinete;
- you already have CAN infrastructure;
- a placa escolhida está bem documentada para Klipper CAN.

CAN pode ser desnecessário se:

- o tabuleiro fica perto do anfitrião;
- you only need one additional MCU;
- USB funciona de forma estável;
- você não tem experiência com flashing, `can0`, terminadores e redes Linux;
- o conselho escolhido está mal documentado.

Para o primeiro controlador adicional simples, o USB costuma ser mais rápido e claro. CAN faz sentido quando resolve um problema real de fiação ou distribuição de placa.

## CAN não alimenta carga

CAN é apenas comunicação.

Se uma placa CAN controlar um ventilador, aquecedor, SSR ou servo, ela ainda precisará de:

- board power;
- load power;
- MOSFET/driver/SSR;
- fuses;
- proper terminals;
- proteção térmica para aquecedores;
- recinto seguro.

CAN não substitui a eletrônica de potência e não torna um aquecedor seguro.

## O que verificar antes de comprar

Antes de comprar uma placa CAN, verifique:

- qual microcontrolador é usado;
- se a placa suportar Klipper CAN;
- se houver um transceptor CAN;
- onde estão `CANL` e `CANL`;
- se existe um terminador e como habilitá-lo;
- qual conector é usado;
- como a placa é alimentada;
- como a placa pisca;
- se existe uma instrução para `canbus_uuid`;
- se for necessário um adaptador USB-CAN separado;
- se houver esquema e pinagem;
- quais pinos e saídas de energia estão disponíveis.

Se o vendedor escrever "CAN" apenas porque o chip teoricamente o suporta, mas a placa não possui transceptor e documentação, é uma má escolha.

## Erros típicos

- misturou `CANL` e `CANL`;
- esqueci que o transceptor CAN é necessário;
- coloque um terminador em vez de dois;
- terminadores habilitados em todas as placas;
- não verificou resistência entre `CANL` e `CANL`;
- escolheu taxas de bits diferentes nos nós;
- espere `/dev/serial/by-id` da ponte USB para CAN;
- placa flashada para USB, mas conecte como CAN;
- piscou para CAN, mas não configurou `can0`;
- fez uma estrela com longos galhos em vez de um ônibus;
- acho que CAN é uma forma de alimentar a carga.

## Key takeaway

CAN é uma boa interface para MCUs remotos, placas de cabeçote de ferramentas e sistemas distribuídos dentro de uma impressora. Ele usa um par diferencial `CANL`/`CANL`, requer transceptores CAN, topologia correta e dois terminadores nas extremidades do barramento.

Para o Klipper, o CAN é útil, mas mais complexo que o USB: você precisa atualizar a placa para CAN, configurar o adaptador/`can0`, encontrar o `canbus_uuid` e verificar o barramento físico. Use CAN onde ele realmente simplifica a hidratação ou melhora a robustez da conexão.

## Related materials

- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) - official Klipper CAN documentation: hardware, host adapter, `can0`, `canbus_uuid`, terminators, and USB-to-CAN bridge.
- [Klipper: CANBUS protocol](https://www.klipper3d.org/CANBUS_protocol.html) - how Klipper assigns CAN node id and uses `canbus_uuid`.
- [CAN Bus Debugger: CAN Bus Termination Explained](https://www.canbusdebugger.com/articles/can-bus-termination) - practical explanation of two `120 Ohm` terminators, `60 Ohm` measurement, and common mistakes.
- [DigiKey: CAN Bus explained](https://www.digikey.com/en/blog/can-bus-explained) - general overview of CAN bus, differential communication, and application in distributed systems.
- [Texas Instruments: Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - basic description of CAN physical layer, transceivers, and typical network.
