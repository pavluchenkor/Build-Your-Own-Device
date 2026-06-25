# Ligação de um Leitor RFID

Um leitor RFID/NFC permite-lhe ler um cartão, etiqueta ou fob sem contacto com fio.

Em dispositivos semelhantes ao iDryer, isto pode ser útil para identificação de bobine, selecção de perfil de material, acesso de serviço ou experimentos de rastreamento de consumíveis.

Erro principal: comprar um "módulo RFID" e assumir que qualquer cartão lerá de qualquer distância em qualquer controlador. Na realidade, precisa verificar frequência, tipo de etiqueta, interface, alimentação, níveis de lógica e colocação de antena.

## Módulos populares

Os comuns incluem:

- RC522 / MFRC522;
- PN532;
- leitores RFID USB/UART prontos;
- módulos NFC com I2C, SPI ou UART.

Para projectos simples de impressora 3D, módulos e etiquetas de 13.56 MHz são mais comuns: cartões, fobs, etiquetas compatíveis com NTAG/MIFARE.

## O que verificar antes da ligação

Antes de ligar, procure:

- frequência do módulo;
- tipos de cartão e etiqueta suportados;
- interface: SPI, I2C ou UART;
- tensão de alimentação;
- níveis de lógica;
- esquema de pinos da placa;
- selecção de interface via jumpers ou pontes de soldadura;
- distância de leitura;
- requisitos de antena e colocação.

Se o módulo para classificação para `5V`, não pode simplesmente ligá-lo à lógica `5V` sem verificar. Algumas placas possuem reguladores de tensão, mas não alteram o nível nas linhas de sinal.

## RC522: ligação SPI típica

Módulos RC522 baratos normalmente funcionam a `3.3V` e ligam-se mais frequentemente por SPI.

Linhas típicas:

- `VCC` - alimentação `3.3V`;
- `GND` - massa;
- `SCK` - sinal de clock SPI;
- `MOSI` - dados do controlador para o módulo;
- `MISO` - dados do módulo para o controlador;
- `SDA`, `SS` ou `CS` - selecção de chip SPI;
- `RST` - reset;
- `IRQ` - interrupção, muitas vezes não usada em projectos simples.

