# Controlador RP2040

RP2040 é um microcontrolador Raspberry Pi. A placa mais conhecida baseada nele é a Raspberry Pi Pico.

Para periféricos DIY em torno de uma impressora 3D, o RP2040 é uma das opções mais práticas: é barato, bem documentado, funciona com a lógica `3.3V`, é conveniente para flash via USB e é adequado como um MCU adicional para Klipper.

## Onde o RP2040 é útil

RP2040 is good for:

- placa de E/S adicional para Klipper;
- fan controller via MOSFET/drivers;
- leitura de termistores e sensores analógicos simples;
- connecting OLED via I2C;
- connecting RFID/NFC via SPI or UART;
- controlando servo com sinal PWM;
- placa autônoma simples sem Wi-Fi;
- bancada de testes para sensores e interfaces.

Se você precisar de rede pronta para uso, é mais fácil olhar para ESP32 ou Pico W. Se você precisar de um MCU com fio adicional para Klipper, o RP2040 geralmente é mais conveniente.

## Por que Raspberry Pi Pico é conveniente

Raspberry Pi Pico é uma placa de desenvolvimento pronta baseada em RP2040. Já possui USB, memória flash, regulador de energia, botão `BOOTSEL` e pinos expostos.

Pico advantages:

- low cost;
- documentação e pinagem decentes;
- USB para flashing e comunicação;
- many GPIO;
- `3.3V` logic;
- 2 UART, 2 SPI, 2 I2C;
- 16 PWM channels;
- 3 entradas ADC em pinos Pico expostos;
- PIO para interfaces não padronizadas;
- convenient UF2 flashing via USB mass storage.

Para um primeiro projeto, é melhor obter um Pico ou Pico H com pinos soldados do que um chip RP2040 vazio. Um chip simples requer uma placa personalizada, memória flash, energia, USB, roteamento e testes.

## BOOTSEL e UF2

Um dos pontos fortes do Pico é um processo simples de flashing:

1. Segure o botão `BOOTSEL`.
2. Conecte o USB ao seu computador.
3. A placa aparece como uma unidade USB.
4. Copie o arquivo de firmware `.uf2`.
5. A placa reinicia com o novo firmware.

Isso é conveniente para projetos MicroPython, CircuitPython, C/C++ e firmware Klipper. Para um iniciante, esse método geralmente é mais compreensível do que ST-Link, DFU ou um USB-UART separado.

## RP2040 e Klipper

RP2040 é um bom candidato para um MCU adicional no Klipper.

Esquema típico:

![Raspberry Pi Pico with RP2040 chip](../../img/02-controllers/03-rp2040-pico-photo.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg), Phiarc, CC BY-SA 4.0*

A ideia é:

- O host Linux com Klipper continua sendo o controlador principal;
- Pico/RP2040 é atualizado com firmware Klipper MCU;
- uma seção `printer.cfg` principal ou adicional é adicionada a `printer.cfg`;
- Os pinos RP2040 podem ser usados para ventiladores, sensores, PWM e outros periféricos;
- cargas de energia ainda estão conectadas via MOSFET, driver, relé ou SSR.

Isso é útil quando você precisa separar parte do periférico em um bloco separado: por exemplo, ventiladores, sensores de câmera, filtro, luz de fundo, botão, interruptor de limite ou saídas de serviço.

## Lógica GPIO e 3,3V

RP2040 funciona com lógica `3.3V`. Isso significa:

- do not apply `5V` to GPIO;
- para módulos `5V` você pode precisar de um conversor de nível;
- Os pull-ups I2C devem ser `3.3V`;
- O GPIO não deve alimentar uma carga diretamente;
- a fan, LED strip, relay, or heater needs an external switch/driver.

Se um módulo for “compatível com Arduino”, isso não significa que seja seguro para RP2040. Você precisa verificar os níveis de entrada e pull-ups.

## Power

O Pico geralmente é alimentado por USB ou pelo pino `VSYS`. A placa possui um regulador para alimentação do microcontrolador.

Practical rules:

- não alimente motores, servos e relés do pino `3V3` no Pico;
- usar energia separada para cargas;
- conecte GND comum com drivers de baixa tensão;
- verifique de onde vem a energia para `VSYS` e USB;
- leve em conta a corrente dos módulos externos, não apenas o próprio Pico.

