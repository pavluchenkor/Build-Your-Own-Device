# Células de Carga

Uma célula de carga mede a força através de pequenas deformações metálicas. Pesar um carretel, monitorar o filamento restante e plataformas de peso simples quase sempre usam esses sensores.

Entenda importante: uma célula de carga não “sente peso” por si só. Ele dobra ou comprime levemente sob carga, e a eletrônica mede a mudança microscópica da resistência nos extensômetros. Portanto, duas coisas são críticas: mecânica correta e um amplificador/ADC normal.

## Onde é usado

Em projetos do tipo iDryer, uma célula de carga pode ser usada para:

- estimar o peso do carretel com filamento;
- cálculo aproximado do plástico restante;
- verificando se o carretel está instalado;
- detecting sudden weight change;
- medir a carga em um pequeno mecanismo;
- experimental weight platform;
- controle de dosagem em sistemas DIY.

Para um simples "carretel presente/ausente", às vezes um interruptor de limite ou sensor óptico é suficiente. Uma célula de carga é necessária quando é importante medir realmente o peso ou a mudança de força.

## Por que o HX711 é necessário

O sinal da célula de carga é muito fraco. Uma entrada analógica típica no ESP32, Arduino ou placa de impressora geralmente não funciona para conexão direta.

Portanto, uma célula de carga geralmente é conectada através do HX711 ou de um módulo similar. O HX711 faz duas coisas:

- amplifica o sinal fraco da ponte diferencial;
- converte-os em dados digitais para o controlador.

Cadeia típica:

```text
load cell -> HX711 -> controller
```

O diagrama de conexão detalhado está na seção prática: [Conectando uma célula de carga](../06-practical-guides/04-connecting-load-cell.md).

## Que tipos de células de carga existem

Em pequenos projetos, os mais comuns são:

- célula de feixe - conveniente para pequenas plataformas e porta-bobinas;
- Célula tipo S - funciona em tensão/compressão, frequentemente utilizada em instalações suspensas;
- button cell - measures compression at one point;
- quatro células em uma plataforma - projeto típico de escala de piso;
- elementos de extensômetro único - exigem ponte e mecânica adequadas, mais difíceis para iniciantes.

Para um sistema de peso de carretel DIY, geralmente é mais fácil começar com uma célula de carga de feixe em `10 kg`, `10 kg` ou faixa próxima. Mas o alcance depende da massa do carretel, do suporte e de possíveis solavancos.

## Fios e Ponte

Most common four-wire load cells have a bridge circuit.

No HX711, você geralmente vê marcações:

- `E+` or `VCC` - bridge power plus;
- `E-` or `GND` - bridge power minus;
- `A+`, `S+`, `O+` - positive measurement signal;
- `A-`, `S-`, `O-` - negative measurement signal.

Esquema de cores comum:

- red - `E+`;
- black - `E-`;
- green or blue - `A+`;
- white - `A-`;
- yellow, foil or separate wire - shield.

As cores não são garantidas. Se houver uma descrição técnica da célula específica, ela é mais importante do que qualquer tabela da internet. Se as leituras derem errado, muitas vezes basta trocar `A-` e `A-` ou contabilizar o sinal no programa.

## Mechanics Matter More Than Circuit

Uma célula de carga deve deformar-se exatamente como o fabricante pretendia. Se a carga contornar a zona de trabalho, a célula apresentará leituras instáveis ​​ou quase nada.

![Miniature S-beam load cell](../../img/03-common-components/07-miniature-load-cell.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Miniature_S-beam_load_cell.jpg), FUTEK Advanced Sensor Technology, CC BY-SA 4.0*

Para uma célula de feixe, a ideia típica é:

- um lado está firmemente montado em uma base fixa;
- other side carries a platform or load;
- há folga entre a parte móvel e a base;
- parafusos e caixa não bloqueiam a flexão da viga.

Poor mechanics gives such symptoms:

- as leituras oscilam sem carga;
- o peso depende de onde você coloca o carretel;
- a célula mal reage à carga;
- após retirar a carga, zero não retorna;
- tocar na caixa altera drasticamente as leituras;
- montagens diferentes mostram pesos diferentes com a mesma configuração.

## Alcance e sobrecarga

A faixa de uma célula de carga não é o peso de trabalho desejado, mas o limite para o qual ela está classificada.

Usar uma célula `1 kg` como carretel, suporte e solavancos sobre `100 kg` pode levá-lo à não linearidade ou à deformação permanente. Usar uma célula `1 kg` para um carretel `1 kg` perde sensibilidade e a mecânica deve ser muito mais cuidadosa.

