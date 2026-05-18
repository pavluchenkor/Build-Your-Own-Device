# Componentes Comuns

Componentes comuns são as peças e módulos que você encontrará com mais frequência ao montar um dispositivo semelhante ao iDryer ou periféricos de impressora 3D.

Objetivo desta seção:

Esta seção serve como referência para as peças que você realmente segura nas mãos durante a montagem.

Você não precisa de conhecimentos profundos de eletrônica aqui. O objetivo principal é ajudá-lo a compreender:

- o que é este componente;
- por que você o precisa;
- como está tipicamente conectado;
- pelo que o pode substituir;
- quais parâmetros importam ao comprar;
- o que se quebra mais frequentemente na primeira conexão.

Formato de cada página:

- o que é;
- onde é utilizado no iDryer e periféricos de impressora 3D;
- como é a conexão típica;
- características importantes;
- erros típicos;
- uma breve lista de verificação antes de comprar.

Arquivos propostos:

- `02-heaters.md` - aquecedores: PTC, almofadas de silicone, cartuchos, 12V/24V/110-230V AC.
- `03-fans.md` - ventiladores: 2-pin, 3-pin, 4-pin PWM, tensão, corrente, ruído, fluxo de ar.
- `04-thermistors.md` - termistores: NTC 100K, tabelas de consulta, montagem, circuitos abertos/curtos.
- `05-led-strips.md` - fitas LED: 5V/12V/24V, regulares e endereçáveis, corrente por metro.
- `06-servo-motors.md` - servomotores: potência, sinal, ângulo, corrente máxima.
- `07-load-cells.md` - células de carga: HX711, calibração, montagem mecânica.
- `08-oled-display.md` - OLED: I2C/SPI, endereço, potência, quando necessário.
- `09-touchscreen.md` - TFT/toque: UART/SPI/HDMI, potência, compatibilidade.
- `10-rfid-and-nfc.md` - RFID/NFC: cartões, etiquetas, frequências, conexão.

## Materiais de Referência

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - seções oficiais do Klipper sobre aquecedores, ventiladores, sensores de temperatura, servomotores e telas na configuração.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - seleção prática de ventilador por fluxo de ar, pressão estática, resistência da caixa e tarefa térmica.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - por que as cargas de alta potência não estão conectadas diretamente ao GPIO e por que você precisa de um interruptor de potência.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - exemplo de célula de carga, HX711, potência, fios de sinal e calibração.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - exemplo de componente onde você precisa verificar potência, níveis lógicos e interface escolhida antes.

## Ver Também

- [Aquecedores](02-heaters.md) - o tipo de carga mais arriscado: potência, temperatura, SSR/MOSFET e proteção independente.
- [Ventiladores](03-fans.md) - fluxo de ar, pressão estática, 2-pin/3-pin/4-pin e potência.
- [Termistores](04-thermistors.md) - sensor de temperatura como base para realimentação do aquecedor.
- [Conectar um ventilador](../05-practical-guides/01-connecting-a-fan.md) - exemplo prático de conexão de componente através de um interruptor de potência.
- [Erros de aquecedor e SSR](../07-common-mistakes/05-heater-and-ssr-errors.md) - erros comuns com cargas de alta potência e rede.
