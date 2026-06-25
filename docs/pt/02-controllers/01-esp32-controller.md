# Controlador ESP32

ESP32 é uma família de microcontroladores Espressif com Wi-Fi, Bluetooth e um grande conjunto de periféricos. Em dispositivos DIY, é frequentemente escolhido quando precisa construir um módulo autónomo: liga-se à rede por si próprio, lê sensores, mostra uma página num navegador e controla saídas simples.

Para dispositivos em torno de uma impressora 3D, ESP32 é útil não como "outra placa de potência", mas como um pequeno controlador em rede: um sensor de temperatura/humidade, um módulo de ventilação, um filtro simples com interface web, monitorização de câmara separada ou um secador autónomo.

## Onde ESP32 é útil

Tarefas típicas:

- sensor de temperatura e humidade Wi-Fi;
- controlador de ventilador separado via módulo MOSFET;
- controlo de relé ou SSR com sinal de baixa tensão;
- ecrã OLED sobre I2C;
- leitor RFID/NFC sobre SPI ou UART;
- servo com potência separada;
- página web simples para estado e configurações;
- integração com MQTT, Home Assistant ou sua própria lógica local;
- protótipo autónomo que não precisa fazer parte de Klipper.

ESP32 é bom quando o dispositivo deve funcionar separadamente da impressora e trocar dados através da rede. Se a tarefa é simplesmente adicionar pinos a Klipper, é normalmente melhor procurar RP2040, STM32 ou uma placa de impressora pré-fabricada.

## Arquitetura típica de dispositivo

ESP32 não alimenta cargas diretamente. Produz sinais de controlo e módulos separados fazem o trabalho de potência.

![Placa de desenvolvimento ESP32 com pinos GPIO](../../img/02-controllers/01-esp32-dev-board.jpg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg), Edwiyanto, CC BY-SA 4.0*

Na prática, isto parece:

- ESP32 é alimentado a partir de USB ou `5V` estável na placa de desenvolvimento;
- a lógica ESP32 em si funciona em `3.3V`;
- sensores estão ligados a GPIO, I2C, SPI, UART ou ADC;
- ventiladores, fitas LED, aquecedores DC estão ligados via MOSFET ou driver;
- aquecedores de rede estão ligados apenas através de um SSR/relé AC apropriado e uma secção de potência segura;
- servo é alimentado a partir de uma fonte `5V/6V` separada, e ESP32 fornece apenas o sinal.

GPIO não é uma fonte de potência para uma carga. Um pino pode comutar a entrada do driver, mas não deve alimentar um ventilador, aquecedor, relé, servo ou fita LED diretamente.

## O que ESP32 significa numa placa

O rótulo "ESP32" pode significar diferentes coisas:

- o chip ESP32 em si;
- um módulo com o chip, memória flash e antena, como ESP32-WROOM;
- uma placa de desenvolvimento com USB, regulador de potência, botões e pinos expostos;
- variantes mais recentes: ESP32-S3, ESP32-C3, ESP32-C6 e outros.

Para um primeiro projeto, é mais conveniente usar uma placa de desenvolvimento do que um módulo simples. Uma placa de desenvolvimento já tem USB, um regulador de potência, botões `BOOT`/`EN` e pinos para breadboarding.

Antes de comprar, verifique:

- o nome exato da placa e chip;
- se tem USB-C ou micro-USB;
- qual USB-UART ou USB incorporado é utilizado;
- se há um esquema e pinout;
- quais GPIO estão realmente expostos;
- qual regulador de potência está na placa;
- se tem uma antena apropriada e espaço em torno dela;
- se o tamanho da placa se encaixa no seu enclosure.

## Lógica 3.3V

ESP32 funciona com lógica `3.3V`. Isto significa que um nível `HIGH` típico em GPIO é cerca de `3.3V`, não `5V`.

O que importa:

- não aplique `5V` ao GPIO do ESP32;
- para sensores e módulos `5V`, pode precisar de um conversor de nível;
- as pull-ups I2C devem ir para `3.3V` se o barramento está ligado a ESP32;
- alguns módulos MOSFET/SSR pré-fabricados podem não funcionar de forma fiável a partir de `3.3V`;
- a potência de carga não pode ser tirada do GPIO.

Muitos sensores já estão disponíveis em variantes `3.3V`. Para ESP32, esta é a melhor escolha.

## Potência

As placas de desenvolvimento normalmente têm uma entrada USB e um pino `5V`/`VIN`, e o ESP32 em si é alimentado por um regulador `3.3V`.

Erros comuns:

- alimentar ESP32 a partir de um cabo USB fraco;
- alimentar um servo, ventilador ou relé a partir do pino `3.3V` na placa;
- ligar uma carga pesada ao pino `5V` sem compreender de onde vem essa corrente;
- não ligar GND comum entre ESP32 e o driver de baixa tensão;
- ESP32 reinicia quando Wi-Fi começa devido a queda de potência.

Wi-Fi drena corrente pulsada. Para funcionamento estável, um bom cabo, regulador, capacitores na placa e potência separada para cargas são importantes.

## GPIO e pinos especiais

ESP32 tem muitos GPIO, mas nem cada pino é igualmente conveniente.

No ESP32 clássico:

- alguns pinos estão ligados ao carregamento de chip, estes são pinos de amarração;
- `GPIO6-GPIO11` normalmente estão ocupados por memória flash e não são utilizados;
- `GPIO34-GPIO39` são apenas entrada;
- `GPIO1` e `GPIO3` são frequentemente utilizados como UART para firmware e registos;
- alguns pinos podem ser ocupados por LED, botão ou outros circuitos numa placa de desenvolvimento específica.

