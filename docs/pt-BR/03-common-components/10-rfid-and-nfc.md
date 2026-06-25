# RFID e NFC

RFID é identificação por radiofrequência. NFC é uma tecnologia relacionada para alcance muito curto, geralmente na frequência `13.56 MHz`.

Em um simples dispositivo DIY, é uma forma de ler um cartão, chaveiro, adesivo ou etiqueta sem contato com fio. Por exemplo, um usuário traz uma etiqueta de carretel de filamento e o dispositivo seleciona o perfil do material.

O principal erro é pensar que “RFID” significa compatibilidade universal. Na prática, você precisa de correspondência de frequência, tipo de tag, microchip leitor, biblioteca, interface, potência e posicionamento da antena, tudo para se alinhar.

## Onde é usado

Em projetos do tipo iDryer, RFID/NFC pode ser usado para:

- identifying a filament spool;
- selecting a material profile;
- vincular configurações a uma tag;
- service access;
- user action confirmation;
- consumable tracking;
- experimenta etiquetas em recipientes, carretéis ou cassetes.

Para a seleção do perfil do material, muitas vezes basta ler o UID do tag e armazenar uma tabela `UID -> material`. Mas essa abordagem deve ter um substituto manual: se a tag não for lida, o usuário ainda poderá escolher manualmente o perfil.

## RFID e NFC em termos simples

RFID é um termo amplo. Inclui diferentes frequências, padrões, faixas e tipos de tags.

NFC geralmente significa comunicação de campo próximo no `13.56 MHz`, compatível com parte do ecossistema RFID. NFC é conhecido por cartões bancários, telefones, adesivos NTAG e cartões MIFARE, mas isso não significa que qualquer leitor NFC leia qualquer cartão e quaisquer dados.

Para pequenos dispositivos DIY, os módulos `13.56 MHz` são mais comuns:

- RC522 / MFRC522;
- PN532;
- ready-made USB/UART RFID/NFC readers;
- Módulos NFC com SPI, I2C ou UART.

Existem outros sistemas RFID, como cartões de acesso `13.56 MHz` ou RFID UHF. Eles não são compatíveis com módulos NFC `13.56 MHz`.

## RC522

RC522 é um módulo `13.56 MHz` barato e comum para cartões e tags. É frequentemente usado com Arduino e ESP32.

Pros:

- cheap;
- many examples;
- adequado para leitura simples de UID;
- geralmente se conecta via SPI.

Cons:

- geralmente funciona apenas com potência e lógica `3.3V`;
- cheap module quality varies;
- o alcance de leitura é pequeno;
- o suporte ao tipo de cartão é limitado;
- fixar `SS` na placa geralmente significa `CS`/`SDA` para SPI, não I2C `SDA`.

O RC522 funciona se você precisar apenas ler o UID de cartões ou chaveiros do tipo MIFARE a curta distância. Para tarefas NFC mais amplas, o PN532 geralmente é mais conveniente.

## PN532

PN532 é um controlador NFC/RFID mais flexível. Muitos módulos PN532 podem funcionar através de:

- SPI;
- I2C;
- UART.

Mas a interface escolhida geralmente precisa ser configurada fisicamente na placa: jumpers, chaves DIP ou solda. Você não pode conectar um módulo via I2C se estiver configurado no modo SPI.

O PN532 é frequentemente escolhido se você precisar de:

- more interface options;
- better NFC scenario support;
- trabalhar com diferentes tipos de tags;
- Python/CircuitPython/Raspberry Pi scenarios;
- better documented module.

Mas o PN532 também não é um leitor mágico universal. Você precisa verificar tipos de cartão, biblioteca e modo de funcionamento específicos.

## Frequência e tipo de tag

A tag deve corresponder ao leitor.

Antes de comprar tags, verifique:

- frequency: `13.56 MHz`, `125 kHz` or other;
- type: MIFARE Classic, NTAG213/215/216, ISO14443A or other;
- se você só precisa ler o UID;
- se você precisa ler/gravar dados personalizados;
- se a biblioteca escolhida oferece suporte às operações necessárias;
- se você pode colocar fisicamente a etiqueta em um carretel ou caixa.

Se a tarefa é selecionar um perfil de material, normalmente apenas ler o UID e armazenar o perfil separadamente é mais simples. Escrever dados dentro da tag complica o projeto: você precisa pensar no formato dos dados, compatibilidade, proteção contra gravação e erros de gravação.

## UID - Not Security

O UID de um cartão ou etiqueta é conveniente para usar como identificador. Mas o UID não é uma proteção confiável.

Para um perfil em spool, isso é normal: se o UID for conhecido, selecione o perfil. Um erro não é crítico porque o usuário pode verificar o material manualmente.

Para acesso a funções perigosas, modos de serviço ou desbloqueio de um aquecedor, o UID por si só é fraco. Alguns UIDs podem ser copiados ou falsificados e alguns cartões têm limites de segurança conhecidos.

Practical rule:

- UID é bom para conveniência e identificação de consumíveis;
- O UID não deve ser a única proteção para modos perigosos;
- para aquecedores e peças de energia, sempre são necessárias verificações de segurança separadas.

## Níveis de potência e lógica

