# Materiais, Inflamabilidade e Emissões Nocivas

O material para câmara, secador, filtro, carcaça ou conduto de ar não pode ser escolhido apenas pelo preço, espessura e facilidade de corte.

Num dispositivo aquecido, o material deve suportar não apenas a operação normal, mas também falhas razoáveis: paragem do ventilador, erro do sensor, interruptor travado, mau contacto, terminal sobreaquecido ou fluxo de ar localizado quente.

## O que "Adequado para Aquecimento" Significa

O material é adequado não porque "não derrete imediatamente". Para um dispositivo aquecido, várias propriedades diferentes importam:

- temperatura máxima de funcionamento contínuo;
- temperatura de amolecimento ou temperatura de deformação térmica;
- inflamabilidade;
- geração de fumo;
- toxicidade dos produtos de combustão;
- resistência da cola, folha, revestimento ou laminação;
- comportamento em contacto com ar quente;
- requisitos do fabricante para montagem.

A temperatura de fusão por si só é quase inútil. O plástico pode perder rigidez e forma muito antes de derreter. O isolamento pode mudar de dimensões. A cola pode descolar. Uma peça impressa pode empenar sob carga.

## Temperatura de Funcionamento e Margem de Segurança

Primeiro, é necessário compreender qual será a temperatura não "em média na câmara", mas em locais específicos:

- perto do aquecedor;
- na saída de ar quente;
- perto de terminais e fios;
- em fixadores de metal;
- na parede interna;
- em peças impressas;
- sob isolamento;
- na superfície externa.

Se a câmara mantém `45°C`, não significa que todas as peças dentro também estão a `45°C`. Perto do aquecedor ou no conduto de ar pode ser significativamente mais quente.

Regra prática: o material deve ter uma margem de segurança para a temperatura de funcionamento contínuo exatamente para o local onde está colocado. Para a zona junto ao aquecedor, a margem deve ser maior do que para o painel decorativo externo.

## Inflamabilidade - Não É uma Única Palavra

A documentação pode conter diferentes sistemas de classificação.

Para plásticos, a UL 94 é frequentemente indicada:

- `HB` - amostra horizontal queima mais lentamente do que o limite especificado;
- `V-2`, `V-1`, `V-0` - amostra vertical deve auto-extinguir-se dentro do tempo especificado, diferenças incluem comportamento de gotejamento;
- `5VB`, `5VA` - testes mais rigorosos para certas aplicações;
- `HBF`, `HF-1`, `HF-2` - classes para materiais espumados.

Importante: UL 94 é um pequeno teste de laboratório em amostras. Ajuda a comparar materiais, mas não prova que uma câmara caseira é segura sob qualquer falha.

Na documentação de materiais de construção em língua russa, pode encontrar:

- `НГ` - material não inflamável;
- `Г1-Г4` - grupos de inflamabilidade;
- `В1-В3` - inflamabilidade;
- `Д1-Д3` - capacidade de geração de fumo;
- `Т1-Т4` - toxicidade dos produtos de combustão;
- `РП1-РП4` - propagação de chamas na superfície.

Se um vendedor escreve "auto-extinguível", isto não substitui a folha de dados. O material pode ainda fumar, pingar, carbonizar, deformar ou libertar produtos perigosos quando sobreaquecido.

## Exemplo: XPS, EPS e PIR

Os materiais de isolamento de construção parecem frequentemente convenientes para câmara ou secador: são leves, planos, baratos, cortam bem e isolam bem. Mas devem ser vistos como materiais de construção com as suas próprias limitações, não como partes universais para um aquecedor.

| Material | Onde Pode Ser Apropriado | Riscos Principais | O Que Verificar |
| --- | --- | --- | --- |
| XPS, poliestireno extrudido | isolamento externo de zonas frias se separado da parte quente | temperatura de funcionamento limitada, deformação, inflamabilidade, fumo no fogo | descrição técnica, temperatura máxima, características de fogo, camada de proteção |
| EPS, poliestireno expandido | apenas com cautela e longe de zonas quentes | baixa resistência térmica, inflamabilidade, deformação, fumo | folha de dados do material, sem aquecimento direto, cobrir com camada não inflamável |
| PIR / poliiso | isolamento de tipo construção, às vezes com melhor comportamento ao fogo do que folhas de poliestireno | não automaticamente não inflamável, depende do revestimento e do produto específico | descrição técnica, temperatura de funcionamento, classe de reação ao fogo, limitações do fabricante |
| Lã mineral | isolamento térmico onde as fibras são permissíveis e é necessária alta resistência térmica | pó, fibras, compressão, humidade, necessidade de selar o fluxo de ar | temperatura permissível, aglutinante, revestimento de proteção, montagem |
| Metal | tela, parede interna, dissipador de calor | pontes térmicas, superfície externa quente, arestas afiadas | aterramento para secção de rede, temperatura, isolamento de fios |
| Plástico impresso em 3D | fixadores e coberturas fora da zona quente | amolecimento, fluência sob carga, inflamabilidade | material, temperatura de deformação, temperatura real da peça |

Para XPS nos dados técnicos do fabricante, a temperatura máxima de serviço em torno de `74°C` (`165°F`) é frequentemente listada. Isto não significa que todos os XPS são iguais, mas mostra a ordem de limitação: este material não pode ser colocado automaticamente perto de um aquecedor ou ar quente.

