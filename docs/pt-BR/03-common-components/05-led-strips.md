# Fitas LED

Uma faixa de LED é uma placa flexível com LEDs e traços de energia. Em uma impressora, secadora ou pequeno dispositivo DIY, geralmente é usado para iluminação de câmara, indicação de status, iluminação de área de trabalho ou iluminação decorativa de gabinete.

O principal erro do iniciante é tratar uma faixa de LED como um pequeno LED. Mesmo uma faixa curta pode consumir mais corrente do que uma ventoinha, e uma faixa longa torna-se uma carga de energia total.

## Onde é usado

Em dispositivos DIY em torno de uma impressora 3D, as tiras de LED são úteis para:

- iluminar a câmara da impressora;
- acender o secador de filamento;
- status indication: heating, drying, error, waiting;
- iluminação da área de trabalho no interior do recinto;
- iluminação noturna suave sem luz principal;
- sinal visual quando a impressão termina ou ocorre um erro.

Para iluminação de serviço, uma faixa branca simples geralmente é melhor. Para indicação de modo, RGB ou faixas endereçáveis ​​são convenientes, mas são mais complexos em potência e controle.

## Voltage: 5V, 12V or 24V

As tiras de LED vêm em diferentes tensões:

- `5V` - often addressable strips like WS2812/NeoPixel;
- `12V` - tiras brancas e RGB comuns;
- `24V` - conveniente para seções mais longas e sistemas de 24V.

A tensão da tira deve corresponder à fonte de alimentação. Você não pode conectar uma faixa `24V` a `24V`. Uma faixa `12V` em `5V` pode escurecer ou não funcionar. Uma tira `12V` em `24V` ou `24V` quase certamente será danificada.

Se a sua impressora já possui o `24V`, isso não significa que qualquer faixa possa ser conectada a ela. Você precisa comprar exatamente uma tira `24V` ou colocar um conversor DC-DC para a voltagem correta.

## Faixas Regulares e Endereçáveis

Existem dois tipos principais de tiras de LED.

Uma faixa normal acende uma só vez. Isso poderia ser:

- single-color white;
- warm/cold white;
- Faixa RGB que muda de cor em todo o seu comprimento;
- Faixa RGBW com canal branco separado.

Essa faixa não possui microchip em cada LED. O brilho é controlado por comutação de energia ou PWM através de um MOSFET, controlador de LED ou saída de placa adequada.

Uma faixa endereçável possui um microchip de controle para LEDs individuais ou grupos de LEDs. Permite iluminar diferentes seções em cores diferentes. Exemplos típicos: WS2812B, SK6812, tiras compatíveis com NeoPixel.

Addressable strips require:

- energia na voltagem certa;
- `GND` comum com controlador;
- data wire `DIN`;
- corrigir a direção dos dados ao longo da seta na faixa;
- often - 5V data signal level;
- potência cuidadosa sem grandes quedas.

Para iluminação simples de câmara, uma faixa endereçável geralmente é um exagero. Para boas indicações e efeitos, é conveniente, mas requer mais atenção à potência.

## Corrente e Potência

Escolha uma faixa de LED não apenas pela cor e comprimento. Você precisa conhecer seu poder.

As páginas de produtos geralmente listam:

- tensão: por exemplo `24V` ou `24V`;
- potência por metro: por exemplo `9.6 W/m`, `14.4 W/m`, `14.4 W/m`;
- número de LEDs por metro;
- LED type: for example `3528`, `5050`, `2835`;
- strip width;
- protection degree: bare, silicone jacket, IP65/IP67;
- maximum length per section.

A corrente é calculada simplesmente:

```text
current = power / voltage
```

Exemplo: você tem `24V` da faixa `9.6 W/m` na potência `9.6 W/m`.

```text
total power = 2 m × 9.6 W/m = 19.2 W
current = 19.2 W / 24 V = 0.8 A
```

Para tal faixa, a fonte de alimentação, MOSFET, fios e conector devem suportar confortavelmente o `30-50%`. Na prática, é melhor adicionar pelo menos margem `30-50%`, especialmente se a tira durar longos períodos.

