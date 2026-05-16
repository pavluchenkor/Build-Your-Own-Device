# Componentes Comuns

Componentes comuns são as peças e módulos que encontrará com mais frequência ao montar um dispositivo semelhante ao iDryer ou periféricos de impressora 3D.

Objectivo desta secção:

Esta secção serve como referência para as peças que realmente segura nas suas mãos durante a montagem.

Não precisa de conhecimentos profundos de electrónica aqui. O objetivo principal é ajudá-lo a compreender:

- o que é este componente;
- por que o precisa;
- como está tipicamente ligado;
- pelo que o pode substituir;
- quais parâmetros importam ao comprar;
- o que se quebra mais frequentemente na primeira ligação.

Formato de cada página:

- o que é;
- onde é utilizado no iDryer e periféricos de impressora 3D;
- como é a ligação típica;
- características importantes;
- erros típicos;
- uma breve lista de verificação antes de comprar.

Ficheiros propostos:

- `02-heaters.md` - aquecedores: PTC, almofadas de silicone, cartuchos, 12V/24V/110-230V AC.
- `03-fans.md` - ventiladores: 2-pin, 3-pin, 4-pin PWM, tensão, corrente, ruído, fluxo de ar.
- `04-thermistors.md` - termistores: NTC 100K, tabelas de consulta, montagem, circuitos abertos/curtos.
- `05-led-strips.md` - fitas LED: 5V/12V/24V, regulares e endereçáveis, corrente por metro.
- `06-servo-motors.md` - servomotores: potência, sinal, ângulo, corrente máxima.
- `07-load-cells.md` - células de carga: HX711, calibração, montagem mecânica.
- `08-oled-display.md` - OLED: I2C/SPI, endereço, potência, quando necessário.
- `09-touchscreen.md` - TFT/toque: UART/SPI/HDMI, potência, compatibilidade.
- `10-rfid-and-nfc.md` - RFID/NFC: cartões, etiquetas, frequências, ligação.

## Materiais de Referência

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - secções oficiais do Klipper sobre aquecedores, ventiladores, sensores de temperatura, servomotores e ecrãs na configuração.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - selecção prática de ventilador por fluxo de ar, pressão estática, resistência da caixa e tarefa térmica.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - por que as cargas de alta potência não estão ligadas directamente ao GPIO e por que precisa de um interruptor de potência.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - exemplo de célula de carga, HX711, potência, fios de sinal e calibração.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - exemplo de componente onde precisa de verificar potência, níveis lógicos e interface escolhida antes.

## Ver Também

- [Aquecedores](02-heaters.md) - o tipo de carga mais arriscado: potência, temperatura, SSR/MOSFET e protecção independente.
- [Ventiladores](03-fans.md) - fluxo de ar, pressão estática, 2-pin/3-pin/4-pin e potência.
- [Termistores](04-thermistors.md) - sensor de temperatura como base para realimentação do aquecedor.
- [Ligar um ventilador](../05-practical-guides/01-connecting-a-fan.md) - exemplo prático de ligação de componente através de um interruptor de potência.
- [Erros de aquecedor e SSR](../07-common-mistakes/05-heater-and-ssr-errors.md) - erros comuns com cargas de alta potência e rede.
