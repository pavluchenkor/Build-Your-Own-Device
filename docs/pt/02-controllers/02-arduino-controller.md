# Controlador Arduino

Arduino não é um microcontrolador específico, mas um ecossistema de placas, bibliotecas, exemplos e ambiente de desenvolvimento. Quando um iniciante diz “Arduino”, geralmente se refere a Arduino Uno, Nano ou uma placa compatível baseada em ATmega328P.

Para a educação, o Arduino ainda é muito útil: é fácil de entender GPIO, botões, LEDs, PWM, entrada analógica, I2C, SPI e sensores simples. Mas para um novo dispositivo em torno de uma impressora 3D, o Arduino Uno/Nano nem sempre é a melhor escolha.

## Por que o Arduino é popular

Strengths of Arduino:

- muitos materiais educativos;
- IDE Arduino simples;
- many ready-made libraries;
- understandable examples like Blink;
- conveniente testar rapidamente um sensor na mesa;
- fácil de encontrar módulos compatíveis;
- placas antigas estão bem documentadas.

Se o objetivo é entender o básico dos microcontroladores, o Arduino é bom. Ele reduz a barreira de entrada e permite que você veja os resultados rapidamente.

## Arduino as an educational board

Arduino é conveniente para:

- testing a button, limit switch, or sensor;
- teste simples de termistor através de um divisor de tensão;
- testing I2C OLED;
- testing SPI RFID module;
- gerando PWM para um pequeno teste;
- reading analog voltage;
- experimentos rápidos em uma placa de ensaio.

Neste modo, o Arduino é uma excelente ferramenta de laboratório. Você não precisa construir um dispositivo final nele: você pode primeiro entender o circuito e o sensor e depois transferir a solução para ESP32, RP2040, STM32 ou uma placa de impressora.

## Uno e Nano em poucas palavras

Os clássicos Arduino Uno e Nano são geralmente baseados em ATmega328P.

Características típicas:

- `5V` logic;
- 16 MHz clock;
- 32 KB flash memory;
- 2 KB SRAM;
- 14 digital pins;
- 6 pinos PWM na classe Uno/Nano;
- 6 entradas analógicas no Uno, 8 no Nano;
- USB para piscar e alimentar a placa.

Isso é suficiente para esboços educacionais e tarefas autônomas simples, mas não o suficiente para lógica complexa, redes, interface web, grandes bibliotecas e integração conveniente com sistemas modernos.

## Original, clone e compatível com Arduino

Você precisa distinguir:

- original Arduino boards;
- cheap Uno/Nano clones;
- Placas compatíveis com Arduino baseadas em outros microcontroladores;
- placas Arduino modernas com Wi-Fi, USB-C, chips Arm e outras lógicas.

Um clone Nano por alguns dólares pode ser adequado para experimentos, mas a qualidade do USB-UART, do regulador, da soldagem e do bootloader pode variar. Às vezes, para um clone Nano no Arduino IDE, você precisa selecionar um bootloader antigo ou um processador diferente.

Se o dispositivo precisar funcionar por muito tempo sem supervisão, a qualidade da placa, o regulador, os conectores e a documentação são mais importantes do que o preço mais baixo.

## 5V logic

O antigo Arduino Uno/Nano usa a lógica `5V`.

Isto é conveniente com alguns módulos antigos, mas perigoso para dispositivos `3.3V`:

- ESP32 geralmente não tolera `5V` no GPIO;
- muitos módulos OLED, RFID, sensores e rádio são projetados para `3.3V`;
- Pull-ups I2C para `3.3V` podem danificar um dispositivo `3.3V`;
- algumas entradas do módulo são compatíveis com `5V`, mas isso precisa ser verificado na documentação.

Se o Arduino estiver conectado a um módulo `3.3V`, você precisará de um conversor de nível ou de um circuito onde os níveis sejam compatíveis.

## GPIO não alimenta cargas

Um pino do Arduino pode acender um LED através de um resistor ou fornecer um sinal de controle. Ele não deve alimentar diretamente um ventilador, aquecedor, servo, relé ou faixa de LED.

Circuito típico:

![Arduino Uno Rev3 with ATmega328P microcontroller](../../img/02-controllers/02-arduino-uno-rev3.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg), HonCode, CC0 Public Domain*

Para cargas você precisa de:

- MOSFET ou driver para ventilador DC, faixa de LED ou aquecedor DC;
- driver de transistor e diodo de proteção para bobina de relé;
- SSR ou relé para carga de rede AC;
- alimentação separada para servo;
- GND comum quando exigido pelo circuito de baixa tensão.

GPIO é um comando, não uma saída de energia.

## PWM e gravação analógica

No Arduino, `analogWrite()` em Uno/Nano geralmente significa PWM, não uma saída analógica verdadeira. A placa liga e desliga rapidamente o pino, alterando o ciclo de trabalho do sinal.

Isto é adequado para:

