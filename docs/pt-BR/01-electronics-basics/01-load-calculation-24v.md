# Corrente, Tensão e Potência de Carga

Antes de conectar um aquecedor, ventilador, fita LED, servo drive ou outro módulo, você precisa entender três coisas:

- tensão;
- corrente;
- potência.

Sem isso, é fácil comprar uma fonte inadequada, aquecer demais o fio, derreter o conector, queimar um módulo MOSFET ou conectar a carga ao controlador de forma que funcione instabilidade.

## Onde encontrar os parâmetros

Tensão, corrente e potência são geralmente encontradas:

- na carcaça do componente;
- na etiqueta da fonte de alimentação;
- na página do produto;
- na especificação técnica;
- no manual;
- no diagrama esquemático ou pinout.

Se o parâmetro não for especificado, não é um detalhe menor. É uma razão para parar e descobrir exatamente o que você está conectando.

Para componentes de periféricos de impressora 3D, os parâmetros típicos se parecem com:

- ventilador: `24V 0.2A`;
- aquecedor: `24V 100W`;
- fita LED: `24V 9.6W/m`;
- servo drive: `5V`, corrente depende da carga;
- placa do controlador: corrente máxima para cada saída é especificada separadamente.

## A tensão deve corresponder

Uma carga é projetada para uma tensão específica.

Exemplos:

- ventilador pode ser `5V`, `12V` ou `24V`;
- fita LED pode ser `5V`, `12V` ou `24V`;
- servo drive geralmente é classificado para `5V` ou `6V`;
- aquecedor pode ser `12V`, `24V` ou `110-230V AC`.

Se você conectar um ventilador `24V` a `12V`, ele pode não ligar ou funcionar fracamente. Se você conectar um ventilador `12V` a `24V`, ele pode falhar rapidamente.

A regra principal:

**a tensão da fonte de alimentação deve corresponder à tensão da carga.**

Não conecte um dispositivo a uma tensão mais alta apenas porque o conector se encaixa fisicamente.

## Potência mostra tamanho da carga

Potência mostra quanta energia a carga consome ou converte em trabalho, calor, luz ou movimento.

Potência é medida em watts: `W`.

Exemplos:

- `24V 5W` - carga pequena;
- `24V 24W` - cerca de `1A`;
- `24V 120W` - já cerca de `5A`;
- `24V 240W` - cerca de `10A`.

Aquecedores geralmente consomem muita potência. Ventiladores consomem menos, mas podem ter corrente de inrush alta. Fitas LED podem ser uma carga pequena se curtas, ou uma carga séria se longas e brilhantes.

## Corrente carrega fios e elementos de potência

Corrente mostra quanta eletricidade flui através de fios, terminais, conectores e elementos de potência.

Corrente frequentemente cria problemas práticos:

- os fios aquecem;
- os terminais ficam escuros;
- os conectores derretem;
- MOSFET superaquece;
- fonte de alimentação não é suficiente;
- dispositivo reinicia quando a carga liga;
- fusível dispara não por acaso, mas por sobrecarga real ou erro.

Portanto, não é suficiente conhecer apenas a tensão. Você precisa calcular a corrente.

## Fórmula de cálculo

Para a maioria dos cálculos simples, você precisa da fórmula de potência:

```text
P = U * I
```

Onde:

- `P` - potência em watts `W`;
- `U` - tensão em volts `V`;
- `I` - corrente em amperes `A`.

Para encontrar corrente:

```text
I = P / U
```

