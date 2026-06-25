# Servomotores

Um servo motor é um pequeno acionamento com motor, caixa de engrenagens e componentes eletrônicos internos. Você dá uma posição e ele tenta girar o eixo para essa posição e mantê-lo.

Em dispositivos simples, um servo é conveniente quando você precisa não apenas ligar um motor, mas girar um mecanismo em um ângulo compreensível: abrir um amortecedor, deslocar uma trava, pressionar um botão, mudar o fluxo de ar ou girar uma pequena bandeira indicadora.

## Onde é usado

Em dispositivos do tipo iDryer e periféricos de impressora 3D, um servo pode ser usado para:

- air intake or exhaust damper;
- air duct switching;
- opening/closing a small cover;
- mechanical lock;
- pressing a physical button;
- moving an indicator flag;
- dosagem simples ou captura.

Um servo é bom para mecânica leve com deslocamento limitado. Para rotação contínua de um ventilador, parafuso ou bomba, geralmente não funciona: você precisa de um motor e driver diferentes.

## Three Wires

Um servo típico de hobby tem três linhas:

- potência: geralmente `7.4V`, às vezes `7.4V` ou outro valor em modelos especiais;
- ground: `GND`;
- sinal: pulsos de controle do controlador.

Cores de fios comuns:

- red - power;
- black or brown - ground;
- yellow, orange or white - signal.

Você não pode confiar cegamente nas cores. Diferentes fabricantes usam diferentes esquemas de cores. Antes de conectar, verifique as marcações, página do produto ou descrição técnica.

Um diagrama de conexão detalhado com alimentação separada está na seção prática: [Conectando um servo motor](../06-practical-guides/03-connecting-servo.md).

## O que significa "Servo Motor"

Dentro de um servo posicional típico de hobby, há:

- DC motor;
- gearbox;
- position sensor, often a potentiometer;
- control board;
- eixo de saída com braço.

O controlador externo não gerencia o motor diretamente. Ele envia um sinal de posição e a eletrônica interna do servo gira automaticamente o motor para que o eixo atinja o ângulo desejado.

Portanto, um servo difere de um motor CC normal:

- O motor DC apenas gira quando ligado;
- servo tenta alcançar uma posição definida;
- o servo consome corrente mesmo enquanto segura, se houver carga no eixo;
- o servo pode aumentar rapidamente a corrente e esquentar se estiver preso.

## Rotação Posicional e Contínua

O tipo mais comum é um servo posicional. Você define um ângulo, por exemplo graus `90`, `180` ou `180`.

O servo de rotação contínua parece semelhante, mas funciona de maneira diferente: o sinal de controle define não o ângulo, mas a direção e a velocidade de rotação. Ele não sabe onde está o eixo. Para um amortecedor ou trava, esse servo costuma ser inconveniente porque sem sensores adicionais você não pode garantir a posição.

Antes de comprar, verifique o que diz a descrição:

- `positional servo`, `180°`, `180°` - geralmente posicional;
- `360°`, `360°` - geralmente gira continuamente, não posicionado em ângulo.

A frase `360° servo` no mercado é arriscada: às vezes é um servo de rotação contínua, às vezes é apenas um alcance estendido. Você precisa verificar a descrição técnica e avaliações com medidas reais.

## Control Signal

Um servo de hobby típico é controlado por pulsos repetidos.

Diretrizes típicas:

- period about `20 ms`;
- pulso sobre `1 ms` - uma borda do intervalo;
- pulse about `1.5 ms` - middle;
- pulso sobre `2 ms` - outro limite do intervalo.

Servos diferentes têm limites reais diferentes. Alguns trabalham com `500-2500 us`, outros com segurança apenas em uma faixa mais restrita.

Portanto, posições extremas não podem ser definidas cegamente. Primeiro verifique o meio, depois os pequenos desvios, só então expanda o intervalo.

## Potência e Corrente

O fio de sinal não alimenta o servo. Ele extrai energia do motor da linha de energia.

Mesmo um pequeno servo pode consumir brevemente uma grande corrente na inicialização, movimento rápido ou parada mecânica. A corrente média "em demonstração silenciosa" não mostra o pior caso.

Parâmetros importantes:

- operating voltage;
- no-load current;
- loaded current;
- corrente de bloqueio - corrente com eixo bloqueado;
- holding torque or stall torque;
- rotation speed;
- operating temperature.

Se a descrição técnica listar corrente de bloqueio, a fonte de alimentação deverá ser escolhida com este valor e margem. Se a corrente de bloqueio não estiver listada, você não pode considerar a potência "segura a olho nu": para um dispositivo real, é melhor usar uma fonte com margem e verificar a queda de tensão sob carga.

