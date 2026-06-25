# Materiais resistentes ao calor

Para peças perto de calor, o que importa não é a etiqueta "resistente ao calor" mas comportamento real do material no seu design específico.

Uma peça pode não derreter, mas já pode:

- amolecer;
- dobrar;
- fluir sob um parafuso;
- mudar tamanho;
- perder rigidez;
- soltar fixadores;
- deslocar um sensor;
- bloquear fluxo de ar.

Portanto, "temperatura de fusão" é quase nunca o parâmetro principal para um invólucro, suporte ou duto de ar.

## O que conta como uma zona quente

Uma zona quente não é apenas onde o aquecedor senta.

Em um dispositivo caseiro, áreas quentes podem incluir:

- fluxo de ar após o aquecedor;
- parede perto do aquecedor;
- ponto de montagem do termistor;
- duto de ar;
- área acima da fonte de alimentação;
- localização perto de um SSR ou MOSFET com dissipador de calor;
- câmara fechada que aquece inteiramente.

Se uma peça está em tal zona, o material é escolhido com margem e testado em montagem real.

## Temperatura de funcionamento, não fusão

Fusão é já um estágio tardio do problema.

Para uma peça impressa, o que é mais importante:

- em que temperatura ela perde rigidez;
- se há carga mecânica;
- quantas horas ela funcionará nesta temperatura;
- há fluxo de ar quente;
- há vibração;
- ela segura um parafuso ou clipe;
- o que acontece se ela se deforma.

Um suporte de sensor pode se tornar perigoso mesmo antes de falha visível. Se o sensor se move para longe da superfície, o controlador pode continuar aquecendo porque lê a temperatura errada.

## Opções básicas

Uma hierarquia bruta de materiais:

- PLA - para protótipos frios e peças decorativas longe de calor.
- PETG - opção básica para temperaturas moderadas e peças simples de trabalho.
- ABS/ASA - melhor para peças mais quentes e mecanicamente carregadas, se tem condições de impressão.
- PA/nylon - material técnico resistente, mas altamente dependente de umidade e condições de impressão.
- PC/policarbonato - material mais resistente ao calor e forte, mas difícil de imprimir.
- Compostos com preenchedor de carbono ou fibra de vidro - podem ser mais rígidos e estáveis, mas requerem bico adequado e compreensão de propriedades.
- Metal, fibra de vidro, cerâmica ou peças prontas resistentes ao calor - onde plástico não é mais apropriado.

Esta não é uma classificação "melhor-pior". É uma lista de opções com complexidade, custo e riscos diferentes.

## PETG

PETG funciona para muitas peças em uma zona de temperatura moderada:

- coberturas de eletrônica;
- suportes de ventilador;
- suportes de sensor de temperatura longe do aquecedor;
- dutos de ar para fluxo moderado;
- elementos de invólucro não tendo segurança crítica.

Mas PETG pode amolecer e fluir sob carga. Se uma peça segura um aquecedor, terminal de energia ou sensor de segurança, PETG deve ser usado muito cuidadosamente.

## ABS e ASA

ABS e ASA tipicamente funcionam melhor em zonas mais quentes que PETG.

Eles são considerados para:

- invólucro de câmara;
- dutos de ar;
- suportes em ambiente quente;
- peças técnicas;
- peças que devem reter forma mais tempo.

Mas eles têm um preço:

- mais difícil de imprimir;
- empenamento;
- cheiro;
- possíveis fumos prejudiciais;
- preferencialmente impresso em câmara fechada;
- requer ventilação.

ASA é frequentemente preferido para peças onde resistência UV e durabilidade importam. ABS pode ser mais barato e mais disponível.

## PA / Nylon

PA, ou nylon, é utilizado para peças técnicas com carga mecânica.

Vantagens:

- alta resistência ao impacto;
- boa resistência ao desgaste;
- baixo atrito;
- boa resistência mecânica;
- algumas variantes têm boa resistência à temperatura.

Desvantagens:

- absorve umidade fortemente;
- requer secagem;
- pode empenar;
- difícil de imprimir;
- requer superfície e condições corretas.

