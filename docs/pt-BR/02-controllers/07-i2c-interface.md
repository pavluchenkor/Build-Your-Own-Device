# Interface I2C

I2C é uma interface de comunicação para pequenos microchips e módulos próximos do controlador. Expansão: `Inter-Integrated Circuit`. Na documentação, frequentemente vê-se `barramento I2C`.

Ideia principal: vários dispositivos podem ser conectados às mesmas duas linhas de sinal `SDA` e `SCL` se tiverem endereços diferentes.

## Onde I2C é utilizado

Em dispositivos simples ao redor de uma impressora 3D, I2C é frequentemente utilizado para:

- displays OLED;
- sensores de temperatura, humidade, pressão e luz;
- relógios em tempo real;
- expansores GPIO;
- alguns módulos de codificador e botões;
- multiplicadores I2C;
- alguns módulos RFID/NFC;
- pequenas placas auxiliares.

I2C funciona bem para conexões curtas dentro de um enclosure. Para fios longos em toda a impressora ou perto de linhas de potência, torna-se mais arriscado.

## SDA, SCL, potência e GND

Um módulo I2C normalmente tem 4 contactos:

- `VCC` ou `VIN` - potência;
- `GND` - terra comum;
- `SDA` - dados;
- `SCL` - sinal de relógio.

Um circuito com vários dispositivos fica assim:

![Barramento I2C: um mestre e três dispositivos em SDA/SCL comum](../../img/02-controllers/07-i2c-bus-topology.svg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:I2C.svg), Cburnett, CC BY-SA 3.0*

Todos os dispositivos no mesmo barramento I2C conectam-se aos mesmos `SDA`, `SCL` e `GND`. A potência pode ser comum, mas sua tensão e níveis lógicos devem ser verificados para cada módulo.

## Endereços de dispositivos

Cada dispositivo I2C tem um endereço. Por exemplo, pequenos OLEDs frequentemente utilizam `0x3C`, alguns sensores utilizam `0x76`, `0x77`, `0x68`, `0x69` e assim por diante.

Se dois dispositivos no mesmo barramento têm o mesmo endereço, o controlador não consegue endereçá-los individualmente corretamente.

O que fazer com conflitos de endereço:

- alterar o endereço através de jumper ou ponte de soldagem, se o módulo o suportar;
- selecionar uma variante de módulo diferente;
- utilizar um multiplicador I2C;
- dividir dispositivos em diferentes barramentos I2C, se o controlador e firmware o permitirem.

O endereço é frequentemente dado em formato hexadecimal (`hex`): `0x3C`. Mas alguns firmware ou configurações podem exigir formato decimal (`decimal`). Por exemplo, `0x3C` em decimal é `60`. Precisa de verificar a documentação do sistema específico.

## Resistores de pull-up

As linhas I2C funcionam através de resistores de pull-up. Os dispositivos no barramento podem normalmente puxar `SDA` ou `SCL` para baixo, e o nível alto vem de pull-up para a alimentação lógica.

Sem pull-ups, o barramento pode não funcionar. Mas muitos módulos com seus próprios pull-ups num barramento também pode ser um problema: a resistência total fica demasiado pequena, as linhas ficam carregadas mais pesadamente, as margens de sinal e níveis podem degradar-se.

Praticamente:

- muitos OLEDs e placas de sensor já têm resistores de pull-up;
- num barramento simples curto isto normalmente funciona imediatamente;
- se há muitos dispositivos, precisa verificar os esquemas do módulo e pull-ups totais;
- se o barramento é instável, uma das primeiras verificações é dos resistores de pull-up.

Uma resistência inicial comum para um barramento separado é por volta de `4.7 kOhm`, mas pull-ups em módulos prontos podem ser diferentes.

## 3.3V e 5V

I2C é especialmente sensível a níveis de tensão, porque `SDA` e `SCL` são normalmente puxados para alguma tensão de alimentação.

ESP32, RP2040 e STM32 normalmente operam com lógica `3.3V`. Arduino Uno/Nano frequentemente opera com lógica `5V`.

Situação perigosa:

- controlador `3.3V`;
- módulo I2C alimentado a partir de `5V`;
- resistores de pull-up no módulo puxam `SDA` e `SCL` para `5V`.

Neste caso, `5V` pode aparecer no GPIO do controlador. Isto pode danificar o microcontrolador.

Antes de conectar, verifique:

- de que tensão o módulo é alimentado;
- para onde `SDA` e `SCL` são puxados;
- se há conversor de nível no módulo;
- se o módulo é compatível com um controlador `3.3V`.

Se tiver dúvidas, utilize potência `3.3V` para módulos I2C ou um conversor de nível.

## Velocidade

Velocidades I2C típicas:

```text
100000   # modo padrão, 100 kHz
400000   # modo rápido, 400 kHz
```

Para fios curtos e módulos normais, `400 kHz` frequentemente funciona. Mas para fios longos, pull-ups fracos, muitos dispositivos ou ambiente ruidoso, é melhor começar com `100 kHz`.

