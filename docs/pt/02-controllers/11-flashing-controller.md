# Gravação do Controlador

Firmware (`firmware`) é um programa escrito na memória flash de um microcontrolador. Sem firmware, a placa não sabe o que fazer com os pinos, sensores, ventiladores e interfaces.

Importante: não confunda firmware com configuração. O firmware é escrito no controlador. A configuração do Klipper geralmente reside no servidor em `printer.cfg` e diz ao MCU já gravado quais pinos e parâmetros usar.

## Firmware, bootloader, configuração

Três conceitos diferentes:

- **firmware** - programa principal do microcontrolador;
- **bootloader** - pequeno programa que ajuda a gravar o firmware principal;
- **configuração** - definições do dispositivo, por exemplo `printer.cfg` no Klipper.

O bootloader é executado primeiro e pode aceitar novo firmware via USB, UART, DFU, cartão SD, CAN ou outro mecanismo. Se o bootloader for acidentalmente apagado, a gravação da placa pode tornar-se difícil: por vezes é necessário ST-LINK/SWD, USB-UART ou outro programador.

## Procedimento geral

Antes de gravar, o procedimento normal é:

1. Aprender o modelo exacto da placa.
2. Aprender o microcontrolador exacto.
3. Encontrar o diagrama dos pinos, esquema e instruções do fabricante.
4. Compreender se é necessário firmware independente ou firmware Klipper MCU.
5. Encontrar uma configuração pronta ou exemplo para esta placa.
6. Escolher o método de gravação correcto.
7. Compilar ou transferir o ficheiro correcto.
8. Colocar a placa em modo de gravação.
9. Gravar o firmware.
10. Verificar se a placa aparece no sistema.
11. Verificar a comunicação com o servidor e pinos básicos sem carga.

Não é possível adivinhar as definições do firmware. Para o Klipper, o tipo de microcontrolador, o deslocamento do bootloader, a referência de relógio e a interface de comunicação são especialmente importantes.

## Métodos típicos de gravação

Placas diferentes gravam-se de forma diferente:

![Caminhos principais para gravação do controlador](../../../img/02-controllers/11-controller-flashing-paths.svg)

Variantes comuns:

- **Armazenamento em massa USB / UF2** - placa aparece como disco, `.uf2` é copiado para ele;
- **USB DFU** - placa entra em modo DFU, firmware é escrito via USB;
- **USB série / bootloader UART** - firmware via porta série;
- **ST-LINK / SWD** - programador conecta-se aos pinos SWD;
- **Cartão SD** - algumas placas de impressora 3D gravam com um ficheiro no cartão;
- **CAN/Katapult/CanBoot** - firmware via bootloader CAN;
- **Bootloader Arduino** - gravação de esboço via Arduino IDE ou avrdude.

Não existe um método universal para todas as placas. O método é determinado pela placa específica, bootloader e firmware.

## RP2040 e UF2

Para Raspberry Pi Pico e muitas placas RP2040, o modo mais simples é `BOOTSEL` e UF2.

Normalmente:

1. Mantenha pressionado `BOOTSEL`.
2. Conecte USB.
3. Placa aparece como disco `RPI-RP2`.
4. Copie ficheiro `.uf2`.
5. Disco desaparece, placa reinicia.

O BOOTSEL do Pico está na ROM do microcontrolador, portanto não pode ser acidentalmente apagado por gravação normal. Isto torna o RP2040 conveniente para principiantes.

## STM32: DFU, ST-LINK, cartão SD

Placas STM32 gravam-se de formas diferentes.

Opções possíveis:

- bootloader USB DFU incorporado;
- bootloader UART;
- ST-LINK/SWD;
- cartão SD na placa de impressora;
- bootloader do fabricante da placa;
- bootloader CAN.

Para STM32, o deslocamento do bootloader é frequentemente importante. Por exemplo, se o bootloader ocupa o primeiro `8 KiB`, o Klipper deve ser compilado com o deslocamento correcto. Se escolhido incorrectamente, a placa pode não iniciar após a gravação.

ST-LINK/SWD é útil como uma opção de nível mais baixo: frequentemente pode recuperar uma placa se o bootloader normal não funcionar. Mas isto requer pinos SWD, programador e compreensão da ligação.

## Klipper: make menuconfig

Para firmware Klipper, você normalmente faz:

```bash
cd ~/klipper
make menuconfig
make
```

Em `make menuconfig`, selecciona:

- arquitectura do microcontrolador;
- modelo do processador;
- deslocamento do bootloader;
- referência de relógio;
- interface de comunicação: USB, série, CAN, etc.;
- por vezes parâmetros adicionais para placa específica.

