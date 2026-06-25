---
title: "Aquecedores para secadores de filamento e câmaras aquecidas"
description: "Como escolher um aquecedor para secador de filamento ou câmara ativa de impressora 3D: 12V, 24V, rede elétrica, potência, controlo e segurança."
---

# Aquecedores para secadores de filamento e câmaras aquecidas

O aquecedor define a velocidade de aquecimento e os limites de segurança do secador ou da câmara. Esta página explica tipos de aquecedores, potência, controlo por MOSFET ou SSR e erros que podem causar sobreaquecimento.

Um aquecedor é uma carga que converte energia elétrica em calor. Em um dispositivo DIY simples, este é o componente mais perigoso: um erro em um ventilador geralmente resulta em fluxo de ar insuficiente, mas um erro no aquecedor pode causar superaquecimento, invólucro derretido, fiação danificada ou risco de incêndio.

Em impressoras 3D e dispositivos semelhantes ao iDryer, os aquecedores são encontrados no hotend, na cama, na câmara, no secador de filamento, no duto de ar ou no módulo de aquecimento separado.

## Onde é usado

Tarefas típicas:

- aquecer o hotend;
- aquecer a cama;
- pré-aquecer a câmara da impressora;
- drying filament;
- pré-aquecer o ar antes de um filtro ou duto;
- manter a temperatura em um pequeno volume de processo.

Estas são tarefas diferentes. Um aquecedor para um hotend de metal, uma almofada de silicone e um módulo PTC de ar não são intercambiáveis ​​sem recalcular a potência, montagem, fluxo de ar e proteção.

## Types of Heaters

Opções comuns:

- cartridge heater;
- silicone pad;
- PTC heater;
- ceramic heating element;
- ready-made fan heater module;
- heating plate;
- mains heating bed;
- nicromo ou montagem resistiva em um invólucro acabado.

Um aquecedor de cartucho geralmente é inserido em um bloco de metal. Ele precisa de um bom contato térmico com o metal e uma montagem confiável do sensor de temperatura.

Uma almofada de silicone geralmente é colada ou pressionada em uma superfície plana. Necessita de superfície plana, boa aderência, sensor de temperatura e proteção contra descamação.

Um aquecedor PTC limita parcialmente o aumento da temperatura devido às suas propriedades, mas isso não substitui o controlador, o sensor, o fusível, o invólucro e a verificação do fluxo de ar. O PTC não torna um dispositivo seguro automaticamente.

Um módulo de aquecedor com ventilador pronto combina aquecedor e fluxo de ar, mas ainda precisa ser verificado quanto a tensão, potência, temperatura, materiais da caixa e proteção de emergência.

## Tensão, Potência e Corrente

Antes de conectar, você precisa encontrar:

- operating voltage;
- power;
- current;
- current type: DC or AC;
- maximum temperature;
- wire operating temperature;
- mounting method;
- airflow requirements;
- allowed control method.

A corrente é calculada pela fórmula:

```text
current = power / voltage
```

