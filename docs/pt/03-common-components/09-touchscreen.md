# Ecrã Tátils

Uma tela sensível ao toque não é apenas uma tela. É uma exibição mais entrada do usuário. Ele não deve apenas mostrar a temperatura ou um botão, mas também informar ao dispositivo onde você tocou.

Por causa disso, uma tela sensível ao toque é quase sempre mais complexa que o OLED. Você precisa escolher não apenas tamanho e resolução, mas entender quem desenha a interface, quem processa os toques, qual interface é usada e se o firmware escolhido suporta isso.

## Quando a tela sensível ao toque é útil

Uma tela sensível ao toque faz sentido se o dispositivo precisar de uma interface local completa:

- choosing drying mode;
- definir temperatura e tempo;
- material profile list;
- confirming errors;
- manual fan, lighting or damper control;
- Wi-Fi setup;
- visualizar o status sem telefone ou computador.

Se você só precisa mostrar temperatura, erro e modo, geralmente OLED, alguns botões, codificador ou interface web são suficientes. Uma tela sensível ao toque acrescenta custo, energia, espaço no gabinete, firmware, cabos e outro ponto de falha.

## Pergunta principal: quem desenha a interface

Antes de comprar, responda à pergunta principal: onde fica a interface do usuário.

Existem várias classes de tela diferentes:

![Classes of touchscreens and who draws the interface](../../img/03-common-components/09-touchscreen-classes.svg)

Raw TFT é uma tela simples com um controlador como `ILI9488`, `ST7789`, `XPT2046`, além de um controlador de toque separado como `FT5x06` ou `FT5x06`. Seu microcontrolador ou firmware desenha a interface. Isso é flexível, mas requer código, memória, drivers e calibração.

O display Smart UART/HMI é uma tela com seu próprio firmware e editor de interface, como o Nextion. O microcontrolador envia comandos via UART e a tela mostra páginas e elementos. Isso reduz a carga do MCU, mas vincula seu projeto às ferramentas e ao protocolo dessa tela.

A impressora TFT, como o BTT TFT35, geralmente possui seu próprio modo de tela sensível ao toque via UART e emulação clássica de LCD 12864 por meio de conectores EXP. Esta tela é conveniente para placas de impressora Marlin/3D, mas não é um painel universal para qualquer dispositivo DIY.

A tela HDMI/DSI/USB para host Linux funciona como um monitor normal e dispositivo de toque para Raspberry Pi ou outro computador Linux. Isso é adequado ao KlipperScreen, mas não se conecta diretamente ao pequeno ESP32 como um módulo simples.

## Connection Interfaces

As telas sensíveis ao toque usam interfaces diferentes.

Opções comuns:

- SPI - geralmente em TFT pequeno para ESP32/Arduino;
- I2C - geralmente em controladores de toque capacitivos, às vezes em controladores de toque;
- UART - em monitores inteligentes e algumas impressoras 3D TFT;
- EXP1/EXP2/EXP3 - em telas compatíveis com placas de impressora 3D;
- HDMI + USB – em telas Linux para Raspberry Pi;
- DSI – em algumas telas do Raspberry Pi;
- RGB/8080 paralelo - em TFT mais rápido, mas com mais fios e requisitos.

Você não pode escolher uma tela apenas pela diagonal. Duas telas `3.5"` podem ser completamente diferentes: um módulo SPI para ESP32, segundo painel UART com firmware próprio, terceira tela HDMI para Raspberry Pi.

## Toque resistivo e capacitivo

A parte de toque também varia.

Resistive touch:

- responde à pressão do dedo, da caneta ou da unha;
- often requires calibration;
- geralmente pior para gestos;
- can be cheaper;
- encontrado com controladores como `XPT2046`.

Capacitive touch:

- responds to a finger;
- geralmente é mais agradável de usar;
- can support multiple touches;
- often has a separate controller like `FT5x06`, `GT911` families;
- funciona pior com luvas grossas e algumas capas protetoras.

Para um dispositivo de oficina, o toque resistivo às vezes é mais prático porque você pode pressioná-lo com a unha ou com uma caneta. Para um belo painel no gabinete, o capacitivo geralmente parece mais moderno.

## Potência, luz de fundo e corrente

Uma tela TFT atrai mais do que um pequeno OLED. O principal consumidor de energia é a luz de fundo.

Antes de conectar, verifique:

- screen power voltage;
- backlight current;
- whether you need a separate 5V source;
- se o brilho da luz de fundo é ajustável;
- se os níveis lógicos são compatíveis;
- se a tela sobrecarrega o regulador da placa;
- se a energia diminui quando a luz de fundo é ligada.

Se a tela ficar branca, piscar, reiniciar o controlador ou perder eventos de toque, primeiro verifique a alimentação e o aterramento, não o código da interface.

Para um dispositivo com aquecedor, a tela não deve ser alimentada por um pino fraco aleatório. Deve fazer parte de um esquema de energia adequado com margem clara.

## Firmware e compatibilidade

Uma tela bonita é inútil se o firmware escolhido não for compatível.

Para a abordagem ESP32/Arduino, você precisa verificar:

- existe um driver de vídeo;
- existe um driver controlador de toque;
- are there enough GPIO;
- há RAM/PSRAM suficiente para buffer;
- qual estrutura gráfica é usada;
- quem vai escrever o cardápio.

Para ESPHome, verifique o suporte para o driver de vídeo específico e o componente touchscreen. Por exemplo, os monitores ILI9xxx e o toque XPT2046 precisam de SPI e configuração separada, e o toque resistivo precisa de calibração.