![Lei de Ohm: circuito com fonte de tensão, corrente e resistência](../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Esta fórmula não é para um exame. É necessária para entender se a fonte de alimentação, fio, terminal, módulo MOSFET, relé, SSR ou saída da placa conseguirá suportar.

## Tabela rápida para 24V

Em impressoras 3D e periféricos, `24V` é comum. Para avaliação rápida, é útil lembrar:

| Potência | Corrente em 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Estes são valores aproximados, mas para a primeira escolha de fonte de alimentação, fio e interruptor de potência são muito úteis.

## Exemplo: aquecedor 24V 100W

Você tem um aquecedor:

```text
24V 100W
```

Calcule a corrente:

```text
I = 100W / 24V = 4.17A
```

Isso significa que o seguinte deve suportar mais de `4.17A`:

- fonte de alimentação;
- fio;
- terminais;
- conector;
- MOSFET ou SSR;
- fusível e porta-fusível;
- trilhas da placa, se o aquecedor estiver conectado à placa.

Se a fonte de alimentação para as condições para `24V 5A`, formalmente se aproxima da carga, mas quase sem margem. Para um dispositivo real é melhor levar mais.

## Exemplo: múltiplas cargas

Suponha que um dispositivo `24V` tem:

- aquecedor `100W`;
- ventilador `24V 0.2A`;
- fita LED `24V 1A`;
- outro ventilador `24V 0.15A`.

Calcule o aquecedor:

```text
100W / 24V = 4.17A
```

Some-os:

```text
4.17A + 0.2A + 1A + 0.15A = 5.52A
```

Uma fonte de alimentação mínima "encaixe apertado" seria em torno de `24V 6A`, mas essa é uma escolha ruim para operação de longo prazo. Com `50%` de margem:

```text
5.52A * 1.5 = 8.28A
```

Na prática você deve procurar uma fonte de alimentação `24V 9A`, `24V 10A` ou maior, se o gabinete, resfriamento e segurança permitirem.

## Margem é obrigatória

Fonte de alimentação, fiação, terminais e módulos de potência não podem ser selecionados exatamente de acordo com a corrente calculada.

Para este guia, uma regra simples para avaliação inicial aproximada:

**planeje pelo menos 50% de margem**, a menos que a documentação de um componente específico exija mais. Esta não é uma garantia universal, mas uma estimativa inicial. A seleção final é feita de acordo com especificações técnicas, temperatura dentro do gabinete, resfriamento, derating e aquecimento real de terminais/fios.

Margem é necessária porque:

- fonte de alimentação aquece;
- temperatura dentro do gabinete pode ser maior que a temperatura ambiente;
- ventiladores e motores têm corrente de inrush;
- os contatos envelhecem e afrouxam;
- terminais têm limites de corrente e temperatura;
- SSR e MOSFET geram calor;
- fonte de alimentação pode ter derating - redução de potência máxima em alta temperatura ou ventilação inadequada.

As fontes de alimentação industrial geralmente têm uma curva de derating na especificação técnica — uma curva de potência máxima reduzida conforme a temperatura sobe. Derating significa que em alta temperatura ou ventilação inadequada, o fabricante reduz a potência máxima permitida. Portanto, o rótulo `240W` em uma fonte de alimentação nem sempre significa que ela entregará com segurança `240W` em um gabinete fechado e quente.

## O ponto fraco pode não ser a fonte de alimentação

Mesmo que a fonte de alimentação seja poderosa, o circuito pode ser fraco em outro lugar.

Você precisa verificar todo o circuito:

- saída da fonte de alimentação;
- fio;
- bloco de terminais;
- conector;
- fusível;
- módulo MOSFET;
- relé ou SSR;
- trilhas da placa;
- a carga em si.

Por exemplo, uma fonte de alimentação pode suportar `10A`, mas um conector pequeno ou terminal parafuso deficiente pode aquecer já em corrente menor. Isso é especialmente importante para aquecedores e fitas LED.

## O que é um interruptor de potência

Um interruptor de potência é um interruptor controlado.

O controlador não alimenta uma carga pesada diretamente. Ele fornece um sinal de controle fraco e o interruptor de potência liga ou desliga a corrente de carga.

Exemplos:

- módulo MOSFET para cargas DC `12V`/`24V`;
- relé;
- SSR;
- controlador de carga pronto;
- saída de potência padrão da placa, se for para opções de carga necessárias.

Para aquecedores, ventiladores, fitas LED e motores, a regra quase sempre se aplica:

**GPIO do controlador não alimenta a carga. GPIO apenas controla.**

## Um pouco sobre a lei de Ohm

A lei de Ohm relacionada tensão, corrente e resistência:

```text
U = I * R
```

Para este artigo, a ideia simples é importante: se você aplicar tensão a uma carga, a corrente fluirá através dela. Quanta corrente flui depende da carga em si.

Mas nem todas as cargas se comportam da mesma forma:

- aquecedor é próximo a uma carga resistiva;
- ventilador e motor têm corrente de inrush;
- servo drive aumenta bruscamente a corrente quando bloqueado;
- fita LED consome corrente por comprimento e brilho;
- módulo eletrônico pode ter corrente transitória quando ligado.

Portanto, para um dispositivo real é melhor levar dados de especificações técnicas ou medir a corrente com um multímetro / fonte de alimentação de laboratório para ter certeza.

## O que verificar antes de conectar

Antes de conectar a carga, responda:

1. Para qual tensão a carga é classificada?
2. É uma carga DC ou AC?
3. Qual potência ou corrente é especificada?
4. Qual corrente você obterá da fórmula `I = P / U`?
5. Quais outras cargas estão na mesma fonte de alimentação?
6. Há pelo menos `50%` de margem?
7. Fios, terminais, conectores e placa suportam?
8. O que controlará a carga: MOSFET, relé, SSR ou saída padrão?
9. Um fusível é necessário?
10. O que acontece se houver um curto-circuito, travamento do motor ou falha do ventilador?

Se for um aquecedor ou tensão de rede `PE`, os requisitos de segurança são mais altos. A seção de rede não pode ser montada por suposição: você precisa de um gabinete adequado, fiação, isolamento, aterramento protetor `PE`, ruptura de tensão para fios e seleção por uma pessoa danificada.

## O ponto principal

- A tensão da fonte de alimentação deve corresponder à tensão da carga.
- Potência mostra o tamanho da carga.
- Corrente mostra a carga em fios, terminais, conectores e elementos de potência.
- Fórmula básica: `I = P / U`.
- Em um sistema `24V`, `24W` é cerca de `1A`, `120W` é cerca de `5A`, `240W` é cerca de `10A`.
- As correntes de todas as cargas em uma fonte de alimentação se somam.
- Você precisa de margem de pelo menos `50%` para estimativa inicial aproximada; a seleção precisa é feita de acordo com especificações técnicas, temperatura, resfriamento e derating.
- O ponto fraco pode não ser a fonte de alimentação, mas um terminal, conector, fio, MOSFET ou trilha de placa.
- GPIO do controlador não alimenta uma carga pesada, apenas controla um interruptor de potência.

## Materiais de referência

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - explicação básica clara de tensão, corrente, resistência e lei de Ohm.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - calculadora para calcular relações de tensão, corrente, resistência e potência.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - por que a potência máxima de uma fonte de alimentação depende de temperatura, ventilação e tensão de entrada.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - seleção de fonte de alimentação levando em conta temperatura, derating, cabos e tipo de carga.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - por que a corrente máxima de terminais e conectores depende de temperatura e design.
