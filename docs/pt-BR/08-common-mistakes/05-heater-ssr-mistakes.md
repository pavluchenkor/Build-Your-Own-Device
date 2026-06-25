# Erros de Aquecedor e SSR

O aquecedor é a carga mais perigosa em um simples dispositivo DIY.

Um ventilador pode não ligar. Um sensor pode fornecer leituras erradas. Mas um aquecedor com erro pode superaquecer o gabinete, derreter o plástico, danificar a fiação ou criar risco de incêndio.

Se o aparelho tiver 110-230V AC e você não entender de segurança elétrica, o correto é parar e pedir ajuda a um especialista.

## Symptoms

Dangerous signs:

- SSR heats up significantly;
- o aquecedor não desliga;
- a temperatura aumenta embora o comando esteja desligado;
- temperature rises too fast or unreasonably;
- sensor de temperatura mostra valor errado;
- terminal darkened;
- wire or connector heats up;
- breaker or fuse trips;
- caso cheire a plástico ou queimado;
- o dispositivo é perigoso ao toque;
- o aquecimento continua após erro do controlador.

Se o aquecedor não se comportar conforme o esperado, desligue a energia.

## AC SSR e DC SSR misturados

Os SSRs vêm para diferentes tipos de carga.

AC SSR é para corrente alternada. DC SSR é para corrente contínua.

Mistake:

- AC SSR put on DC heater;
- DC SSR put on 230V AC;
- comprei "SSR 40A" sem entender o que está escrito na caixa.

O tipo errado de SSR pode não desligar a carga ou funcionar perigosamente.

Antes de conectar verify:

- output type: AC or DC;
- allowed load voltage;
- allowed current;
- control input voltage;
- manufacturer connection diagram;
- é necessário dissipador de calor.

## SSR sem dissipador de calor

SSR heats up during operation.

Mesmo que o gabinete indique corrente grande, isso não significa que o relé irá lidar com isso sem dissipador de calor em um gabinete fechado.

Verifique:

- load current;
- voltage drop across SSR;
- dissipated power;
- heatsink requirements;
- Temperatura da caixa SSR após operação;
- is there airflow.

Se o SSR estiver tão quente que é difícil segurá-lo com a mão, este é um motivo para parar e descobrir.

## MOSFET for 110-230V AC

Módulos MOSFET regulares para Arduino/ESP32 são geralmente para cargas DC: 12V ou 24V.

Eles não podem ser usados como um simples interruptor para rede elétrica CA 110-230V.

Para carga da rede elétrica, você precisa de componentes diferentes, isolamento diferente, terminais diferentes, aterramento, fusíveis e compreensão de segurança elétrica.

Se não tiver certeza de que o módulo selecionado foi projetado para carga de rede elétrica, não o conecte à rede elétrica.

## No Fuse

Um fusível não torna o dispositivo totalmente seguro, mas limita as consequências de algumas falhas.

Bad ideas:

- “Vou adicionar mais tarde”;
- “a fonte de alimentação se protegerá”;
- "my heater is small";
- "se o fusível queimar vou colocar um maior".

O fusível é selecionado para o circuito, fiação e carga. Não pode ser aumentado só porque tropeça.

Se o fusível disparar, encontre a causa.

## No Independent Thermal Protection

O firmware e o sensor de temperatura não são a única proteção.

Para aquecedores, a proteção de hardware independente é útil:

- thermostat;
- thermal fuse;
- bimetallic switch;
- separate emergency heater power cutoff.

Essa proteção deve funcionar independentemente do controlador e do firmware.

Se o controlador travar, o pino travar no estado ligado, o SSR falhar ou o sensor for desconectado, a proteção do hardware poderá ser a última linha de defesa.

## Temperature Sensor Poorly Mounted

O aquecedor é controlado pelo feedback do sensor.

Se sensor:

- disconnected;
- poorly pressed;
- no lugar errado;
- has no thermal contact;
- mostra a temperatura do ar em vez do aquecedor;
- tipo errado selecionado no firmware;

o controlador pode continuar aquecendo porque detecta a temperatura errada.

O mau contato térmico é um dos erros mais perigosos nos sistemas de aquecimento.

## Potência errada do aquecedor

A potência do aquecedor deve ser calculada antes de conectar.

Exemplo:

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> about 1.3A
```

Para aquecedores potentes de baixa tensão, a corrente rapidamente se torna grande. Isso requer fios, terminais, MOSFET/SSR e fonte de alimentação adequados.

Para aquecedores de rede, a corrente é menor, mas o risco de choque é muito maior.

## Terminais e fios fracos

Um terminal que "meio que segura" pode aquecer sob corrente.

Reasons:

- poor contact;
- insulation clamped;
- wire too thin;
- terminal não classificado para corrente;
- fio trançado sem ponteira desgastada;
- parafuso afrouxado pelo calor e vibração.

Terminal escurecido, cheiro, aquecimento ou amolecimento de plástico ao redor são motivos para desligar o dispositivo.

## O que não fazer

Você não pode:

- hold open mains part under power;
- change wires under power;
- usar módulo Arduino MOSFET para 230V AC;
- utilize SSR sem dissipador de calor, se necessário;
- disable thermal protection;
- curto o termostato de emergência;
- aumentar o fusível “para não queimar”;
- deixe o aquecedor sem vigilância no primeiro teste;
- use montagem PLA perto do aquecedor.

## O que verificar

Antes do primeiro aquecimento:

1. Heater voltage.
2. Potência e corrente.
3. Power switch type: MOSFET, AC SSR, DC SSR, relay.
4. Current margin.
5. Dissipador de calor SSR ou MOSFET, se necessário.
6. Fuse.
7. Aterramento, se necessário.
8. Terminais e fios.
9. Temperature sensor mounting.
10. Corrija `sensor_type` no firmware.
11. `max_temp` e `max_temp`.
12. Independent thermal protection.
13. Comportamento quando o controlador está desligado.
14. Temperatura terminal e SSR após breve teste.

## Key Points

- O aquecedor não pode ser testado como uma pequena carga comum.
- AC SSR e DC SSR são dispositivos diferentes.
- SSR often requires heatsink.
- O módulo MOSFET para cargas CC não funciona para 110-230V CA.
- O sensor de temperatura deve ser montado firmemente no local correto.
- A proteção térmica do hardware deve ser independente do firmware.
- Se houver cheiro, aquecimento terminal ou comportamento incomum do aquecedor, desligue a energia.

## References

- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - official heater verification and temperature sensor checking by rise rate and accumulated error.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - checking thermistor, heating cartridge, fan, power, and wiring during thermal runaway.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`, `MAXTEMP`, and thermal protection as part of safety.
- [Sensata/Crydom SSR Heat Sink Selection](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - why SSR requires thermal calculation and heatsink at significant currents.
- [Omron: Solid State Relay Basics](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - basic information about SSR, application, heating, and differences from mechanical relays.
