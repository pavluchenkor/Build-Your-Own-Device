# Verificação de um Termistor

Um termistor é um sensor de temperatura que altera a resistência quando aquecido ou arrefecido.

Em impressoras 3D, secadores e aquecedores de câmara, o tipo mais comum é um termistor NTC classificado em `100K`. NTC significa que a resistência diminui à medida que a temperatura aumenta.

Precisa verificar um termistor se:

- as leituras de temperatura são irrealistas;
- a temperatura salta constantemente;
- o aquecedor entra num estado de erro;
- o firmware relata `MINTEMP`, `MAXTEMP`, `Thermal runaway`, ou similar;
- o termistor foi substituído, movido ou recrimp;
- o dispositivo foi montado pela primeira vez.

## Em primeiro lugar, desligue a alimentação

A resistência é medida apenas em circuitos desenergizados.

Antes de verificar:

1. Desligue o dispositivo.
2. Desconecte a alimentação da rede ou fonte de alimentação.
3. Aguarde que o aquecedor arrefeça.
4. Desconecte o termistor da placa se precisar medir o sensor propriamente dito.

Se medir a resistência enquanto o termistor está conectado à placa, as leituras podem ser distorcidas por outros componentes do circuito. Se medir a resistência com a alimentação ligada, pode danificar o multímetro ou a placa.

## O que um NTC 100K deve ter

Um NTC típico `100K` tem uma resistência de cerca de `100 kOhm` a `25°C`.

Isto não significa que o multímetro mostre sempre exactamente `100.0 kOhm`.

É normal que a leitura difira aumentando à temperatura ambiente:

- numa sala fresca a resistência será superior;
- numa sala quente a resistência será menor;
- diferentes tipos de termistores têm tabelas diferentes;
- fios longos e maus contactos podem afectar a medição.

A verificação principal é simples: um NTC 100K à temperatura ambiente deve ler bolsas ou cerca de cem quilohms, não `OL` ou `OL`.

## Medição com um multímetro

Coloque seu multímetro no modo de resistência `Ohm`.

Se seu multímetro não tiver auto-alcance, seleccione um intervalo acima de `100 kOhm`, como `200 kOhm` ou `2 MOhm`.

Depois:

1. Desconecte o termistor da placa.
2. Toque as sondas do multímetro aos dois fios do termistor.
3. Não segure os fins de metal das sondas e fios simultaneamente: seu corpo pode adicionar resistência em paralelo.
4. Aguarde que a leitura se estabilize.
5. Registe o valor.

