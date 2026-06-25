# PETG, ABS e ASA

PETG, ABS e ASA são frequentemente considerados os materiais seguintes após PLA, quando uma peça deve ser não apenas bonita mas funcional.

Em dispositivos em torno de uma secadora, câmara de impressora ou aquecedor, a escolha do material afeta a segurança. Uma peça pode parecer normal após a impressão, mas após uma hora num invólucro morno pode começar a amolecer, deformar o conduto de ar, soltar fixadores ou deslocar um sensor.

## PETG

PETG é frequentemente um bom primeiro material de trabalho após PLA.

Tipicamente:

- imprime mais facilmente que ABS e ASA;
- cheira menos durante a impressão;
- empeña menos;
- lida melhor com temperatura do que PLA;
- funciona bem para muitos suportes, coberturas, suportes e condutas de ar sob condições moderadas.

Para dispositivos semelhantes ao iDryer, PETG pode funcionar bem para:

- suporte de ventilador longe do aquecedor;
- cobertura de electrónica;
- suporte de sensor numa zona de temperatura moderada;
- conduta de ar para ar não demasiado quente;
- protótipo de invólucro.

Mas PETG não se torna automaticamente resistente ao calor para qualquer zona quente.

Se uma peça fica perto de um aquecedor, num fluxo de ar quente ou sob carga constante, PETG pode gradualmente perder rigidez e deformar.

## ABS

ABS é um material mais técnico que PLA e PETG.

Tipicamente funciona melhor para:

- peças com carga mecânica;
- invólucro num ambiente mais quente;
- suportes onde PETG já é questionável;
- peças necessitando melhor resistência à temperatura.

Desvantagens de ABS:

- empeña mais;
- requer uma câmara fechada ou ambiente morno estável durante a impressão;
- cheira notavelmente;
- pode emitir fumos perigosos durante a impressão;
- não adequado para impressão num espaço habitado sem ventilação.

Não escolha ABS apenas porque "é mais forte". Você precisa saber como imprimi-lo. ABS mal impresso com deslamina e stress interno pode resultar pior que PETG bem impresso.

## ASA

ASA é similar a ABS em propósito, mas frequentemente melhor adequado para peças externas e técnicas.

Vantagens de ASA:

- boa resistência à temperatura;
- resistência UV;
- menos cheiro comparado a ABS, mas cheiro e fumos ainda estão presentes;
- geralmente empeña menos que ABS;
- adequado para peças técnicas de trabalho.

Desvantagens:

- também requer boas condições de impressão;
- para peças grandes, uma câmara de impressão fechada é preferida;
- possíveis fumos perigosos durante a impressão;
- material é mais caro e exigente que PETG.

ASA é frequentemente mais sensato que ABS para peças que viverão longamente num dispositivo ou perto de janelas/luz solar. Mas para uma pequena cobertura de electrónica interna, ASA nem sempre é necessário.

## Onde usar qual material

Um guia bruto:

| Tarefa | PETG | ABS/ASA |
| --- | --- | --- |
| Protótipo frio | funciona | funciona, mas frequentemente excessivo |
| Cobertura de electrónica longe de calor | funciona | funciona |
| Suporte de ventilador numa zona moderada | funciona | funciona |
| Conduta de ar perto de fluxo de ar morno | às vezes funciona | frequentemente melhor |
| Peça dentro de câmara quente | verifique temperatura | frequentemente mais sensato |
| Suporte perto do aquecedor | arriscado | também requer verificação, às vezes metal é necessário |
| Peça sob carga constante no calor | cautela | melhor, mas não automaticamente seguro |
| Peça perto de 110-230V AC | material não é a única resposta | material não é a única resposta |

Isto não é uma tabela de permissão. É apenas lógica inicial.

A verdadeira solução depende da temperatura, distância ao aquecedor, fluxo de ar, carga, tempo de execução e consequências de falha.

## A temperatura de fusão não é o parâmetro principal

Para invólucros e suportes, o que importa não é a temperatura em que o material derrete.

Mais importante é quando irá:

- amolecer;
- fluir sob carga;
- perder forma;
- soltar um parafuso;
- empenar;
- mudar tamanho.

Uma peça pode se tornar perigosa muito antes de derreter.

Por exemplo, um suporte de sensor pode deslocar-se por apenas alguns milímetros. Externamente isto parece menor, mas o controlador já verá a temperatura errada.

## Impressão de ABS/ASA requer condições

ABS e ASA frequentemente requerem:

- uma câmara fechada;
- temperatura de cama alta;
- temperatura estável em torno da peça;
- boa aderência da cama;
- protecção contra correntes de ar;
- ventilação da sala;
- secagem cuidadosa de filamento se necessário.

Se você imprime ABS/ASA numa impressora aberta, uma peça grande pode empenar, rachar ou deslaminar.

Para peças pequenas, às vezes você pode se virar sem uma câmara fechada perfeita, mas para um invólucro, conduta de ar ou peça longa, planeie condições de impressão apropriadas desde o início.

## Não escolha material separado do design

Material é apenas parte da solução.

Mesmo bom material não salvará geometria pobre:

- paredes finas;
- pequenos postes para parafusos;
- cantos internos afiados;
- carga perpendicular às camadas;
- montagem pobre ao invólucro;
- sem lacuna para partes quentes;
- ventilação bloqueada.

Se uma peça segura um aquecedor, conector de alimentação ou sensor de temperatura, você deve pensar não apenas em plástico, mas também em suportes de metal, blindagem, lacunas e protecção de falha segura.

## Regra prática

Para um dispositivo simples, você pode pensar assim:

- PLA - protótipo, modelo, peça decorativa fria.
- PETG - mínimo básico para muitas peças de trabalho a temperatura moderada.
- ABS/ASA - melhor para peças quentes e mecanicamente carregadas, se você pode imprimi-las.
- Metal, fibra de vidro, cerâmica ou peças prontas não inflamáveis - onde plástico perto de calor já não é apropriado.

Se falha de uma peça pode levar a sobreaquecimento, curto-circuito ou contacto entre fio e peça quente, o material deve ser escolhido com uma grande margem de segurança e testado em montagem real.

## Erros comuns

- pensar que PETG é totalmente resistente ao calor;
- imprimir ABS/ASA sem uma câmara fechada e obter deslamina;
- escolher material baseado em conselho da internet sem saber a temperatura dentro do invólucro;
- colocar conduta de ar PETG muito perto do aquecedor;
- usar ABS/ASA num espaço habitado sem ventilação;
- pensar que trocar PLA por ASA automaticamente torna o design seguro;
- não verificar a peça após uma hora de operação à temperatura real;
- esquecer que parafusos e carga podem deformar plástico ao longo do tempo.

## Conclusões-chave

- PETG é frequentemente um bom mínimo para peças de trabalho, mas não para qualquer zona quente.
- ABS e ASA melhor lidam com temperatura mas são mais difíceis de imprimir e requerem ventilação.
- ASA geralmente bate ABS em resistência UV e frequentemente cheira menos, mas ainda requer cuidado.
- Material é escolhido baseado na temperatura actual, carga e consequências de falha.
- Para peças perto de um aquecedor, às vezes a resposta correcta não é plástico mas metal ou um suporte pronto.

## Referências

- [Prusa Knowledge Base: PETG](https://help.prusa3d.com/article/petg_2059) - descrição PETG, impressão, força, resistência à temperatura e limites.
- [Prusa Knowledge Base: ABS](https://cdn.help.prusa3d.com/article/abs_2058) - propriedades ABS, requisitos de impressão, empenamento e aviso de fumo.
- [Prusa Knowledge Base: ASA](https://help.prusa3d.com/article/asa_5078) - ASA como material técnico com resistência à temperatura e UV, além de requisitos de câmara fechada.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - tabela comparativa de materiais: PLA, PETG, ABS, ASA, PC, PA e compostos.
- [Bambu Lab: ASA Filament Guide](https://bambulab.com/en-us/filament/asa) - breve descrição ASA, suas vantagens, desvantagens e casos de uso.
