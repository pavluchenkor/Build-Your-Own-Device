# Ligação de um Ventilador

Uma ventoinha parece um componente simples: aplique alimentação e ela gira.

Na prática, os problemas surgem de quatro coisas:

- escolher uma ventoinha com a tensão errada;
- conectá-la a uma saída fraca do controlador;
- não entender a diferença entre ventoinhas de 2, 3 e 4 pinos;
- colocar a ventoinha onde falta pressão por causa de filtro, grade ou duto.

Em dispositivos semelhantes ao iDryer, a ventoinha normalmente é usada para circulação de ar, resfriamento do aquecedor, exaustão da câmara, filtragem ou resfriamento da eletrônica.

## O que verificar antes da conexão

Antes de conectar, procure os parâmetros do ventoinha:

- tensão: `5V`, `12V`, ou `24V`;
- corrente ou potência;
- tipo de conector: 2-pin, 3-pin, ou 4-pin;
- capacidade de controle PWM;
- presença de sinal taquométrico;
- fluxo de ar;
- pressão estática;
- nível de ruído;
- temperatura de funcionamento.

Estes dados encontram-se numa etiqueta, página de produto ou na datasheet.

Por exemplo, uma datasheet de um ventoinha contém geralmente não apenas tensão e corrente, mas também fluxo de ar, pressão estática, ruído `SPL dB(A)`, temperatura de funcionamento e tempo de vida útil. Estes são mais úteis do que selecionar um ventoinha apenas pelo tamanho.

## Não alimente um ventoinha a partir de GPIO

GPIO de um controlador é um sinal de controle, não uma saída de alimentação.

Nunca alimente um ventoinha diretamente a partir de GPIO. Isto pode danificar o controlador ou causar resets quando o ventoinha arranca.

A lógica correta é:

- o ventoinha recebe alimentação de uma fonte de alimentação ou saída de alimentação da placa;
- o controlador apenas gere conectado/desconectado ou velocidade;
- se for utilizado um módulo MOSFET externo, o `GND` da fonte de alimentação e o `GND` do driver devem ser comuns.

