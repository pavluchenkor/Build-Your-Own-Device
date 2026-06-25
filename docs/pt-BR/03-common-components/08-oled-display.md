# Display OLED

Um display OLED é uma pequena tela que mostra texto, números, ícones simples e status do dispositivo. Ao contrário do LCD normal, o OLED ilumina-se sozinho e não precisa de luz de fundo separada. Portanto, pequenos módulos OLED são legíveis, ocupam pouco espaço e são convenientes para dispositivos DIY simples.

Em um dispositivo semelhante ao iDryer, um OLED pode mostrar temperatura, umidade, modo de trabalho, erro, status do Wi-Fi, filamento restante ou fase de secagem atual.

## Quando o OLED é útil

Vale a pena adicionar um OLED se os usuários precisarem ver o status do dispositivo diretamente no gabinete:

- current chamber temperature;
- humidity;
- target temperature;
- working mode;
- timer;
- sensor error;
- fan or heater status;
- connection status;
- menu simples sem tela grande.

Se o dispositivo for sempre gerenciado através do Klipper, uma interface web ou aplicativo móvel, um OLED separado pode ser desnecessário. Ele adiciona fiação, espaço no gabinete, código e outro ponto de falha.

## Tamanhos e controladores típicos

Os pequenos módulos OLED mais comuns:

- `128x32` pixels;
- `128x64` pixels;
- diagonal about `0.91"` or `0.96"`;
- monochrome: white, blue, yellow-blue;
- com controlador `SH1106` ou similar `SH1106`.

`SH1106` e `SSD1306` parecem semelhantes, mas nem sempre são totalmente compatíveis no código. Se uma biblioteca estiver definida para `SH1106`, mas o módulo for na verdade `SH1106`, a tela poderá mostrar uma imagem deslocada, lixo ou não funcionar.

Antes de comprar, é importante verificar não apenas o tamanho da tela, mas também o controlador, a interface e a tensão de alimentação.

## I2C e SPI

Módulos OLED pequenos geralmente são conectados por I2C ou SPI.

Um módulo I2C geralmente possui 4 contatos:

- `VCC`;
- `GND`;
- `SDA`;
- `SCL`.

Um módulo SPI geralmente precisa de mais linhas:

- `VCC`;
- `GND`;
- `SCK`/`CLK`;
- `MOSI`/`DIN`;
- `CS`;
- `DC`;
- sometimes `RST`.

I2C é mais simples de conectar e geralmente é suficiente para status, temperatura e menu simples. O SPI é mais rápido e melhor se a tela for redesenhada com frequência, mas para uma exibição de status pequena isso raramente é crítico.

![Connecting I2C OLED display to controller](../../img/03-common-components/08-oled-i2c-wiring.jpg)

