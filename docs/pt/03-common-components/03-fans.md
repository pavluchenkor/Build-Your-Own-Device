---
title: "Ventoinhas e fluxo de ar num secador de filamento"
description: "Porque o fluxo de ar é importante num secador de filamento e numa câmara aquecida: escolha da ventoinha, caudal, pressão estática, ruído e aquecimento uniforme."
---

# Ventoinhas e fluxo de ar num secador de filamento

Uma ventoinha não serve apenas para mover ar: distribui calor, reduz pontos quentes e ajuda o filamento a secar de forma uniforme. Esta página ajuda a escolher a ventoinha e a perceber o efeito do fluxo de ar na caixa, aquecedor e sensor.

Um ventilador é um motor com um impulsor que movimenta o ar. Em dispositivos em torno de uma impressora 3D, você precisa dela não apenas para “soprar”, mas para empurrar o ar pela zona certa: um aquecedor, carretel, filtro, radiador, câmara ou compartimento eletrônico.

Ventiladores do mesmo tamanho podem funcionar de maneira muito diferente. Um empurra bem o ar em espaços abertos, outro empurra melhor o ar através de um filtro ou duto, um terceiro é mais silencioso, mas mais fraco sob resistência.

## Onde é usado

Em projetos do tipo iDryer, os ventiladores são usados para:

- circulação de ar dentro da secadora;
- transferir calor do aquecedor para a câmara;
- exaustão do ar da câmara da impressora;
- filtering through HEPA/carbon filter;
- cooling electronics;
- cooling a radiator;
- temperatura de nivelamento dentro do gabinete.

Para aquecimento da câmara, um ventilador é especialmente importante. O aquecedor libera calor e o fluxo de ar remove esse calor do elemento e o transporta ainda mais. Sem fluxo de ar adequado, o aquecedor pode superaquecer localmente enquanto a câmara aquece mal.

## Fluxo de ar e pressão estática

Na descrição técnica de um ventilador, normalmente você vê dois parâmetros importantes:

- fluxo de ar - geralmente em `m3/h` ou `m3/h`;
- pressão estática - geralmente em `Pa`, `inch H2O` ou `inch H2O`.

O fluxo de ar mostra quanto ar um ventilador pode bombear em condições ideais com pouca resistência.

A pressão estática mostra quão bem um ventilador pode empurrar o ar através da resistência: um filtro, grade, radiador, duto estreito ou tubo de ar longo.

Practical rule:

- para circulação aberta, o fluxo de ar é mais importante;
- para filtros, radiadores, grades e dutos densos, a pressão estática é mais importante;
- para um gabinete real, o ponto operacional é importante, não apenas o número máximo na especificação.

Se você colocar uma ventoinha silenciosa em um filtro denso, ela mal poderá empurrar o ar, mesmo que o fluxo de ar pareça forte em um espaço aberto.

## Ventiladores Axiais e Radiais

Um ventilador axial empurra o ar ao longo do eixo de rotação. Estes são ventiladores quadrados típicos `60x60`, `80x80`, `120x120 mm`, `120x120 mm`.

Um ventilador radial retira o ar lateralmente e o expele por uma saída estreita. Muitas vezes funciona melhor para dutos, bicos, filtros e locais onde é necessária pressão.

Para a livre circulação dentro de uma câmara, um ventilador axial geralmente é conveniente. Para um duto compacto, filtro ou fluxo direcionado, um ventilador radial às vezes é melhor.

## 2 pinos, 3 pinos e 4 pinos

Os ventiladores geralmente diferem no número de fios.

![3-pin connector on a computer fan](../../img/03-common-components/03-fan-3pin-connector.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Three-pin_connector_on_a_computer_fan.jpg), Dsimic, CC BY-SA 4.0*

2-pin:

- `+V`;
- `GND`.

Esse tipo de ventilador simplesmente obtém energia. Você pode controlar a velocidade alterando a tensão de alimentação ou PWM na linha de alimentação se a placa e o ventilador suportarem.

3-pin:

- `+V`;
- `GND`;
- tachometric signal (`tach`/`sense`).

O terceiro fio geralmente emite um sinal de velocidade. Ele não controla a velocidade por si só.

4-pin PWM:

- `GND`;
- `+V`;
- tachometric signal (`tach`/`sense`);
- PWM control signal.

Em um ventilador PWM de 4 pinos, a energia geralmente é fornecida constantemente e a velocidade é definida por uma linha PWM separada. Isso não é o mesmo que ligar e desligar rapidamente o ventilador.

## PWM e tacômetro

PWM é um sinal de controle que define a velocidade desejada. Ventiladores PWM de 4 pinos de computador normalmente têm uma frequência em torno de `25 kHz` e a energia permanece constante.

Se o fio PWM não estiver conectado, muitos ventiladores de 4 pinos funcionarão em velocidade máxima.

O sinal tacométrico mostra RPM. É necessário se o dispositivo compreender:

- se o ventilador está girando ou parado;
- se a velocidade corresponde ao comando;
- whether a filter or duct creates too much resistance;
- se o ventilador está preso.

O tacômetro não substitui o controle de temperatura. Em um dispositivo com aquecedor, você precisa monitorar a temperatura e o status do fluxo de ar se a falha do ventilador for perigosa.

## Tensão e Corrente

