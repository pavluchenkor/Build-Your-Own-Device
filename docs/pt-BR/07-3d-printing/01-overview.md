# Impressão 3D

Esta seção não é um curso de impressão 3D.

Serve um propósito diferente: ajudar a compreender quais peças impressas podem ser usadas com segurança em um dispositivo caseiro, e quais se tornam um risco perto de aquecedores, eletrônica, fiação e peças móveis.

Em projetos semelhantes ao iDryer, impressão 3D é tipicamente utilizada para:

- invólucros;
- coberturas;
- dutos de ar;
- suportes de ventilador;
- suportes de sensor;
- guias;
- puxadores e clipes;
- painéis decorativos ou de serviço.

Imprimir uma peça é fácil. Fazê-la funcionar com segurança em um invólucro morno durante meses é mais difícil.

## Questões-chave

Antes de imprimir uma peça para um dispositivo, você deve responder não apenas "o STL encaixará no slicer", mas várias questões:

- onde a peça será localizada;
- que temperatura haverá lá;
- há um aquecedor por perto;
- há 110-230V AC por perto;
- a peça aguentará uma carga;
- ela contatará fios;
- ela dirigirá ar quente;
- ela pode ser substituída ou reparada;
- o que acontece se ela se deforma.

Se a deformação de uma peça pode deslocar um sensor, bloquear fluxo de ar, aproximar um fio de uma zona quente, ou soltar uma montagem de aquecedor, já não é apenas um "defeito cosmético".

## STL não é uma instrução de montagem

STL descreve a forma de uma peça, mas não diz:

- de que material imprimi-la;
- em que orientação imprimi-la;
- quantas paredes usar;
- que preenchimento aplicar;
- onde suportes são necessários;
- que parafusos usar;
- que temperatura a peça aguentará;
- em que direção será mais fraca.

O mesmo modelo pode ser uma cobertura normal ou um suporte estrutural pobre dependendo do material, orientação e condições de trabalho.

Portanto, uma peça de trabalho precisa não apenas de um STL, mas também de contexto: material, configurações de impressão, localização de instalação, carga e regime de temperatura.

## Material é mais importante que aparência

Para um protótipo, PLA frequentemente funciona. Imprime facilmente e produz uma peça de aspecto agradável.

Mas para peças perto de calor, PLA é uma escolha pobre. O problema não é que derreterá imediatamente, mas que pode gradualmente perder rigidez e forma nas temperaturas encontradas em um invólucro fechado ou perto de um aquecedor.

Para peças de trabalho em torno de um secador, câmara ou aquecedor, você tipicamente considera:

- ABS;
- ASA;
- materiais de engenharia mais resistentes ao calor, se tem experiência e uma impressora adequada.

O material é escolhido com base nas condições:

- temperatura de funcionamento;
- rigidez;
- resistência ao impacto;
- contração e deformação;
- cheiro e emissões durante a impressão;
- comportamento quando aquecido;
- documentação do fabricante.

## Temperatura dentro de um invólucro

A temperatura dentro de um invólucro fechado difere da temperatura ambiente.

Mesmo que o aquecedor não toque no plástico, uma peça pode estar:

- em um fluxo de ar quente;
- perto do aquecedor;
- perto de um dissipador de calor;
- perto da fonte de alimentação;
- em uma área com ventilação pobre;
- em uma parede que aquece lentamente.

Portanto, você não pode avaliar segurança com apenas a frase "a peça não toca o aquecedor". Você precisa compreender que temperatura haverá nesse local durante funcionamento estendido.

![Zonas em um invólucro impresso para um dispositivo aquecido](../../img/07-3d-printing/01-printed-device-zones.svg)

## A força depende da direção da seção

Peças FDM não são igualmente fortes em todas as direções.

A direção da camada relativa a uma peça se quebra:

- ao longo das linhas de plástico é geralmente mais forte;
- entre camadas é frequentemente mais fraca;
- postes e clipes finos podem quebrar entre camadas;
- parafusos podem deslaminar uma peça se a geometria não é projetada para isso.

Para suportes estruturais, é importante pensar sobre onde a carga irá.

Se um suporte de ventilador simplesmente pendurado em uma parede, isso é uma coisa. Se um suporte segura um aquecedor ou eixo de carretel, orientação de impressão e espessura de parede se tornam importantes.

## Invólucro deve ser reparável

Um bom invólucro não é apenas uma caixa bonita.

Deve permitir:

- acesso a terminais;
- substituição de um ventilador;
- inspeção de um sensor de temperatura;
- aperto de fixadores;
- remoção de um controlador;
- substituição de um fio;
- ver se algo superaqueceu ou escureceu.

Se você precisa desmontar metade do dispositivo para acessar um fusível ou terminal, será reparado menos frequentemente. Esta é uma prática de engenharia pobre.

## Peça impressa não deve comprometer segurança

Um invólucro impresso pode ser útil, mas não deve transformar um pequeno erro em uma situação perigosa.

Cenários ruins:

- suporte de aquecedor amolecido;
- duto de ar deformado e fluxo de ar através de aquecedor diminuído;
- suporte de termistor deslocado;
- fio esfregou contra uma aresta afiada;
- terminal acabou apertado contra plástico;
- cobertura bloqueou ventilação da fonte de alimentação;

Para zonas quentes e com carga, é melhor pensar desta forma: se uma peça impressa se deforma, o dispositivo deve permanecer seguro ou entrar em um estado de erro, não continuar aquecendo cegamente.

## O que estará nesta seção

A seção cobre vários tópicos práticos:

- `02-what-is-stl.md` - por que STL não contém material, orientação, força ou instruções de montagem.
- `03-materials-petg-abs-asa.md` - escolhas básicas entre PETG, ABS e ASA.
- `04-heat-resistant-materials.md` - como pensar sobre peças perto de calor.
- `05-enclosure-design.md` - zonas de invólucro, ventilação, fixação, acesso e fiação.
- `06-why-pla-is-risky.md` - porque o PLA é conveniente para protótipos mas arriscados perto de calor.

## O que esta seção não faz

Não haverá um curso completo de impressão 3D aqui.

Não mergulharemos em:

- todos os plásticos do mundo;
- configurações de retração;
- pós-processamento decorativo;
- modelos artísticos;
- calibração perfeita da impressora;
- seleção específica de marca de filamento.

O foco é simples: peças para um dispositivo real devem ser fortes o suficiente, resistentes ao calor, reparáveis e seguras.

## Conclusões-chave

- STL é apenas geometria, não instruções de montagem segura.
- O material é escolhido com base na temperatura de funcionamento e carga, não na aparência.
- PLA é conveniente para protótipos mas arriscado perto de calor.
- A orientação de impressão afeta a força.
- O invólucro deve separar a zona quente, eletrônica, fiação de alimentação e zona do usuário.
- Uma peça impressa não deve ser a única coisa protegendo a segurança do dispositivo.

## Referências

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - visão geral de materiais populares, condições de impressão e propriedades.
- [Prusa Knowledge Base: PLA](https://help.prusa3d.com/article/pla_2062) - descrição de PLA como material simples para protótipos e peças sem carga de alta temperatura.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - por que uma câmara de impressão fechada é necessária e como temperatura ambiente afeta impressão e materiais.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - tabela comparativa de materiais, incluindo PLA, PETG, ABS, ASA e plásticos de engenharia.
- [Makelab: Is 3D printing strong enough for functional parts?](https://help.makelab.com/help/article/is-3d-printing-strong-enough-for-functional-parts) - notas práticas sobre material, orientação de impressão, paredes, preenchimento e peças funcionais.