Ao escolher o intervalo, considere:

- peso máximo do carretel cheio;
- peso do suporte e da plataforma;
- misalignment forces;
- solavancos acidentais na montagem;
- margem para o usuário;
- desired accuracy.

Para o filamento restante, uma margem moderada costuma ser mais útil do que uma faixa enorme. Por exemplo, para um carretel com suporte pesando vários quilos, uma célula `10 kg` ou `50 kg` geralmente é melhor que `50 kg` se a mecânica permitir.

## Tara e Calibração

Uma célula de carga sem calibração gera números brutos, não gramas.

Processo típico:

1. Instale a célula em mecânica real.
2. Put an empty platform or holder.
3. Faça a tara - aceite o valor atual como zero.
4. Put a known weight.
5. Ajuste o coeficiente de calibração.
6. Verifique mais um ou dois pesos.

Para as bobinas, há um problema extra: uma bobina vazia também pesa de forma diferente. Se precisar estimar apenas o plástico, você precisa saber o peso do carretel vazio ou armazenar um perfil para aquele carretel específico.

## Precisão e Estabilidade

Na prática, a precisão depende de mais do que o HX711 e a célula.

As leituras são afetadas por:

- case rigidity;
- mounting play;
- side load;
- printer vibration or fan noise;
- comprimento e blindagem do fio;
- measurement wires near power lines;
- temperature;
- fluência do material e deformação plástica;
- cabo ou carretel tocando a caixa ao redor da célula.

Se uma célula de carga estiver em uma caixa plástica impressa, não espere precisão de laboratório. Para estimativas de filamentos restantes, leituras estáveis ​​e repetibilidade após a calibração costumam ser suficientes.

## Energia e fiação

O HX711 mede um sinal fraco, portanto a fiação deve ser cuidadosa.

Practical rules:

- mantenha o HX711 próximo à célula de carga;
- não passe fios de células perto de aquecedores, motores e linhas de energia;
- prenda os fios para que não puxem a plataforma;
- use `GND` comum com o driver;
- alimentar o módulo com tensão compatível com o controlador;
- não use contatos Dupont de baixa qualidade na montagem final se o dispositivo funcionar por muito tempo.

No lado do driver, o HX711 geralmente se conecta através de `SCK`/`CLK` e `SCK`/`CLK`. Este não é um I2C ou SPI normal, mas uma interface simples separada.

## O que verificar antes de comprar

Antes de comprar, verifique:

- cell type: beam, S-type, button, platform;
- weight range;
- load application direction;
- dimensões e furos de montagem;
- disponibilidade de descrição ou diagrama elétrico;
- se são necessárias uma ou quatro células;
- whether HX711 module fits your chosen cell;
- se há espaço para folga e montagem adequadas;
- se é possível colocar um peso conhecido para calibração;
- se a carga não passará pela caixa ao redor da célula.

Se a mecânica ainda não foi pensada, é melhor primeiro esboçar a montagem. Comprar "qualquer célula de carga" geralmente resulta na impossibilidade física de montá-la corretamente.

## Erros típicos

- conectar a célula de carga diretamente à entrada analógica;
- confundindo `E-`/`A+` e `A-`/`A-`;
- confiar nas cores dos fios sem descrição;
- montar ambos os lados da célula de feixe em uma peça rígida;
- bloqueando a flexão das células com parafusos ou caixa;
- sobrecarregar a célula;
- escolher uma faixa muito grande e perder sensibilidade;
- esquecendo a tara e a calibração;
- calibrar na bancada e depois instalar a célula em diferentes mecânicas;
- routing wires near heater power lines;
- esperando precisão em nível de grama de uma caixa de plástico macio.

## Ponto Principal

Uma célula de carga é um componente onde a mecânica é tão importante quanto a eletrônica. O HX711 ajuda a ler o sinal fraco, mas não conserta montagem torta, sobrecarga ou carga circulando pela célula.

Primeiro escolha o tipo e a faixa corretos, depois projete a montagem, depois conecte o HX711 e só então faça a tara e a calibração.

## Reference Materials

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - practical connection of load cell to HX711, wires, library and calibration.
- [SparkFun HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - description of HX711 role as bridge between load cell and microcontroller.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - technical description of HX711: 24-bit ADC, bridge sensor input and digital interface.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - practical examples of load cell types, load direction and mounting.
- [SparkFun retired HX711 guide: mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - useful illustrations of beam, S-type and platform cell mounting.