Em Klipper, o parâmetro `i2c_speed` não é igualmente suportado em todos os MCUs. A documentação afirma que muitos microcontroladores utilizam `100000`, enquanto algumas plataformas suportam `400000`. Portanto, não pode simplesmente escrever uma velocidade alta e assumir que é realmente aplicada.

## Scanner I2C

Um scanner I2C é um pequeno programa ou comando que itera através de endereços e mostra quais dispositivos respondem no barramento.

Ajuda a compreender:

- o controlador vê o módulo;
- qual é o endereço do dispositivo;
- `SDA` e `SCL` estão misturados;
- há potência e `GND` comum;
- há conflito de endereço.

Mas o scanner não prova que o dispositivo funciona completamente. Apenas mostra que alguém responde nesse endereço.

## I2C em Klipper

Em Klipper, um dispositivo I2C é conectado a um MCU específico.

A configuração pode incluir parâmetros:

- `i2c_mcu` - para qual MCU o dispositivo está conectado;
- `i2c_bus` - barramento I2C de hardware, se há múltiplos;
- `i2c_software_scl_pin` e `i2c_software_sda_pin` - I2C de software em pinos selecionados;
- `i2c_address` - endereço do dispositivo;
- `i2c_speed` - velocidade, se suportada.

Importante: `i2c_address` em Klipper é frequentemente especificada como um número decimal, não formato hex. Se a datasheet diz `0x3C`, a configuração pode exigir `60`.

Se o dispositivo está conectado a um MCU adicional, isto também deve ser especificado. Caso contrário, Klipper irá procurá-lo na placa principal.

## Comprimento de fio e interferência

I2C é projectado para conexões curtas. Dentro de um pequeno enclosure ou numa placa, é conveniente. Numa impressora 3D, as condições são piores:

- motores próximos;
- aquecedores próximos;
- fios longos;
- conectores em portas;
- linhas de potência de ventoinhaes e aquecedores;
- interferência electromagnética.

Regras práticas:

- manter `SDA` e `SCL` curtos;
- encaminhar perto de `GND`;
- não encaminhar paralelo a fios de potência de aquecedor;
- não fazer cabos de fita longos para peças móveis sem motivo;
- reduzir velocidade para `100 kHz` se há erros;
- utilizar conectores adequados e alívio de tensão;
- para conexões longas, escolha outra interface: UART, CAN, RS-485 ou MCU local perto do sensor.

## O que verificar antes de conectar

Antes de conectar um módulo I2C, verifique:

- potência do módulo;
- nível lógico;
- para onde `SDA` e `SCL` são puxados;
- endereço do dispositivo;
- se o endereço pode ser alterado;
- se há conflito com outros dispositivos;
- comprimento do fio;
- se há suporte de firmware;
- qual MCU e barramento o dispositivo conecta;
- se é necessário I2C de hardware ou I2C de software.

## Erros típicos

- `SDA` e `SCL` misturados;
- esqueceu `GND` comum;
- aplicou pull-ups `5V` a um controlador `3.3V`;
- dois dispositivos têm o mesmo endereço;
- especificou endereço hex onde decimal era necessário;
- utilizou fios demasiado longos;
- conectou muitos módulos com resistores de pull-up;
- escolheu um módulo não suportado por firmware;
- conectou dispositivo a um MCU adicional mas não especificou `i2c_mcu`;
- confundir I2C e I2S.

## Ponto-chave

I2C é conveniente para pequenos displays, sensores e módulos auxiliares próximos do controlador. Requer `SDA`, `SCL`, potência e `GND` comum.

Verificações principais antes de conectar: endereço, níveis `3.3V/5V`, resistores de pull-up, comprimento de fio e suporte de firmware. No ambiente ruidoso da impressora, manter I2C curto.

## Materiais relacionados

- [SparkFun: I2C at the Hardware Level](https://learn.sparkfun.com/tutorials/i2c/i2c-at-the-hardware-level) - explicação prática de `SDA`, `SCL`, linhas open-drain e resistores de pull-up.
- [SparkFun: I2C tutorial](https://learn.sparkfun.com/tutorials/i2c/all) - guia I2C geral, endereços, múltiplos dispositivos num barramento e características de hardware.
- [Adafruit: STEMMA QT technical specs](https://learn.adafruit.com/introducing-adafruit-stemma-qt/technical-specs) - exemplo de conector I2C padronizado, pinout, potência e `GND`.
- [Adafruit: PCA9548 I2C multiplexer](https://learn.adafruit.com/adafruit-pca9548-8-channel-stemma-qt-qwiic-i2c-multiplexer/pinouts) - exemplo de resolução de conflitos de endereço I2C duplicados através de multiplicador.
- [Klipper Configuration Reference: common I2C settings](https://www.klipper3d.org/Config_Reference.html) - parâmetros `i2c_address`, `i2c_mcu`, `i2c_bus`, I2C de software e `i2c_speed`.
