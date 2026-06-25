# Controladores STM32

STM32 é uma grande família de microcontroladores de 32 bits da STMicroelectronics baseados em núcleos Arm Cortex-M. Não é uma placa ou um chip: sob o nome STM32 existem dezenas de séries e centenas de modelos.

No mundo das impressoras 3D, o STM32 é muito comum. Muitas placas de impressora, placas de expansão, placas CAN e controladores prontos usam STM32. Para periféricos Klipper e impressoras, é uma das opções mais práticas se você estiver pronto para trabalhar com uma placa específica.

## Onde o STM32 é útil

STM32 is good for:

- placa principal da impressora 3D;
- MCU adicional no Klipper;
- ventilador, sensor e placa de controle de saída;
- CAN board or toolhead board;
- more serious custom board;
- tasks requiring timers, PWM, ADC, UART, SPI, I2C, CAN, or USB;
- projetos que necessitam de um ecossistema industrial pronto e documentação.

Se o RP2040 é um começo simples e claro, o STM32 é um amplo mundo de controladores onde você pode selecionar um chip para praticamente qualquer tarefa. Mas a flexibilidade tem o custo da complexidade.

## STM32 is a family

Você não pode dizer “Eu tenho um STM32” e parar de escolher. Você precisa saber o modelo exato.

Exemplos de séries:

- **STM32F0 / STM32C0 / STM32G0** — séries de orçamento e mercado de massa;
- **STM32F1** — série antiga, mas muito conhecida, frequentemente encontrada em Blue Pill e placas antigas;
- **STM32F4** — série mais poderosa, popular em controladores;
- **STM32G4** — interessante para tarefas de controle, temporizador e periféricos analógicos;
- **STM32H7** — powerful high-end controllers;
- **STM32L / STM32U** — série focada em baixo consumo de energia.

Para um usuário típico, o que importa não é o marketing da série, mas coisas específicas:

- existe suporte no firmware que você precisa;
- quantos GPIO estão realmente expostos na placa;
- possui USB, CAN, UART, I2C, SPI;
- quanto flash e RAM;
- como piscar;
- existe uma pinagem e um esquema adequados.

## A placa é mais importante do que o nome do chip

O mesmo STM32 pode estar em placas muito diferentes.

Variantes comuns:

- **Blue Pill / Black Pill** — placas pequenas baratas, geralmente com classe STM32F103 ou STM32F4, mas a qualidade do clone varia;
- **STM32 Nucleo** — placas oficiais de desenvolvimento ST com ST-LINK integrado;
- **placa de impressora 3D pronta** — já possui drivers, conectores, saídas MOSFET, entradas de termistor, fusíveis e conectores de alimentação;
- **toolhead/placa CAN** — placa especializada para um cabeçote de impressora ou módulo remoto;
- **placa personalizada** — requer alimentação completa, USB, SWD, proteção e design de roteamento.

Para um primeiro projeto prático, geralmente é mais fácil obter uma placa pronta com documentação do que um STM32 simples ou um clone aleatório sem esquema.

## STM32 e Clipper

STM32 é um dos principais caminhos para um Klipper MCU.

Arquitetura típica:

