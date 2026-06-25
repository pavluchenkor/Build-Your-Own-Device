# Erros do Controlador

Um controlador não é uma caixa universal onde você pode conectar tudo diretamente.

Ele lê sensores, emite sinais de controle e se comunica com o host. Mas as cargas de energia devem ser alimentadas através de saídas apropriadas, MOSFETs, relés, SSRs ou drivers.

## Symptoms

Sinais típicos de problemas de controlador ou conexão:

- placa não detectada via USB;
- o firmware não inicia;
- pins do not respond;
- controller reboots;
- controller heats up significantly;
- a placa para de funcionar depois que o módulo é conectado;
- ESP32 perde Wi-Fi quando o carregamento é ligado;
- sensor não visível embora haja energia;
- Klipper não se conecta ao MCU;
- comandos funcionam no pino errado.

## Controlador errado escolhido

Antes de escolher uma prancha você deve entender a tarefa.

Para um dispositivo Wi-Fi autônomo simples, o ESP32 pode ser uma boa escolha.

Para um MCU adicional no Klipper, geralmente é mais prático observar:

- RP2040;
- STM32;
- ready-made 3D printer board.

Arduino Uno/Nano são úteis para aprendizado e experimentos simples, mas para um novo dispositivo sério em torno de uma impressora você rapidamente se depara com limitações.

O erro é escolher uma prancha só porque “é popular”, sem verificar:

- número de pinos necessários;
- logic levels;
- power supply;
- firmware support;
- USB/UART/CAN availability;
- suporte para bibliotecas necessárias;
- output current;
- development environment.

## ESP32 as Klipper MCU

ESP32 é útil como um dispositivo IoT/Wi-Fi separado.

Mas não espere automaticamente que o ESP32 seja a melhor escolha como Klipper MCU.

Se o objetivo é a integração com o Klipper como um MCU adicional, primeiro observe as opções oficiais e comprovadas do Klipper. Para novas extensões de hardware, geralmente é mais simples e confiável usar RP2040 ou STM32.

ESP32 é bom se o dispositivo:

- trabalhar de forma autônoma;
- have Wi-Fi;
- provide data via MQTT or HTTP;
- have web interface;
- comunicar-se com o Home Assistant;
- trabalhe separadamente do Klipper.

## Lógica de 3,3 V e 5 V

Muitos controladores modernos funcionam com lógica de 3,3V.

Por exemplo:

- ESP32;
- RP2040;
- many STM32.

O erro é aplicar um sinal de 5V a uma entrada projetada apenas para 3,3V.

Isso pode:

- danificar imediatamente o pino;
- danificar o controlador posteriormente;
- cause unstable operation;
- quebrar um módulo que parecia bom.

Antes de conectar verify:

- module power voltage;
- input/output logic level;
- existe um conversor de nível;
- a entrada aceita 5V;
- o que está escrito na descrição técnica.

## GPIO não alimenta uma carga

GPIO is a signal pin.

Não deve alimentar:

- fan;
- servo;
- heater;
- LED strip;
- relé sem driver;
- solenoid;
- motor.

GPIO pode enviar um comando. A corrente de carga deve passar por uma saída de energia, MOSFET, driver, relé ou módulo separado.

Se a carga estiver conectada diretamente ao GPIO, você poderá danificar o pino ou a placa inteira.

## No Common GND

Um controlador pode acionar um módulo externo somente se eles tiverem um nível de referência comum.

Erro típico:

- servo alimentado por fonte separada de 5V;
- o sinal vem do controlador;
- `GND` not connected;
- o servo sacode ou não responde.

O mesmo acontece com módulos MOSFET, ventiladores PWM, alguns sensores e placas externas.

## Incorrect Firmware

A placa pode estar boa, mas o firmware não cabe.

Errors:

- firmware atualizado para microcontrolador errado;
- escolheu o bootloader errado;
- firmware USB e UART misturado;
- escolheu a porta serial errada;
- O Klipper especificou o caminho errado do dispositivo;
- os pinos na configuração não correspondem à placa;
- não reiniciou o firmware/host após piscar.

Antes de piscar você deve saber exatamente o modelo da placa e do microcontrolador.

## O pino existe no esquema, mas não é adequado

Nem todos os pinos são iguais.

Pins can have restrictions:

- input only;
- usado por USB/UART/SPI;
- usado durante a inicialização;
- related to boot mode;
- não suporta PWM necessário;
- pulled up or down;
- entra em conflito com outro módulo.

Se o pino se comportar de maneira estranha, verifique a documentação da placa, não apenas o número GPIO.

## O que verificar

Mini-checklist:

1. A placa certa foi escolhida para a tarefa?
2. De que potência a placa precisa?
3. Qual lógica: 3,3V ou 5V?
4. Existe `GND` comum com módulos externos?
5. A carga não é alimentada pelo GPIO?
6. A placa suporta a interface necessária?
7. O pino selecionado não é usado?
8. Is firmware correct?
9. A placa é visível via USB?
10. A configuração corresponde à pinagem da placa?

## O que não fazer

Você não pode:

- aplique entrada de 5V a 3,3V sem verificar;
- conecte a carga diretamente ao GPIO;
- atualizar firmware aleatório de uma placa "semelhante";
- change wiring under power;
- assume any GPIO fits any task;
- ignore controller heating;
- conecte módulos externos sem aterramento comum quando necessário.

## Key Points

- O controlador controla, mas não alimenta diretamente uma carga.
- A lógica de 3,3 V e 5 V deve ser compatível.
- GPIO é um sinal, não uma fonte de alimentação.
- Para Klipper MCU você costuma olhar para RP2040/STM32, ESP32 é mais conveniente como dispositivo Wi-Fi autônomo.
- O firmware e a pinagem devem corresponder à placa real.
- Se a placa aquecer ou parar de ser detectada, desligue a energia e encontre o erro de conexão.

## References

- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - general process of preparing and flashing MCU for Klipper.
- [Klipper: Config Reference, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - `[mcu]` section, serial/CAN connection, and additional MCUs.
- [Arduino: Digital Pins](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - basic explanation of digital pins as inputs/outputs, not power supply.
- [Espressif ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - official electrical specifications of ESP32.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - official data on RP2040/Pico, power, and GPIO.