![N-channel MOSFET in switching mode (low-side) for load control](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Opção mais simples: ventoinha de 2 pinos

Um ventoinha de 2 pinos tipicamente tem apenas:

- `+` alimentação;
- `-` alimentação.

Se for um ventoinha de 24V, ligue-o a 24V. Se for um ventoinha de 12V, ligue-o a 12V.

Para controle simples conectado/desconectado, pode utilizar:

- uma saída dedicada de ventoinha na placa, se classificada para a tensão e corrente necessárias;
- um módulo MOSFET externo para cargas DC;
- um controlador de ventoinha separado.

Se o ventoinha deve funcionar continuamente, pode ser conectado diretamente a uma fonte de alimentação apropriada através de um fusível ou linha de alimentação protegida. Mas num dispositivo com um aquecedor, é frequentemente melhor que o ventoinha seja controlado pelo controlador como parte da lógica de segurança.

## Ventilador de 3 pinos

Um ventoinha de 3 pinos tipicamente tem:

- alimentação;
- massa;
- sinal taquométrico.

O sinal taquométrico permite-lhe monitorizar o RPM do ventoinha. Não controla a velocidade por si só.

A velocidade de um ventoinha de 3 pinos é geralmente alterada em tensão de alimentação ou PWM na linha de alimentação, se a placa específica e o ventoinha o suportarem. Mas este método pode funcionar pior do que um PWM adequado de 4 pinos: o ventoinha pode gritar, falhar ao arrancar em baixa velocidade ou funcionar de forma instável.

Se o controle de velocidade não for necessário, um ventoinha de 3 pinos pode ser usado como um normal de 2 pinos: a alimentação e a massa estão conectadas, o fio taquométrico não é usado.

## Ventilador PWM de 4 pinos

Um ventoinha PWM de 4 pinos tipicamente tem:

- massa;
- alimentação;
- sinal taquométrico;
- sinal de controle PWM.

A diferença fundamental: a alimentação do ventoinha é aplicada continuamente, e a velocidade é definida por um sinal PWM separado.

Esta é a forma correta de controlar ventoinhaes PWM de computador. Não assuma que um ventoinha de 4 pinos precisa ser controlado através da comutação constante da alimentação. Para um ventoinha PWM adequado, o sinal de controle deve ir para um pino PWM separado.

Os ventoinhas PWM de computador de 4 pinos frequentemente têm uma entrada de controle concebida para sinais open-collector/open-drain com pull-up interno, sem qualquer tensão de GPIO. Não aplique `24V` ou `24V` ao pino PWM. Verifique a documentação do ventoinha; se open-drain/open-collector for necessário, utilize uma saída de transistor correspondente ou modo GPIO.

Para muitos ventoinhaes PWM de 4 pinos, a frequência PWM típica é cerca de `25 kHz`. Alguns ventoinhaes funcionam numa gama próxima, mas com uma frequência demasiado baixa ou alta podem comportar-se de forma imprevisível: funcionar a velocidade máxima, parar ou fazer ruído.

Se o fio PWM não estiver conectado, muitos ventoinhaes de 4 pinos funcionam a velocidade máxima.

## GND comum / negativo comum

Se o ventoinha for alimentado por uma fonte de alimentação separada e o sinal PWM vem do controlador, é necessário um `GND` comum / negativo comum.

Sem um `GND` comum, o controlador e o ventoinha não têm um nível de referência comum. Como resultado, o PWM pode não funcionar ou pode funcionar intermitentemente.

Regra simples:

- a alimentação positiva do ventoinha vem de uma fonte de alimentação apropriada;
- a alimentação negativa do ventoinha está conectada ao negativo da fonte de alimentação;
- a `GND` do controlador está conectada ao mesmo negativo;
- o sinal de controle só funciona com uma massa comum.

## Seleccionar um ventoinha para a tarefa

Para arrefecimento aberto, o fluxo de ar é importante.

Para um filtro, dissipador de calor, grelha apertada, conduta longa ou canal estreito, a pressão estática é mais importante.

Portanto, para um filtro de câmara de impressora, um ventoinha de gabinete silencioso ordinário pode ser fraco. Sopra bem em ar livre mas mal consegue fazer passar ar através de um filtro HEPA, camada de carvão ou canal estreito.

Linhas de orientação:

- para circulação livre de ar procure `CFM` ou `m³/h`;
- para filtros, dissipadores de calor e condutas, a pressão estática é essencial;
- para funcionamento silencioso procure não apenas `dB(A)` mas também montagem, grelha e vibração;
- para uma câmara aquecida procure a temperatura de funcionamento do ventoinha.

## Corrente de arranque e margem

Quando um ventoinha arranca, pode brevemente atrair mais corrente do que durante o funcionamento normal.

Se vários ventoinhaes estiverem conectados a uma saída, as suas correntes somam-se.

Verifique:

- corrente de saída máxima da placa;
- corrente de um ventoinha;
- corrente total de todos os ventoinhaes;
- pelo menos 50% de margem;
- aquecimento de terminais, fios e módulo MOSFET durante funcionamento prolongado.

Por exemplo, se um ventoinha desenha `0.25A`, quatro ventoinhaes assim desenham cerca de `1A` sem contabilizar a corrente de arranque.

## Exemplo: conexão através de módulo MOSFET

Circuito típico para um ventoinha de 12V ou 24V:

1. O positivo da fonte de alimentação vai para o positivo do ventoinha.
2. O negativo do ventoinha vai para a saída de alimentação do módulo MOSFET.
3. O negativo da fonte de alimentação vai para o módulo MOSFET.
4. A `GND` do controlador está conectada ao negativo da fonte de alimentação.
5. O pino de controle do controlador vai para a entrada do módulo MOSFET.

Isto chama-se comutação de baixo lado: o MOSFET quebra o negativo da carga.

Para um ventoinha simples de 2 pinos isto é uma opção padrão e claro se o módulo MOSFET for classificado para a tensão e corrente elétrica. Para um ventoinha de 3 pinos/4 pinos com taquômetro ou entrada PWM separada, "cortar o negativo" nem sempre é bom: a monitorização de RPM e controle PWM nativo geralmente desabilita um `GND` comum constante.

## Exemplo de configuração Klipper

Os nomes de pinos nos exemplos não são universais. Antes de copiar, verifique o esquema de pinos da sua placa: um `pin` incorreta pode activar a saída errada.

Se o ventoinha está conectado a uma saída controlada e deve ser controlado manualmente:

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

Se o ventoinha deve conectar com base na temperatura da câmara:

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

## O que verificar após a conexão

Antes do funcionamento prolongado, verifique:

- o ventoinha roda na direcção correta;
- a tensão corresponde ao ventoinha;
- o módulo MOSFET não sobreaquece;
- os terminais não se sobrequentem;
- os fios não são demasiado finos para a corrente escolhida;
- o ventoinha arranca após uma paragem completa;
- sem gritaria ou travamento a baixa velocidade;
- o fluxo de ar passa através da área necessária, não para além dela;
- a grelha, filtro ou gabinete não sufoca o fluxo mais do que esperado.

Se o ventoinha está perto de um aquecedor, teste-o à temperatura real da câmara. Um ventoinha que funciona bem na bancada pode degradar-se rapidamente num gabinete quente.

## Erros comuns

- conectar um ventoinha de 12V a 24V;
- conectar um ventoinha de 24V a 12V e decidir que está quebrado;
- alimentar um ventoinha a partir de GPIO;
- esquecer massa comum entre controlador e alimentação externa;
- esperar controle PWM de um ventoinha de 3 pinos;
- controlar um ventoinha PWM de 4 pinos cortando a alimentação em vez de utilizar o pino PWM;
- não contabilizar a corrente total de vários ventoinhaes;
- escolher um ventoinha por tamanho sem verificar a pressão estática;
- colocar um ventoinha silencioso num filtro denso e obter fluxo quase nulo;
- não verificar a direcção do fluxo após a instalação;
- deixar fios não fixados e obter desfibramento contra o rotor ou gabinete.

## Pontos-chave

- A tensão do ventoinha deve corresponder à fonte de alimentação.
- GPIO não alimenta um ventoinha, apenas o controla.
- Para alimentação externa, é necessária uma massa comum com o controlador.
- Um ventoinha de 2 pinos é mais fácil de controlar através de uma saída de alimentação ou MOSFET.
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