Para tiras RGB, você deve levar em conta a corrente máxima de todos os canais. Branco em RGB geralmente significa que os canais vermelho, verde e azul estão ativados simultaneamente.

Para tiras endereçáveis ​​de 5V, uma estimativa aproximada é de até `60 mA` por pixel RGB em branco total. Em efeitos reais, a corrente pode ser menor, mas você não pode dimensionar a fonte de alimentação e a fiação para "normalmente não com brilho total".

## Por que você não pode alimentar um Strip do GPIO

O GPIO de um controlador é uma saída de sinal, não uma fonte de energia.

Você não pode conectar uma faixa de LED diretamente a um pino do microcontrolador. GPIO não está classificado para corrente de faixa. Isso pode danificar a placa, causar reinicializações, operação instável ou superaquecimento.

Correct logic:

- a corrente de tira vem da fonte de alimentação;
- o controlador gerencia apenas liga/desliga, brilho ou dados;
- um MOSFET, driver de LED, controlador de LED ou saída de energia da placa cuida da comutação de energia;
- o controlador e os aterramentos de alimentação estão conectados se houver um sinal de controle.

## Conectando uma faixa simples de cor única

Para uma faixa `24V` ou `24V` branca, um MOSFET do lado inferior é frequentemente usado: o positivo da faixa é conectado ao power plus e o negativo da faixa é comutado pelo módulo MOSFET.

![Close-up of LED strip with SMD diodes](../../img/03-common-components/05-led-strip-closeup.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:LED_strip_closeup.jpg), Akbermamps, CC BY 4.0*

Circuito típico:

1. A fonte de alimentação `+` vai para a faixa de LED `+`.
2. A faixa de LED `-` vai para a saída de energia do módulo MOSFET.
3. A fonte de alimentação `GND` vai para o módulo MOSFET.
4. O controlador `GND` está conectado à fonte de alimentação `GND`.
5. O pino de controle do controlador vai para a entrada do módulo MOSFET.

Se a placa da impressora já tiver uma saída gerenciada para ventiladores ou LEDs, você poderá usá-la somente se estiver classificada para a tensão e corrente necessárias. Você não pode conectar uma faixa longa a qualquer conector aleatório sem verificar o limite de saída.

## RGB Strip

Uma faixa RGB típica geralmente tem um ponto positivo comum e três pontos negativos gerenciados:

- `+V`;
- `R`;
- `G`;
- `B`.

Cada canal de cor requer um canal MOSFET separado ou um controlador RGB pronto para uso. Um MOSFET para toda a faixa RGB só pode ligá-lo e desligá-lo, sem mudar de cor.

Ao selecionar um módulo MOSFET para uma faixa RGB, observe a corrente por canal e a corrente total. O conector, o terminal e o fio também devem suportar a carga.

## Addressable Strip

Uma faixa endereçável geralmente possui:

- `+5V` ou outra alimentação se não for um modelo 5V;
- `GND`;
- `DIN` - data input;
- às vezes `DOUT` - saída de dados para a próxima seção.

Regras importantes:

- conecte os dados em direção à seta na faixa;
- o controlador e a faixa devem ter um terreno comum;
- para tiras endereçáveis ​​de 5 V em um controlador de 3,3 V, geralmente é necessário um conversor de nível;
- antes de uma longa tira, um capacitor eletrolítico na alimentação é útil;
- um resistor em torno de `300-500 Ohm` é frequentemente colocado na linha de dados próximo à entrada da faixa;
- para uma faixa longa, é melhor fornecer energia não apenas no início, mas em pontos adicionais.

Se uma faixa endereçável for alimentada por uma fonte separada, você não poderá aplicar apenas `GND` sem `GND` comum. O sinal de dados não terá nível de referência adequado e a faixa piscará aleatoriamente ou não funcionará.

## Queda de tensão e potência multiponto

Uma longa faixa de LED pode ser brilhante no início e visivelmente mais fraca no final. Este não é um "controlador ruim", é uma queda de tensão nos fios e nos traços de cobre da tira.

