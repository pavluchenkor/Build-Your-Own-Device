# Ligação de uma Célula de Carga

Uma célula de carga mede força ou peso através de pequena deformação de uma viga de metal, botão ou plataforma.

Em dispositivos semelhantes ao iDryer, uma célula de carga pode estimar peso da bobine, filamento restante ou carga do mecanismo.

Ponto principal: uma célula de carga raramente é ligada directamente a um controlador. Seu sinal é demasiado pequeno. Normalmente, um módulo HX711 ou amplificador/ADC similar é colocado entre o sensor e o controlador.

## O que precisa

Conjunto mínimo:

- célula de carga do intervalo de peso necessário;
- módulo HX711;
- controlador: Arduino, ESP32, RP2040, STM32, ou outra placa;
- montagem mecânica rígida;
- massa conhecida para calibração;
- fios curtos e arrumados.

Se a mecânica falhar, o circuito não ajudará. Uma célula de carga pode ser fiada perfeitamente, mas dar leituras sem sentido devido a desalinhamento, jogo ou carga aplicada no ponto errado.

## Como a ligação é arrumada

A célula de carga liga-se ao HX711 com fios analógicos.

O HX711 liga-se ao controlador com fios digitais.

Cadeia típica:

```text
célula de carga -> HX711 -> controlador
```

O HX711 normalmente tem dois lados:

- entrada da célula de carga: `E+`, `E-`, `A+`, `A-`, ou similar;
- ligação ao controlador: `VCC`, `GND`, `DT`/`DOUT`, `SCK`/`CLK`.

