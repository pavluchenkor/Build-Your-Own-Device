# Soldagem

A soldagem é usada quando você precisa conectar com segurança um fio a uma almofada, soldar um conector, reparar uma conexão quebrada ou montar um pequeno módulo.

Mas a soldagem não deve substituir um conector, terminal ou fixação mecânica adequada onde o fio possa puxar, vibrar ou aquecer.

## Quando a soldagem é apropriada

Soldering is good for:

- soldar fios em uma placa;
- installing a pin header;
- repairing a broken wire;
- connecting a small module;
- soldering a thermistor or signal wire;
- prototype assembly.

Soldar não é a melhor escolha para:

- frequently disassembled connections;
- terminais de potência sem alívio de tensão;
- fios que irão se mover;
- conexões dentro de zonas quentes sem proteção;
- peças de rede elétrica de 110-230 Vca sem terminais e invólucros adequados.

## Minimal kit

Para uma soldagem adequada, você precisa de:

- ferro de soldar com controle de temperatura;
- solder;
- flux;
- soldering iron stand;
- esponja ou fio de latão para limpeza da ponta;
- wire cutters;
- wire stripper;
- tweezers or third hand;
- heat shrink tubing;
- álcool isopropílico para limpeza, se necessário.

Um ferro de soldar sem suporte é uma má ideia. Uma ponta quente queima facilmente sua mão, fio, gabinete ou mesa.

## Tin a wire

Estanhar um fio significa revestir os fios expostos com uma fina camada de solda.

Procedure:

1. Retire um pouco do isolamento.
2. Torça os fios juntos se o fio for multifilar.
3. Aplique fluxo se a solda não fluir bem.
4. Aqueça o fio com o ferro de soldar.
5. Aplique um pouco de solda na área aquecida.
6. Deixe a solda fluir pelos fios.

Não transforme a extremidade do fio em uma bolha grossa e rígida. A estanhagem deve ser limpa e fina.

## Solder a wire to a pad

Procedure:

1. Prenda a placa e o fio.
2. Estanhe a almofada.
3. Estanhe o fio.
4. Aplique o fio na almofada.
5. Aqueça o fio e a almofada simultaneamente.
6. Deixe a solda derreter e unir as peças.
7. Remova a solda e depois o ferro.
8. Não mova a junta enquanto a solda esfria.

Uma boa junta de solda parece lisa e brilhante ou uniformemente opaca, dependendo da solda. Não deve haver uma bolha no topo que não tenha molhado a almofada.

## Cold solder joints

Uma junta de solda fria é onde a solda não aqueceu adequadamente e não fluiu normalmente.

Signs:

- rough surface;
- solder in a lump;
- wire moves;
- o contato vai e vem;
- rupturas articulares com leve movimento.

As juntas de solda fria são perigosas porque às vezes podem funcionar. Em um dispositivo aquecido ou vibratório, esse contato será degradado.

Normalmente, uma junta fria é fixada por reaquecimento com fluxo até que a solda flua adequadamente.

## Overheated pad

Se você aquecer uma almofada por muito tempo, ela pode se soltar da prancha.

Isso afeta especialmente:

- cheap modules;
- small pads;
- thin traces;
- multiple rework attempts;
- fios puxando a almofada.

Se a solda não fluir, nem sempre será necessário aquecer por mais tempo. Muitas vezes, adicionar fluxo, limpar a ponta, usar a temperatura certa ou uma ponta maior ajuda.

## Flux

O fluxo ajuda a solda a molhar o metal.

Sem fluxo, a solda geralmente se enrola e não une bem as peças.

Após a soldagem, algum fluxo precisa ser removido. Isso depende do tipo de fluxo:

- no-clean can often be left;
- solúvel em água deve ser removido;
- o fluxo ativo não deve ser deixado na placa.

Se você não conhece o tipo de fluxo, use fluxo de nível eletrônico e leia sua descrição.

## Encolhimento térmico e isolamento

Uma junta soldada deve ser isolada.

Para fios, geralmente é usado tubo termorretrátil.

Procedure:

1. Deslize o termorretrátil sobre o fio antes de soldar.
2. Solde os fios.
3. Verifique a junta.
4. Deslize o termorretrátil no lugar.
5. Heat it gently.

Não deixe juntas soldadas expostas onde possam tocar no gabinete, em outro fio, em um terminal ou em um ventilador.

## Strain relief

Solder doesn't like mechanical stress.

Se um fio puxar, vibrar ou se mover, você precisa de um alívio de tensão:

- cable tie;
- clamp;
- strain relief connector;
- uma gota de silicone em local seguro;
- fio preso ao gabinete;
- um conector em vez de solda direta.

Má prática: o fio é preso apenas pela almofada de solda. Com o tempo, ele pode soltar a almofada.

## Power wires

Os fios de alimentação devem ser soldados com muito cuidado.

Verify:

- o fio tem a bitola correta;
- a junta está totalmente aquecida;
- no cold solder joints;
- no exposed strands;
- o isolamento está presente;
- fixação mecânica está presente;
- a junta não está próxima de uma zona quente sem proteção.

Para linhas de energia, um terminal ou conector adequado geralmente é melhor do que soldar fios permanentemente.

## O que verificar após a soldagem

Após a soldagem:

- inspecionar a junta;
- verifique se os contatos vizinhos não estão em curto;
- use o multímetro para verificar a necessidade de conexão;
- verifique se não há curto entre `GND` e `GND`;
- puxe suavemente o fio;
- confirme se o encolhimento térmico cobre o metal;
- verifique se o fio não puxa a almofada.

## Erros comuns

- soldar com ponta suja;
- não usar fluxo;
- aquecendo apenas a solda, não a almofada e o fio;
- making a solder blob;
- mover o fio enquanto a solda esfria;
- superaquecimento da almofada;
- deixando uma junta aberta sem contração térmica;
- fio preso apenas por solda;
- soldar fio de alimentação muito fino com ferro fraco;
- usando fluxo ácido não destinado à eletrônica.

## O essencial

- Uma boa soldagem requer aquecimento de ambas as partes, e não apenas gotejamento de solda.
- Flux often solves poor wetting problems.
- As juntas de solda fria podem funcionar às vezes, por isso são perigosas.
- Uma junta soldada deve ser isolada e aliviada mecanicamente.
- Para conexões de alimentação e desmontagens frequentes, um conector ou terminal geralmente é melhor do que soldar.

## Reference materials

- [SparkFun: How to Solder, Through-Hole Soldering](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) - tools, temperature, flux, good soldering and connection checking.
- [SparkFun: Soldering Your First Component](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/soldering-your-first-component) - basic rules: heating the pad and lead, solder application order, good joint shape.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide for electronics.
- [Adafruit: Common Soldering Problems](https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems) - cold joints, overheating, too much solder and fixes.
- [NASA Workmanship: Soldered Electrical Connections](https://workmanship.nasa.gov/lib/insp/2%20books/links/sections/407%20Soldering.html) - reference material on solder joint quality and mechanical wire support.