Os pinos de amarração determinam o modo de arranque na inicialização. Se circuitos externos puxarem tal pino da forma errada, ESP32 pode não arrancar ou pode entrar no modo de atualização de firmware.

Regra prática: para a primeira versão, use pinos do pinout de sua placa específica e evite pinos marcados `FLASH`, `STRAP`, `TX0`, `RX0`, `GPIO6-GPIO11`, `GPIO6-GPIO11` a menos que compreenda seu papel.

## ADC em ESP32

ESP32 pode medir tensão analógica através de ADC, mas não é um multímetro de laboratório.

O que importa:

- no ESP32 clássico há ADC1 e ADC2;
- ADC2 entra em conflito com Wi-Fi, portanto para um dispositivo Wi-Fi é melhor usar pinos ADC1;
- o intervalo de medição depende da definição de atenuação;
- a medição pode exigir calibração;
- não pode aplicar tensão acima do nível seguro do GPIO ao ADC;
- um termistor normalmente precisa de um divisor de tensão e a tabela/modelo correto no firmware.

Se precisar de um sensor de temperatura preciso, é frequentemente mais simples usar um sensor digital ou um módulo pré-fabricado com uma biblioteca conhecida. Para um termistor NTC, ESP32 funciona, mas o circuito e as definições de ADC devem ser verificadas.

## PWM, I2C, SPI e UART

ESP32 é conveniente para periféricos:

- PWM via LEDC é adequado para ventiladores, iluminação de fundo e sinais de servo;
- I2C é adequado para ecrãs OLED e muitos sensores;
- SPI é adequado para módulos RFID, ecrãs e dispositivos rápidos;
- UART é adequado para GPS, alguns sensores, outros controladores e depuração.

ESP32 tem uma matriz de GPIO flexível: muitos sinais podem ser atribuídos a diferentes pinos. Mas isto não significa que qualquer pino é sempre uma boa escolha. Limitações específicas de placa, memória flash, pinos de arranque e UART ocupado ainda precisam de ser considerados.

## ESP32 e Klipper

ESP32 é melhor visto como um dispositivo Wi-Fi/IoT separado perto da impressora, não como o caminho principal para um MCU adicional em Klipper.

Klipper está organizado como um anfitrião mais um ou mais MCUs. Para novos MCUs adicionais, é normalmente mais prático usar:

- RP2040;
- STM32;
- placas de impressora 3D pré-fabricadas.

ESP32 pode trocar dados com o sistema de impressão separadamente: via MQTT, API HTTP, Home Assistant, seu próprio servidor ou outra integração. Mas isto já não é o mesmo que adicionar `[mcu]` à configuração de Klipper e usar pinos diretamente.

## O que verificar antes de comprar

Antes de comprar uma placa ESP32, verifique:

- modelo exato: ESP32, S3, C3, C6, etc.;
- tensão de lógica;
- se tem USB e como a placa é gravada;
- se há um pinout oficial ou esquema;
- quais pinos são seguros para GPIO;
- quais pinos são apenas entrada;
- quais pinos estão ocupados por flash/PSRAM, USB, UART ou LED;
- se tem ADC/I2C/SPI/UART suficiente para a tarefa;
- como a placa é alimentada;
- se se encaixa no enclosure;
- se há uma biblioteca ou firmware para o seu cenário.

Se uma placa de um mercado não tem um esquema e um pinout apropriado, pode ser utilizada para experiências, mas não é adequada para um dispositivo que precisa funcionar sem supervisão durante muito tempo.

## Erros comuns

- aplicar `5V` ao GPIO do ESP32;
- alimentar uma carga de GPIO;
- alimentar um servo ou relé a partir de um pino `3.3V` fraco;
- esquecer GND comum com MOSFET/driver;
- escolher um pino ADC2 para um sensor e depois ativar Wi-Fi;
- usar um pino de amarração de arranque para que ESP32 não inicie;
- usar `GPIO34-GPIO39` como saídas;
- comprar um módulo sem um pinout e esquema;
- pensar que "ESP32 com Wi-Fi" automaticamente significa controlo seguro de aquecedor de rede;
- tentar substituir eletrónica de potência com firmware.

## Pontos-chave

ESP32 é uma boa escolha para dispositivos Wi-Fi autónomos: sensores, interfaces web, controlo de ventilação simples, filtros, ecrãs e periféricos.

Mas ESP32 funciona com lógica `3.3V`, tem pinos especiais e não deve alimentar cargas diretamente. Para circuitos de potência, MOSFET, drivers, relés ou SSRs são necessários, e para um aquecedor de rede, uma secção de potência completamente segura é necessária.

## Materiais relacionados

- [Espressif: ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — visão geral oficial da família ESP32, módulos, placas de desenvolvimento e ligações para documentação.
- [Espressif: ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — características do chip, periféricos, ADC, PWM, UART, I2C, SPI e limitações de pinos.
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — tabela GPIO, pinos de amarração, pinos apenas entrada, pinos flash/PSRAM e limitação ADC2 com Wi-Fi.
- [Espressif: ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — recomendações para potência, pinos de amarração, GPIO, ADC e design de placa.
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — PWM/LEDC em Arduino-ESP32 para ventiladores, iluminação de fundo e outros sinais PWM.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — contexto de arquitetura Klipper para MCU e lista de backends de micro-controlador suportados na árvore de origem.
