# Corrente, Tensão e Potência de Carga

Antes de ligar um aquecedor, ventilador, fita LED, servo drive ou outro módulo, precisa de compreender três coisas:

- tensão;
- corrente;
- potência.

Sem isto, é fácil comprar uma fonte de alimentação incorreta, sobreaquecer o cabo, derreter o conector, danificar um módulo MOSFET ou ligar a carga ao controlador de forma a funcionar instável.

## Onde encontrar os parâmetros

A tensão, corrente e potência normalmente sofrem:

- na caixa do componente;
- na etiqueta da fonte de alimentação;
- na página do produto;
- nas especificações técnicas;
- no manual;
- no esquema ou pinout da placa.

Se o parâmetro não for especificado, não se trata de uma questão menor. É uma razão para parar e perceber exatamente o que está ligado.

Para componentes da periferia de impressoras 3D, os parâmetros típicos são:

- ventilador: `24V 0.2A`;
- aquecedor: `24V 100W`;
- fita LED: `24V 9.6W/m`;
- servo drive: `5V`, a corrente depende da carga;
- placa do controlador: a corrente máxima para cada saída é especificada separadamente.

## A tensão deve corresponder

Uma carga é concebida para uma tensão específica.

Exemplos:

- ventilador pode ser `5V`, `12V` ou `24V`;
- fita LED pode ser `5V`, `12V` ou `24V`;
- servo drive é frequentemente classificado como `5V` ou `6V`;
- aquecedor pode ser `12V`, `24V` ou `110-230V AC`.

Se ligar um ventilador `24V` a `12V`, pode não ligar ou funcionar fracamente. Se ligar um ventilador `12V` a `24V`, pode falhar rapidamente.

A regra principal:

**a tensão da fonte de alimentação deve corresponder à tensão da carga.**

Não ligue um dispositivo a uma tensão superior apenas porque o conector encaixa fisicamente.

## A potência mostra o tamanho da carga

A potência indica quanto a energia que uma carga consome ou converte em trabalho, calor, luz ou movimento.

A potência é medida em watts: `W`.

Exemplos:

- `24V 5W` - carga pequena;
- `24V 24W` - cerca de `1A`;
- `24V 120W` - já cerca de `5A`;
- `24V 240W` - cerca de `10A`.

Os aquecedores normalmente consomem muita potência. Os ventiladores consomem menos, mas podem ter corrente de arranque elevada. As fitas LED podem ser uma carga pequena se forem curtas, ou uma carga séria se forem longas e brilhantes.

## A corrente carrega cabos e elementos de potência

A corrente indica quanto a eletricidade flui através de cabos, terminais, conectores e elementos de potência.

A corrente cria frequentemente problemas práticos:

- os cabos aquecem;
- os terminais ficam escuros;
- os conectores derretem;
- MOSFET sobreaquecem;
- a fonte de alimentação é insuficiente;
- o dispositivo reinicia quando a carga liga;
- o fusível queima não por acaso, mas por sobrecarga real ou erro.

Portanto, não é suficiente conhecer apenas a tensão. Precisa de calcular a corrente.

## Fórmula de cálculo

Para a maioria dos cálculos simples, precisa da fórmula de potência:

```text
P = U * I
```

Onde:

- `P` - potência em watts `W`;
- `U` - tensão em volts `V`;
- `I` - corrente em amperes `A`.

Para encontrar a corrente:

```text
I = P / U
```