- LED brightness;
- entrada de controle para um driver;
- PWM simples para ventilador ou módulo MOSFET;
- educational experiments.

Mas existem limitações:

- O PWM não está disponível em todos os pinos;
- A frequência PWM é fixa ou muda de maneiras não óbvias;
- `analogRead()` e `analogRead()` são coisas diferentes;
- uma ventoinha de PC de 4 pinos pode exigir uma frequência diferente e uma abordagem adequada de coletor aberto/dreno aberto;
- aquecedores e SSRs não podem simplesmente usar qualquer PWM rápido sem entender a seção de potência.

## Analog inputs

Arduino Uno/Nano é conveniente para medições analógicas simples:

- potentiometer;
- thermistor via voltage divider;
- light sensor;
- sensor de tensão simples via divisor de tensão.

Mas uma entrada analógica não deve ver tensão acima de sua faixa segura. Para Uno/Nano este é geralmente o intervalo relativo à potência `AREF` ou `AREF` selecionado. Se estiver medindo tensões mais altas, você precisará de um divisor e proteção.

Para medições precisas de temperatura, você não precisa apenas do `analogRead()`, mas também de:

- correct voltage divider circuit;
- valor do resistor;
- thermistor table or Beta parameter;
- stable power/reference voltage;
- noise filtering;
- contato do sensor mecânico com o objeto.

## Arduino e Klipper

Algumas placas AVR antigas podem ser encontradas historicamente perto de impressoras 3D, mas para um novo dispositivo em torno do Klipper é melhor não começar com Uno/Nano.

Reasons:

- limited memory;
- weak performance;
- A lógica de 5V pode interferir nos módulos `3.3V` modernos;
- nenhuma rede sem módulos adicionais;
- não é o caminho mais prático para um novo Klipper MCU.

Se você precisar de um MCU adicional para o Klipper, geralmente é mais prático procurar RP2040, STM32 ou uma placa de impressora 3D pronta. O Arduino pode ser mantido para educação, breadboard e teste de sensores individuais.

## Quando o Arduino ainda é apropriado

Arduino é apropriado se:

- você precisa testar uma ideia rapidamente;
- você precisa explicar como algo funciona;
- o dispositivo é muito simples e não precisa de rede;
- you already have a working sketch;
- a clareza é mais importante que a compactação e o desempenho;
- esta é uma bancada educacional, não uma eletrônica de potência final.

Arduino não é uma boa escolha se:

- você precisa de Wi-Fi pronto para uso;
- você precisa de forte integração com o Klipper;
- você precisa de muita memória;
- you need many modern `3.3V` sensors;
- o dispositivo deve ser compacto, de longa duração e industrialmente limpo;
- existe uma seção de alimentação com aquecedor onde proteções independentes são importantes.

## O que verificar antes de comprar

Antes de comprar uma placa compatível com Arduino, verifique:

- se é uma placa original, clone ou compatível;
- qual microcontrolador está instalado;
- `5V` or `3.3V` logic;
- qual chip USB-UART é usado;
- se existe um driver para o seu computador;
- qual bootloader é necessário;
- quanto flash e SRAM;
- quantas entradas PWM e analógicas;
- se existe esquema e pinagem;
- qualidade do regulador de potência e conectores;
- se o quadro é adequado para a tarefa final.

## Erros comuns

- pensar que o Arduino é uma placa específica;
- conectando `3.3V` Arduino diretamente ao módulo `3.3V`;
- alimentando uma carga do GPIO;
- alimentar um servo a partir do pino `5V` e obter redefinições;
- usando `analogWrite()` como uma verdadeira saída analógica;
- selecionando o bootloader errado para um clone Nano;
- não instalar driver para USB-UART;
- tentando construir um dispositivo de rede moderno no Uno sem motivo;
- transferir uma placa de ensaio educacional para um dispositivo de energia fechado sem refazer a energia, a fiação e a proteção.

## Pontos principais

Arduino é um bom ecossistema educacional e uma ferramenta conveniente para testes rápidos. É ótimo para entender GPIO, PWM, ADC e sensores.

Mas os clássicos Uno/Nano são placas `5V` antigas com memória limitada e sem rede. Para um novo dispositivo em torno de uma impressora 3D, ESP32, RP2040, STM32 ou uma placa de impressora pronta costuma ser mais prática, deixando o Arduino como uma ferramenta educacional e de diagnóstico.

## Related materials

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — official Uno R3 specifications: ATmega328P, `5V`, pins, PWM, analog inputs, and board resources.
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — table with voltage, GPIO current, memory, frequency, and board dimensions.
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — Nano specifications, power, memory, digital and analog pins.
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — why Nano and Nano clones may have different bootloaders.
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — official reference for `pinMode`, `digitalWrite`, `analogRead`, `analogWrite`, PWM, and basic functions.
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — list of PWM pins for popular boards and limitations of `analogWrite()`.