![HX711 and load cell connection diagram](../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Fios da célula de carga

Uma célula de carga típica de quatro fios normalmente tem:

- `E+` - mais da ponte de alimentação;
- `E-` - menos da ponte de alimentação;
- `S+`, `A+`, ou `O+` - sinal de medição positivo;
- `S-`, `A-`, ou `O-` - sinal de medição negativo.

Esquema de cor comum:

- vermelho - `E+`;
- preto - `E-`;
- verde ou azul - `A+`;
- branco - `A-`.

Mas as cores não são lei. Diferentes sensores podem diferir. Se houver uma ficha técnica para a célula de carga específica, siga-a.

Se o sensor tiver um quinto fio, folha ou blindagem, frequentemente é blindagem electromagnética. Não confunda com um fio de medição de ponte. Normalmente, a blindagem é ligada a `GND` ou alojamento num lado se a documentação o disser, mas não à medição `A+`/`A-`.

Se não houver diagrama de fio, não ligue a célula de carga "ao acaso". Primeiro procure a ficha técnica do sensor ou teste a ponte por guia do fabricante: fios incorrectos facilmente dão leituras instáveis ou sobrecarregam a entrada HX711.

## Ligação de HX711 ao controlador

No lado do controlador, normalmente precisa de quatro linhas:

- `VCC` - alimentação do módulo;
- `GND` - negativo comum;
- `DT`, `DOUT`, ou `DATA` - dados;
- `SCK`, `CLK`, ou `PD_SCK` - relógio.

Para muitos módulos HX711, a alimentação pode ser `3.3V` ou `5V`, mas verifique o módulo específico. Se o controlador funciona em 3.3V, é conveniente usar um módulo e alimentação compatível com lógica 3.3V.

Os pinos `DT` e `SCK` normalmente podem ligar-se a GPIO regular. Isto não é I2C ou SPI no sentido usual, mas uma interface simples de dois fios HX711.

## Mecânica é mais importante do que o circuito

Uma célula de carga deve deformar-se conforme o fabricante pretendeu.

Para um sensor de viga, um lado normalmente monta-se numa base fixa, o outro lado suporta a carga. Se ambos os lados estiverem rigidamente montados numa parte, o sensor não se dobrará normalmente.

Verifique:

- onde está o lado de montagem do sensor;
- onde a carga deve ser aplicada;
- que direcção a força deve ir;
- se são necessários espaçadores;
- se a parte móvel limpa o alojamento;
- nenhum desalinhamento;
- nenhum carregamento lateral;
- os parafusos não estão demasiado apertados;
- a bobine ou plataforma não cai para além da zona de trabalho do sensor.

Para peso da bobine, é especialmente importante que toda a carga passe através do sensor, não parcialmente pela parede do alojamento, eixo, cabo ou cobertura cosmética.

## Não sobrecarregue o sensor

O intervalo de uma célula de carga não é uma recomendação mas um limite de medição.

Se um sensor de 1 kg for colocado onde uma bobina e suporte pode exceder isto, o sensor funcionará mal ou se deformará permanentemente.

Escolha o intervalo com margem:

- peso máximo da bobine;
- peso do suporte;
- possíveis solavancos;
- desalinhamento;
- margem de segurança para erro do utilizador.

Mas um intervalo demasiado grande também nem sempre é bom. Um sensor de 100 kg sentirá uma pequena bobine pior do que um sensor de 5 kg ou 10 kg com mecânica e electrónica idênticas.

## Primeiro arranque

Antes de instalar no dispositivo, teste o sistema na bancada:

1. Ligue a célula de carga ao HX711.
2. Ligue o HX711 ao controlador.
3. Execute código de teste ou biblioteca.
4. Certifique-se de que os valores brutos mudam quando pressiona no sensor.
5. Remova a carga e verifique se o valor é bastante estável.
6. Coloque uma massa conhecida e verifique a mudança.

Nesta fase, não exija precisão em gramas. Em primeiro lugar, precisa ver que o sensor está vivo, a direcção da carga está correcta e as leituras mudam previsivelmente.

Se o valor diminui à medida que o peso aumenta, normalmente apenas troque `A+` e `A-` ou contabilize o sinal no código.

## Tara e calibração

Uma célula de carga sem calibração não sabe o que são gramas.

Processo típico:

1. Coloque plataforma vazia.
2. Tara: isto é zero contabilizando o peso da plataforma.
3. Coloque uma massa conhecida.
4. Seleccione factor de calibração.
5. Verifique vários pesos diferentes.

Para bobines de filamento, decida o que conta como peso:

- bobine inteira com plástico;
- apenas plástico restante sem peso da bobine vazia;
- mudança de peso do valor inicial.

Se bobines vazias de diferentes fabricantes pesarem diferentemente, o cálculo preciso do restante requer conhecer o peso específico da bobine vazia ou trabalhar com estimativas aproximadas.

## Ruído e leituras instáveis

O HX711 mede um sinal muito pequeno, portanto o sistema é sensível a ruído e problemas mecânicos.

Causas de leituras instáveis:

- fios longos do sensor ao HX711;
- maus contactos;
- fios de alimentação do aquecedor próximos a fios de sinal;
- vibração do ventilador ou impressora;
- base mole;
- jogo na montagem;
- desvio de temperatura;
- carga tocando o alojamento contornando o sensor.

Medidas práticas:

- mantenha o HX711 próximo à célula de carga;
- não execute fios de sinal junto a fios de alimentação do aquecedor;
- fixe os fios para não puxarem o sensor;
- usar média de medição;
- calibre após montagem no alojamento;
- tare após aquecimento do dispositivo se a temperatura afecta notavelmente as leituras.

## O que verificar após montagem

Antes de usar:

- sensor é classificado para o peso necessário;
- a carga passa através da parte de trabalho do sensor;
- os fixadores não bloqueiam a deformação;
- o HX711 recebe alimentação correcta;
- `DT` e `SCK` estão ligados ao GPIO correcto;
- existe massa comum;
- os valores brutos mudam sob carga;
- sem carga, as leituras não desviam muito rapidamente;
- a massa conhecida mostra peso esperado após calibração;
- os fios não puxam a plataforma;
- a bobine ou suporte não toca o alojamento para além do sensor.

## Erros comuns

- ligar a célula de carga directamente à entrada analógica do controlador;
- confundir `E+`/`E-` e `A+`/`A-`;
- confiar nas cores dos fios sem ficha técnica;
- esquecer calibração;
- tara antes da instalação mecânica final;
- montar o sensor para que não se possa dobrar;
- sobrecarregar o sensor;
- escolher um intervalo demasiado grande e perder sensibilidade;
- obter instabilidade de fios longos e interferência;
- esperar precisão em gramas de um corpo plástico flexível sem mecânica rígida.

## Pontos-chave

- A célula de carga normalmente liga-se através de HX711, não directamente ao controlador.
- Os fios do sensor vão para `E+`, `E-`, `A+`, `A-`.
- O HX711 liga-se ao controlador através de alimentação, massa, `DT` e `SCK`.
- A mecânica é mais importante do que o circuito: a carga deve passar corretamente através do sensor.
- Tara e calibração com massa conhecida são necessárias.
- Sem montagem rígida e mecânica adequada, leituras precisas não acontecerão.

## Leitura relacionada

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - practical HX711 and load cell connection, wire colors, `DT`/`SCK`, and calibration example.
- [SparkFun: Load Cell Amplifier HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - HX711 module description, purpose, and microcontroller interface.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - HX711 technical datasheet: 24-bit ADC, differential bridge input, gain, and digital interface.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - practical examples of load cell mechanical installation and load application direction.
- [SparkFun retired HX711 guide: load cell mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - useful illustrations of beam, button, and platform sensor mounting options.
