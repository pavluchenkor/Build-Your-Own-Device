# TRIAC

Um TRIAC, ou tiristor, é um semicondutor de potência para corrente alternada. É utilizado onde é necessário ligar ou controlar uma carga em CA: por exemplo um aquecedor de rede elétrica, lâmpada incandescente ou outro dispositivo simples a `110-230V AC`.

Para dispositivos artesanais este é um tema de alto risco. O TRIAC em si não torna a tensão de rede segura. Apenas fornece uma forma de controlar uma carga em CA sem contactos mecânicos.

## Como o TRIAC difere do MOSFET

O módulo MOSFET do artigo anterior é normalmente utilizado para cargas em CC: `5V`, `12V`, `24V`.

O TRIAC é utilizado para cargas em CA. É ativado por um impulso de controlo e conduz corrente até que a corrente que o atravessa caia abaixo do valor de manutenção. Na rede de CA isto acontece normalmente perto da passagem pelo zero da onda sinusoidal.

Na prática:

- MOSFET - escolha típica para ventilador `12V`/`24V`, fita LED ou aquecedor CC;
- TRIAC - elemento típico dentro de reguladores de potência CA e muitos SSR CA;
- SSR - relé de estado sólido já pronto, que pode conter um optoacoplador, TRIAC/tiristor, caixa, terminais e por vezes dissipador de calor.

Para um principiante, numa carga de rede elétrica, é frequentemente mais seguro considerar um SSR já pronto ou módulo certificado do que montar um circuito TRIAC próprio numa breadboard.

## Por que é utilizado para cargas CA

Uma carga de baixa tensão e alta potência requer corrente elevada.

Por exemplo:

```text
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> about 1.3A
```

A `24V` são necessários fios grossos, fonte de alimentação potente, MOSFET robusto, terminais adequados e refrigeração. A `230V AC` a corrente é menor, mas existe tensão de rede perigosa e todos os requisitos de segurança elétrica.

A abordagem com TRIAC não é "melhor" nem "mais simples". É um compromisso diferente: menos corrente no circuito de potência, mas requisitos muito mais elevados para isolamento, caixa, fusível, distâncias e qualificações.

## Arquitetura típica

O controlador normalmente não é ligado diretamente ao TRIAC.

Uma arquitetura segura típica tem o seguinte aspeto:

![AC dimmer circuit with TRIAC](../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Contém:

- lado de baixa tensão: controlador e resistência de controlo;
- TRIAC optoisolador: transmite o comando através de isolamento ótico;
- lado da rede: TRIAC de potência, carga CA, fusível, terminais e caixa;
- por vezes circuito snubber e varistor/TVS para ruído e picos.

O TRIAC optoisolador é necessário para isolamento galvânico. Isto significa que não existe ligação elétrica direta entre o microcontrolador e a secção de rede. O controlo é transmitido através de luz dentro do optoacoplador.

O isolamento galvânico reduz o risco de a tensão de rede atingir o controlador, USB e computador. Mas não torna a secção de rede segura para tocar.

## Passagem pelo zero e controlo de fase

Os TRIACs optoisoladores existem com passagem pelo zero e sem ela.

Um TRIAC optoisolador com passagem pelo zero liga a carga perto da passagem pelo zero da tensão de rede. Isto é conveniente para ligar/desligar simplesmente um aquecedor ou outra carga resistiva: menos ruído e comutação mais suave.

Um TRIAC optoisolador sem passagem pelo zero é utilizado onde é necessário controlo de fase de potência, por exemplo um dimmer. Este circuito é mais complexo: é necessário detetar a passagem pelo zero, contar o atraso e ter em conta o ruído.

Para um aquecedor num secador ou câmara, o controlo de nível dimmer normalmente não é necessário. Frequentemente é suficiente uma abordagem lenta de ligar/desligar ou controlo por rajadas, se for suportado pelo módulo escolhido e seguro para a carga.

## Cargas adequadas

Um TRIAC é mais fácil de utilizar com cargas CA resistivas:

- aquecedor;
- lâmpada incandescente;
- carga térmica simples sem eletrónica interna.

Use com precaução:

- motores;
- ventiladores CA;
- transformadores;
- solenoides;
- fontes de alimentação;
- controladores eletrónicos;
- cargas com corrente de arranque elevada.

Uma carga indutiva desloca a fase da corrente em relação à tensão e pode interferir com o desligamento normal do TRIAC. Pode exigir outros tipos de TRIACs, circuito snubber, varistor ou um método de comutação diferente.

Uma fonte de alimentação ou controlador eletrónico não deve ser considerado uma carga resistiva normal. Se tiver eletrónica própria no interior, o controlo por TRIAC pode funcionar mal ou de forma perigosa.

## Circuito snubber

O snubber é um circuito RC (resistência + condensador em paralelo com o TRIAC) que amortece variações bruscas de tensão e evita o disparo falso do TRIAC.

Pode ajudar:

- com cargas indutivas;
- com ruído rápido na rede;
- com disparo falso do TRIAC;
- com problemas de desligamento.

Um ponto de partida típico para uma carga resistiva de 200–400 W a 230 V: **100 nF + 100 Ω**. O condensador deve ser do tipo X2 ou equivalente, dimensionado para funcionamento em circuito de rede. Esta não é uma solução universal, mas um valor de partida. Para outra carga, os valores são recalculados de acordo com a folha de dados do TRIAC e as notas de aplicação do fabricante.

Se não tiver experiência com circuitos CA, é preferível utilizar um módulo já pronto ou SSR onde o snubber já foi calculado pelo fabricante.

## Aquecimento e dissipador de calor

Um TRIAC aquece durante o funcionamento. Não é um interruptor perfeito: existe uma queda de tensão sobre ele, o que significa que é gerado calor.

É necessário verificar:

- corrente da carga;
- encapsulamento do TRIAC;
- queda de tensão no estado condutor;
- requisitos do dissipador de calor;
- temperatura ambiente;
- temperatura dentro da caixa;
- distância de plásticos e fios;
- margem nos parâmetros.

Na especificação técnica existem muitos parâmetros. Para uma primeira escolha, três são suficientes:

- `IT(RMS)` — corrente eficaz máxima através do TRIAC. Deve ser superior à corrente da carga com margem, com refrigeração real.
- `VDRM`/`VRRM` — tensão máxima no estado de bloqueio. Para rede de 230 V, escolha TRIAC com tensão nominal de 600 V ou superior.
- `IGT` — corrente de porta. Deve corresponder às capacidades do TRIAC optoisolador.

Outros parâmetros (`IH`, `dV/dt`, `Tj`, `Rth`) são importantes para cálculo preciso ou quando existem problemas no circuito real.

A classificação de corrente na especificação técnica é dada em determinadas condições de refrigeração. Numa caixa fechada e quente sem dissipador de calor, a corrente máxima real é inferior.

## TRIAC e SSR

Um SSR para carga CA utiliza frequentemente um optoacoplador e um TRIAC ou tiristor de potência no interior.

Vantagens de um SSR já pronto:

- terminais convenientes;
- entrada de controlo clara;
- caixa;
- parâmetros declarados;
- frequentemente mais fácil de montar e refrigerar mecanicamente.

Desvantagens:

- o SSR também aquece;
- é necessário o tipo correto: SSR com saída CA para carga CA;
- muitos SSRs requerem dissipador de calor;
- o mercado tem muitas falsificações e módulos com especificações exageradas;
- o SSR não substitui o fusível, a caixa e a segurança elétrica.

Se a tarefa é controlar um aquecedor de rede num dispositivo real, um SSR de qualidade já pronto é frequentemente mais prático do que um circuito artesanal com TRIAC separado.

## O que não se deve fazer

Não se deve:

- montar um circuito TRIAC de rede numa breadboard sem solda;
- deixar a secção de rede aberta sob tensão;
- ligar o controlador diretamente à secção de rede sem isolamento;
- utilizar módulo MOSFET de baixa tensão em vez de TRIAC/SSR para `230V AC`;
- colocar um condensador aleatório no circuito snubber de rede;
- considerar a indicação "40A" num módulo barato como verificação suficiente;
- prescindir de fusível;
- colocar terminais de rede junto a USB, botões e contactos de baixa tensão expostos;
- testar este tipo de circuito sem compreender segurança elétrica.

Trabalhar com `110-230V AC` requer conhecimento, ferramentas adequadas, caixa, verificação do isolamento e compreensão das regras locais. Em caso de dúvida, uma pessoa qualificada deve montar ou inspecionar a secção de potência.

## O que verificar antes de comprar

Antes de comprar um TRIAC, módulo ou SSR, verifique:

- se é carga CA ou CC;
- tensão de rede;
- corrente e potência da carga;
- se é carga resistiva ou indutiva;
- se é necessária passagem pelo zero;
- se é necessário snubber;
- corrente máxima com refrigeração real;
- se é necessário dissipador de calor;
- se existe optoisolamento;
- terminais e espaçamentos para rede;
- fusível e caixa;
- se existe especificação técnica ou documentação do fabricante.

Se não houver documentação e o módulo tiver de controlar um aquecedor de rede, essa é uma má escolha.

## Erros frequentes

- utilizar TRIAC para carga CC;
- confundir MOSFET, TRIAC e SSR;
- ligar carga de rede sem optoisolamento;
- utilizar TRIAC optoisolador com passagem pelo zero e esperar dimming suave;
- utilizar TRIAC com motor sem snubber e verificação do tipo de carga;
- não instalar dissipador de calor;
- não ter em conta a temperatura dentro da caixa;
- utilizar terminais aleatórios e fios finos;
- pensar que SSR ou TRIAC substitui o fusível;
- deixar a secção de rede aberta junto ao controlador e USB.

## O essencial

O TRIAC é um interruptor de potência para cargas CA. É útil para cargas resistivas de rede, como aquecedores, mas requer uma conceção correta da secção de rede.

Para um microcontrolador, é necessário optoisolamento. Para a carga, são necessários o TRIAC/SSR correto, fusível, terminais, caixa, dissipador de calor se necessário e verificação de segurança. Se não tiver experiência com `110-230V AC`, não monte a secção de potência por conta própria.

## Materiais de referência

- [STMicroelectronics: Standard and snubberless triacs documentation](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - Seleção de TRIAC, parâmetros e notas de aplicação sobre TRIAC standard/snubberless.
- [ST AN437: RC snubber circuit design for TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - Explicação detalhada de por que é necessário o circuito RC de amortecimento e como afeta o desligamento do TRIAC.
- [MOC3063 datasheet: zero-cross optoisolator TRIAC driver](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - Exemplo de TRIAC optoisolador para interface de lógica com cargas `115/240 VAC`.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - Explicação básica do SSR como relé de estado sólido sem contactos mecânicos.
- [Omron SSR glossary: phototriac, zero-cross, snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - Definições breves de fototriac, passagem pelo zero e circuito snubber.