Exemplos:

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> about 1.3A
```

Um aquecedor de baixa tensão e alta potência é mais seguro para tensão, mas requer grandes correntes. Grandes correntes requerem fonte de alimentação, fios, terminais, MOSFET/SSR e fusível adequados.

Um aquecedor principal no `110-230V AC` pode fornecer alta potência com corrente mais baixa, mas o risco de choque é muito maior. Para a parte principal você precisa de conhecimentos de segurança elétrica, gabinete, terminais, isolamento, aterramento quando necessário, fusíveis e isolamento galvânico de controle.

## Heater Control

O controlador não deve alimentar o aquecedor diretamente do GPIO. GPIO fornece apenas um sinal de controle.

Opções típicas de controle de energia:

- MOSFET - para aquecedores DC `24V`/`24V`;
- DC SSR - para aquecedores DC, se devidamente classificados para DC;
- AC SSR - para aquecedores de rede AC;
- relé mecânico - para liga/desliga raro, mas não para PID/PWM frequente;
- saída de energia pronta - somente se classificada para a corrente e tensão necessárias.

AC SSR e DC SSR são dispositivos diferentes. O tipo errado pode não desligar o aquecedor ou funcionar de forma insegura.

Um módulo MOSFET típico para Arduino/ESP32 não pode ser usado como um switch `110-230V AC`. Se o módulo não for projetado para carga de rede elétrica, ele não poderá ser conectado à rede elétrica.

## Layers of Safety

Um aquecedor não pode ser projetado como "o controlador liga - o controlador desliga". Você precisa de várias camadas de proteção.

![Layers of safe heater control](../../img/03-common-components/02-heater-safety-stack.svg)

Minimum logic:

- a fonte de alimentação é classificada para a corrente;
- o fusível é selecionado para fiação e carga;
- o interruptor liga/desliga corresponde ao tipo de carga;
- o sensor de temperatura está montado no lugar certo;
- firmware possui `max_temp`, `max_temp` e verificação de aquecimento;
- existe proteção térmica de hardware independente: fusível térmico, termostato ou chave bimetálica;
- o invólucro e os materiais suportam a temperatura real;
- o primeiro teste é feito sob supervisão.

A proteção térmica do hardware deve funcionar independentemente do controlador. No caso simples, ele é colocado em série no circuito de alimentação do aquecedor para interromper fisicamente a alimentação. Este não é apenas mais um sensor para o firmware.

Se o controlador travar, o sensor cair, um MOSFET entrar em curto ou um SSR travar, a proteção deverá interromper a alimentação do aquecedor.

## Temperature Sensor

Um aquecedor não conhece sua própria temperatura. O controlador toma a decisão com base no sensor.

Se o sensor:

- is pressed poorly;
- está no local errado;
- falls off;
- é o tipo errado no firmware;
- has poor thermal contact;
- mede o ar em vez da parte crítica;

o controlador pode continuar aquecendo mesmo que a temperatura real já seja perigosa.

Para um hotend, o contato do sensor de temperatura com o bloco de metal é importante. Para um aquecedor de ar, é importante entender o que está sendo medido: a temperatura do elemento, a temperatura do ar após o elemento, a temperatura da câmara ou a temperatura próxima ao carretel. Esses são pontos diferentes e podem diferir significativamente.

## Fluxo de ar e transferência de calor

Um aquecedor libera energia, mas essa energia deve ir com segurança para onde pretendido.

Para um aquecedor de ar, o fluxo de ar é crítico:

- sem fluxo, o elemento pode superaquecer localmente;
- weak ventilation doesn't remove heat;
- a clogged filter changes heating mode;
- plastic ducting can soften;
- um sensor de temperatura pode não ver o que está acontecendo no elemento.

Para um aquecedor de câmara, é importante verificar não apenas a temperatura alvo do ar, mas também a temperatura próxima ao aquecedor, fios, SSR/MOSFET, terminais e peças plásticas.

## Fios, Terminais e Conectores

Um aquecedor geralmente funciona por longos períodos e consome uma corrente significativa. O mau contato se torna uma fonte de calor.

Verifique:

- wire gauge;
- insulation temperature class;
- terminal current rating;
- crimp quality;
- screw tightness;
- ponteiras em fios trançados;
- strain relief;
- distância das partes quentes;
- ausência de condutores expostos.

Se um terminal escurecer, cheirar mal, amolecer o plástico ou ficar quente, a energia deverá ser desligada e a causa encontrada. Não basta aumentar o fusível ou apertá-lo mais tarde.

## O que verificar antes de comprar

Antes de comprar um aquecedor, verifique:

- que meio deve aquecer: metal, ar, cama, câmara;
- tipo de tensão e corrente;
- power;
- current;
- operating temperature;
- maximum surface temperature;
- airflow requirements;
- mounting method;
- fio e material de isolamento;
- compatible power switch;
- local para sensor de temperatura;
- local para proteção térmica independente;
- invólucro e materiais circundantes;
- disponibilidade de descrição técnica ou documentação clara.

Se a página do produto não tiver informações sobre tensão, potência, temperatura e aplicação, esse aquecedor não é adequado para um primeiro projeto seguro.

## Primeiro teste

O primeiro aquecimento é feito brevemente e sob supervisão.

Procedure:

1. Verifique a resistência do aquecedor e compare com o cálculo `R = U^2 / P` se a tensão e a potência forem conhecidas.
2. Verifique se há curto-circuitos, quando aplicável.
3. Se houver um invólucro de metal ou aterramento de proteção `PE`, verifique se o aquecedor não está em curto com o invólucro.
4. Verifique a tensão de alimentação sem o aquecedor.
5. Verifique se a chave de controle desliga a carga.
6. Verifique se o sensor de temperatura lê um valor razoável.
7. Para o aquecedor `24V`/`24V`, se possível, inicie através de uma fonte de alimentação de laboratório com limitação de corrente ou fusível temporário.
8. Enable heating at low power or briefly.
9. Observe se a temperatura sobe no lugar certo.
10. Verifique se o comando de desligamento realmente interrompe o aquecimento.
11. Verifique o aquecimento dos fios, terminais, MOSFET/SSR e gabinete.
12. Verifique a proteção de emergência por meio de um cenário que você possa simular com segurança.

Não deixe um novo aquecedor sem supervisão na primeira inicialização.

## Erros típicos

- aquecedor conectado à tensão errada;
- didn't calculate current;
- powering heater through weak connector;
- usando MOSFET para aquecedor CA;
- confundiu AC SSR e DC SSR;
- instalou SSR sem dissipador de calor quando necessário;
- forgot fuse;
- no independent thermal protection;
- poor temperature sensor mounting;
- gabinete feito de PLA próximo ao aquecedor;
- não levou em conta o fluxo de ar e o filtro entupido;
- testado em bancada, mas não em gabinete;
- left mains part exposed;
- aumentou o fusível em vez de descobrir por que ele disparou.

## Ponto Principal

Um aquecedor é escolhido de acordo com a tarefa, tensão, potência, método de transferência de calor e segurança. Você não pode tratá-lo como uma simples “carga de dois fios”.

Primeiro calcule a corrente, selecione o interruptor de alimentação, a fiação e o fusível. Em seguida, garanta sensor de temperatura, proteção de firmware, proteção térmica de hardware independente, um gabinete adequado e testes no mundo real.

## Reference Materials

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - heater settings, temperature sensors, `min_temp`, `max_temp` and heating verification in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - temperature limits, `MINTEMP`, `MAXTEMP` and thermal protection in Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - basic explanation of SSR, types, application and thermal measures.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - why SSR needs a heatsink and how thermal regime relates to load current.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - practical notes on cartridge heater application, thermal contact and power selection.
