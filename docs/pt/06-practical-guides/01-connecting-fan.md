# Ligação de um Ventilador

Um ventilador parece um componente simples: aplica-se alimentação e ele gira.

Na prática, os problemas surgem de quatro coisas:

- seleccionar um ventilador com a tensão errada;
- ligá-lo a uma saída fraca do controlador;
- não compreender a diferença entre ventiladores de 2, 3 e 4 pinos;
- colocar o ventilador onde falta pressão devido a filtro, grelha ou conduta.

Em dispositivos semelhantes ao iDryer, o ventilador é normalmente usado para circulação de ar, arrefecimento do aquecedor, exaustão da câmara, filtragem ou arrefecimento da electrónica.

## O que verificar antes da ligação

Antes de ligar, procure os parâmetros do ventilador:

- tensão: `5V`, `12V`, ou `24V`;
- corrente ou potência;
- tipo de conector: 2-pin, 3-pin, ou 4-pin;
- capacidade de controlo PWM;
- presença de sinal taquométrico;
- fluxo de ar;
- pressão estática;
- nível de ruído;
- temperatura de funcionamento.

Estes dados encontram-se numa etiqueta, página de produto ou na ficha técnica.

Por exemplo, uma ficha técnica de um ventilador contém geralmente não apenas tensão e corrente, mas também fluxo de ar, pressão estática, ruído `SPL dB(A)`, temperatura de funcionamento e tempo de vida útil. Estes são mais úteis do que seleccionar um ventilador apenas pelo tamanho.

## Não alimente um ventilador a partir de GPIO

GPIO de um controlador é um sinal de controlo, não uma saída de alimentação.

Nunca alimente um ventilador directamente a partir de GPIO. Isto pode danificar o controlador ou causar resets quando o ventilador arranca.

A lógica correta é:

- o ventilador recebe alimentação de uma fonte de alimentação ou saída de alimentação da placa;
- o controlador apenas gere ligado/desligado ou velocidade;
- se for utilizado um módulo MOSFET externo, o `GND` da fonte de alimentação e o `GND` do driver devem ser comuns.

