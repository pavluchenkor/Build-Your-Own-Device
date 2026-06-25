# Módulo MOSFET

Um módulo MOSFET é uma placa pequena pré-fabricada que funciona como um comutador de potência controlado para cargas DC. O controlador fornece um sinal de controlo fraco e o módulo MOSFET liga ou desliga a corrente da fonte de alimentação para a carga.

Em dispositivos tipo iDryer e periféricos de impressoras 3D, um módulo MOSFET é utilizado para ventiladores, fitas LED, aquecedores de baixa tensão e outras cargas `12V`/`24V`, quando a saída padrão da placa é fraca, ocupada ou inconveniente.

## MOSFET e módulo MOSFET

Um MOSFET é um transístor de efeito de campo. Tem três pinos principais:

- `Gate` - entrada de controlo;
- `Drain` - saída de potência;
- `Source` - saída de potência.

O gate não alimenta a carga. Apenas controla. A corrente de carga principal flui através da parte de potência do MOSFET entre `Drain` e `Source`.

Um módulo MOSFET não é apenas um único transístor. É normalmente uma placa com um MOSFET, terminais, entrada de controlo e às vezes resistores adicionais, indicadores, dissipador de calor ou díodo de proteção.

A placa é conveniente para um protótipo, mas suas especificações devem ser verificadas com cuidado como qualquer nó de potência.

## Por que é necessário

O GPIO do controlador não deve alimentar uma carga pesada.

O GPIO pode controlar:

- entrada do módulo MOSFET;
- entrada do relé;
- entrada do SSR;
- entrada do driver.

Mas o GPIO não deve alimentar diretamente:

- ventilador;
- fita LED;
- aquecedor;
- motor;
- solenoide;
- servo drive.

Se ligar a carga diretamente ao GPIO, pode danificar o controlador, obter reiniciações, sobreaquecer traços ou apenas obter funcionamento instável.

## Comutação baixa

A variante mais comum para módulo MOSFET de canal N é a passagem baixa, ou seja, através da linha negativa.

