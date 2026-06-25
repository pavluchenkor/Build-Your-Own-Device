# Lista de Verificação de Diagnóstico

Esta lista de verificação é necessária quando o dispositivo não funciona ou se comporta de maneira estranha.

A ideia é simples: primeiro elimine o perigo, depois verifique a alimentação e a fiação e só depois passe para o firmware, sensores e cargas.

## 1. Pare e desligue a energia

Primeiro, desligue o dispositivo.

Especialmente se houver:

- smell;
- wire heating;
- terminal heating;
- smoke;
- strange sound;
- sparking;
- o aquecedor não desliga;
- breaker or fuse trips.

Não troque os fios sob alimentação.

## 2. Disconnect Power Load

Antes do diagnóstico, é melhor desconectar temporariamente:

- heater;
- powerful LED strip;
- servo;
- motor;
- external power load.

Primeiro verifique se o controlador e a lógica estão ativos sem carga perigosa.

Se o dispositivo tiver 110-230 V CA, não mantenha a parte da rede elétrica aberta sob alimentação na bancada.

## 3. Verifique a fonte de alimentação

Com verificação do multímetro:

- existe tensão na saída da fonte de alimentação;
- is voltage correct;
- is polarity correct;
- a tensão cai sob carga.

Por exemplo:

- A linha de 24 V deve ser de cerca de 24 V;
- A linha de 12V deve ser de cerca de 12V;
- A linha de 5V deve ser de cerca de 5V;
- A linha de 3,3 V deve ser de cerca de 3,3 V.

O desvio aceitável depende da fonte de alimentação e do dispositivo, mas um erro óbvio como 24V em vez de 12V deve ser encontrado antes de conectar a carga.

## 4. Verifique a polaridade

Verifique onde estão mais e menos.

Não confie apenas na cor do fio.

Verifique:

- board markings;
- power supply markings;
- module pinout;
- multimeter;
- connection diagram.

Reversed polarity often kills module instantly.

## 5. Verifique o GND comum

Se houver módulo externo ou alimentação separada, verifique `GND` comum.

Isto é importante para:

- MOSFET module;
- servo;
- PWM fan;
- HX711;
- RFID;
- external sensors;
- separate DC-DC.

Se os sinais passarem entre dispositivos, eles deverão ter um nível de referência comum, a menos que o circuito utilize isolamento especial.

## 6. Verifique os terminais e conectores

Inspect:

- fio inserido até o fim;
- condutor preso, não isolante;
- no exposed strands;
- no darkening;
- no smell;
- terminal não treme;
- o conector não se sustenta "pela fé";
- a tampa da caixa não comprime o fio.

Mova os fios com a energia desligada. Se o contato cair claramente mecanicamente, conserte a fiação primeiro.

## 7. Verifique o controlador sem carga

Conecte o controlador sem carga de energia.

Verifique:

- is it detected via USB;
- o firmware inicia;
- há comunicação com o anfitrião;
- o microcontrolador não aquece;
- a energia não pisca;
- are logs visible.

Se o controlador não for detectado mesmo sem carga, não reconecte o aquecedor e os módulos de energia até encontrar a causa.

## 8. Verifique o firmware e a configuração

Verifique:

- firmware construído para placa correta;
- correct serial/CAN/USB path selected;
- pinos na configuração correspondem à pinagem;
- `sensor_type` correct;
- `max_temp` e `max_temp` razoáveis;
- saídas não invertidas acidentalmente;
- no pin conflicts.

Se o aquecedor se comportar de maneira oposta após a alteração da configuração, por exemplo, "desligado", mas a temperatura subir, desligue a energia e verifique a configuração e o circuito de energia.

## 9. Verifique os sensores

Antes de aquecer, verifique os sensores.

Para termistor:

- temperature like room temperature;
- no `MINTEMP`;
- no `MAXTEMP`;
- readings do not jump;
- resistance like expected;
- quando aquecido manualmente, as leituras mudam corretamente.

