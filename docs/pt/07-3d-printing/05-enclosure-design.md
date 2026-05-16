# Design do invólucro

Um invólucro de dispositivo não é apenas uma caixa em torno de componentes.

Deve manter com segurança:

- aquecedor;
- ventilador;
- sensores;
- fonte de alimentação;
- controlador;
- terminais;
- fios;
- conectores;
- visor ou botões;
- partes mecânicas.

Para um dispositivo aquecido, um invólucro pobre pode criar um problema mesmo com boa electrónica: bloqueando fluxo de ar, sobreaquecendo o controlador, roçando um fio ou aproximando plástico demasiado de uma peça quente.

## Comece com layout de componentes

Antes de modelar o invólucro, organize componentes reais:

- placa de controlador;
- fonte de alimentação ou conversor DC-DC;
- ventilador;
- aquecedor;
- sensor de temperatura;
- terminais;
- fusível;
- fios;
- conectores;
- botões, visor, RFID ou outros módulos.

O invólucro é projectado em torno de dimensões reais de peças, não "aproximadamente este tamanho".

Verifique:

- onde os conectores estão localizados;
- onde USB sai;
- onde o botão de reset é pressionado;
- como a cobertura sairá;
- como o ventilador será substituído;
- onde o fio de energia funcionará;
- como a placa será montada.

## Separe zonas

Num dispositivo aquecido, é útil pensar em zonas:

- zona quente;
- zona de electrónica;
- zona de fiação de energia;
- zona do utilizador;
- zona de serviço.

A zona quente é o aquecedor, fluxo de ar quente, sensor de temperatura e peças próximas.

A zona de electrónica é o controlador, visor, sensores de baixa tensão, fios de lógica.

A zona de fiação de energia é a fonte de alimentação, SSR, MOSFET, terminais, fusíveis, entrada de rede se presente.

A zona do utilizador é tudo tocado pelas mãos: botões, puxadores, coberturas, visor, localização do leitor RFID.

Estas zonas não devem intersectar aleatoriamente.

## Não coloque electrónica directamente ao lado do aquecedor

Controlador, visor, DC-DC e fios não gostam de sobreaquecimento.

Deixe:

- distância ao aquecedor;
- lacuna de ar;
- escudo ou partição se necessário;
- ventilação para electrónica;
- acesso para verificar temperatura após montagem.

Se a electrónica fica num bolso fechado sem ventilação, pode sobreaquecerse mesmo sem contacto directo com o aquecedor.

## O ar deve fluir onde necessário

Um ventilador por si só não garante fluxo de ar.

O invólucro deve dirigir ar:

- através do aquecedor;
- através do carretel ou zona de trabalho;
- através de um filtro se presente;
- passado o sensor no ponto certo;
- fora ou num ciclo conforme projectado.

Design pobre pode resultar num ventilador legal e fluxo quase nulo útil. O ar seguirá o caminho de menor resistência, através de lacunas, em torno de filtros ou passado o aquecedor.

Para condutas de ar, evite:

- estreitamento afiado;
- curvas desnecessárias;
- canais longos finos;
- grelhas com pequena área aberta;
- filtros sem ventilador com pressão estática suficiente.

## Faça montagens para parafusos reais

Não conte com um parafuso auto-batente num poste fino durando para sempre.

Para um invólucro que será desmontado, melhor usar:

- porcas de insertores com calor de latão;
- porcas em bolsos;
- suportes de placa apropriados;
- parafusos de tamanho padrão;
- anilhas onde o plástico pode amassar.

Para suportes impressos, importante:

- diâmetro adequado;
- base arredondada;
- sem paredes finas;
- orientação correcta de impressão;
- limpeza de material em torno do furo.

Se a cobertura será aberta frequentemente, fios de plástico nú se desgastam rapidamente.

## Os fios não devem roçar

Os fios no invólucro devem ser protegidos.

Você precisa:

- canais de cabo;
- espaços para amarrações;
- alívio de tensão na entrada de cabo;
- raios em vez de arestas afiadas;
- limpeza do ventilador;
- limpeza do aquecedor;
- protecção contra aperto pela cobertura.

Um cenário ruim: utilizador puxa um cabo externo e a força vai directamente para um terminal ou pino de placa.

Melhor é para o cabo ser fixado pelo invólucro primeiro, depois alcançar o conector ou terminal.

## Não misture rede com baixa tensão

