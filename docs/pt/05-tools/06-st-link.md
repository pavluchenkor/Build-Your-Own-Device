# ST-Link

ST-Link é um programador e depurador para microcontroladores STM32.

No contexto de dispositivos simples, é usado para:

- programar uma placa STM32;
- recuperar uma placa após programação falhada;
- conectar-se ao chip através de SWD;
- apagar memória;
- verificar se o microcontrolador é visível;
- às vezes depurar o programa.

ST-Link não é necessário para todas as placas. ESP32, RP2040 e Arduino geralmente programam de forma diferente.

## O que é SWD

SWD é `Serial Wire Debug`.

É uma interface de depuração e programação para microcontroladores ARM, comumente utilizada com STM32.

Para conexão básica você geralmente precisa:

- `SWDIO`;
- `SWCLK`;
- `GND`;
- às vezes `NRST`;
- às vezes `3.3V` ou `VTref` como tensão de referência de alvo.

Importante: `3.3V` em ST-Link nem sempre significa "alimentar a placa a partir daqui". Frequentemente ST-Link precisa ver a tensão da placa de alvo para compreender os níveis de sinal.

## Conexão mínima

Normalmente você conecta:

```text
ST-Link SWDIO -> board SWDIO
ST-Link SWCLK -> board SWCLK
ST-Link GND   -> board GND
ST-Link NRST  -> board NRST if reset is needed
ST-Link 3.3V/VTref -> 3.3V target if required by specific ST-Link
```

A placa STM32 é frequentemente alimentada por sua alimentação normal ou USB.

Antes de conectar, verifique a documentação para seu ST-Link e placa específicos.

![Placas Nucleo para STM32 com depurador ST-Link integrado](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Alimentação da placa

A confusão mais comum: a placa é alimentada por ST-Link ou separadamente?

Opções:

1. Placa é alimentada separadamente, ST-Link apenas conecta-se a SWD e GND.
2. ST-Link fornece 3.3V a uma pequena placa de alvo, se é realmente projectada para isto.
3. ST-Link apenas lê `VTref`, mas não deve alimentar a placa.

Você não pode conectar cegamente múltiplas fontes de energia.

Se a placa já é alimentada por USB ou fonte de alimentação, não conecte energia de ST-Link até ter certeza que o esquema permite.

## Como ST-Link difere de DFU

DFU é um modo de programação através de um bootloader USB, se disponível.

ST-Link funciona através de SWD directamente com o microcontrolador.

ST-Link é útil quando:

- DFU não está disponível;
- o bootloader está corrompido ou não é utilizado;
- a programação desactivou USB;
- a placa não entra no modo de programação normal;
- você precisa apagar memória;
- você precisa recuperar acesso STM32.

Mas se uma placa programa normalmente através de USB/DFU ou cartão SD, ST-Link pode não ser necessário.

## Conectar sob reset

Às vezes o firmware quebra acesso SWD.

Por exemplo:

- pinos SWD são usados como GPIO normais;
- firmware coloca rapidamente o chip em sleep;
- código trava logo após startup;
- modos de relógio/potência estão configurados incorrectamente.

Em tais casos, o modo `Connect under reset` ajuda.

A ideia: ST-Link mantém reset e tenta conectar antes de firmware funcionar mal.

Isto frequentemente requer conectar `NRST`.

## Como saber se ST-Link vê a placa

Em STM32CubeProgrammer ou ferramenta similar você geralmente vê:

- se ST-Link está conectado;
- se o alvo é encontrado;
- que chip é detectado;
- se você pode ler memória;
- se você pode apagar flash.

Se ST-Link é visível como dispositivo USB mas o alvo não é encontrado, o problema é frequentemente a conexão da placa:

- placa de alvo não tem energia;
- sem `GND` comum;
- `SWDIO` e `SWCLK` estão trocados;
- `VTref` não está conectado se necessário;
- frequência SWD muito alta;
- chip está bloqueado;
- firmware impede conexão;
- `Connect under reset` é necessário.

## Frequência SWD

Se a comunicação é instável, tente reduzir a frequência SWD.

Em fios longos, jumpers Dupont pobres ou placas instáveis, alta frequência pode interferir com conexão.

Para recuperação de placa, lento e fiável bate rápido.

## Erros comuns

- esqueceu `GND`;
- trocou `SWDIO` e `SWCLK`;
- conectou energia de ST-Link e USB ao mesmo tempo sem compreender o esquema;
- não alimentou a placa de alvo;
- não conectou `NRST` quando `Connect under reset` é necessário;
- definiu frequência SWD muito alta;
- tentando programar ESP32 ou RP2040 com ST-Link;
- tentando conectar a um chip bloqueado sem compreender protecção de leitura;
- usando fios longos de má qualidade;
- não actualizou firmware ST-Link ou não instalou driver.

## O que você não pode fazer

Você não pode:

- aplicar 5V a uma placa STM32 3.3V sem verificar;
- conectar múltiplas fontes de energia cegamente;
- conectar ST-Link a uma placa sob tensão de rede sem isolamento seguro e invólucro;
- mudar fios SWD com energia ligada se há risco de curto-circuito;
- assumir que um clone ST-Link tem o mesmo pinout do original.

Os pinouts dos clones ST-Link podem diferir. Verifique sempre as marcações do seu adaptador específico.

## Os essenciais

- ST-Link é necessário para STM32 através de SWD.
- Mínimo: `SWDIO`, `SWCLK`, `GND`, às vezes `NRST` e `VTref`.
- A placa deve ser alimentada correctamente, mas não necessariamente a partir de ST-Link.
- DFU e ST-Link são métodos de programação diferentes.
- `Connect under reset` ajuda a recuperar acesso após firmware ruim.
- Se o alvo não é encontrado, primeiro verifique potência, `GND`, `SWDIO/SWCLK`, `NRST` e frequência SWD.

## Materiais de referência

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - manual oficial ST-LINK/V2, pinos SWD/JTAG, alvo VCC e GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - modos de conexão ST-LINK, incluindo Normal, Connect under reset e Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - visão geral de ST-LINK como sonda de hardware para STM32/STM8 e protocolos suportados.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - processo geral de preparação MCU para Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - ferramenta oficial ST para programar STM32 através de ST-LINK/SWD, UART, USB DFU, SPI, I2C e bootloaders CAN.