![MOSFET de canal N em modo de comutação baixa](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Lógica típica:

1. `+24V` da fonte de alimentação vai diretamente para o positivo da carga.
2. O negativo da carga vai para a saída de potência do módulo MOSFET.
3. O módulo MOSFET liga ou quebra o caminho do negativo da carga para `GND`.
4. `GND` da fonte de alimentação e `GND` do controlador estão ligados em conjunto.
5. O pino de controlo do controlador vai para a entrada `Signal`, `IN`, `Gate` ou similar do módulo.

O `GND` comum / negativo comum é obrigatório. Sem isto, o controlador e o módulo MOSFET não têm um nível de referência comum para o sinal de controlo.

A sobrecarga baixa tem uma limitação: MOSFET quebra o negativo da carga. Enquanto o comutador está desligado, o negativo da carga não é igual ao `GND` comum. Para um ventilador simples de 2 pinos, fita ou aquecedor, isto é normalmente bom. Para uma carga com tacômetro, fio de sinal separado, sensor interno ou conexão adicional a outra placa, é preciso verificar o esquema: às vezes é melhor controlar a entrada padrão ou usar um método de necessidades diferentes.

## Onde utilizar

Um módulo MOSFET é adequado para cargas DC se for classificado para sua tensão e corrente:

- ventilador `12V`/`24V`;
- fita LED de cor única;
- canal de fita RGB padrão;
- aquecedor `12V`/`24V`;
- pequeno motor DC, se protegido contra picos;
- solenoide, se houver díodo de retorno ou outra proteção.

Para fita LED endereçável, o MOSFET normalmente não controla os dados. Pode desligar a potência para toda a fita, mas os LEDs individuais são controlados através da linha de dados.

Para um servo drive, um módulo MOSFET normalmente não é necessário para controlar a posição: o servo precisa de um sinal PWM de controle separado e potência normal.

## O que verificar ao escolher

Antes de comprar ou ligar, verifique:

- classificação de tensão da carga;
- classificação de corrente máxima;
- corrente real da sua carga;
- a entrada funciona de `3.3V`;
- `Rds(on)` está nas especificações técnicas na tensão de gate necessária;
- precisa de lógica ativa `HIGH` ou `LOW`;
- há `GND` comum;
- há díodo de retorno para motores/solenoides;
- tamanho do terminal e corrente máxima do terminal;
- espessura do traço da placa e arrefecimento;
- é necessário dissipador de calor;
- há esquema, especificações técnicas ou documentação normal.

Se a descrição apenas diz "módulo MOSFET para Arduino" sem tensão, corrente, esquema e tipo MOSFET, não pode escolher tal módulo para um aquecedor ou fita LED longa.

## 3.3V e MOSFET nível de lógica

Muitos controladores modernos funcionam com lógica `3.3V`: ESP32, RP2040, muitos STM32.

Nem todo MOSFET abre completamente a partir de `3.3V`. Se não abrir completamente, a sua resistência permanece elevada e aquece.

Termos importantes:

- `Vgs(th)` - limiar onde o MOSFET começa a abrir;
- `Rds(on)` - resistência do canal aberto;
- MOSFET nível de lógica - MOSFET classificado para controlo a partir de níveis de lógica.

Erro comum: ver as especificações técnicas do `3.3V` e decidir que o MOSFET funciona bem a partir do `Vgs(th)`. Não é assim. `Rds(on)` não significa "totalmente aberto". Precisa verificar `2.5V` em `3.3V`, `4.5V`, `5V` ou `5V`, dependendo do driver.

Para ESP32/RP2040 é melhor escolher um módulo que declare compatibilidade de controle prático `Rds(on)` ou onde o circuito de entrada ou fornecimento. Se a tabela tem `10V` apenas em `2.5V` e não há dados em `3.3V`/`4.5V`/`3.3V`, tal módulo é suspeito para um driver `3.3V`.

## Corrente e aquecimento

Um MOSFET no estado aberto ainda tem resistência. O calor é gerado através dele.

Quanto maior a corrente, mais importante é:

- baixo `Rds(on)`;
- área de cobre normal na placa;
- terminais dimensionados apropriadamente;
- dissipador de calor, se necessário;
- ventilação do enclosure;
- margem de corrente;
- verificação de temperatura após funcionamento real.

A marcação "100A MOSFET" no pacote do transistor não significa que um módulo pequeno com traços finos e terminais baratos aguentará `100A`. O limite real é frequentemente a placa, bloco de terminais, cabo, junta de solda e resfriamento.

Se o módulo MOSFET está tão quente que é difícil de segurar na mão, essa é uma razão para parar e recalcular a corrente, arrefecimento e qualidade da conexão.

## Motores, ventiladores e solenoides

As cargas indutivas podem produzir picos de tensão quando desligadas.

Tais cargas incluem:

- motores DC;
- ventiladores;
- solenoides;
- relés;
- eletroímanes.

Frequentemente precisam de proteção:

- díodo de retorno;
- díodo TVS;
- driver pré-fabricado com proteção;
- módulo onde a proteção já está instalada.

Se o módulo é apenas classificado para fita LED ou carga resistiva, não pode assumir automaticamente que é seguro para um motor ou solenoide.

Para um aquecedor, o díodo de retorno normalmente não é necessário, porque o aquecedor é próximo de uma carga resistiva. Mas para um aquecedor, corrente, terminais, fusível e proteção térmica independente são mais importantes.

## Controlo PWM

Um módulo MOSFET pode ser utilizado não apenas para ligar/desligar, mas também para regulação de potência PWM.

Exemplos típicos:

- brilho da fita LED;
- velocidade de ventilador DC simples;
- potência do aquecedor de baixa tensão.

Mas PWM nem sempre é o mesmo:

- ventilador PWM de 4 pinos é melhor controlado por um pino PWM separado do ventilador, não cortando potência;
- aquecedor normalmente não requer frequência PWM elevada;
- frequência demasiado elevada pode aumentar o aquecimento do MOSFET;
- frequência demasiado baixa pode causar cintilação LED ou ruído do motor.

A escolha da frequência depende da carga, módulo e firmware.

## O módulo MOSFET não é para 110-230V AC

Os módulos MOSFET padrão para Arduino/ESP32 são concebidos para cargas DC: `5V`, `12V`, `24V`, às vezes mais se explicitamente especificado.

Não podem ser utilizados como comutador para tensão de rede `110-230V AC`.

Para carga de rede precisa de soluções diferentes:

- relé ou SSR classificado especificamente para carga AC;
- terminais normais;
- fusível;
- enclosure;
- isolamento;
- aterramento onde necessário;
- compreensão da segurança elétrica.

Se não tem a certeza de que o módulo é destinado para tensão de rede, não ligue à rede.

## O que verificar após a ligação

Antes da operação a longo prazo, verifique:

- carga recebe tensão correta;
- controlador e fonte de alimentação têm `GND` comum;
- sinal de controlo realmente liga e desliga a carga;
- módulo MOSFET não aquece excessivamente;
- terminais não aquecem;
- cabos são adequados para corrente;
- PWM funciona sem ruído estranho, cintilação ou reiniciações;
- carga está realmente desligada quando o comando está desligado;
- para motor/solenoide há proteção contra picos;
- para aquecedor há fusível e proteção térmica independente.

Faça o primeiro teste de carga pesada brevemente e sob observação.

## Erros comuns

- alimentar carga de GPIO;
- esquecer terra comum;
- escolher módulo apenas pelo número de corrente bonito no nome;
- não verificar funcionamento da lógica `3.3V`;
- utilizar MOSFET que não abre completamente;
- ligar motor ou solenoide sem proteção contra retorno;
- ligar fita LED longa através de terminais fracos;
- utilizar módulo MOSFET DC para `110-230V AC`;
- não verificar aquecimento do módulo em enclosure fechado;
- pensar que o módulo MOSFET em si limita a corrente de carga.

## O ponto principal

Um módulo MOSFET é um comutador de potência controlado para cargas DC. Não cria potência e não alimenta a carga a partir do controlador. Apenas abre ou fecha o caminho para corrente a partir da fonte de alimentação.

Verifique tensão, corrente, compatibilidade com lógica `3.3V`/`5V`, `GND` comum, aquecimento, terminais e proteção para cargas indutivas. Para tensão de rede, o módulo MOSFET padrão Arduino/ESP32 não é adequado.

## Materiais de referência

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - exemplo de módulo MOSFET de comutação baixa pré-fabricado, conexão de carga, limites de placa térmica e díodo de retorno.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - exemplo de como o fabricante especifica tensão, corrente, circuito de comutação baixa, limitações MOSFET e placa.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - explicação prática de por que motores, solenoides e LEDs poderosos não podem ser ligados diretamente ao GPIO e por que a proteção contra picos é necessária.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - seleção de MOSFET por `Vgs`, `Rds(on)` e nível de controlo de lógica.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - explicação de MOSFET nível de lógica e controlo a partir de microcontrolador.