Se o dispositivo tem 110-230V AC, o invólucro deve ser projectado muito mais rigorosamente.

Lógica mínima:

- entrada de rede separada;
- fusível acessível mas protegido;
- terminais de rede cobertos;
- fios de baixa tensão não misturados com fios de rede;
- utilizador não pode tocar a peça de rede;
- fio não pode sair do terminal sob tensão;
- o plástico não toca terminais quentes e componentes de energia;
- aterramento está presente onde necessário.

Não invente segurança de rede "por imagem". Para a peça de rede, você precisa terminais apropriados, isolamento, alívio de tensão, fusíveis e compreensão de requisitos de segurança.

## Deixe acesso para serviço

O dispositivo precisará de manutenção.

Deixe acesso a:

- fusível;
- terminais;
- controlador;
- conector USB ou de serviço;
- sensor de temperatura;
- ventilador;
- filtro;
- aquecedor;
- parafusos de montagem.

Se a substituição de um ventilador requer dessoldar fios ou remover o aquecedor, o design não será bem-servido.

## Verifique a temperatura real

Após montagem, você precisa mais do que apenas verificar que tudo encaixa.

Verifique:

- temperatura da electrónica após operação estendida;
- temperatura da parede perto do aquecedor;
- o plástico está amolecendo;
- a conduta de ar está deformando;
- os terminais ficam quentes;
- as lacunas para peças quentes mudaram;
- o plástico cheira;
- os fios estão tocando superfícies quentes.

O primeiro teste é melhor feito sob supervisão com a capacidade de cortar poder rapidamente.

## Checklist antes de imprimir o invólucro

Antes de imprimir, verifique:

1. Todos os componentes reais são medidos.
2. Há limpeza em torno de placas, conectores e cabos.
3. A zona quente está separada da electrónica.
4. O fluxo de ar tem um caminho claro.
5. O ventilador pode ser substituído.
6. O filtro pode ser substituído.
7. O sensor de temperatura pode ser verificado e reinstalado.
8. Os fios não passam através de arestas afiadas.
9. Há lugares para amarrações ou clipes.
10. Os fios de rede estão separados da baixa tensão.
11. A cobertura não aperta os cabos.
12. Os parafusos e insertores têm plástico suficiente em torno deles.
13. O material adequa-se à temperatura de funcionamento.
14. A deformação de peça não torna o dispositivo inseguro.

## Erros comuns

- projectando uma caixa bonita primeiro, depois tentando ajustar fios;
- não deixando espaço para conectores;
- bloqueando ventilação da fonte de alimentação;
- colocando o controlador num canto quente;
- executando fios de rede e sinal juntos;
- não fornecendo alívio de tensão de cabo;
- usando suportes finos para parafusos;
- esquecendo que filtros e ventiladores precisam manutenção;
- imprimindo o invólucro de PLA para uma zona quente;
- não verificando o invólucro após aquecimento estendido.

## Conclusões-chave

- O invólucro é projectado em torno de componentes e fios reais.
- A zona quente, electrónica, fiação de energia e zona do utilizador devem estar separadas.
- O ar deve fluir ao longo de um caminho útil, não apenas "em algum lugar soprando".
- Os fios devem estar protegidos de arestas afiadas, calor e tensão.
- A rede não pode ser misturada com lógica de baixa tensão.
- A manutenção deve ser planeada antes da impressão, não após montagem.

## Referências

- [Protolabs Network: Enclosure design for 3D printing](https://www.hubs.com/knowledge-base/enclosure-design-3d-printing-step-step-guide/) - regras práticas para paredes, lacunas, chefes, nervuras e suportes.
- [Prusa Knowledge Base: Enclosure guidepost](https://help.prusa3d.com/article/enclosure-guidepost_366332) - como o invólucro afecta temperatura, pó, cheiro, acesso a peças quentes e colocação da fonte de alimentação fora da câmara morna.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - dicas para invólucros de electrónica, acesso de porta, ventilação e insertores com calor.
- [3D On Demand: 3D printed enclosures guide](https://www.3d-demand.com/blog/3d-printed-enclosures-electronics-guide) - design em torno de componentes internos, espessura de parede, clipes e dissipação de calor.
- [3DSearch: Custom electronics enclosures](https://www.3dsearch.app/blog/3d-printing-electronics-enclosures) - ventilação, suportes de placa, insertores com rosca, lacunas e dimensões práticas para FDM.
