# Ferramentas

Esta seção não é sobre coleta de ferramentas.

É sobre o conjunto mínimo que ajuda você a montar com segurança um dispositivo, verificar conexões e encontrar erros simples sem adivinhar.

Em dispositivos caseiros em torno do iDryer e impressoras 3D, as ferramentas são necessárias para tarefas práticas:

- verificar se há 24V na fonte de alimentação;
- compreender se o positivo e negativo estão trocados;
- verificar continuidade em um fio;
- testar um termistor;
- ver se o sinal UART chega;
- programar um controlador;
- fazer um conector apropriado;
- encontrar queda de tensão na fonte;
- compreender por que um ventilador ou aquecedor não liga.

## Conjunto mínimo

Para a maioria das construções simples, ferramentas úteis incluem:

- multímetro;
- adaptador USB-UART ou USB-TTL;
- ferro de solda;
- ferramenta de crimpagem;
- cortadores de fio e descascador;
- tubagem de encolhimento por calor;
- terminais e conectores apropriados;
- ST-Link se trabalhar com STM32;
- osciloscópio ou pelo menos um multímetro com contador de frequência para diagnósticos mais complexos.

Nem tudo precisa ser comprado de uma vez. Mas um multímetro e ferramentas apropriadas de fio geralmente se pagam rapidamente.

## Ferramentas não substituem compreensão

Um multímetro não torna a parte de rede segura.

Um ferro de solda não corrige um esquema ruim.

Um osciloscópio não é necessário se o positivo e negativo estão trocados.

Então a ordem é:

1. Compreender o que deve ser conectado.
2. Verificar a fonte de alimentação.
3. Verificar a fiação.
4. Verificar sensores e sinais.
5. Só então procurar por problemas complexos.

## O que estará nesta seção

- `02-multimeter.md` - medir tensão DC, continuidade, resistência, fusíveis e por que medição de corrente é mais perigosa.
- `03-usb-ttl-adapter.md` - adaptadores USB-UART, TX/RX/GND, níveis lógicos 3.3V/5V, programação e logs.
- `04-soldering.md` - soldar fios, pads, módulos, juntas de solda frias, tubagem de encolhimento e alívio de tensão.
- `05-crimping-connectors.md` - Dupont, JST, ferrules, Faston, terminais e verificações de qualidade de crimpagem.
- `06-st-link.md` - ST-Link, STM32, SWD, recuperação de placa após programação falhada.
- `07-oscilloscope.md` - PWM, UART, queda de tensão, ruído e aviso crítico de segurança sobre tensão de rede.

## O que vale a pena comprar corretamente

Há coisas que você não deve economizar:

- um multímetro com sondas apropriadas e modo de continuidade;
- um ferro de solda com controle de temperatura;
- solda de qualidade e fluxo;
- uma ferramenta de crimpagem para terminais específicos;
- conectores e terminais classificados para a corrente necessária;
- tubagem de encolhimento por calor;
- fios de bitola correta.

Crimpagem pobre ou terminais fracos podem causar mais problemas do que firmware ruim.

## O que você não pode fazer

Você não pode:

- medir resistência em um circuito energizado;
- medir corrente da mesma forma que mede tensão;
- colocar um multímetro em 110-230V AC sem compreender segurança;
- soldar a parte de alimentação "de qualquer forma";
- usar Dupont para um aquecedor;
- mudar fios enquanto a alimentação está ligada;
- manter peças de rede abertas na mesa;
- pensar que se um fio "segura", o contato é bom.

## Os essenciais

- Multímetro é a primeira ferramenta de diagnóstico.
- USB-UART é necessário para logs, programação e comunicação com dispositivos UART.
- Soldar e crimpar são tarefas diferentes, e para conectores, crimpagem é frequentemente melhor.
- ST-Link é necessário quando trabalha com STM32 e SWD.
- Osciloscópio não é necessário para todos, mas mostra rapidamente sinais, queda e ruído.
- Para a parte de alimentação, qualidade de contato, bitola de fio e segurança importam mais do que a aparência da montagem.

## Materiais de referência

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - noções básicas de multímetro: tensão, corrente, resistência, continuidade.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - verificações de hardware para alimentação, conexões e calor.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART e lógica básica de comunicação em série.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - guia prático de solda e qualidade de conexão.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - documentação oficial de ST-Link e SWD/SWIM.