![Nucleo boards for STM8 and STM32 from STMicroelectronics](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

O host Klipper é executado em um dispositivo Linux, e a placa STM32 controla fisicamente os pinos: alterna saídas MOSFET, lê termistores, controla ventiladores, recebe sinais de interruptor de limite e se comunica com o host via USB, UART ou CAN.

Para periféricos do tipo iDryer, o STM32 faz sentido se:

- o dispositivo deve fazer parte da configuração do Klipper;
- você precisa de uma placa de impressora pronta com saídas de energia;
- you need CAN;
- you need a more industrial board approach;
- você já possui uma placa STM32 e uma configuração conhecida.

Se você precisar adicionar rapidamente alguns pinos e sensores, o RP2040 costuma ser mais simples. Se você precisar de uma placa poderosa pronta com conectores e drivers, uma placa STM32 pode ser melhor.

## Flashing: USB, DFU, UART, SWD, ST-LINK

O STM32 não possui um método universal de flashing para todas as placas.

Options:

- **USB bootloader / DFU** — piscando via bootloader USB integrado se a placa e o chip suportarem;
- **Bootloader UART** — piscando através de pinos seriais no modo BOOT correto;
- **SWD via ST-LINK** — maneira confiável de atualizar e depurar por meio de um programador;
- **ST-LINK integrado no Nucleo** — conveniente para desenvolvimento;
- **bootloader na placa da impressora** — às vezes a atualização é feita via cartão SD, USB ou bootloader especial do fabricante.

Portanto, antes de comprar uma placa, você precisa procurar não apenas a folha de dados do chip, mas também as instruções para aquela placa específica. Para o Klipper, é especialmente importante ler os comentários na configuração da placa pronta e nas instruções do fabricante.

## Nucleo, Blue Pill e placas de impressora

As placas **STM32 Nucleo** são convenientes para aprendizado e prototipagem. Eles geralmente têm conectores ST-LINK integrados, Arduino Uno V3 e pinos ST morfo que fornecem acesso a mais sinais. Esta é uma boa opção se você deseja aprender STM32 e ter uma ferramenta oficial de flashing.

**Blue Pill / Black Pill** são atraentes pelo preço e tamanho, mas os clones costumam ter problemas: chip errado, regulador fraco, USB ruim, nenhum esquema adequado, bootloader estranho. Para experimentos eles são úteis, para um dispositivo confiável — somente após verificação.

**Placas de impressora 3D prontas** costumam ser mais práticas para aquecedores, ventiladores e sensores porque a seção de alimentação já está roteada: há terminais, saídas MOSFET, entradas de termistores, alimentação, fusíveis ou espaço para eles. Mas mesmo uma placa pronta requer verificação de correntes, conectores, refrigeração e segurança.

## Lógica de 3,3 V e GPIO

A maioria dos STM32 funciona com lógica `3.3V`.

Importante:

- não aplique `5V` aos pinos, a menos que a folha de dados do chip diga especificamente que este pino aceita `5V`;
- A compatibilidade do escudo Arduino no Nucleo não significa que todos os sinais são seguros como em um Arduino Uno `5V`;
- Os pull-ups I2C geralmente são para `3.3V`;
- O GPIO não deve alimentar uma carga diretamente;
- ventiladores, faixas de LED, aquecedores, relés e servos são conectados por meio de drivers e alimentação separada.

Mesmo que alguns pinos STM32 aceitem `5V`, isso não é permissão para conectar tudo. Você precisa verificar a tabela de pinagem e as características elétricas do chip específico.

## Por que o STM32 é frequentemente escolhido para impressoras

STM32 é bom para placas de impressora 3D porque possui muitos periféricos úteis:

- temporizadores e PWM para ventiladores, aquecedores e sinais;
- ADC para termistores e sensores;
- UART/SPI para drivers e módulos de passo;
- I2C para displays e sensores;
- USB para comunicação com o host;
- CAN em algumas séries e placas;
- desempenho suficiente para tarefas de MCU em tempo real.

Mas o microcontrolador em si não torna a placa segura. Aquecedores, MOSFETs de potência, SSRs, fusíveis, conectores e proteção térmica permanecem uma tarefa de engenharia separada.

## O que verificar antes de comprar

Antes de comprar uma placa STM32, verifique:

- exact microcontroller model;
- se há suporte no Klipper ou no firmware que você precisa;
- quanto flash e RAM;
- como a placa pisca;
- se possui USB, CAN, UART ou outra interface necessária;
- se há pinagem e esquema oficial;
- quais pinos são ocupados por LEDs, USB, oscilador, modo de inicialização ou SWD;
- quais pinos são tolerantes a 5V e quais não;
- quais saídas de energia estão na placa e para qual corrente elas são classificadas;
- se existem fusíveis, terminais e alimentação adequada;
- quão compreensível é a documentação do fabricante.

Se uma placa for vendida apenas com uma bela foto e sem esquema, não é uma boa base para um aparelho com aquecedor.

## Erros comuns

- pensar que o STM32 é uma placa específica;
- comprar um clone da Blue Pill e esperar o comportamento oficial do conselho;
- não verificar o modelo exato do chip;
- não entender como piscar o quadro;
- confundir DFU, BOOT0, UART e ST-LINK;
- conectar um módulo `5V` a um pino intolerante a `5V`;
- usando pinos SWD como GPIO normais e perdendo a capacidade de flash/depuração;
- pensar que GPIO é uma saída de energia;
- escolher uma placa sem esquema de aquecedor;
- não verificar a configuração pronta do Klipper antes de comprar.

## Pontos principais

STM32 é uma família poderosa e prática de microcontroladores, especialmente para placas de impressora 3D e Klipper MCU. Mas você não precisa escolher "STM32 em geral", mas uma placa específica com um chip, pinagem, método de flash e documentação específicos.

Para um primeiro controlador simples, o RP2040 costuma ser mais fácil. Para componentes eletrônicos de impressoras prontos, placas CAN e periféricos mais sérios, o STM32 costuma ser a escolha certa.

## Related materials

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — official overview of the STM32 family, series, performance, and tools.
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — overview of mass-market series STM32C0, G0, F0, F1, G4, and their positioning.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — official STM32 flashing tool via ST-LINK/SWD, UART, USB DFU, I2C, SPI, and CAN bootloader.
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — example of an official Nucleo board with built-in ST-LINK, Arduino Uno V3 connectors, and ST morpho pins.
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — documentation for Nucleo-64, connectors, ST-LINK, and warning about `3.3V` I/O.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — Klipper architecture and MCU backend context, including STM32 in the source tree.