Se o Pico for reiniciado quando um servo ou ventilador for iniciado, o problema quase sempre é energia, aterramento ou ruído.

## ADC on Pico

O Pico possui entradas ADC que você pode usar para tarefas analógicas simples:

- thermistor via voltage divider;
- potentiometer;
- light sensor;
- measuring low voltage via voltage divider.

Limitations:

- A entrada ADC não deve exceder a tensão GPIO segura;
- para medir `24V` ou `24V` você precisa de divisória e proteção;
- um termistor requer um resistor, tabela/modelo e contato mecânico corretos;
- O ADC não substitui um multímetro ou medidor industrial.

Para aquecedores, lembre-se: o ADC lê apenas o sensor. A segurança do aquecimento é fornecida pelo interruptor de alimentação, limites de firmware, fusível e proteção térmica independente.

## PIO em termos simples

PIO é E/S programável. O RP2040 possui pequenos blocos programáveis ​​que podem gerar ou ler sinais não padronizados sem carga constante no código principal.

Um recém-chegado não precisa começar com PIO. Mas esta é uma das razões pelas quais o RP2040 é popular para interfaces, temporização e periféricos não padrão.

Para um dispositivo simples do tipo iDryer, GPIO, PWM, I2C, SPI, UART e ADC regulares geralmente são suficientes.

## Pico, Pico W e Pico 2

É importante não confundir as placas:

- **Pico / Pico H** — placa RP2040 clássica sem Wi-Fi;
- **Pico W / Pico WH** — RP2040 com módulo Wi-Fi/Bluetooth integrado;
- **Pico 2 / Pico 2 W** — nova geração baseada em RP2350, este não é RP2040.

Se um artigo ou projeto diz RP2040, geralmente significa o Pico de primeira geração ou uma placa compatível. O Pico 2 é semelhante em conceito, mas é um microcontrolador diferente e a compatibilidade de firmware/pino precisa ser verificada separadamente.

## O que verificar antes de comprar

Antes de comprar uma placa baseada em RP2040, verifique:

- seja um Pico original, Pico W ou clone;
- se os pinos estão soldados;
- se possui o conector USB que você precisa;
- se existe uma pinagem adequada;
- quais GPIO estão disponíveis;
- whether you need Wi-Fi;
- se a placa é adequada para firmware Klipper;
- como será alimentada a placa e as cargas;
- se você tem ADC/PWM/I2C/SPI/UART suficiente para a tarefa;
- se há espaço no gabinete para montagem.

Se estiver planejando um Klipper MCU, verifique com antecedência as instruções existentes para sua placa específica e método de flash.

## Erros comuns

- applying `5V` to RP2040 GPIO;
- alimentar um servo ou relé de `3V3`;
- esquecendo o GND comum com MOSFET/driver;
- pensar que o Pico W é um Pico normal e não contabilizar os recursos usados/energia Wi-Fi;
- buying Pico 2 expecting exact RP2040 behavior;
- medindo `24V`/`24V` em ADC sem divisor;
- conectar um aquecedor diretamente a um pino;
- escolha RP2040 para tarefa de Wi-Fi quando um Pico normal não tem Wi-Fi;
- não verificar a pinagem de um clone específico.

## Pontos principais

RP2040 e Raspberry Pi Pico são uma escolha forte para periféricos DIY com fio e MCU adicionais no Klipper. A placa é barata, compreensível, bem documentada e fácil de atualizar.

Mas o RP2040 é um microcontrolador `3.3V`, não um controlador de energia. As cargas são conectadas por meio de drivers, MOSFET, relés ou SSR. Para tarefas Wi-Fi, você precisa do Pico W ou outro controlador de rede.

## Related materials

- [Raspberry Pi: RP2040 specifications](https://www.raspberrypi.com/products/rp2040/specifications/) — official RP2040 specifications: CPU, SRAM, UART/SPI/I2C, PWM, USB, and PIO.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — differences between Pico, Pico W, Pico 2, GPIO, ADC, PWM, and board variants.
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — detailed technical description of the microcontroller, peripherals, PIO, GPIO, and ADC.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — documentation for the Pico board itself: power, USB, exposed GPIO, and board limitations.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — official example of BOOTSEL, USB mass storage `RPI-RP2`, and copying UF2 to Pico.
- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) — context of RP2040 support in Klipper and settings for peripherals like I2C.
