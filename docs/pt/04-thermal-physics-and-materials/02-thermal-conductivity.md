# Condutividade Térmica

A condutividade térmica mostra como um material transfere facilmente ou calor através de si mesmo.

Para um secador caseiro, câmara, filtro, conduto de ar ou carcaça, isto não é física abstracta. A condutividade térmica determina se o calor irá escapar para o exterior, se um ponto quente irá aparecer perto do aquecedor, quanto a parede externa irá aquecer, e se uma peça impressa irá amolecer.

## Ideia Simples

O calor tende sempre a escapar de uma zona mais quente para uma mais fria. Quanto maior a condutividade térmica de um material, mais facilmente o calor passa através dele.

A taxa de transferência de calor é afetada por:

- material;
- espessura da parede;
- área de contacto;
- diferença de temperatura;
- qualidade do contacto entre peças;
- presença de ar, lacunas e isolamento.

Uma placa de alumínio fina pode espalhar rapidamente o calor por toda a carcaça. Uma camada espessa de lã mineral ou isolamento de espuma, pelo contrário, impede o calor de escapar.

## Valores de Referência de Materiais

Os valores abaixo servem apenas para compreender ordens de magnitude. Para uma construção real, verifique a folha de dados do material específico.

| Material | Condutividade Térmica Aproximada, `W/(m*K)` | O que Significa na Prática |
| --- | ---: | --- |
| Cobre | cerca de `400` | excelente condutor de calor, adequado para dissipação de calor, mas transfere rapidamente o calor para onde nem sempre é necessário |
| Alumínio | cerca de `200-240` | distribui bem o calor, útil como placa, radiador ou dissipador de calor |
| Aço | cerca de `15-60` | conduz o calor pior que o alumínio, mas parafusos e postes ainda podem ser pontes térmicas |
| Vidro | cerca de `1` | conduz o calor muito pior que o metal, mas não é isolamento no sentido convencional |
| Plásticos comuns | cerca de `0.1-0.5` | conduzem o calor mal, mas podem amolecer e ser inflamáveis |
| Lã mineral, fibra de vidro | cerca de `0.04` | reduz efectivamente a perda de calor, mas requer protecção contra pó, humidade e danos mecânicos |
| Poliestireno expandido / espuma de poliuretano | cerca de `0.03` | bom isolamento, mas perto do calor, a temperatura de funcionamento e as propriedades de incêndio são importantes |
| Ar | cerca de `0.026` | conduz o calor mal por si, mas transfere calor por convecção quando se move |

A conclusão principal: metal e isolamento térmico não por um fator de dois, mas por pedidos de magnitude. Portanto, mesmo uma pequena parte de metal pode mudar significativamente o quadro térmico.

## Ponte Térmica

Uma ponte térmica é um caminho através do qual o calor escapa mais facilmente do que através do resto da estrutura.

![Ponte térmica clássica através de um invólucro](../../img/04-thermal-physics-and-materials/02-thermal-bridge-classic.png)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pont_thermique_classique.png), AmisDeLaThermique, CC BY-SA 3.0*

Pontes térmicas típicas:

- parafuso de metal através de uma parede isolada;
- placa de alumínio ligada ao invólucro externo;
- poste de metal entre câmara quente e painel externo;
- bloco de terminais ou fixador perto do aquecedor;
- conduto de ar que toca directamente uma parte quente.

Uma ponte térmica nem sempre é má. Às vezes é necessária para dissipar calor de um interruptor de energia, radiador ou nó quente. O problema começa quando a ponte é acidental: a câmara perde calor, a superfície externa fica quente, e o plástico perto da ponte aquece mais do que o esperado.

## Metal: Dissipador de Calor ou Aquecimento Acidental

O metal é conveniente de usar em dispositivos aquecidos:

- como tela entre aquecedor e plástico;
- como placa de distribuição de calor;
- como base para montagem do aquecedor;
- como radiador para electrónica de potência;
- como superfície interna não inflamável.

