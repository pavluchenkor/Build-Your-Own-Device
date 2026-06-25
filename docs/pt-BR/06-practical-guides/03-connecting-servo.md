# Ligação de um Servomotor

Um servomotor é um pequeno motor com gabinete de velocidades e eletrônica de controle. Pode dizer-lhe para que posição rodar o veio.

Em dispositivos semelhantes ao iDryer, um servomotor pode abrir um amortecedor, mover um pequeno trinco, pressionar um comutador mecânico ou redirecionar o fluxo de ar.

O erro principal com servomotores: pensar que é uma "coisa pequena" e pode alimentá-la a partir de qualquer pino 5V do controlador. Um servomotor pode desenhar corrente significativa, especialmente no arranque, movimento repentino ou quando o mecanismo se prende.

## Três fios

Um servomotor hobby típico tem três fios:

- alimentação: geralmente `5V` ou `6V`;
- massa: `GND`;
- sinal: pulsos de controle do controlador.

Cores comuns:

- vermelho - alimentação;
- preto ou castanho - massa;
- amarelo, laranja ou branco - sinal.

Mas não pode confiar cegamente nas cores. Diferentes fabricantes podem usar esquemas de cores diferentes. Antes de conectar, verifique a marcação, página de produto ou datasheet.

## Alimentação separada, sinal separado

O fio de sinal não alimenta o servomotor. Apenas diz ao servomotor para onde rodar.

O servomotor desenha energia do fio de alimentação.

A lógica correta é:

- o controlador fornece apenas o sinal de controle;
- o servomotor é alimentado por uma fonte de 5V/6V que possa lidar com a sua corrente;
- a massa do controlador e a massa de alimentação do servomotor estão conectadas em conjunto.

![Servo wire color code](../../img/03-common-components/06-servo-color-code.jpg)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## Porque não pode alimentar a partir de 5V fraco

Muitas placas têm um pino 5V. Isto não significa que um servomotor possa ser alimentado com segurança a partir dele.

Ao mover, um servomotor pode desenhar muito mais atual do que seu tamanho sugere. Se a alimentação for insuficiente, aparecem sintomas típicos:

- controlador reinicia;
- display cintila;
- conexão USB cai;
- servomotor se move aos solavancos;
- Wi-Fi em ESP32 cai;
- servomotor zumbe mas não se move;
- alimentação diminui no início do movimento.

Para um pequeno servomotor, a alimentação fornecida pela placa por vezes funciona se a placa e a fonte forem explicitamente classificadas para essa corrente. Mas para um dispositivo real com um amortecedor, trinco ou mecanismo, é melhor usar uma fonte de alimentação DC-DC ou fonte de alimentação separada de 5V/6V com margem.

## Massa comum

Se o servomotor for alimentado por uma fonte separada, é necessária uma massa comum.

Sem uma massa comum, o controlador e o servomotor não têm um nível de sinal comum. O servomotor pode não responder, pode se mover aos solavancos ou pode comportar-se aleatoriamente.

Ligação simples:

1. `+5V` ou `+6V` da fonte de alimentação vai para a alimentação do servomotor.
2. `GND` da fonte de alimentação vai para a massa do servomotor.
3. A `GND` do controlador está conectada à mesma massa.
4. O pino PWM/GPIO do controlador vai para o fio de sinal do servomotor.

A alimentação do servomotor e a alimentação do controlador podem ser diferentes, mas a massa deve ser comum.

## Que sinal é necessário

Um servomotor hobby posicional típico é controlado por pulsos.

Sinal típico:

- pulso aproximadamente a cada `20 ms`;
- cerca de `1 ms` - um extremo do intervalo;
- cerca de `1.5 ms` - meio;
- cerca de `2 ms` - outro extremo do intervalo.

Isto não é PWM típico para brilho LED ou velocidade de ventoinha. Aqui, a largura do pulso em microsegundos é importante.

Os limites reais de um servomotor específico podem diferir. Alguns funcionam com segurança não de 0 a 180 graus mas menos. Portanto, posições extremas precisam de teste cuidadoso.

## Não prenda um servomotor contra o mecanismo

Um servomotor tenta manter a posição ordenada.

Se um amortecedor bate no alojamento, um braço se prende ou o mecanismo atinge uma paragem física antes do comando terminar, o servomotor continua a empurrar. Nesse ponto, a corrente sobe, o motor aquece, a gabinete de velocidades se desgasta.

Isto é especialmente crítico para amortecedores e trincos.

Antes de operação permanente, verifique:

- o mecanismo se move livremente em todo o intervalo;
- nenhum desalinhamento;
- nenhuma vinculação de ligações;
- o servomotor não zumbe na posição final;
- ângulos extremos no firmware não forçam o mecanismo contra uma paragem;
- com a alimentação desconectada, o dispositivo permanece seguro ou volta via mola, conforme pretendido.

