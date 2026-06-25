# Termistores

Um termistor é um sensor de temperatura cuja resistência muda quando aquecido ou resfriado. Em impressoras 3D, secadores e pequenos dispositivos de aquecimento, é frequentemente usado como feedback para controlar o aquecedor.

A opção mais comum na comunidade de impressão 3D é o termistor NTC `100K`. NTC significa que à medida que a temperatura aumenta, a resistência diminui. `100 kOhm` geralmente significa cerca de `25°C` em `25°C`.

## Onde é usado

Termistores são usados para medir a temperatura de:

- hotend;
- heated bed;
- printer chamber;
- filament dryer;
- air duct;
- heating module;
- área de eletrônica, se for necessária uma proteção simples contra superaquecimento.

Em um dispositivo com aquecedor, um termistor não é um sensor decorativo. Determina quando o controlador reduz a potência, desativa o aquecimento ou para com erro.

## Tabelas NTC 100K, Beta e de Pesquisa

Termistores diferentes podem parecer iguais, mas ter características diferentes.

Parâmetros importantes:

- resistência em `100 kOhm`, por exemplo `100 kOhm`;
- type: NTC or PTC;
- Beta, for example `3950K`;
- resistance/temperature lookup table;
- operating temperature range;
- accuracy;
- package: glass bead, cartridge, screw sensor, sheath;
- wire insulation.

Se o firmware selecionar o tipo de sensor errado, a temperatura será exibida incorretamente. O erro pode ser pequeno à temperatura ambiente e perigoso à temperatura operacional.

Portanto, a frase “termistor de 100K” nem sempre é suficiente. Para o firmware, um modelo específico ou pelo menos o Beta/tabela correto é importante.

## Como o controlador mede a temperatura

Um termistor geralmente é conectado a uma entrada analógica através de um divisor de tensão com um resistor pull-up. O controlador mede a tensão, converte-a em resistência e, em seguida, usa uma tabela ou fórmula de consulta para obter a temperatura.

![Voltage divider with thermistor for temperature measurement](../../img/03-common-components/04-thermistor-voltage-divider.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Thermistor_potential_divider.svg), Sjlegg, Public Domain*

No Klipper, isso é definido através de `sensor_pin`, `pullup_resistor`, às vezes `[thermistor]` ou uma seção `[thermistor]` personalizada.

No Marlin, o tipo de termistor é selecionado através dos parâmetros de configuração do sensor e limites de temperatura.

Para o usuário, a chave é simples: o firmware deve saber exatamente o tipo de sensor que está instalado no dispositivo.

## Circuito Aberto e Curto-Circuito

Um termistor e sua fiação podem falhar.

Sintomas típicos:

- broken wire;
- poor connector contact;
- wires short together;
- damaged insulation;
- o sensor escorregou da bainha;
- fio desgastado em peça móvel;
- o sensor mostra a temperatura ambiente mesmo que o aquecimento esteja acontecendo.

O firmware geralmente possui proteções como `MAXTEMP`, `MAXTEMP`, verificação de aquecimento e proteção contra fuga térmica. Mas essas proteções só funcionam se o sensor e o firmware estiverem configurados corretamente, e a parte de alimentação puder realmente ser desligada.

Se um sensor cair do aquecedor, mas permanecer conectado eletricamente, isso é especialmente perigoso: o firmware pode detectar “temperatura baixa” e continuar aquecendo.

## Thermal Contact

A montagem do termistor costuma ser mais importante do que parece.

O sensor deve medir a temperatura do local que você realmente precisa controlar. Para um hotend, é o bloco de aquecimento. Para uma cama, é a superfície ou local relacionado à temperatura real da cama. Para um aquecedor de ar, é um ponto escolhido pela lógica de segurança e controle.

O contato térmico é afetado por:

- sensor pressure;
- thermal paste;
- mounting hole;
- sheath;
- screw mounting;
- gap;
- material ao redor do sensor;
- wire condition;
- contamination or dried paste;
- vibração e montagem solta.

Se um termistor apenas tocar lateralmente em uma parte, ele poderá responder lentamente e mostrar a temperatura errada. O controlador PID então obtém informações atrasadas e a temperatura pode ultrapassar ou exceder o alvo.