![Lei de Ohm: circuito com fonte de tensão, corrente e resistência](../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Esta fórmula não é para um exame. É necessária para compreender se a fonte de alimentação, cabo, terminal, módulo MOSFET, relé, SSR ou saída da placa a aguentará.

## Tabela rápida para 24V

Em impressoras 3D e periféricos, `24V` é comum. Para uma avaliação rápida, é útil memorizar:

| Potência | Corrente em 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Estes são valores aproximados, mas para a primeira escolha de fonte de alimentação, cabo e comutador de potência são muito úteis.

## Exemplo: aquecedor 24V 100W

Tem um aquecedor:

```text
24V 100W
```

Calcule a corrente:

```text
I = 100W / 24V = 4.17A
```

Isto significa que o seguinte deve aguentar mais de `4.17A`:

- fonte de alimentação;
- cabo;
- terminais;
- conector;
- MOSFET ou SSR;
- fusível e porta-fusível;
- traços da placa, se o aquecedor estiver ligado à placa.

Se a fonte de alimentação para situações como `24V 5A`, formalmente aproxima-se da carga, mas quase sem margem. Para um dispositivo real é melhor levar mais.

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

Uma fonte de alimentação mínima seria cerca de `24V 6A`, mas essa é uma má escolha para funcionamento a longo prazo. Com margem de `50%`:

```text
5.52A * 1.5 = 8.28A
```

Praticamente, deve procurar uma fonte de alimentação `24V 9A`, `24V 10A` ou maior, se o enclosure, arrefecimento e segurança permitirem.

## A margem é obrigatória

A fonte de alimentação, cabeamento, terminais e módulos de potência não podem ser selecionados exatamente de acordo com a corrente calculada.

Para este guia, uma regra simples para avaliação inicial aproximada:

**planeie pelo menos margem de 50%**, a menos que a documentação de um componente específico exija mais. Isto não é uma garantia universal, mas uma estimativa inicial. A seleção final é feita de acordo com as especificações técnicas, temperatura dentro do enclosure, arrefecimento, redução de potência e aquecimento real dos terminais/cabos.

A margem é necessária porque:

- a fonte de alimentação aquece;
- a temperatura dentro do enclosure pode ser superior à temperatura ambiente;
- ventiladores e motores têm corrente de arranque;
- os contactos envelhecem e afrouxam;
- os terminais têm limites de corrente e temperatura;
- SSR e MOSFET geram calor;
- a fonte de alimentação pode ter redução de potência - redução da potência máxima em temperatura elevada ou ventilação fraca.

As fontes de alimentação industriais frequentemente têm uma curva de redução de potência nas especificações técnicas — uma curva de redução da potência máxima com o aumento da temperatura. A redução de potência significa que em temperatura elevada ou ventilação fraca, o fabricante reduz a potência máxima permitida. Portanto, a etiqueta `240W` numa fonte de alimentação nem sempre significa que irá fornecer `240W` de forma segura num enclosure fechado e quente.

## O ponto fraco pode não ser a fonte de alimentação

Mesmo que a fonte de alimentação seja poderosa, o circuito pode ser fraco noutro lado.

Precisa de verificar todo o circuito:

- saída da fonte de alimentação;
- cabo;
- bloco de terminais;
- conector;
- fusível;
- módulo MOSFET;
- relé ou SSR;
- traços da placa;
- a carga em si.

Por exemplo, uma fonte de alimentação pode aguentar `10A`, mas um conector pequeno ou um terminal de parafuso fraco pode aquecer já em corrente menor. Isto é especialmente importante para aquecedores e fitas LED.

## O que é um comutador de potência

Um comutador de potência é um comutador controlado.

O controlador não alimenta diretamente uma carga pesada. Dá um sinal de controlo fraco e o comutador de potência liga ou desliga a corrente da carga.

Exemplos:

- módulo MOSFET para cargas `12V`/`24V` DC;
- relé;
- SSR;
- driver de carga pré-fabricado;
- saída de potência padrão da placa, se for para opções de carga necessárias.

Para aquecedores, ventiladores, fitas LED e motores, a regra quase sempre se aplica:

**o GPIO do controlador não alimenta a carga. O GPIO apenas controla.**

## Um pouco sobre a lei de Ohm

A lei de Ohm relacionada tensão, corrente e resistência:

```text
U = I * R
```

Para este artigo, a ideia simples é importante: se aplicar tensão a uma carga, a corrente fluirá através dela. Quanto a corrente flui depende da própria carga.

Mas nem todas as cargas se comportam da mesma forma:

- aquecedor é próximo de uma carga resistiva;
- ventilador e motor têm corrente de arranque;
- servo drive aumenta a corrente rapidamente quando bloqueado;
- fita LED consome corrente por comprimento e brilho;
- módulo eletrónico pode ter corrente transitória quando ligado.

Portanto, para um dispositivo real é melhor usar dados das especificações técnicas ou medir a corrente com um multímetro / fonte de alimentação de laboratório para ter certeza.

## O que verificar antes de ligar

Antes de ligar a carga, responda:

1. Para que tensão é a carga classificada?
2. É uma carga DC ou AC?
3. Que potência ou corrente é especificada?
4. Que corrente obtém da fórmula `I = P / U`?
5. Que outras cargas estão na mesma fonte de alimentação?
6. Existe pelo menos margem de `50%`?
7. Os cabos, terminais, conectores e placa a aguentam?
8. O que controlará a carga: MOSFET, relé, SSR ou saída padrão?
9. É necessário um fusível?
10. O que acontece se houver um curto-circuito, bloqueio do motor ou falha do ventilador?

Se isto for um aquecedor ou tensão de rede `PE`, os requisitos de segurança são mais elevados. A seção de rede não pode ser montada adivinhando: precisa de um invólucro adequado, inclusão, isolamento, proteção de aterramento `PE`, ruptura de tensão para cabos e seleção por uma pessoa danificada.

## O ponto principal

- A tensão da fonte de alimentação deve corresponder à tensão da carga.
- A potência mostra o tamanho da carga.
- A corrente mostra a carga em cabos, terminais, conectores e elementos de potência.
- Fórmula básica: `I = P / U`.
- Num sistema `24V` `24W` é cerca de `1A`, `120W` é cerca de `5A`, `240W` é cerca de `10A`.
- As correntes de todas as cargas numa fonte de alimentação somam-se.
- Precisa de margem de pelo menos `50%` para estimativa inicial aproximada; a seleção precisa é feita de acordo com as especificações técnicas, temperatura, arrefecimento e redução de potência.
- O ponto fraco pode não ser a fonte de alimentação, mas um terminal, conector, cabo, MOSFET ou traço de placa.
- O GPIO do controlador não alimenta uma carga pesada, apenas controla um comutador de potência.

## Materiais de referência

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - explicação básica clara de tensão, corrente, resistência e lei de Ohm.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - calculadora para calcular relações de tensão, corrente, resistência e potência.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - por que a potência máxima de uma fonte de alimentação depende da temperatura, ventilação e tensão de entrada.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - seleção de uma fonte de alimentação levando em conta temperatura, redução de potência, cabos e tipo de carga.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - por que a corrente máxima dos terminais e conectores depende da temperatura e design.