![RFID RC522 (MFRC522) module for reading 13.56 MHz cards](../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

Os nomes dos pinos podem variar. Por exemplo, no RC522, o pino `SDA` muitas vezes significa `SS`/`CS` para SPI, não a linha `SDA` de I2C. Isto é uma fonte comum de confusão.

## PN532: SPI, I2C, ou UART

PN532 é um módulo mais flexível. Dependendo da placa, pode funcionar via:

- SPI;
- I2C;
- UART.

Mas não pode simplesmente ligar qualquer pino. Em muitas placas PN532, a interface é seleccionada por jumpers, comutadores DIP ou pontes de soldadura.

Antes de ligar, verifique:

- qual interface é fisicamente seleccionada na placa;
- quais pinos correspondem à interface seleccionada;
- se são necessários resistores pull-up para I2C;
- se é necessário pino pull-up ou reposição;
- se os níveis de lógica são compatíveis com o controlador.

Se a placa diz "lógica 3.3V", não a ligue directamente a GPIO 5V.

## Massa comum

Como outros módulos, é necessária uma massa comum.

Se o módulo RFID para alimentação de uma fonte e o driver de outra, seus `GND` devem estar conectados.

Sem massa comum, SPI/I2C/UART pode não funcionar ou funcionar instàvelmente.

## Etiqueta deve corresponder ao leitor

RFID/NFC não é um padrão universal único.

Um módulo pode fisicamente apenas ler etiquetas suportadas por seu chip e biblioteca.

Verifique:

- frequência da etiqueta;
- tipo de cartão ou fob;
- o módulo suporta MIFARE, NTAG, ISO14443A, ou o tipo necessário;
- precisa apenas ler UID ou também ler/escrever dados;
- a biblioteca escolhida suporta a operação necessária.

Para selecção simples de perfil de material, frequentemente apenas ler o UID da etiqueta e armazenar mapeamento UID -> material no firmware ou anfitrião é suficiente.

## Distância de leitura

A distância de leitura para pequenos módulos RFID/NFC é geralmente curta.

Os resultados dependem de:

- tamanho da antena;
- tipo de etiqueta;
- orientação da etiqueta;
- distância;
- plástico do alojamento;
- metal próximo;
- interferência;
- potência do módulo.

Metal perto da antena pode piorar significativamente a leitura. Se o leitor para montado numa secadora, câmara ou suporte de bobina, teste a distância na montagem real, não apenas na bancada.

## Onde colocar o leitor

Para uma bobine de filamento, é melhor colocar o leitor RFID/NFC onde o utilizador intencionalmente traz a etiqueta.

Não conceba lógica assumindo que a etiqueta lerá sempre automaticamente.

Opções práticas:

- zona "traga etiqueta aqui" no alojamento;
- localização perto do suporte de bobine;
- zona de serviço para cartão de acesso;
- painel separado com distância curta de leitura.

Se a etiqueta está na bobine, teste com diferentes bobines, diferentes orientações de etiqueta, diferentes plásticos e proximidade de metal.

## Primeiro arranque

Antes da integração:

1. Ligue o módulo na bancada.
2. Execute um exemplo da biblioteca para seu módulo.
3. Verifique se o cartão ou etiqueta lê estàvelmente.
4. Registre UID de várias etiquetas.
5. Verifique se cartões não suportados não quebram a lógica.
6. Monte o módulo no alojamento e reteste.

Nesta fase, não construa sistemas de perfil complexos logo. Primeiro, alcance leitura UID estável.

## Exemplo de lógica de dispositivo

Para perfil de material, a lógica simples pode ser:

1. Utilizador traz etiqueta.
2. Dispositivo lê UID.
3. UID é procurado numa tabela.
4. Se UID é conhecido, perfil de material é seleccionado.
5. Se UID é desconhecido, dispositivo pede selecção manual de perfil.

RFID não deve ser o único método de controlo. Precisa de uma cópia de segurança manual: perfil em menu, botão, ecrã ou configuração de interface.

## O que verificar após montagem

Verifique:

- módulo recebe tensão correcta;
- níveis de lógica são compatíveis com controlador;
- interface correcta é seleccionada;
- `MOSI`, `MISO`, `SCK`, `CS` não estão trocados para SPI;
- `SDA`, `SCL` não estão trocados para I2C;
- `TX` e `RX` estão correctamente cruzados para UART;
- massa comum existe;
- reset/IRQ estão ligados conforme a biblioteca requer;
- etiquetas do tipo correcto leem;
- a distância de leitura é normal no alojamento;
- metal e fios não bloqueiam a antena;
- dispositivo funciona normalmente se etiqueta não lê.

## Erros comuns

- ligar RC522 3.3V a alimentação 5V ou lógica 5V;
- confundir RC522 `SDA` com I2C `SDA`;
- esquecer `CS`/`SS` em SPI;
- trocar `MOSI` e `MISO`;
- seleccionar uma interface em PN532 com jumpers mas fiação outra;
- usar tipo de cartão não suportado;
- colocar antena imediatamente próxima ao metal;
- teste a distância de leitura na bancada mas não no alojamento;
- fazer RFID o único método de selecção de perfil;
- armazenar lógica importante apenas em UID sem verificação de erro de leitura.

## Pontos-chave

- O módulo RFID/NFC deve ser escolhido para etiquetas e interface específicas.
- RC522 normalmente precisa de `3.3V` e SPI.
- PN532 pode funcionar via SPI, I2C ou UART, mas a interface deve ser seleccionada na placa.
- Massa comum é necessária.
- Metal perto da antena pode muito piorar a leitura.
- Para perfis de material, UID da etiqueta é frequentemente suficiente, mas selecção de cópia de segurança manual é necessária.
- Teste no alojamento real, não apenas na bancada.

## Leitura relacionada

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection, and 3.3V logic warnings.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - full PN532 guide, wiring, CircuitPython, Raspberry Pi, and interface selection.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - PN532 capabilities, NFC/RFID tag support, and 3.3V UART/I2C/SPI interfaces.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - official MFRC522/RC522 page for 13.56 MHz MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - MFRC522 technical datasheet: supported cards, power, communication interfaces with controller, and antenna/power effects on distance.