Para outros sensores:

- power correct;
- interface selected correctly;
- address or pins match config;
- fios curtos e não pendurados.

## 10. Verifique a saída sem carga

Se for necessário verificar o MOSFET, o relé ou a saída da placa, faça-o primeiro sem carga perigosa.

Options:

- small test fan;
- LED com resistor;
- multimeter;
- carga segura fraca.

Não inicie o diagnóstico com um aquecedor potente.

Para o aquecedor, antes de ligar pela primeira vez, a verificação numérica é útil: meça a resistência e compare com o `PE` esperado. Se houver caixa de metal ou `12V`, verifique se não há curto com a caixa. Para o aquecedor `24V`/`24V`, a primeira operação é melhor através da fonte de alimentação do laboratório com limite de corrente ou fusível temporário.

## 11. Verifique a chave de potência separadamente

Para verificação de MOSFET/SSR/relé:

- correct load type: AC or DC;
- correct voltage;
- correct terminals;
- control input;
- `GND` comum, se necessário;
- dissipador de calor, se necessário;
- entrada e saída não misturadas.

AC SSR e DC SSR não podem ser trocados.

Para SSR, verifique separadamente o estado "desligado": com o sinal de controle removido, a carga não deve aquecer. Primeiro, é melhor usar uma carga pequena e segura, uma lâmpada ou um multímetro, e não o aquecedor principal.

## 12. Conecte a carga com um breve teste

Quando as verificações básicas forem aprovadas, conecte a carga brevemente e sob supervisão.

Verifique:

- load turns on;
- load turns off;
- terminals do not heat;
- wires do not heat;
- MOSFET/SSR não superaquece;
- sensor shows realistic temperature;
- o controlador não reinicia;
- fusível não desarma.

O primeiro teste do aquecedor não deve ser longo e desacompanhado.

## 13. Verifique após alguns minutos de operação

Após alguns minutos, verifique:

- terminals;
- wires;
- power supply;
- MOSFET;
- SSR;
- case near heater;
- sensor readings;
- controller stability.

Se algo esquentar inesperadamente, desligue a energia e volte a verificar a energia, a fiação e o interruptor de energia.

## O que não fazer

Você não pode:

- ligue o dispositivo repetidamente se algo aquecer ou cheirar mal;
- mantenha 110-230 V CA aberto na bancada;
- change wires under power;
- aumentar o fusível “para não queimar”;
- desabilitar a proteção térmica para testes;
- short emergency thermostat;
- teste um aquecedor potente sem sensor de temperatura;
- deixe o primeiro teste sem supervisão.

## Short Order

Se você precisar de um pedido muito curto:

1. Turn off power.
2. Disconnect power load.
3. Verifique a tensão da fonte de alimentação.
4. Verifique a polaridade.
5. Verifique o `GND` comum.
6. Verifique terminais e fios.
7. Verifique o controlador sem carga.
8. Verifique o firmware e a pinagem.
9. Verifique os sensores.
10. Verifique a saída sem carga perigosa.
11. Verifique MOSFET/SSR/relé.
12. Conecte a carga com um breve teste.
13. Verifique o aquecimento dos fios, terminais e peças de alimentação.

## Key Points

- O diagnóstico começa desligando a energia e reduzindo o risco.
- É melhor desconectar a carga de energia para verificações básicas.
- Alimentação, polaridade, `GND` e terminais verificados antes do firmware.
- O aquecedor não pode ser usado como primeiro indicador de teste.
- Se a proteção for acionada, encontre a causa e não desative a proteção.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic sequence of checking connections, power, and hardware problems.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - how to think about voltage, current, and project power.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - safe resistance measurement on de-energized circuit.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - practical checks of thermistor, heater, fan, power, and wiring.
- [Klipper Configuration Reference: min_temp, max_temp and verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - software checks of temperature, sensor, and expected heater temperature rise.