Mas o metal não torna um dispositivo seguro automaticamente. Se uma placa de metal tocar uma zona quente e o invólucro externo, pode direcionar o calor para o exterior. Se o plástico for parafusado a ela, esse plástico pode aquecer através do fixador. Se os fios passarem através dele, perto da borda você precisa de entradas de fios, proteção contra fricção e margem de temperatura para isolamento.

## Isolamento: Perda Menor, Maior Responsabilidade

O isolamento reduz a perda de calor, mas não elimina o controlo de temperatura.

Quando você isola uma câmara:

- é mais fácil para o aquecedor elevar a temperatura;
- a carcaça pode ficar mais fria no exterior;
- o tempo de arrefecimento aumenta;
- a temperatura local perto do aquecedor pode aumentar;
- falha do ventilador ou interruptor travado torna-se mais perigoso.

Portanto, o isolamento não pode ser adicionado como uma "melhoria" sem testar novamente. Após isolamento, você precisa remedir temperaturas dentro da câmara, no aquecedor, nos fios, nos terminais e na superfície externa.

## Lacuna de Ar Também Funciona

O ar estacionário conduz o calor mal. Portanto, lacunas de ar, paredes duplas e materiais de espuma podem reduzir a transferência de calor.

Mas se o ar começar a mover-se, a convecção entra em acção. Então o calor é transferido pelo fluxo de ar, não apenas por condução térmica. Portanto, uma lacuna através da qual passa um fluxo quente pode aquecer a carcaça mais do que uma parede espessa sem fluxo.

Na prática, isto significa:

- não deixe lacunas acidentais perto do aquecedor;
- não direccione fluxo quente directamente para plástico;
- não trate lacunas de ar como protecção se um fluxo passa através delas;
- verifique a temperatura em modo operacional real, não apenas num dispositivo frio.

## O Que Procurar na Folha de Dados do Material

Para material perto do calor, a condutividade térmica não é a única coisa que importa.

Verifique:

- temperatura máxima de funcionamento contínuo;
- temperatura de amolecimento ou temperatura de deformação térmica;
- inflamabilidade e classe de comportamento ao fogo;
- permissibilidade de contacto com ar quente;
- comportamento da camada de cola, folha, revestimento ou laminação;
- recomendações do fabricante para uso;
- disponibilidade de folha de segurança SDS/MSDS se o material pode aquecer ou ser processado.

Se um material não tem documentação clara, não o coloque perto do aquecedor e não o utilize como única protecção.

## Ordem Prática de Verificação

Para carcaça, câmara ou secador, é conveniente proceder assim:

1. Identifique a zona quente: aquecedor, saída de ar, terminais, interruptor de energia.
2. Separe a zona quente do plástico com metal, cerâmica ou outro material adequado.
3. Verifique onde o metal conduz o calor.
4. Adicione isolamento apenas onde não cobre nós quentes perigosos.
5. Meça a temperatura em vários pontos após aquecimento.
6. Verifique o modo de falha do ventilador se o aquecedor depende do fluxo de ar.
7. Adicione protecção de sobreaquecimento independente onde o sobreaquecimento é perigoso.

Um sensor de temperatura na câmara não mostra o quadro térmico completo. Você precisa de medições perto do aquecedor, nos fixadores, nos fios, na carcaça e em peças impressas.

## Conclusão Principal

A condutividade térmica ajuda a compreender onde o calor realmente irá. O metal pode ser um dissipador de calor útil ou uma ponte térmica acidental. O isolamento pode melhorar a eficiência, mas ao mesmo tempo amplificar as consequências da falha.

Qualquer mudança na carcaça, isolamento, fixadores ou conduto de ar deve ser verificada medindo a temperatura em modo operacional real.

## Materiais sobre o Tópico

- [Engineering ToolBox: Thermal Conductivity of Common Materials](https://www.engineeringtoolbox.com/thermal-conductivity-d_429.html) - valores de referência de condutividade térmica para metais, plásticos, ar, vidro e isolamento.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - relação entre fluxo de calor, material, espessura da parede, área e diferença de temperatura.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - explicação básica de transferência de calor de corpo quente para frio.
- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - explicação simples de condução térmica, convecção, radiação e papel do isolamento.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - referência prática para comportamento de temperatura de materiais populares de impressão 3D.