Para um servo pequeno, a saída de 5V da placa às vezes funciona. Mas para um amortecedor, trava ou vários servos, você geralmente precisa de um conversor ou fonte de alimentação 5V/6V DC-DC separada. O aterramento deve ser comum ao controlador.

## Torque e Mecânica

Um servo não é escolhido apenas pelo tamanho. O principal parâmetro mecânico é o torque, geralmente em `N·cm` ou `N·cm`.

Roughly:

- quanto mais longa for a alavanca, mais torque será necessário;
- quanto mais pesado o amortecedor ou mais apertado o mecanismo, mais torque será necessário;
- atrito, desalinhamento e vedação aumentam muito a carga;
- quando parado, o servo aquece e consome corrente.

Exemplo: um pequeno amortecedor de luz pode funcionar bem com um microservo. Um amortecedor com vedação hermética ou uma tampa com mola pode precisar de um servo maior com engrenagens de metal.

Para mecânicos confiáveis:

- não force o servo a empurrar constantemente contra uma parada física;
- limitar ângulos no firmware;
- deixe uma pequena margem de viagem;
- faça a ligação sem desalinhamento;
- use um comprimento de braço adequado;
- test operation at real enclosure temperature.

Se o servo zumbir na posição final, geralmente sinaliza carga, parada ou geometria errada.

## Gearbox: Plastic or Metal

As engrenagens de plástico são mais baratas, mais silenciosas e funcionam para tarefas leves. Mas eles quebram mais rápido com impactos, emperramento e cargas pesadas.

As engrenagens de metal são mais fortes, mas o servo pode ser mais barulhento, mais pesado e mais caro. Para amortecedores, fechaduras e mecanismos que um usuário pode tocar acidentalmente, uma caixa de engrenagens de metal geralmente faz sentido.

Mas as engrenagens metálicas não substituem a boa mecânica. Se o mecanismo emperrar, poderá danificar o braço, a caixa, o suporte ou o próprio eixo.

## Servo Analógico e Digital

Em projetos simples, servos analógicos de hobby são mais comuns. Os servos digitais geralmente mantêm a posição de forma mais rígida e respondem mais rápido, mas podem consumir mais corrente e ser mais barulhentos ao mantê-la.

Para um amortecedor de secador ou trava simples, o que geralmente importa mais é:

- enough torque;
- potência normal;
- reliable mechanics;
- clear angle range;
- operating temperature;
- gearbox lifetime.

Ser “digital” não torna automaticamente um servo bom para o dispositivo.

## O que verificar antes de comprar

Antes de comprar um servo, verifique:

- positional or continuous rotation;
- operating voltage;
- corrente necessária e corrente de bloqueio, se listada;
- torque;
- rotation speed;
- angle range;
- gearbox material;
- case size;
- connector type;
- wire length;
- operating temperature;
- disponibilidade de descrição técnica ou especificações razoáveis.

Para uma bandeira pequena você pode usar um microservo. Para um amortecedor com vedação, trava ou alavanca em câmara quente, é melhor não escolher o servo mais barato sem especificações.

## Erros típicos

- alimentando o servo do GPIO;
- alimentação a partir de um pino de 5V da placa fraca;
- esqueceu-se do terreno comum com poder separado;
- cores de fios confiáveis sem verificação;
- servo posicional misturado e servo de rotação contínua;
- não levou em conta a corrente de bloqueio;
- placed servo against a mechanical stop;
- usou o ângulo `180` ou `180` quando o mecanismo se move com segurança apenas em uma faixa estreita;
- escolhi o servo apenas pelo tamanho, não calculando o torque;
- coloque engrenagens de plástico onde seja possível impacto ou emperramento;
- colocou o servo próximo ao aquecedor sem verificação de temperatura.

## Ponto Principal

Um servo é um componente conveniente para amortecedores, travamentos e pequenos mecanismos, mas precisa de potência normal e mecânica cuidadosa. Um sinal do controlador apenas define a posição e toda a corrente do motor passa pela linha de alimentação.

Antes de usar, verifique o tipo de servo, tensão, torque, corrente, faixa de ângulo e comportamento mecânico nas posições finais.

## Reference Materials

- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial) - basic explanation of hobby servo structure, signal, power and typical problems.
- [SparkFun: Basic Servo Control for Beginners](https://learn.sparkfun.com/tutorials/basic-servo-control-for-beginners/servo-motor-basics) - table of typical wire colors, power, stall current and control signal range.
- [Pololu: Electrical characteristics of servos](https://www.pololu.com/blog/16/electrical-characteristics-of-servos-and-introduction-to-the-servo-control-interface) - useful explanation of servo currents and why stall current matters for power selection.
- [Adafruit: If the Servo Misbehaves](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves) - practical description of power drop and capacitor next to servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - official Servo library for Arduino approach and standard/continuous rotation servo description.