![N-channel MOSFET in switching mode (low-side) for load control](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Opção mais simples: ventilador de 2 pinos

Um ventilador de 2 pinos tipicamente tem apenas:

- `+` alimentação;
- `-` alimentação.

Se for um ventilador de 24V, ligue-o a 24V. Se for um ventilador de 12V, ligue-o a 12V.

Para controlo simples ligado/desligado, pode utilizar:

- uma saída dedicada de ventilador na placa, se classificada para a tensão e corrente necessárias;
- um módulo MOSFET externo para cargas DC;
- um controlador de ventilador separado.

Se o ventilador deve funcionar continuamente, pode ser ligado directamente a uma fonte de alimentação apropriada através de um fusível ou linha de alimentação protegida. Mas num dispositivo com um aquecedor, é frequentemente melhor que o ventilador seja controlado pelo controlador como parte da lógica de segurança.

## Ventilador de 3 pinos

Um ventilador de 3 pinos tipicamente tem:

- alimentação;
- massa;
- sinal taquométrico.

O sinal taquométrico permite-lhe monitorizar o RPM do ventilador. Não controla a velocidade por si só.

A velocidade de um ventilador de 3 pinos é geralmente alterada a tensão de alimentação ou PWM na linha de alimentação, se a placa específica e o ventilador o suportarem. Mas este método pode funcionar pior do que um PWM adequado de 4 pinos: o ventilador pode gritar, falhar ao arrancar em baixa velocidade ou funcionar de forma assustadora.

Se o controle de velocidade não for necessário, um ventilador de 3 pinos pode ser usado como um normal de 2 pinos: a alimentação e a massa estão ligadas, o fio taquométrico não é usado.

## Ventilador PWM de 4 pinos

Um ventilador PWM de 4 pinos tipicamente tem:

- massa;
- alimentação;
- sinal taquométrico;
- sinal de controlo PWM.

A diferença fundamental: a alimentação do ventilador é aplicada continuamente, e a velocidade é definida por um sinal PWM separado.

Esta é a forma correcta de controlar ventiladores PWM de computador. Não assuma que um ventilador de 4 pinos precisa ser controlado através da comutação constante da alimentação. Para um ventilador PWM adequado, o sinal de controlo deve ir para um pino PWM separado.

Os ventiladores PWM de computador de 4 pinos frequentemente têm uma entrada de controle concebida para sinais open-collector/open-drain com pull-up interno, sem qualquer tensão de GPIO. Não aplique `24V` ou `24V` ao pino PWM. Verifique a documentação do ventilador; se open-drain/open-collector for necessário, utilize uma saída de transistor correspondente ou modo GPIO.

Para muitos ventiladores PWM de 4 pinos, a frequência PWM típica é cerca de `25 kHz`. Alguns ventiladores funcionam numa gama próxima, mas com uma frequência demasiado baixa ou alta podem comportar-se de forma imprevisível: funcionar a velocidade máxima, parar ou fazer ruído.

Se o fio PWM não estiver ligado, muitos ventiladores de 4 pinos funcionam a velocidade máxima.

## GND comum / negativo comum

Se o ventilador for alimentado por uma fonte de alimentação separada e o sinal PWM vem do controlador, é necessário um `GND` comum / negativo comum.

Sem um `GND` comum, o controlador e o ventilador não têm um nível de referência comum. Como resultado, o PWM pode não funcionar ou pode funcionar intermitentemente.

Regra simples:

- a alimentação positiva do ventilador vem de uma fonte de alimentação apropriada;
- a alimentação negativa do ventilador está ligada ao negativo da fonte de alimentação;
- a `GND` do controlador está ligada ao mesmo negativo;
- o sinal de controlo só funciona com uma massa comum.

## Seleccionar um ventilador para a tarefa

Para arrefecimento aberto, o fluxo de ar é importante.

Para um filtro, dissipador de calor, grelha apertada, conduta longa ou canal estreito, a pressão estática é mais importante.

Portanto, para um filtro de câmara de impressora, um ventilador de caixa silencioso ordinário pode ser fraco. Sopra bem em ar livre mas mal consegue fazer passar ar através de um filtro HEPA, camada de carvão ou canal estreito.

Linhas de orientação:

- para circulação livre de ar procure `CFM` ou `m³/h`;
- para filtros, dissipadores de calor e condutas, a pressão estática é essencial;
- para funcionamento silencioso procure não apenas `dB(A)` mas também montagem, grelha e vibração;
- para uma câmara aquecida procure a temperatura de funcionamento do ventilador.

## Corrente de arranque e margem

Quando um ventilador arranca, pode atrair brevemente mais corrente do que durante o funcionamento normal.

Se vários ventiladores estiverem ligados a uma saída, as suas correntes somam-se.

Verifique:

- corrente de saída máxima da placa;
- corrente de um ventilador;
- corrente total de todos os ventiladores;
- pelo menos 50% de margem;
- aquecimento de terminais, fios e módulo MOSFET durante funcionamento prolongado.

Por exemplo, se um ventilador desenha `0.25A`, quatro ventiladores assim desenham cerca de `1A` sem contabilizar a corrente de arranque.

## Exemplo: ligação através de módulo MOSFET

Circuito típico para um ventilador de 12V ou 24V:

1. O positivo da fonte de alimentação vai para o positivo do ventilador.
2. O negativo do ventilador vai para a saída de alimentação do módulo MOSFET.
3. O negativo da fonte de alimentação vai para o módulo MOSFET.
4. A `GND` do controlador está ligada ao negativo da fonte de alimentação.
5. O pino de controlo do controlador vai para a entrada do módulo MOSFET.

Isto chama-se comutação de baixo lado: o MOSFET quebra o negativo da carga.

Para um ventilador simples de 2 pinos isto é uma opção padrão e claro se o módulo MOSFET for classificado para a tensão e corrente elétrica. Para um ventilador de 3 pinos/4 pinos com taquômetro ou entrada PWM separada, "cortar o negativo" nem sempre é bom: a monitorização de RPM e controle PWM nativo geralmente desabilita um `GND` comum constante.

## Exemplo de configuração Klipper

Os nomes de pinos nos exemplos não são universais. Antes de copiar, verifique o esquema de pinos da sua placa: um `pin` incorrecta pode activar a saída errada.

Se o ventilador está ligado a uma saída controlada e deve ser controlado manualmente:

```ini
[fan_generic chamber_fan]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 0.5
off_below: 0.15
```

Control:

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.4
SET_FAN_SPEED FAN=chamber_fan SPEED=0
```

Se o ventilador deve ligar com base na temperatura da câmara:

```ini
[temperature_fan chamber_exhaust]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 2.0
off_below: 0.15
sensor_type: NTC 100K beta 3950
sensor_pin: PA0
min_temp: 0
max_temp: 80
target_temp: 45
control: watermark
```

Os nomes de pinos aqui são típicos. Num dispositivo real, verifique o esquema de pinos da sua placa.

## O que verificar após a ligação

Antes do funcionamento prolongado, verifique:

- o ventilador roda na direcção correcta;
- a tensão corresponde ao ventilador;
- o módulo MOSFET não sobreaquece;
- os terminais não se sobrequentem;
- os fios não são demasiado finos para a corrente escolhida;
- o ventilador arranca após uma paragem completa;
- sem gritaria ou travamento a baixa velocidade;
- o fluxo de ar passa através da área necessária, não para além dela;
- a grelha, filtro ou invólucro não sufoca o fluxo mais do que esperado.

Se o ventilador está perto de um aquecedor, teste-o à temperatura real da câmara. Um ventilador que funciona bem na bancada pode degradar-se rapidamente num invólucro quente.

## Erros comuns

- ligar um ventilador de 12V a 24V;
- ligar um ventilador de 24V a 12V e decidir que está quebrado;
- alimentar um ventilador a partir de GPIO;
- esquecer massa comum entre controlador e alimentação externa;
- esperar controlo PWM de um ventilador de 3 pinos;
- controlar um ventilador PWM de 4 pinos cortando a alimentação em vez de utilizar o pino PWM;
- não contabilizar a corrente total de vários ventiladores;
- escolher um ventilador por tamanho sem verificar a pressão estática;
- colocar um ventilador silencioso num filtro denso e obter fluxo quase nulo;
- não verificar a direcção do fluxo após a instalação;
- deixar fios não fixados e obter desfibramento contra o rotor ou invólucro.

## Pontos-chave

- A tensão do ventilador deve corresponder à fonte de alimentação.
- GPIO não alimenta um ventilador, apenas o controla.
- Para alimentação externa, é necessária uma massa comum com o controlador.
- Um ventilador de 2 pinos é mais fácil de controlar através de uma saída de alimentação ou MOSFET.
- 3 pinos acrescenta um taquómetro mas não uma entrada PWM separada.
- PWM de 4 pinos é melhor controlado por um sinal PWM separado, não por comutação de alimentação.
- Para filtros e condutas, a pressão estática é mais importante do que um número de `CFM` bonito.
- Após montagem, verifique não apenas a rotação mas o fluxo real através da construção.

## Leitura relacionada

- [Noctua: PWM setup and RPM monitoring of a fan with microcontrollers](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - practical explanation of 4-pin PWM, RPM signal, common ground, and typical PWM frequency.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - official sections `fan`, `heater_fan`, `controller_fan`, `temperature_fan`, and `fan_generic`.
- [Voron Documentation: Chamber Temperature & Exhaust Fan](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - example of controlling chamber exhaust fan by temperature in Klipper.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - fan selection accounting for airflow, static pressure, housing resistance, and filters.
- [SANYO DENKI: DC fan example datasheet](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - example of real parameters: voltage, current, airflow, static pressure, noise, operating temperature, and service life.
