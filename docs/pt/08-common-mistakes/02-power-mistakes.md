# Erros de Fonte de Alimentação

A fonte de alimentação é a primeira coisa a verificar quando o dispositivo se comporta estranhamente.

Uma fonte de alimentação fraca, fio fino ou terminal pobre pode parecer um problema de firmware, Wi-Fi, sensor ou controlador.

## Sintomas

Sinais típicos de problemas de fonte de alimentação:

- controlador reinicia;
- tela cintila;
- Wi-Fi em ESP32 desconecta;
- ventilador começa e para;
- servo se mexe;
- aquecedor aquece fraco;
- USB desaparece quando carga é ligada;
- MOSFET, terminal ou fio aquece;
- sensores mostram valores instáveis;
- dispositivo funciona sem carga mas quebra quando aquecedor ou motor está conectado.

Se um sintoma aparece exactamente quando a carga é ligada, quase sempre a fonte de alimentação e fiação precisam ser verificadas.

## Fonte de Alimentação Sem Margem

Você não pode seleccionar uma fonte de alimentação correspondendo exactamente à potência da carga.

Se a carga consome `100W`, uma fonte de alimentação `100W` funcionará no seu limite. Pode sobreaquecer, queda de tensão e lida mal com correntes de inrush.

Regra prática para esta secção:

**margem de potência mínima é 50%, a menos que a documentação de um componente específico exija mais.**

Exemplo:

```text
aquecedor: 24V 120W
corrente: 120W / 24V = 5A
margem mínima 50%: 7.5A
```

Então a fonte de alimentação é melhor escolher pelo menos `24V 7.5A`, e na prática frequentemente maior, se há ventiladores, controlador, iluminação e outras cargas.

## Corrente Total Não Calculada

Você deve calcular não um componente, mas o dispositivo inteiro.

Por exemplo:

- aquecedor;
- ventiladores;
- servo;
- tira LED;
- controlador;
- visor;
- sensores;
- conversor DC-DC.

As correntes adicionam. As correntes de inrush e picos breves também precisam ser contabilizados.

Um servo ou ventilador pode brevemente extrair mais do que em modo normal. Se a margem é pequena, exactamente este momento causará o controlador reiniciar.

## Confundido 12V e 24V

O erro mais simples e mais perigoso:

- ventilador 12V conectado em 24V;
- módulo 5V conectado em 12V;
- aquecedor 24V esperado funcionar normalmente de 12V;
- módulo 3.3V alimentado de 5V sem verificação.

Antes de conectar verifique:

- classificação de carga;
- classificação da fonte de alimentação;
- tensão com multímetro;
- diagrama de conexão;
- classificações de tensão do controlador e módulo.

Não confie apenas na cor do fio ou tipo de conector similar.

## Queda de Tensão em Fios

O fio tem resistência.

Quanto mais longo o fio e quanto maior a corrente, maior a queda de tensão e aquecimento.

Sintomas:

- fonte de alimentação outputs 24V, mas carga obtém menos;
- aquecedor aquece mais fraco que esperado;
- ventilador começa mal;
- servo se mexe;
- fio notavelmente morno;
- terminal aquece.

Verifique tensão não apenas na saída da fonte de alimentação, mas também na carga em si durante operação.

Se a tensão cai significativamente sob carga, o problema pode estar no fio, terminal, conector, fonte de alimentação ou carga demasiado grande.

## Sem Terra Comum

Se um controlador aciona um módulo ou carga externo, frequentemente uma terra comum é necessária.

Por exemplo:

- controlador aciona um módulo MOSFET;
- controlador define PWM para um ventilador 4-pino;
- controlador aciona um servo com energia separada;
- HX711, RFID ou outro módulo é alimentado separadamente.

Sem `GND` comum o sinal pode não ter o nível correcto. O dispositivo pode não funcionar ou funcionar aleatoriamente.

A terra comum não significa que toda a carga deve ser alimentada através do controlador. É apenas o nível de referência comum para o sinal.

## Controlador Alimentado de Linha Ruidosa

Motores, ventiladores, servos, aquecedores e tiras LED podem criar quedas de tensão e ruído.

Se o controlador é alimentado de la mesma linha sem DC-DC apropriado, filtragem e margem, pode reiniciar.

Soluções comuns:

- DC-DC apropriado separado para controlador;
- fios de energia de controlador curtos;
- `GND` comum num ponto claro;
- capacitor perto da carga, se apropriado;
- separação de fiação de energia e lógica;
- fonte de alimentação apropriada com margem.

## O Que Verificar com um Multímetro

No mínimo:

1. Tensão da fonte de alimentação sem carga.
2. Tensão da fonte de alimentação sob carga.
3. Tensão nos terminais de carga sob carga.
4. Polaridade.
5. Presença de terra comum.
6. Aquecimento de fio e terminal após teste breve.

Se o dispositivo funciona apenas sem carga, meça-o sob carga. A tensão sem carga pode parecer normal.

## O Que Não Fazer

Você não pode:

- usar uma fonte de alimentação "ao limite";
- aumentar classificação de fusível porque funciona;
- usar fios Dupont finos para carga de energia;
- torcer fios de energia sem terminal apropriado;
- alimentar aquecedor através de conector fraco;
- conectar carga directamente a GPIO;
- ligar repetidamente dispositivo se fio ou terminal aquece.

Se algo está aquecendo, primeiro desligue a energia e encontre a causa.

## Erros Típicos

- não calculou corrente de carga;
- escolheu fonte de alimentação sem margem;
- esqueceu corrente de inrush de ventilador ou servo;
- confundiu 12V e 24V;
- alimenta controlador 5V de linha instável;
- sem `GND` comum;
- fio demasiado fino;
- fio demasiado longo para a corrente;
- terminal não apertado bem;
- carga funciona mas tensão cai significativamente.

## Pontos-chave

- A fonte de alimentação é verificada primeiro.
- Calcule corrente para todas as cargas, não apenas uma peça.
- Precisa de pelo menos 50% de margem de potência.
- A tensão deve ser medida sob carga.
- `GND` comum é frequentemente obrigatório para controlar módulos externos.
- Fio fino ou longo pode causar queda de tensão e aquecimento.

## Referências

- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - considerações básicas sobre tensão, corrente e potência para projectos de microcontrolador.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - verificação de fonte de alimentação, conexões e aquecimento ao resolver problemas.
- [ProdataKey: How does wire gauge affect line loss?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss) - por que comprimento, secção transversal e corrente afectam queda de tensão e perdas.
- [WiringCalcs: Voltage Drop Explained](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - explicação prática de queda de tensão, resistência de fio e efeito de corrente.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - exemplo de `GND` comum ao medir/controlar carga externa.