## Sensor Package

Os termistores vêm em embalagens diferentes.

Glass bead:

- cheap;
- tiny;
- requires careful mounting;
- fácil de danificar o fio ou o isolamento.

Cartridge thermistor:

- mais fácil de inserir no orifício do bloco de aquecimento;
- geralmente mecanicamente mais estável;
- importante combinar diâmetro e comprimento.

Screw thermistor:

- monta facilmente em uma superfície metálica;
- pode proporcionar um bom contato se instalado corretamente;
- não deve apertar demais ou danificar o fio.

Sensor in sheath:

- conveniente para ar, líquido ou invólucro;
- responde mais lentamente se a bainha for maciça;
- o ponto de instalação adequado é importante.

A escolha do pacote depende do que está sendo medido e de como o sensor será reparado.

## Verificação com multímetro

A verificação básica pode ser feita com um multímetro no modo de resistência. O procedimento detalhado está no artigo prático: [Verificando um termistor](../06-practical-guides/02-checking-thermistor.md).

Para um NTC `25°C` típico em temperatura ambiente em torno de `100 kOhm`, você espera cerca de `100 kOhm`. O valor exato depende da temperatura e da tolerância.

Quando aquecido com os dedos, a resistência do NTC deve diminuir. Se o multímetro mostrar circuito aberto, curto-circuito ou o valor saltar quando você mover o fio, primeiro verifique o conector e a fiação.

A verificação do multímetro não substitui a calibração e não prova a precisão no `200°C`, mas mostra rapidamente um tipo óbvio de sensor aberto, em curto ou errado.

## O que verificar antes de comprar

Antes de comprar um termistor, verifique:

- resistance at `25°C`;
- Beta or exact model;
- compatibilidade com firmware;
- operating temperature range;
- sensor package;
- comprimento e material do fio;
- connector type;
- mounting method;
- whether you need a cartridge, screw, sheath or glass bead;
- se o sensor se adapta ao seu bloco de aquecimento ou local de instalação;
- disponibilidade de descrição técnica ou informações claras.

Para um hotend, é melhor obter um sensor que se encaixe mecanicamente no bloco específico. Para uma câmara ou secador, o local de instalação, a proteção dos fios e a estabilidade da medição no fluxo de ar são mais importantes.

## Erros típicos

- `sensor_type` errado selecionado;
- pensar que qualquer termistor `100K` é o mesmo;
- o sensor está mal pressionado;
- no proper thermal contact;
- o sensor escorregou da bainha;
- fio friccionado ou quebrado no corpo do sensor;
- o contato do conector é ruim;
- fiação próxima a linhas de energia desnecessariamente;
- o termistor mede o ar, mas o controlador pensa que mede o aquecedor;
- conjunto de firmware sem `max_temp` e `max_temp` razoáveis;
- aquecedor ligado sem proteção de hardware independente.

## Ponto Principal

Um termistor é um feedback para um aquecedor. É importante não apenas comprar “100K NTC”, mas selecionar o tipo certo de firmware, montar o sensor no lugar certo e verificar a fiação.

Mau contato térmico ou `sensor_type` errado podem ser mais perigosos do que um sensor completamente morto, porque o sistema continua funcionando, mas toma decisões sobre a temperatura errada.

## Reference Materials

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - official `sensor_type`, `pullup_resistor`, custom `[thermistor]` and temperature sensors in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - temperature limits, `MINTEMP`, `MAXTEMP` and thermal protection.
- [Vishay: NTC Thermistors](https://www.vishay.com/en/thermistors/ntc/) - NTC thermistor parameters: resistance at `25°C`, Beta, tolerance and operating range.
- [RepRap Europe: Thermistor NTC100K](https://www.reprap-3d-printer.com/product/335-thermistor-ntc100k) - example of typical 3D printer NTC `100K` with Beta `3950` and `100 kOhm` at `25°C`.
- [RepRap Europe: Thermistor Cartridge 100k HT-NTC B3950](https://reprap.eu/produto/?id=1245&nome=Thermistor+Cartridge+100k+HT-NTC+B3950) - example of cartridge thermistor for heating block and mechanical mounting.