Para o Klipper, geralmente existem dois mundos diferentes:

- pequenos displays conectados ao MCU e descritos na configuração do Klipper;
- KlipperScreen no host Linux, onde a tela funciona como monitor e dispositivo de toque.

O KlipperScreen geralmente precisa de uma tela onde o Linux possa mostrar um desktop ou console. Isto não é o mesmo que um pequeno UART TFT conectado a uma placa de impressora.

Para placas Marlin/impressora, verifique se a tela específica suporta o modo necessário: modo de toque UART, emulação 12864, EXP1/EXP2/EXP3, tipo de controlador específico na configuração do firmware.

## Smart Display e telas semelhantes ao Nextion

O display inteligente é conveniente porque a tela armazena páginas, botões, fontes e imagens. O controlador envia comandos via UART e recebe eventos de toque.

Pros:

- menos carga no microcontrolador;
- menos código gráfico no firmware principal;
- você pode desenhar a interface no editor de tela;
- apenas UART e energia necessários.

Cons:

- você precisa aprender um editor e protocolo separados;
- a interface geralmente é armazenada na tela;
- mais difícil manter sincronizadas as versões da interface do usuário e do firmware do dispositivo;
- nem todos os elementos se comportam como em um aplicativo normal;
- substituir a tela pode exigir um redesenho.

Para um dispositivo simples, o display inteligente pode ser uma boa solução se você precisar de um painel bonito sem um host Linux. Mas não é um “monitor normal”: é um módulo separado com lógica própria.

## Caixa, cabos e manutenção

Uma tela sensível ao toque é algo que os usuários tocarão com as mãos. Portanto, a mecânica é importante, não apenas os fios.

Verifique com antecedência:

- a tela não está em uma zona quente;
- there's a frame or protective mount;
- o cabo não dobra acentuadamente ao abrir a tampa;
- o cabo pode ser desconectado para manutenção;
- o conector não pode entrar para trás;
- case não pressiona na tela;
- há acesso ao cartão SD ou USB para atualizações, se necessário;
- o usuário não toca nas partes elétricas enquanto usa a tela;
- a fiação de toque/display é separada dos fios do aquecedor.

Para dispositivos com aquecedor, é melhor mover a tela para a zona do usuário, longe do ar quente e de peças de energia.

## O que verificar antes de comprar

Antes de comprar uma tela sensível ao toque, verifique:

- diagonal e resolução;
- display type: raw TFT, smart UART, printer TFT, HDMI/DSI;
- display interface;
- touch interface;
- controlador de exibição: por exemplo `ILI9488`, `ST7789`, `ST7789`;
- controlador de toque: por exemplo `FT5x06`, `GT911`, `GT911`;
- corrente de energia e luz de fundo;
- logic levels;
- support in firmware;
- disponibilidade de documentação e exemplos;
- disponibilidade de bibliotecas;
- RAM/PSRAM requirements;
- dimensões da placa, furos e cabos;
- operating temperature;
- firmware/interface update method.

Se a descrição do produto não tiver exemplos de controlador de exibição, interface, alimentação e conexão, é melhor não usar essa tela em seu primeiro projeto.

## Erros típicos

- comprei uma tela “para Arduino”, mas o projeto é KlipperScreen no Linux;
- comprei tela HDMI e tentei conectar diretamente ao ESP32;
- comprei um display UART inteligente, mas esperava que funcionasse como um TFT normal;
- escolheu TFT bruto, mas não planejou tempo para menu e código gráfico;
- GPIO insuficiente para display SPI e controlador de toque;
- RAM insuficiente para buffer de tela;
- didn't check touch controller;
- didn't calibrate resistive touch;
- a tela treme devido à fraca potência da luz de fundo;
- o cabo passa próximo aos fios de alimentação do aquecedor;
- tela montada em zona quente;
- a interface parece boa, mas o erro principal é difícil de ver.

## Ponto Principal

Escolha uma tela sensível ao toque pela arquitetura, não pela diagonal. Primeiro decida quem desenha a interface: microcontrolador, a própria tela, firmware da impressora ou host Linux. Em seguida, verifique a interface, a alimentação, o controlador de toque, o suporte de firmware e a mecânica do gabinete.

Para um simples aquecedor, secador ou filtro, geralmente OLED, botões ou interface web são suficientes. Use uma tela sensível ao toque quando os usuários realmente precisarem de uma interface local.

## Reference Materials

- [KlipperScreen: Hardware](https://klipperscreen.github.io/KlipperScreen/Hardware/) - requirements and screen examples for KlipperScreen, including HDMI/DSI/Raspberry Pi options.
- [BIGTREETECH TouchScreenFirmware](https://github.com/bigtreetech/BIGTREETECH-TouchScreenFirmware) - firmware and BTT TFT modes: touch mode, Marlin/12864 emulation, EXP connectors and settings.
- [BIGTREETECH TFT35 V3.0 repository](https://github.com/bigtreetech/BIGTREETECH-TFT35-V3.0) - documentation and files for popular 3D printer TFT35.
- [Adafruit 3.5 inch TFT Touchscreen Breakout](https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout) - example of raw TFT with SPI/8-bit modes, separate touch and libraries.
- [ESPHome: Touchscreen Components](https://esphome.io/components/touchscreen) - documentation on touch components, calibration and linking raw touch coordinates to display coordinates.
- [ESPHome: ILI9xxx TFT LCD Series](https://esphome.io/components/display/ili9xxx/) - example of raw TFT display support on ESPHome and important memory limitations.