![Digital multimeter for measuring thermistor resistance](../../img/05-tools/02-digital-multimeter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Teste rápido de aquecimento com o dedo

Após medir à temperatura ambiente, pode aquecer cuidadosamente o sensor com seus dedos.

Para um termistor NTC, a resistência deve começar a diminuir.

Por exemplo:

- era cerca de `100 kOhm` à temperatura ambiente;
- tornou-se menor após aquecimento com dedo.

Os números exactos não importam aqui. A direcção da mudança é importante.

Se a resistência não mudar em absoluto, salta aleatoriamente ou desaparece quando o fio se move, o problema pode estar no sensor, fio, crimp ou conector.

## Ruptura e curto-circuito

Um multímetro ajuda a distinguir rapidamente um sensor normal de uma falha óbvia.

Sinais típicos:

- `OL`, `over limit`, `1` no lado esquerdo do ecrã, ou resistência infinita - circuito aberto;
- quase `0 Ohm` - curto-circuito;
- valor salta significativamente quando o fio se move - mau contacto ou condutor quebrado;
- valor cerca de `100 kOhm` à temperatura ambiente e diminui com o aquecimento - parece um NTC 100K saudável.

Diferentes multímetros usam designações diferentes para circuito aberto. Normalmente é `OL` ou um valor além do intervalo seleccionado.

## Verificação da fiação

O termistor pode estar bem enquanto o problema está na fiação.

Verifique:

- o conector está completamente inserido;
- os pinos não saíram do alojamento do conector;
- os fios não estão desfibrados;
- nenhum dano de isolamento perto do aquecedor;
- nenhuma tensão do fio quando os eixos ou cobertura se movem;
- o cabo não corre imediatamente adjacente aos fios de alimentação do aquecedor sem motivo;
- a localização do crimp é segura.

Se as leituras mudarem quando move o fio, isto não é uma "característica do sensor". Este é um problema de contacto que deve ser corrigido antes de ligar o aquecedor.

## Verificação em Klipper

Em Klipper o tipo de sensor é definido na configuração.

Exemplo para um sensor típico de temperatura de câmara:

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

Exemplo para um aquecedor de câmara:

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

Os nomes de pinos aqui são típicos. Num dispositivo real, verifique o esquema de pinos da sua placa.

Importante: `sensor_type` deve corresponder ao sensor real. Dois termistores podem parecer idênticos mas ter tabelas diferentes. Se escolher o tipo errado, a temperatura pode ser notavelmente imprecisa, especialmente no intervalo de aquecimento de trabalho.

## O que observar na interface

Após a ligação, verifique a temperatura na interface Klipper, Mainsail, Fluidd ou outra IU.

À temperatura ambiente, a leitura deve estar próxima da temperatura real da sala.

Sinais suspeitos:

- lê significativamente inferior à realidade;
- lê significativamente superior à realidade;
- a temperatura salta dezenas de graus;
- a temperatura muda quando move o fio;
- a temperatura não aumenta quando o aquecimento está ligado;
- a temperatura aumenta muito lentamente;
- a temperatura aumenta mesmo que o aquecedor esteja desligado.

Se o sensor estiver no aquecedor, não inicie aquecimento prolongado até que as leituras pareçam razoáveis.

## Erros de firmware

No firmware da impressora 3D, os erros de temperatura não são um problema menor mas parte da segurança.

Para um circuito típico com um NTC e pull-up a bordo:

- a ruptura do sensor frequentemente se parece com temperatura demasiado baixa ou `MINTEMP`;
- curto-circuito frequentemente se parece com temperatura demasiado alta ou `MAXTEMP`;
- mau contacto térmico pode causar `Heating failed` ou `Thermal runaway`;
- arrefecimento forte do bloco de aquecimento pode causar um erro porque a temperatura sobe muito lentamente ou não se mantém.

Os nomes de erros dependem do firmware, mas o significado é o mesmo: o controlador já não confia na temperatura ou vê que o aquecimento não está funcionando conforme esperado.

Não desactive a protecção térmica apenas para "verificar". Se a protecção dispara, primeiro procure a causa no sensor, fiação, montagem, aquecedor, configurações PID e arrefecimento.

## Contacto térmico

Um termistor funcionando electricamente não garante temperatura correcta.

O sensor deve transferir bem o calor da parte que está a medir.

Verifique:

- o sensor se senta completamente na manga ou furo;
- há abertura normal;
- nenhuma lacuna entre sensor e superfície;
- a pasta térmica não secou ou descascou se foi utilizada;
- os fixadores não estão soltos;
- o sensor não saiu do seu assento;
- os fios não estão a puxar o sensor para fora.

Mau contacto é perigoso porque o sensor lê temperatura inferior à realidade. O controlador continua a aquecer enquanto a parte real pode já estar sobraquecida.

## Mini-checklist

Antes do primeiro aquecimento:

- a resistência do termistor se parece conforme esperado;
- a resistência NTC diminui com o aquecimento dos dedos;
- nenhum circuito aberto ou curto-circuito;
- os fios não reagem com saltos quando se movem;
- o conector está inserido correctamente;
- o `sensor_type` correcto é escolhido no firmware;
- a temperatura na interface se parece com a temperatura da sala;
- o sensor está seguramente montado no local correcto;
- `min_temp` e `max_temp` estão definidos razoavelmente para o dispositivo.

## Erros comuns

- medir a resistência com a placa alimentada;
- não desconectar o sensor da placa e obter valores estranhos;
- confundir um termistor `100K` com outro tipo de sensor;
- escolher o `sensor_type` errado;
- ver `OL` e pensar que significa "100K";
- assumir que qualquer NTC 100K é idêntico;
- deixar o termistor solto próximo ao aquecedor;
- apertar demasiado um termistor de vidro com um parafuso;
- puxar o fio para que o sensor saia da manga;
- desactivar a protecção térmica em vez de corrigir a causa do erro.

## Pontos-chave

- A resistência é medida apenas em circuitos desenergizados.
- Um NTC 100K típico é cerca de `100 kOhm` a `25°C`.
- Quando aquecido, a resistência NTC diminui.
- `OL` normalmente significa circuito aberto, quase `0 Ohm` significa curto-circuito.
- O firmware deve ter o tipo de sensor correcto seleccionado.
- Bom contacto térmico é tão importante quanto fiação funcionante.
- Não inicie o aquecedor se as leituras de temperatura parecerem incorrectas.

## Leitura relacionada

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - official `sensor_type`, `sensor_pin`, `pullup_resistor` parameters and list of common thermistors.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - explanation of `MINTEMP`, `MAXTEMP`, and thermal runaway protection.
- [Marlin Troubleshooting: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - typical heating error causes: thermistor, slow temperature rise, thermal runaway.
- [RepRap Wiki: Thermistor](https://reprap.org/wiki/Thermistor) - basic description of NTC/PTC thermistors and room-temperature resistance checking.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - safe procedure for measuring resistance with a digital multimeter.