Quanto menor a tensão e maior a corrente, pior é o problema. Portanto, as tiras `12V` e `24V` precisam com mais frequência de energia de vários pontos do que as tiras `24V` com a mesma potência.

Signs of voltage drop:

- strip end is dimmer;
- branco em RGB muda para amarelo ou vermelho;
- addressable strip flickers during bright effects;
- o controlador reinicia ao aumentar o brilho;
- wires, connector or strip start become hot.

Solution:

- use tira com voltagem apropriada;
- utilize fio com bitola suficiente;
- aplique energia no início e no final de seções longas;
- divida a tira longa em seções;
- usar fornecimento na linha de energia;
- don't route all current through weak connector or thin traces.

## Calor e montagem

A própria faixa de LED produz calor. Isto é especialmente perceptível para tiras brilhantes em revestimento de silicone e tiras montadas dentro de um invólucro fechado.

Bad mounting locations:

- next to a heater;
- em PLA macio dentro de uma câmara quente;
- em uma superfície que não dissipe calor;
- onde a tira toca as partes móveis;
- em uma tampa que geralmente é removida sem conector.

Para uma vida longa, é melhor montar a tira em um perfil de alumínio ou outra superfície que dissipe o calor. Se a tira estiver dentro da câmara da impressora, leve em consideração a temperatura da câmara e a temperatura da camada adesiva.

## O que verificar antes de comprar

Antes de comprar uma faixa de LED, verifique:

- strip voltage;
- power per meter;
- total length;
- color: white, RGB, RGBW, addressable;
- control type;
- largura da tira e local de montagem;
- installation location temperature;
- whether you need an aluminum profile;
- whether you need a MOSFET module or LED controller;
- se a fonte de alimentação pode suportar a carga adicional;
- se há um conector adequado para manutenção.

Para uma câmara de impressora, uma faixa branca `24V` costuma ser mais prática se todo o sistema já for `5V`. Para um pequeno indicador ESP32, uma faixa endereçável `5V` curta pode ser conveniente. Para iluminação RGB decorativa de longa duração, é melhor calcular a corrente com antecedência e pensar na potência multiponto.

## Erros típicos

- tira conectada à tensão errada;
- faixa de alimentação do GPIO;
- não calculou a corrente para todo o comprimento;
- módulo MOSFET selecionado sem margem;
- uma longa tira conectada com fio fino;
- esqueci o ponto comum entre o controlador e a faixa;
- conectou dados de faixa endereçável a `DIN` em vez de `DIN`;
- não instalou um conversor de nível para faixa endereçável de 5V do controlador de 3,3V quando necessário;
- alimenta apenas uma extremidade de uma longa tira;
- faixa instalada em zona quente sem verificação de temperatura;
- faixa esquerda sem conector em uma tampa removível.

## Ponto Principal

Uma faixa de LED não é um LED de sinal, é uma carga. Primeiro verifique a tensão e a potência, depois calcule a corrente, selecione o fio, MOSFET ou controlador e só então conecte à placa.

Para iluminação simples, escolha uma faixa branca regular na tensão do sistema. Para efeitos e indicação, você pode usar uma faixa endereçável, mas alimentação, aterramento comum, nível de sinal e proteção contra queda de tensão são especialmente importantes.

## Reference Materials

- [Adafruit NeoPixel Überguide: Best Practices](https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices) - practical rules for addressable strips: common ground, data line resistor, capacitor and signal level.
- [Adafruit NeoPixel Überguide: Powering NeoPixels](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels) - detailed explanation of addressable strip power, voltage drop and multi-point power.
- [Adafruit RGB LED Strips: Usage](https://learn.adafruit.com/rgb-led-strips/usage) - example of managing regular RGB strips through power transistors/MOSFET, not directly from microcontroller.
- [SparkFun WS2812 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide/addressable-led-strips) - introduction to addressable WS2812 strips and their variants.
- [QuinLED: 12V vs 24V LED strip and voltage drop](https://quinled.info/2018/08/24/12v-vs-24v-led-strip-or-voltage-drop/) - practical explanation of why long strips suffer from voltage drop and why 24V is often better for long sections.