Antes de conectar, verifique:

- fan voltage: `5V`, `12V`, `24V`;
- operating current;
- startup current;
- connector type;
- pinout;
- whether it has PWM;
- whether it has a tachometer;
- operating temperature;
- airflow direction;
- noise level;
- vida útil e tipo de rolamento.

Você não pode alimentar um ventilador pelo GPIO do controlador. GPIO é um sinal, não uma saída de energia. A corrente do ventilador deve vir da fonte de alimentação, de uma saída de alimentação da placa ou de um módulo MOSFET.

Na inicialização, um ventilador pode extrair brevemente mais corrente do que na operação normal. Se vários ventiladores estiverem conectados a uma saída, suas correntes aumentam.

## Ruído, vibração e rolamento

O ruído depende de mais do que apenas RPM.

Sound is affected by:

- blade shape;
- balancing;
- bearing type;
- mounting;
- grill;
- duct;
- filter;
- enclosure resonance;
- multiple fans nearby.

As descrições técnicas listam ruídos no `dB(A)`, mas em um gabinete real a ventoinha pode soar diferente. Uma grade com geometria ruim, uma parede próxima ou uma montagem rígida em um painel fino pode tornar um bom ventilador barulhento.

Para um dispositivo que funciona por horas, é melhor escolher uma ventoinha não apenas pelo preço e tamanho, mas também pela vida útil, rolamento e temperatura.

## Temperatura e local de instalação

Um ventilador que funciona bem em uma bancada pode degradar-se rapidamente em uma câmara quente.

Verifique:

- fan operating temperature;
- temperatura do ar próximo ao aquecedor;
- distância do elemento de aquecimento;
- se o fluxo quente atinge diretamente o motor;
- se a montagem amolece;
- whether wires dry out;
- se o ventilador fica entupido com poeira ou fibras.

Se o ventilador for responsável pelo fluxo de ar do aquecedor, sua falha deverá ser considerada na lógica de segurança. Você não pode projetar um aquecedor de forma que um ventilador desligado crie imediatamente uma temperatura perigosa sem um desligamento de emergência.

## Filtros e Dutos

Um filtro, grelha e duto podem reduzir significativamente o fluxo de ar útil.

Sinais típicos:

- o ventilador está barulhento, mas o fluxo de ar é fraco;
- filter barely gets any air through;
- o ar desvia do filtro através das aberturas;
- a temperatura perto do aquecedor aumenta mais rapidamente que a temperatura da câmara;
- depois de montar a tampa, o fluxo de ar é pior do que na bancada.

Para filtrar uma câmara de forma eficaz, você não precisa apenas colocar um ventilador, mas também garantir a passagem do ar através do filtro. Se o ar achar mais fácil passar por uma lacuna, ele passará.

## O que verificar antes de comprar

Antes de comprar um ventilador, verifique:

- tamanho e espessura;
- voltage;
- current;
- type: axial or radial;
- airflow;
- static pressure;
- noise;
- RPM;
- bearing type;
- 2-pin/3-pin/4-pin;
- operating temperature;
- lifetime;
- airflow direction;
- conector e pinagem;
- whether it suits a filter, duct or free circulation.

Para filtro e duto estreito, não escolha um ventilador apenas por CFM. Observe a pressão estática e teste em montagem real.

## Erros típicos

- connected 12V fan to 24V;
- conectei uma ventoinha de 24V em 12V e pensei que estava quebrada;
- alimentando o ventilador do GPIO;
- não estabeleceu um terreno comum para MOSFET/PWM externo;
- não levou em conta a corrente de inicialização;
- conectou vários ventiladores a uma saída fraca;
- ventilador selecionado apenas por tamanho;
- instalou um ventilador de fluxo livre em um filtro denso;
- pense que o fio do tacômetro é um fio de controle;
- acho que PWM de 4 pinos é igual a 2 pinos;
- controlar o ventilador PWM de 4 pinos ligando/desligando;
- ventilador instalado em zona quente sem verificação de temperatura;
- não verifiquei o fluxo de ar após instalar a tampa, filtro e duto.

## Ponto Principal

Para a tarefa é escolhido um ventilador: circulação livre, filtro, duto, radiador, aquecedor ou resfriamento de eletrônicos. Para espaços abertos, o fluxo de ar é importante; para filtros e dutos, a pressão é importante.

Verifique tensão, corrente, tipo de fio, PWM/tacômetro, temperatura operacional e resistência real do sistema. Em um dispositivo com aquecedor, o ventilador deve fazer parte de um sistema térmico seguro e não um componente decorativo.

## Reference Materials

- [Noctua: Microcontroller guide for PWM and RPM monitoring](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - practical explanation of 4-pin PWM, tachometer, power and PWM frequency around 25 kHz.
- [Noctua: Fan pin configuration](https://www.noctua.at/faq-redirects/en/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-) - standard 4-pin fan pinout and behavior when only power is connected.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - explanation of airflow, static pressure, operating point and system resistance.
- [DigiKey: Selecting A Fan](https://www.digikey.ca/en/articles/selecting-a-fan) - fan type selection, fan curve, system resistance and difference between axial and radial fans.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - official Klipper sections for fans: `fan`, `heater_fan`, `temperature_fan`, `controller_fan` and `fan_generic`.