Se um servomotor zumbe em repouso, frequentemente sinaliza carga, uma paragem ou geometria de alavanca errada.

## Corrente de arranque e travamento

Um servomotor tem corrente de funcionamento normal e corrente quando o came está bloqueado. A última é frequentemente chamada de corrente de trabalho.

Uma corrente de travamento aparece quando o servomotor tenta se mover, mas o eixo está bloqueado ou o mecanismo é muito pesado.

Este modo frequentemente causa:

- diminuição de alimentação;
- reinicialização do controlador;
- aquecimento do fio;
- sobraquecimento do DC-DC;
- ruptura da gabinete de velocidades.

Se a datasheet lista a corrente de travamento, escolha a fonte de alimentação contabilizando este valor e margem de segurança. Se não houver datasheet, não pode assumir que um servomotor é seguro para executar "à vista".

## Condensador junto ao servomotor

Às vezes um condensador electrolítico entre `+5V` e `GND` junto ao servomotor ajuda.

Não substitui uma fonte de alimentação adequada, mas pode suavizar uma breve queda no início do movimento.

Para um pequeno servomotor: centenas de microfarads, como `470 uF` ou mais, com classificação de tensão acima da tensão de alimentação.

A polaridade do condensador eletrolítico é importante:

- positivo do condensador para `+5V`;
- negativo do condensador para `GND`.

Se o dispositivo precisar ser confiável, primeiro escolha a alimentação e as fibras condutoras, depois use um condensador como medida adicional.

## Exemplo de configuração Klipper

Em Klipper, um servomotor é descrito com uma seção `[servo]`.

Exemplo:

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

Comandos:

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

Os nomes de pinos aqui são típicos. Num dispositivo real, verifique o esquema de pinos da sua placa.

Para mecânica, não comece com `0` e `180` logo. Primeiro teste um intervalo seguro como `60`, `90`, `120`, depois expanda os ângulos.

## Exemplo de lógica Arduino/ESP32

A abordagem do Arduino normalmente usa a biblioteca Servo:

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

Este é apenas um exemplo da lógica do sinal. A alimentação do servomotor ainda precisa ser concebida separadamente. Mesmo que o fio de sinal esteja conectado ao Arduino ou ESP32, o motor do servomotor não deve sobrecarregar a alimentação do controlador.

## O que verificar após a conexão

Antes de montar no alojamento:

- servomotor recebe a tensão correta;
- fonte de alimentação pode lidar com corrente do servomotor;
- massa do controlador e massa do servomotor são comuns;
- fio de sinal está conectado ao pino correto;
- servomotor se move na direcção correta;
- ângulos extremos não quebram o mecanismo;
- mecanismo não se prende;
- servomotor não zumbe continuamente;
- fios não pegam na alavanca ou engrenagens;
- alimentação não diminui após movimento;
- controlador não reinicia.

Teste mecânica descarregada e sob carga real. Um amortecedor que se move facilmente à mão pode se prender após montagem no alojamento.

## Erros comuns

- alimentar servomotor a partir de GPIO;
- alimentar servomotor a partir de um pino fraco 5V da placa;
- esquecer massa comum;
- confiar nas cores do fio sem verificar;
- conectar alimentação ao contrário;
- usar fios demasiado finos;
- não contabilizar corrente de arranque e travamento;
- forçar servomotor a empurrar contra uma paragem mecânica;
- usar ângulo `0` ou `180` quando o mecanismo real funciona com segurança apenas num intervalo menor;
- montar servomotor perto de calor sem verificar temperatura de funcionamento;
- tratar um servomotor de rotação contínua como um servomotor posicional regular.

## Pontos-chave

- Um servomotor tem três linhas: alimentação, massa e sinal.
- O sinal não alimenta o servomotor.
- Dispositivos reais frequentemente precisam de uma fonte de alimentação separada de 5V/6V.
- Massa do servomotor e massa do controlador devem ser comuns.
- A carga mais perigosa é travamento ou vinculação mecânica.
- Ângulos extremos precisam de selecção cuidadosa, não `0` e `180` imediatos.
- Se o controlador reinicia quando o servomotor se move, primeiro verifique a alimentação e a massa comum.

## Leitura relacionada

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - official `[servo]` section, `SET_SERVO`, angles, and pulse width.
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - basic explanation of hobby servo, three wires, and pulse control.
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - breakdown of electrical connection, typical wire colors, and hobby servo mechanics.
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - practical example of connection, power sag behavior, and capacitor next to servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - official Servo library for Arduino approach.