*Source: [Adafruit Learning System](https://learn.adafruit.com/adafruit-128x64-oled-featherwing/), CC BY-SA 3.0*

## Níveis de potência e lógica

Um módulo OLED pode ser classificado para `5V`, para `5V` ou ter um regulador e mudança de nível na placa. Externamente, esses módulos podem parecer quase idênticos.

Antes de conectar, check:

- qual potência está listada no módulo ou na página do produto;
- se as linhas `SCL`/`SCL` são compatíveis com a lógica do controlador;
- se o módulo possui pull-ups I2C;
- se os pull-ups não entram em conflito com a tensão do controlador.

Para ESP32 e a maioria dos microcontroladores modernos, é mais seguro assumir a lógica `5V`. Se um módulo OLED puxar I2C para `5V`, pode ser problemático para um controlador de 3,3V.

Muitos módulos OLED I2C populares funcionam no `3.3V` e se conectam perfeitamente ao ESP32 diretamente, mas você precisa verificar o módulo específico.

## I2C Address

I2C OLED often has addresses:

- `0x3C`;
- `0x3D`.

Se a tela não responder, o endereço é a primeira coisa a verificar depois da alimentação e dos fios. Alguns módulos permitem alterar o endereço via jumper ou soldar um pequeno jumper na placa.

Sinais de endereço errado:

- o esboço ou firmware é iniciado, mas a tela fica em branco;
- O scanner I2C vê o dispositivo em um endereço diferente;
- biblioteca inicializa exibição sem resultado visível;
- mudar `0x3D` para `0x3D` faz com que funcione.

## O que mostrar em uma tela pequena

Um OLED `128x64` ou `128x64` tem muito pouco espaço. Não tente fazer uma interface completa para smartphone nele.

Bom conjunto para secadora ou aquecedor:

- large current temperature;
- target temperature;
- umidade se houver sensor;
- mode: `HEAT`, `DRY`, `IDLE`, `ERROR`;
- small fan/heat icon;
- error code or short message.

Bad set:

- long sentences;
- tiny tables;
- muitos itens de menu em uma tela;
- constantly scrolling text;
- animação decorativa em vez de status útil.

Para um dispositivo com aquecedor, é mais importante ver rapidamente um erro do que uma bela tela inicial.

## Burn-in e brilho

Os pixels OLED envelhecem devido ao brilho. Se você mostrar o mesmo texto brilhante em um lugar por muitas horas, um traço poderá aparecer.

Para um dispositivo DIY, isso nem sempre é crítico, mas é melhor:

- não manter o brilho no máximo sem necessidade;
- desligue a tela após o tempo ocioso;
- occasionally move static elements;
- não apresentar preenchimento branco constantemente;
- use atualizações breves em vez de animação extra.

Em uma câmara quente ou perto de um aquecedor, o OLED também vive pior. É melhor manter os componentes eletrônicos em uma zona com temperatura controlada que não exceda a faixa do módulo.

## Comprimento do fio e interferência

I2C não gosta de fios longos, especialmente perto de motores, aquecedores e linhas de energia. Se o OLED estiver em uma porta ou painel removível, um cabo longo e flexível pode se tornar uma fonte de ruído.

Practical rules:

- mantenha `SCL` e `SCL` curtos;
- afaste-os dos fios de alimentação do aquecedor;
- use `GND` comum;
- não faça um conector que entre ao contrário;
- para uma tampa fechada, use um conector e ruptura de tensão adequada;
- se o I2C estiver instável, primeiro encurte os fios e verifique os pull-ups.

SPI geralmente tolera melhor velocidades de atualização mais altas, mas tem mais fios e erros de conexão são mais comuns.

## OLED or Touchscreen

OLED é bom para mostrar status. Não resolve o problema de entrada sem botões, codificador ou outro controle.

Se os usuários frequentemente precisarem alterar as configurações diretamente no dispositivo, talvez seja necessário:

- encoder + OLED;
- several buttons + OLED;
- TFT display;
- touchscreen;
- web interface or app.

Não instale uma tela sensível ao toque só porque o OLED parece pequeno. Para dispositivos simples, um pequeno OLED com um botão às vezes é mais confiável e claro.

## O que verificar antes de comprar

Antes de comprar um módulo OLED, verifique:

- size: `128x32`, `128x64` or other;
- controller: `SSD1306`, `SH1106`, `SH1107`;
- interface: I2C or SPI;
- power: `3.3V`, `5V` or range;
- logic level;
- Endereço I2C, se listado;
- reset pin support;
- suporte no firmware ou biblioteca escolhida;
- dimensões físicas da placa e furos de montagem;
- connector location;
- operating temperature;
- cor e legibilidade no ângulo que você precisa.

Para um dispositivo ESP32, I2C OLED `SSD1306` em `0x3C` com endereço `0x3C` geralmente é mais conveniente. Para uma placa Klipper, verifique se a placa específica suporta o barramento escolhido e como o display é descrito na configuração.

## Erros típicos

- misturou `SCL` e `SCL`;
- energia conectada à tensão errada;
- didn't check I2C address;
- selecionou `SH1106` no código, mas o módulo é `SH1106`;
- made I2C wires too long;
- forgot common `GND`;
- módulo pull-up de 5 V conectado ao controlador de 3,3 V sem verificação;
- selected SPI module expecting 4 pins like I2C;
- put screen in hot zone;
- exibição adicionada sem entender qual problema ela resolve para os usuários.

## Ponto Principal

Um display OLED é bom para status curto e interface local simples. Para a maioria dos dispositivos DIY, um I2C OLED `128x64` é suficiente se for compatível com energia e suportado pelo firmware escolhido.

Antes de conectar, verifique o controlador de vídeo, interface, alimentação, endereço I2C e comprimento do fio. Se o dispositivo já for conveniente via interface web, o OLED pode não ser necessário.

## Reference Materials

- [Adafruit: Monochrome OLED Breakouts](https://learn.adafruit.com/monochrome-oled-breakouts) - practical guide to small SSD1306 OLED, I2C/SPI connection, sizes and examples.
- [SparkFun: Qwiic Micro OLED Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-micro-oled-hookup-guide) - example of I2C OLED module, library and text/graphics output.
- [ESPHome: SSD1306 OLED Display](https://esphome.io/components/display/ssd1306) - documentation on `ssd1306_i2c`, `ssd1306_spi`, addresses, SSD1306/SH1106 models and configuration.
- [Klipper Configuration Reference: display](https://www.klipper3d.org/Config_Reference.html#display) - display support in Klipper, including `ssd1306` and `sh1106`.
- [SSD1306 Datasheet: Solomon Systech](https://www.radiolocman.com/datasheet/pdf.html?di=168297) - technical description of SSD1306 controller: resolution, I2C/SPI/parallel interfaces and commands.