Nylon úmido imprime mal: bolhas, sibilo, má superfície e força fraca resultam. Para uma cobertura de invólucro simples, nylon é geralmente excessivo.

## PC / Policarbonato

Policarbonato é considerado quando você precisa de alta força e resistência à temperatura.

Vantagens:

- alta força de impacto;
- alta resistência à temperatura;
- boa rigidez;
- adequado para peças funcionais.

Desvantagens:

- difícil de imprimir;
- temperatura alta de bico e cama;
- propenso a empenamento;
- precisa de ambiente morno estável;
- nem toda impressora é adequada.

PC não é um material "iniciante". Se a impressão for assustadora, uma peça pode parecer normal, mas ter força entre camadas.

## Compostos

Filamentos compostos contêm enchimentos: fibra de carbono, fibra de vidro, Kevlar ou outro material.

Eles podem fornecer:

- maior rigidez;
- menos deformação;
- melhor estabilidade dimensional;
- superfície técnica bonita.

Mas eles não tornam o plástico base magicamente não inflamável ou totalmente resistente ao calor.

Importante:

- preenchedor de carbono desgasta bicos de latão;
- bico endurecido ou adequado é necessário;
- composto pode ser mais frágil;
- propriedades dependem do material específico, não apenas das letras `CF` no nome.

## Quando plástico não funciona

Para algumas localizações, o material certo não é plástico impresso.

Melhor considerar metal, fibra de vidro, cerâmica ou peças prontas industriais para:

- suporte de aquecedor;
- zona de calor direto;
- contato com terminal de energia;
- montagem de fio de rede;
- barreira mecânica entre 110-230V AC e usuário;
- lugar onde deformação de peça poderia levar a fogo ou choque elétrico.

Uma peça impressa pode manter forma do invólucro, mas não deve ser a única proteção de uma falha perigosa.

## Como escolher material

Antes de escolher um material, responda:

1. Qual é a temperatura máxima na localização de instalação?
2. Quanto tempo a peça funcionará nesta temperatura?
3. Há carga mecânica?
4. Há parafusos, clipes ou compressão constante?
5. Há um aquecedor, SSR, MOSFET, fonte de alimentação ou 110-230V AC por perto?
6. O que acontecerá se a peça se deforma?
7. Você pode substituir plástico com metal ou um suporte pronto?

Se a consequência de falha é séria, você não quer "o plástico mais conveniente" mas um design com margem e proteção independente.

## Erros comuns

- olhar apenas para temperatura de fusão;
- pensar que PETG é seguro próximo a qualquer aquecedor;
- usar PLA em uma câmara quente fechada;
- imprimir PC/nylon sem uma impressora adequada e obter uma peça fraca;
- escolher composto apenas para a marcação legal `CF`;
- colocar uma peça de plástico diretamente próxima a um terminal de energia;
- não verificar a peça após aquecimento estendido;
- esquecer sobre carga de parafuso e fluência de material;
- não contabilizar o fato que um invólucro fechado aquece inteiramente.

## Conclusões-chave

- Temperatura de funcionamento é mais importante que temperatura de fusão.
- Uma peça pode se tornar perigosa antes de fusão visível.
- PETG é uma opção básica para uma zona moderada, não proteção universal de calor.
- ABS/ASA melhor lidam com calor mas requerem condições de impressão e ventilação.
- Nylon e PC são materiais técnicos para usuários experientes e equipamento adequado.
- Em localizações quentes e com carga, metal ou um suporte pronto resistente ao calor é frequentemente melhor.

## Referências

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - catálogo abrangente Prusa de materiais com PLA, PETG, ABS, ASA, PC, Nylon e compostos.
- [Prusa Knowledge Base: Polycarbonate](https://help.prusa3d.com/article/polycarbonate-pc_165812) - propriedades PC, resistência à alta temperatura e dificuldade de impressão.
- [Prusa Knowledge Base: Polyamide / Nylon](https://help.prusa3d.com/article/polyamide-nylon_167188) - nylon como material técnico, absorção de umidade, secagem e requisitos de impressão.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - comparação de material por resistência ao calor, força, absorção de umidade e necessidades de secagem.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - por que uma câmara fechada é importante para materiais que empenam durante resfriamento.
