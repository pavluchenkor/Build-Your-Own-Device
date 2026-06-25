# Interface UART

UART é uma interface simples de transmissão de dados em série entre dois dispositivos. Expansão: `Universal Asynchronous Receiver/Transmitter`.

Nos projetos práticos, normalmente encontra-se "UART", "serial", "TX/RX" ou "porta UART". Para iniciantes, o ponto-chave é: UART transmite dados na linha `TX`, recebe na linha `RX`, e ambos os dispositivos precisam de um `GND` comum para funcionarem corretamente.

## Onde UART é utilizado

UART encontra-se quase em toda a parte:

- registos de depuração de microcontroladores;
- programação de placas através de adaptador USB-UART;
- comunicação anfitrião-para-MCU em alguns cenários Klipper;
- módulos de GPS, RFID, impressão digital e sensores;
- configuração do controlador de motor TMC;
- comunicação entre dois microcontroladores;
- porta de serviço na placa.

UART é conveniente porque requer poucos fios e funciona bem para troca simples de texto, comandos e diagnósticos.

## TX, RX e GND

Conexão mínima:

- `TX` - transmissão;
- `RX` - recepção;
- `GND` - terra comum.

TX de um dispositivo conecta-se a RX do outro:

![TX/RX conectados cruzadamente e GND comum na conexão UART](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Fonte: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

Regra:

```text
Dispositivo A TX -> Dispositivo B RX
Dispositivo A RX <- Dispositivo B TX
Dispositivo A GND -> Dispositivo B GND
```

O erro mais comum é conectar `TX` a `TX` e `RX` a `RX`. Às vezes, as marcações do módulo são confusas, portanto, se não houver conexão, primeiro verifique novamente o diagrama de pinos e a documentação em vez de alterar aleatoriamente todos os fios.

## UART, USB e USB-UART

UART não é USB.

Um computador normalmente não tem pinos UART nus. Por isso é necessário um adaptador USB-UART: conecta-se à USB do computador de um lado e fornece linhas `TX`, `RX`, `GND` e, às vezes, `VCC`, `DTR`, `CTS` do outro.

Exemplos:

- computador a ler registos de uma placa através de USB-UART;
- USB-UART a programar uma placa sem USB incorporado;
- anfitrião conectando-se a MCU através de série;
- adaptador ajudando na recuperação de uma placa após falha de programação.

Não confunda um conector USB numa placa com pinos UART no conector. Em algumas placas, o USB já está conectado a um chip USB-UART incorporado, enquanto noutras o USB vai diretamente para o microcontrolador.

## Níveis lógicos: 3.3V, 5V, RS-232

UART descreve o método de transmissão de dados, mas não garante níveis de tensão seguros.

Na eletrônica DIY, UART TTL/CMOS é o mais comum:

- UART `3.3V` - ESP32, RP2040, STM32 e muitas placas modernas;
- UART `5V` - Arduino Uno/Nano e alguns módulos mais antigos.

Aplicar um sinal `5V` a uma entrada de microcontrolador `3.3V` pode danificar a placa. Para níveis incompatíveis, é necessário um conversor de nível ou outro circuito de correspondência.

Existe também RS-232, que é separado. Isto não é "apenas UART num conector DB9". RS-232 tem níveis de tensão diferentes e lógica elétrica diferente. Não pode conectar uma porta RS-232 verdadeira diretamente a um GPIO de microcontrolador. É necessário um conversor de nível, como um circuito tipo MAX232 ou um adaptador pronto.

## Velocidade e formato

A velocidade UART deve ser responsável. Valores comuns:

```text
9600
57600
115200
250000
1000000
```

Se a velocidade não corresponder, o terminal mostrará lixo ou silêncio.

Existe também formato de transmissão. `8N1` é frequentemente utilizado:

- `8` - 8 bits de dados;
- `N` - sem paridade;
- `1` - um bit de paragem.

Para a maioria das tarefas simples, configurar a mesma velocidade e `8N1` padrão é suficiente, a menos que a documentação do módulo exija o contrário.

## UART em impressoras 3D

Nas impressoras 3D, UART frequentemente serve três papéis diferentes.

**Comunicação entre anfitrião e placa**

Algumas placas podem comunicar com o anfitrião através de série/UART. Em Klipper, isto é descrito na seção `[mcu]` através de `serial`.

**Configuração do controlador TMC**

Alguns controladores de motor utilizam UART para configurar corrente, stealthChop/spreadCycle, diagnósticos e leitura de estado. O motor em si é normalmente controlado não por UART, mas pelos sinais `STEP` e `DIR`.

**Depuração e programação**

UART pode ser utilizado para registos, modo bootloader e recuperação de placa através de adaptador USB-UART.

## Um UART - normalmente dois dispositivos activos

O UART clássico é uma conexão entre dois dispositivos. Não pode simplesmente conectar vários transmissores a uma linha `RX`.

Problemas:

- dois dispositivos puxam simultaneamente a linha `TX`;
- os dados ficam misturados;
- um módulo recebe comandos destinados a outro;
- possível conflito elétrico.

Às vezes, um `TX` pode ser ouvido por vários receptores, mas esta é uma decisão consciente e não adequada como regra universal. Para iniciantes, é mais seguro assumir: uma porta UART - um par de dispositivos.

## O que verificar antes de conectar

Antes de conectar UART, verifique:

- onde estão `TX` e `RX`;
- é necessário um `GND` comum;
- nível lógico: `3.3V` ou `5V`;
- é isto UART TTL ou RS-232;
- velocidade de transmissão;
- formato, se especificado;
- isto UART não está ocupado por registos USB ou programação;
- há outro transmissor conectado a esta linha;
- é necessário conectar potência ou apenas `TX`/`RX`/`GND`.

A alimentação do adaptador USB-UART é conectada apenas para que a placa seja alimentada por ele. Freqüentemente, para diagnósticos, apenas `RX`, `GND` e `GND` são necessários.

## Erros típicos

- conectar `TX` com `TX`, `RX` com `RX`;
- esquecer o `GND` comum;
- aplicar UART `5V` a uma entrada `3.3V`;
- confundir UART TTL e RS-232;
- selecionar a taxa de transmissão errada;
- conectar potência de um adaptador USB-UART a uma placa já alimentada;
- utilizar pinos UART ocupados por registos USB ou bootloader;
- conectar vários transmissores a uma linha;
- pensar que UART pode accionar uma carga potente diretamente.

## Ponto-chave

UART é uma interface simples para troca de dados entre dois dispositivos. Precisa de `TX`/`RX` conectados cruzadamente, `GND` comum, velocidade correspondente e níveis lógicos compatíveis.

UART não é uma fonte de alimentação e não funciona como saída de potência. Transmite dados, não faz rodar motores ou activa aquecedores diretamente.

## Materiais relacionados

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - explicação prática boa de UART, TX/RX, taxa de transmissão, série TTL, RS-232 e erros comuns.
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - o que UART faz dentro de um microcontrolador e por que TX/RX são necessários.
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - exemplo de adaptador USB-UART e conexão de TX/RX/GND a um dispositivo série.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - exemplo de adaptador USB-UART, pinos RX/TX/VCC/GND e teste de loopback.
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - como a conexão MCU série é descrita na configuração Klipper.
