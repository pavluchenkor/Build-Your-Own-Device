# O que é STL

STL é um arquivo que contém a geometria de um modelo 3D.

Em termos simples: STL informa ao fatiador qual formato imprimir. Mas o STL não diz quase nada sobre como tornar essa peça forte, resistente ao calor e segura em um dispositivo real.

Portanto, a afirmação "Tenho um arquivo STL para um gabinete" não significa que você tenha instruções de montagem completas para construir um dispositivo.

## O que STL armazena

STL descreve a superfície de um modelo como um conjunto de triângulos.

A segmentação de dados pega essa geometria e a converte em caminhos de impressão.

STL é útil porque:

- almost all slicers understand it;
- pode ser exportado da maioria dos programas CAD;
- é simples trocar um modelo;
- é adequado para uma peça acabada com geometria simples.

Mas a simplicidade do STL é também a sua limitação.

## O que o STL não armazena

Um STL típico não armazena:

- material;
- color;
- print orientation;
- layer height;
- infill;
- number of walls;
- temperature settings;
- support type;
- fasteners;
- assembly instructions;
- tolerances;
- part purpose;
- heat warnings;
- informações sobre onde a peça será mais fraca.

Isso significa que duas pessoas podem imprimir o mesmo STL e obter peças diferentes.

Pode-se imprimir PLA de forma rápida e adequada. Outro poderia imprimir ASA com mais paredes e a orientação correta. As peças parecem semelhantes externamente, mas próximas ao calor elas se comportarão de maneira diferente.

## Por que isso é importante para dispositivos aquecidos

Para uma capa decorativa, o STL costuma ser suficiente.

Para uma peça perto de um aquecedor, não é.

Você precisa saber:

- de que material imprimir;
- que temperatura estará próxima;
- a peça suportará uma carga;
- há fios próximos;
- o sensor mudará se a peça for deformada;
- a peça bloqueará o fluxo de ar;
- o plástico ficará muito perto de um terminal ou aquecedor.

Se um STL for baixado sem informações sobre o material e as condições de trabalho, ele não poderá ser considerado uma solução pronta para um secador, câmara de impressora ou módulo de aquecimento.

## Print orientation changes strength

As peças FDM são feitas de camadas.

Por causa disso, o mesmo modelo pode ser:

- strong at one orientation;
- weak at another;
- propenso a delaminação sob carga;
- ruim para fixação com parafusos;
- só serve para uso decorativo.

Por exemplo, um suporte fino pode suportar bem uma carga se as camadas correrem ao longo da direção da força. Mas o mesmo colchete pode quebrar entre as camadas se for impresso de outra maneira.

O próprio STL não diz como orientar uma peça corretamente.

## Slicer settings also matter

Mesmo com o material e a orientação corretos, as configurações de impressão afetam o resultado.

Para uma parte funcional, são importantes:

- number of perimeters;
- wall thickness;
- camadas superior e inferior;
- infill percentage;
- print temperature;
- cooling;
- supports;
- line width;
- interlayer adhesion quality.

Mais preenchimento nem sempre resolve o problema. Freqüentemente, para um gabinete, suporte ou duto de ar, as paredes, os perímetros, o formato da peça e a direção da carga são mais importantes.

## O que você precisa antes de imprimir uma peça funcional

Se uma peça fizer parte de um dispositivo, você precisará de mais do que apenas o STL. Você precisa de um breve conjunto de requisitos:

- material;
- orientação na cama;
- espessura de parede e preenchimento recomendados;
- se são necessários apoios;
- quais parafusos e inserções usar;
- onde a peça não pode ser colocada perto do calor;
- temperatura máxima de trabalho da zona;
- como verificar o ajuste após a impressão;
- o que fazer se a peça estiver deformada.

Isto é especialmente importante para:

- heater bracket;
- air duct;
- fan mount;
- temperature sensor holder;
- electronics enclosure;
- terminal bracket;
- parts near 110-230V AC.

## STL, 3MF e arquivos de projeto

STL é o formato mais simples e compatível, mas não o mais completo.

O formato 3MF foi criado como um formato mais moderno para impressão 3D. Ele pode armazenar mais dados: não apenas geometria, mas também algumas informações sobre materiais, cores, objetos e configurações de fabricação.

Muitas segmentações de dados também podem salvar um arquivo de projeto. Esse arquivo é útil porque armazena não apenas o modelo, mas também a orientação, configurações de impressão, modificadores e posicionamento na base.

Uma regra prática:

- STL é bom para passar uma forma;
- 3MF ou um projeto de segmentação de dados é melhor para passar a intenção de impressão;
- instruções de texto ainda serão necessárias se a peça afetar a segurança.

## Como avaliar um STL baixado

Antes de imprimir uma parte baixada, pergunte-se:

1. Está claro de qual material imprimir?
2. Há algum aviso de temperatura?
3. Você consegue ver em que orientação foi impresso?
4. Há fotos da peça real em montagem?
5. Os parafusos, porcas, insertos e tolerâncias são especificados?
6. Está claro qual carga ele suportará?
7. Existe o risco de que a deformação possa criar uma situação perigosa?

Se você não tiver respostas, a peça pode ser usada como uma ideia ou protótipo, mas não como um componente de funcionamento seguro garantido.

## Erros comuns

- treating an STL as a complete instruction;
- imprimir uma peça funcional do PLA só porque é mais fácil;
- não alterar a orientação da impressão durante o carregamento;
- usar poucas paredes e esperar que o preenchimento alto resolva o problema;
- não levar em conta a temperatura dentro do gabinete;
- não verificar lacunas após a impressão;
- aparafusar em postes finos sem margem;
- usar um invólucro baixado próximo ao calor sem entender o material;
- não deixando acesso para manutenção após a montagem.

## Key takeaways

- STL armazena forma, não é uma forma segura de fabricar uma peça.
- Para um dispositivo, o material, a orientação, as paredes, os fixadores e as condições de trabalho são importantes.
- Um STL pode resultar em uma parte fraca ou forte.
- Para peças próximas ao calor, você precisa de informações sobre materiais e limites de temperatura.
- Os arquivos de projeto 3MF ou slicer transmitem melhor as configurações, mas não substituem a revisão de engenharia.

## References

- [3MF Consortium: The File Format for 3D Printing](https://3mf.io/) - why 3MF was created and what limits of old formats it addresses.
- [3MF Consortium FAQ: 3MF vs STL](https://3mf.io/resources/faq/) - brief comparison of STL and 3MF: materials, properties, topology, and extensibility.
- [Prusa Knowledge Base: Supported file formats](https://help.prusa3d.com/article/supported-file-formats_1772) - which formats PrusaSlicer supports and why 3MF is used as the preferred project format.
- [Xometry: STL File Format](https://www.xometry.com/resources/3d-printing/stl-file-format/) - practical description of STL and the data it does not store: material, color, print profile, and CAD history.
- [Xometry: 3MF File Format](https://www.xometry.com/resources/3d-printing/3mf-file-format/) - overview of 3MF as a more modern container for manufacturing data.