Os valores correctos são frequentemente escritos em comentários no topo de um ficheiro de configuração pronto para a placa. Se tal configuração existir, leia primeiro seus comentários superiores.

Após compilação, o ficheiro firmware normalmente aparece em `~/klipper/out/`. Seguidamente, é escrito usando o método adequado para a placa específica.

## Verificação após gravação

Após a gravação, deve verificar mais do que apenas "o gravador escreveu sucesso".

Verifique:

- o dispositivo aparece no sistema;
- está presente `/dev/serial/by-id/...`, se usar USB/série;
- é visível `canbus_uuid`, se usar CAN;
- o caminho corresponde a `printer.cfg`;
- não há erros de comunicação no Klipper;
- pinos coincidem com o diagrama de pinos desta placa específica;
- entradas/saídas básicas funcionam sem carga de potência;
- ventilador/MOSFET/SSR estão desligados em estado seguro.

Para a primeira verificação, não conecte o aquecedor como carga final. Primeiro verifique a comunicação, sensores e lógica em condições seguras.

## O que guardar antes da gravação

Antes de alterar o firmware, é útil guardar:

- `printer.cfg` actual;
- versão antiga do firmware, se disponível;
- modelo da placa e microcontrolador;
- caminho série encontrado ou UUID CAN;
- foto das ligações;
- diagrama de pinos;
- definições `make menuconfig`;
- ligação para instruções do fabricante.

Se algo correr mal, estes dados ajudarão a recuperar rapidamente.

## O que pode correr mal

Problemas comuns:

- cabo USB é apenas de carregamento;
- placa não entrou em bootloader;
- microcontrolador errado selecionado;
- deslocamento do bootloader errado selecionado;
- interface de comunicação errada selecionada;
- firmware escrito, mas placa procurada no lugar errado;
- caminho série alterado após reconexão;
- cartão SD não lido pela placa;
- ficheiro firmware nomeado incorrectamente para bootloader da placa;
- controlador DFU/USB-UART não instalado;
- placa alimentada de dois lados;
- após gravação, configuração referencia pinos antigos.

Não altere tudo em resposta ao primeiro erro. Melhor ir passo a passo: cabo, modo de bootloader, modelo MCU, definições de compilação, método de escrita, aparência do dispositivo do sistema, configuração.

## Gravação e segurança

O firmware pode ligar e desligar saídas, mas não substitui a segurança do hardware.

Para aquecedores precisa:

- interruptor de potência correcto;
- fusível;
- protecção térmica independente;
- sensor de temperatura correcto;
- caixa segura;
- verificar comportamento em erro de firmware, travamento de MCU ou perda de comunicação.

Após gravar o controlador, não ligue o aquecedor sem verificar que o pino é escolhido correctamente, a lógica de ligação não está invertida e os limites de segurança funcionam.

## Erros típicos

- confundir firmware e `printer.cfg`;
- gravar ficheiro de placa semelhante mas diferente;
- não ler comentários no topo da configuração Klipper pronta;
- seleccionar deslocamento errado do bootloader;
- apagar bootloader sem compreender as consequências;
- usar cabo USB apenas de carregamento;
- não colocar placa em modo de gravação;
- procurar placa CAN em `/dev/serial/by-id`;
- procurar placa USB-série via `canbus_uuid`;
- ligar carga de potência antes de verificar pinos;
- não guardar configuração antiga.

## Ponto-chave

O firmware é o programa dentro do controlador, a configuração são suas definições operacionais. Para cada placa, deve conhecer o modelo exacto, microcontrolador, bootloader, método de gravação e parâmetros de compilação.

Para RP2040, UF2/BOOTSEL é geralmente mais simples. Para STM32, verifique a placa específica: DFU, ST-LINK, cartão SD, UART ou bootloader CAN. Para Klipper, primeiro encontre uma configuração pronta e comentários para `make menuconfig`.

## Materiais relacionados

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - procedimento oficial para `make menuconfig`, `make` e verificação de caminho série.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - por que os bootloaders diferem entre placas, por que é necessário deslocamento do bootloader e como diferentes MCUs são gravados.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL, UF2 e especificidades de Pico/RP2040/RP2350.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - exemplo oficial de BOOTSEL, armazenamento em massa USB `RPI-RP2` e gravação de Pico via UF2.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - ferramenta STM32 oficial para gravação via ST-LINK/SWD, UART, USB DFU, SPI, I2C e bootloader CAN.