Muitos módulos RFID/NFC são classificados para lógica `3.3V`. Isto é especialmente importante para módulos breakout RC522 e PN532.

Verifique:

- module power voltage;
- nível lógico em SPI/I2C/UART;
- se o conselho possui regulador;
- whether signal lines have level matching;
- se são necessários resistores pull-up I2C;
- se é necessário um terreno comum com o controlador.

A presença do pino `5V` em uma placa de módulo nem sempre significa que as linhas de sinal toleram `5V`. Alguns módulos podem ser alimentados pelo `3.3V` através de um regulador, mas a lógica permanece `3.3V`.

## Connection Interface

An RFID/NFC module can connect via SPI, I2C or UART.

SPI:

- rápido e comum;
- requires `SCK`, `MOSI`, `MISO`, `CS`;
- no RC522, o pino `CS` geralmente significa `CS`;
- importante não confundir `MISO` e `MISO`.

I2C:

- usa `SCL` e `SCL`;
- pode compartilhar barramento com outros dispositivos;
- needs correct pull-up resistors;
- importante verificar o endereço e o modo do módulo selecionado.

UART:

- usa `RX` e `RX`;
- `RX` de um dispositivo vai para `RX` de outro;
- conveniente para alguns leitores prontos;
- precisa de velocidade e protocolo correspondentes.

A conexão RC522 SPI detalhada está na seção prática: [Conectando um leitor RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## Antena e Estojo

RFID/NFC funciona através de uma antena. Em módulos pequenos, geralmente está impresso diretamente no quadro.

A leitura é afetada por:

- antenna size;
- tag orientation;
- distance;
- case plastic;
- metal nearby;
- fios e linhas de energia próximas;
- module power;
- tag type;
- onde o usuário traz o cartão.

O metal próximo à antena pode piorar drasticamente a leitura. Se o leitor for montado próximo à estrutura metálica, parafusos, tela, fonte de alimentação ou painel de alumínio da impressora, o alcance pode ser muito pior.

Para o caso, é melhor deixar uma zona clara: “traga a etiqueta aqui”. Não espere que a etiqueta em um carretel sempre faça a leitura automática de plástico, ar, eixo, suporte e peças próximas.

## Device Logic

A RFID deve melhorar a conveniência e não quebrar o controle.

Lógica normal para um carretel:

1. User brings a tag.
2. O dispositivo lê o UID.
3. O UID é consultado na tabela de perfis.
4. Se o UID for encontrado, o perfil do material será sugerido.
5. User can confirm or change profile.
6. Se o UID não for encontrado ou não for lido, a seleção manual estará disponível.

Bad logic:

- o dispositivo não pode ser iniciado sem uma tag;
- unknown tag selects random profile;
- erro de leitura mantém silenciosamente o perfil antigo;
- alterações de perfil sem confirmação do usuário;
- UID é a única proteção para um modo de serviço.

Para um aquecedor, é especialmente importante que a seleção do perfil não ignore os limites de temperatura, sensores e proteção de emergência.

## O que verificar antes de comprar

Antes de comprar, verifique:

- module frequency;
- supported tag types;
- interface: SPI, I2C, UART, USB;
- power voltage;
- logic levels;
- disponibilidade de correspondência de nível;
- disponibilidade de documentação e pinagem;
- como a interface é selecionada no quadro;
- se existe uma biblioteca para o seu controlador;
- antenna size;
- tipo e tamanho da etiqueta;
- intervalo esperado em um caso real;
- se a seleção manual de fallback é possível.

Para um primeiro projeto, escolha um módulo com boa documentação e exemplos, não o mais barato sem esquema.

## Erros típicos

- comprei cartão `13.56 MHz` para leitor `13.56 MHz`;
- conectou `5V` RC522 à alimentação ou lógica `5V`;
- peguei o pino `SDA` em RC522 para I2C `SDA`;
- misturou `MISO` e `MISO`;
- forgot `CS`/`SS` in SPI;
- configure uma interface no PN532 com jumpers, mas conecte uma diferente;
- não colocou pull-ups I2C onde necessário;
- put antenna near metal;
- testei a leitura na bancada, mas não testei no caso;
- tornou o RFID a única maneira de selecionar o perfil;
- use UID como proteção de acesso confiável;
- não lidou com a situação de "tag não lida".

## Ponto Principal

RFID/NFC é útil para identificação de carretel, seleção de perfil de material e entrada simples de serviço. Mas não é um leitor universal para nenhum cartão e nem um sistema de segurança confiável por si só.

Primeiro escolha a frequência e os tipos de tag, depois o módulo, a interface, a potência e a localização da antena. Em seguida, teste a leitura em um caso real e definitivamente mantenha a seleção manual de substitutos.

## Reference Materials

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection and warning about `3.3V` logic.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - complete PN532 guide, CircuitPython/Python, interfaces and SEL jumper setup.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - description of PN532 module, supported interfaces and NFC/RFID capabilities.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - MFRC522/RC522 microchip page and its purpose for `13.56 MHz` MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - technical description of MFRC522: `13.56 MHz` reader/writer, ISO/IEC 14443 A/MIFARE/NTAG support and communication interfaces.
