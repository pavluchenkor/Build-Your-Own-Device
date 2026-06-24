# TRIAC

Um TRIAC, ou tiristor, é um interruptor semicondutor de potência para corrente alternada. É utilizado onde você precisa ligar ou controlar uma carga AC: por exemplo um aquecedor de rede, lâmpada incandescente ou outro dispositivo simples em `110-230V AC`.

Para dispositivos caseiros este é um tópico de alto risco. O TRIAC em si não torna a tensão de rede segura. Apenas fornece uma forma de controlar uma carga AC sem contatos mecânicos.

## Como TRIAC difere de MOSFET

O módulo MOSFET do artigo anterior é geralmente utilizado para cargas DC: `5V`, `12V`, `24V`.

TRIAC é utilizado para cargas AC. É ligado por um pulso de controlo e conduz corrente até que a corrente através dele caia abaixo do valor de retenção. Em rede AC isto geralmente acontece perto do cruzamento zero da onda senoidal.

Na prática:

- MOSFET - escolha típica para ventilador `12V`/`24V`, tira LED ou aquecedor DC;
- TRIAC - elemento típico dentro de reguladores AC e muitos SSRs AC;
- SSR - relé de estado sólido pronto, que pode conter um optocoplador, TRIAC/tiristor, enclosure, terminais e às vezes dissipador de calor.

Para um iniciante, para uma carga de rede, frequentemente é mais seguro considerar um SSR pronto ou módulo certificado do que montar seu próprio circuito TRIAC em uma breadboard.

## Por que é utilizado para cargas AC

Uma carga de baixa tensão poderosa requer alta corrente.

Por exemplo:

```text
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> cerca de 1.3A
```

Em `24V` você precisa de fios grossos, fonte de alimentação poderosa, MOSFET forte, terminais normais e arrefecimento. Em `230V AC` a corrente é menor, mas há tensão de rede perigosa e todos os requisitos de segurança elétrica.

A abordagem TRIAC não é "melhor" e não "mais simples". É um compromisso diferente: menos corrente no circuito de potência, mas requisitos muito maiores para isolamento, enclosure, fusível, distâncias e qualificações.

## Arquitetura típica

O controlador geralmente não está conectado ao TRIAC diretamente.

Uma arquitetura segura típica se parece com isto:

![Circuito dimmer AC com TRIAC](../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Tem:

- lado de baixa tensão: controlador e resistor de controlo;
- optoisolador TRIAC: transmite comando através de isolamento óptico;
- lado de rede: TRIAC de potência, carga AC, fusível, terminais e enclosure;
- às vezes circuito snubber e varistor/TVS para ruído e picos.

O optoisolador TRIAC é necessário para isolamento galvânico. Isto significa que não há conexão elétrica direta entre o microcontrolador e a secção de rede. O controlo é transmitido através de luz dentro do optocoplador.

O isolamento galvânico reduz o risco de tensão de rede alcançar o controlador, USB e computador. Mas não torna a secção de rede segura para tocar.

## Zero-cross e controlo de fase

Optoisoladores TRIACs vêm com zero-cross e sem ele.

Um optoisolador TRIAC zero-cross liga a carga perto do cruzamento zero da tensão de rede. Isto é conveniente para simples ligar/desligar de um aquecedor ou outra carga resistiva: menos ruído e comutação mais suave.

Um optoisolador TRIAC sem zero-cross é utilizado onde controlo de fase de potência é necessário, por exemplo um dimmer. Um tal circuito é mais complexo: você precisa detectar cruzamento zero, contar atraso e contabilizar ruído.

Para um aquecedor em um secador ou câmara, controlo de nível dimmer geralmente não é necessário. Frequentemente uma abordagem lenta ligar/desligar ou controlo de rajada é suficiente, se é suportado pelo módulo escolhido e seguro para a carga.

## Que cargas são apropriadas

Um TRIAC é mais fácil de utilizar com cargas AC resistivas:

- aquecedor;
- lâmpada incandescente;
- carga térmica simples sem electrónica dentro.

Use cautela com:

- motores;
- ventiladores AC;
- transformadores;
- solenóides;
- fontes de alimentação;
- drivers electrónicos;
- cargas com alta corrente de inrush.

A carga indutiva desloca a fase de corrente relativa à tensão e pode interferir com o desligamento normal de TRIAC. Pode requerer outros tipos de TRIACs, circuito snubber, varistor ou um método de comutação diferente.

Uma fonte de alimentação ou driver electrónico não deve ser considerado uma carga resistiva normal. Se tem sua própria electrónica dentro, controlo de TRIAC pode funcionar mal ou perigosamente.

## Circuito snubber

Snubber é um circuito RC (resistor + capacitor em paralelo com TRIAC) que amortece mudanças de tensão agudas e previne disparo falso de TRIAC.

Pode ajudar:

- com cargas indutivas;
- com ruído rápido na rede;
- com disparo falso de TRIAC;
- com problemas de desligamento.

Um ponto de partida típico para uma carga resistiva de 200–400 W em 230 V: **100 nF + 100 Ω**. O capacitor deve ser do tipo X2 ou equivalente, classificado para operação de circuito de rede. Esta não é uma solução universal, mas um valor inicial. Para outra carga, as classificações são recalculadas de acordo com a folha de dados TRIAC e notas de aplicação do fabricante.

Se você não tem experiência com circuitos AC, é melhor utilizar um módulo pronto ou SSR onde o snubber já está calculado pelo fabricante.

## Aquecimento e dissipador de calor

Um TRIAC aquece durante a operação. Não é um interruptor perfeito: há uma queda de tensão através dele, o que significa que calor é gerado.

Você precisa verificar:

- corrente de carga;
- pacote TRIAC;
- queda de tensão no estado ligado;
- requisitos de dissipador de calor;
- temperatura ambiente;
- temperatura dentro do enclosure;
- distância de plástico e fios;
- margem de parâmetro.

Na especificação técnica há muitos parâmetros. Para a primeira escolha, três são suficientes:

- `IT(RMS)` — corrente RMS máxima através de TRIAC. Deve ser maior que corrente de carga com margem, no arrefecimento real.
- `VDRM`/`VRRM` — tensão máxima no estado desligado. Para rede 230 V, escolha TRIAC classificado 600 V e mais alto.
- `IGT` — corrente de gate. Deve corresponder às capacidades do optoisolador TRIAC.

Outros parâmetros (`IH`, `dV/dt`, `Tj`, `Rth`) são importantes para cálculo preciso ou quando há problemas no circuito real.

A classificação de corrente na especificação técnica é dada sob certas condições de arrefecimento. Em um enclosure fechado, quente sem dissipador de calor, a corrente máxima real é menor.

## TRIAC e SSR

Um SSR para uma carga AC frequentemente utiliza um optocoplador e TRIAC ou estágio de potência tiristor dentro.

Vantagens de um SSR pronto:

- terminais convenientes;
- entrada de controlo clara;
- enclosure;
- parâmetros definidos;
- frequentemente mais fácil de montar e arrefecer mecanicamente.

Desvantagens:

- SSR também aquece;
- tipo correcto é necessário: SSR saída AC para carga AC;
- muitos SSRs requerem dissipador de calor;
- mercado tem muitas falsificações e módulos com especificações exageradas;
- SSR não substitui fusível, enclosure e segurança elétrica.

Se a tarefa é controlar um aquecedor de rede em um dispositivo real, um SSR de qualidade pronto é frequentemente mais prático que um circuito caseiro em um TRIAC separado.

## O que você não pode fazer

Você não pode:

- montar um circuito TRIAC de rede em uma breadboard sem solda;
- deixar a secção de rede aberta sob potência;
- conectar o controlador diretamente à secção de rede sem isolamento;
- utilizar módulo MOSFET de baixa tensão em vez de TRIAC/SSR para `230V AC`;
- colocar um capacitor aleatório no circuito snubber de rede;
- considerar a etiqueta "40A" em um módulo barato como verificação suficiente;
- fazer sem um fusível;
- colocar terminais de rede ao lado de USB, botões e contactos de baixa tensão abertos;
- testar tal circuito sem compreender segurança elétrica.

Trabalhar com `110-230V AC` requer conhecimento, ferramentas apropriadas, enclosure, verificação de isolamento e compreensão de regras locais. Se em dúvida, uma pessoa qualificada deve montar ou inspecionar a secção de potência.

## O que verificar antes de comprar

Antes de comprar um TRIAC, módulo ou SSR, verifique:

- é carga AC ou DC;
- tensão de rede;
- corrente e potência de carga;
- é carga resistiva ou indutiva;
- é zero-cross necessário;
- é snubber necessário;
- corrente máxima no arrefecimento real;
- é dissipador de calor necessário;
- há optoisolação;
- terminais e espaçamento para rede;
- fusível e enclosure;
- há especificação técnica ou documentação do fabricante.

Se não há documentação, e o módulo deve controlar um aquecedor de rede, essa é uma escolha pobre.

## Erros comuns

- utilizar TRIAC para carga DC;
- confundir MOSFET, TRIAC e SSR;
- conectar carga de rede sem optoisolação;
- utilizar optoisolador TRIAC zero-cross e esperar atenuação suave;
- utilizar TRIAC com motor sem snubber e verificação de tipo de carga;
- não instalar dissipador de calor;
- não contabilizar temperatura dentro de enclosure;
- utilizar terminais aleatórios e fios finos;
- pensar que SSR ou TRIAC substitui o fusível;
- deixar a secção de rede aberta ao lado do controlador e USB.

## O ponto principal

TRIAC é um interruptor de potência para cargas AC. É útil para cargas resistivas de rede, como aquecedores, mas requer design correcto de secção de rede.

Para um microcontrolador, optoisolação é necessária. Para a carga, o TRIAC/SSR correcto, fusível, terminais, enclosure, dissipador de calor se necessário e verificação de segurança são necessários. Se você não tem experiência com `110-230V AC`, não monte a secção de potência você mesmo.

## Materiais de referência

- [STMicroelectronics: Standard and snubberless triacs documentation](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - selecção TRIAC, parâmetros e notas de aplicação em TRIAC sem snubber/padrão.
- [ST AN437: RC snubber circuit design for TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - explicação detalhada de por que circuito RC de amortecimento é necessário e como afecta desligamento TRIAC.
- [MOC3063 datasheet: zero-cross optoisolator TRIAC driver](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - exemplo de optoisolador TRIAC para interfacear lógica com cargas `115/240 VAC`.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - explicação básica de SSR como relé de estado sólido sem contactos mecânicos.
- [Omron SSR glossary: phototriac, zero-cross, snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - breves definições de phototriac, zero-cross e circuito snubber.