Para EPS, recomendações para manter as temperaturas de funcionamento em torno de `75°C` são encontradas; acima disto o material pode perder estabilidade dimensional. Novamente, o valor exato deve ser retirado da documentação do produto específico.

PIR/poliiso pode ter um intervalo permissível mais alto em produtos individuais, mas isto não elimina a verificação de propriedades de fogo, revestimento, cola, fumo e recomendações do fabricante.

## "Stack" de Material Seguro

Para uma câmara aquecida, é frequentemente melhor pensar não em "material de parede" mas em camadas.

![Exemplo de camadas de material perto de calor](../../../img/04-thermal-physics-and-materials/03-safe-material-stack.svg)

Exemplo de lógica mais sólida:

- dentro da zona quente - metal, cerâmica, vidro ou outro material que suporte temperatura e não pegue fogo com sobreaquecimento local;
- mais adiante - espaço de ar ou isolamento se realmente for necessário;
- fora - carcaça que não aquece para temperatura perigosa;
- fios e terminais não tocam isolamento e não estão escondidos em zonas onde o sobreaquecimento passaria despercebido;
- existe proteção independente contra sobreaquecimento se a falha de controlo pudesse levar a aquecimento perigoso.

O isolamento não deve ser o primeiro material que vê o aquecedor.

## Peças Impressas em 3D Perto do Calor

O plástico impresso é conveniente para suportes, coberturas, suportes de sensor e condutas de ar. Mas numa câmara aquecida pode comportar-se pior do que parece pelo carretel.

Riscos típicos:

- PLA perde rapidamente rigidez quando aquecido e sob carga;
- PETG é melhor do que PLA, mas também pode fluir e deformar;
- ABS/ASA geralmente toleram melhor câmara morna, mas requerem verificação de temperatura real;
- PC e materiais de engenharia podem suportar mais, mas requerem impressão adequada e ainda não eliminam avaliação de fogo.

Para peças perto do aquecedor, não é possível confiar apenas no nome do plástico. Importantes são marca de filamento, configurações de impressão, espessura, carga, direção da camada, ventilação e temperatura real da peça.

## O Que Ler Antes de Comprar

Procure documentos técnicos, não marketing:

- descrição técnica ou folha de dados do produto;
- SDS/MSDS se o material pode aquecer, ser cortado, lixado ou queimado;
- classificação de fogo / reação ao fogo;
- UL 94 ou outra classe de inflamabilidade para plásticos;
- temperatura máxima de funcionamento contínuo;
- limitações de montagem;
- limitações no contacto com fontes de calor;
- requisitos para cobrir com revestimento, metal, placas de gesso ou outra camada.

Se o material é vendido apenas como "folha de isolamento" sem folha de dados adequada, não deve ser colocado num dispositivo aquecido caseiro.

## O Que Definitivamente Não É Normal

Soluções ruins:

- colar espuma ou XPS diretamente perto do aquecedor;
- dirigir fluxo quente para plástico desconhecido;
- cobrir terminais e fios com isolamento;
- colocar material inflamável perto da secção de rede `110-230V AC`;
- confiar num sensor de temperatura único;
- tratar material de construção como seguro para câmara sem verificação;
- usar "auto-extinguível" como substituto para proteção independente contra sobreaquecimento;
- fazer primeiro aquecimento sem observação e medições.

## Conclusão Principal

A segurança dos materiais não é um parâmetro único. É necessário observar a temperatura de funcionamento, inflamabilidade, fumo, toxicidade dos produtos de combustão, colas, revestimentos e cenários de falha reais.

Se o material não tem documentação clara, não pode ser colocado perto do aquecedor como proteção primária. Se o material é inflamável, deve ser removido da zona quente, coberto com camada adequada e verificado por medição em modo operacional real.

## Materiais sobre o Tema

- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - explicação de UL 94, testes verticais/horizontais, classes para plásticos e materiais espumados.
- [UL Solutions Code Authorities: UL 94 Rating Certifications and Limitations](https://code-authorities.ul.com/about/blog/understanding-ul-94-rating-certifications-and-limitations/) - limitações da aplicação de UL 94 a produtos reais e peças grandes.
- [Russian Emergency Ministry: Federal Law No. 123-FZ, Technical Regulations on Fire Safety Requirements](https://mchs.gov.ru/uploads/document/2022-04-08/c907f456516c1f21009131cfdb944deb.pdf) - classificação russa de materiais de risco de fogo: inflamabilidade, inflamabilidade, fumo, toxicidade, propagação de chamas.
- [DuPont: Styrofoam Brand XPS Product Information Sheet](https://www.dupont.com/content/dam/dupont/amer/us/en/performance-building-solutions/public/documents/en/styrofoam-brand-ultra-sl-pis-43-D100087-enUS.pdf) - exemplo de descrição técnica de XPS com temperatura máxima de serviço `165°F`.
- [IKO: EPS Insulation in an IKO Roof System](https://www.iko.com/comm/documents/bulletin-eps-insulation-in-an-iko-roof-system/) - exemplo de limitação de temperatura de funcionamento de EPS e estabilidade dimensional.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - referência prática para resistência térmica de materiais populares de impressão 3D.
