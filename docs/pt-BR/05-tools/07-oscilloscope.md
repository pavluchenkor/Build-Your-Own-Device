# Osciloscópio

Um osciloscópio mostra como um sinal muda ao longo do tempo.

Um multímetro pode mostrar "cerca de 3,3 V" ou "há frequência". Um osciloscópio mostra a forma do sinal: pulsos, bordas, queda, ruído, salto, pacotes UART, PWM.

![Screen of a digital oscilloscope](../../img/05-tools/07-digital-oscilloscope.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

Um sinal PWM na tela do osciloscópio se parece com isto:

![Animation of PWM: duty cycle change and signal waveform](../../img/05-tools/07-pwm-signal-waveform.gif)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

Você não precisa de um para cada construção simples. Mas quando um dispositivo se comporta de forma instável, um osciloscópio pode revelar em minutos o que um multímetro não consegue ver.

## O que você pode ver

Em dispositivos do tipo iDryer, um osciloscópio é útil para visualizar:

- fan PWM;
- MOSFET module PWM;
- UART `TX/RX`;
- 5V or 3.3V sag at servo startup;
- power supply noise;
- button bounce;
- tachometric fan signal;
- breves falhas que um multímetro calcula.

Um osciloscópio responde não apenas "existe tensão", mas "o que está acontecendo com o sinal ao longo do tempo".

## O aviso mais importante

A maioria dos osciloscópios de bancada tem o aterramento da ponta de prova conectado ao aterramento de proteção da rede elétrica.

Isto significa: o clipe de aterramento da sonda não é “apenas mais um fio”.

Se você conectar o clipe de aterramento a um ponto que não seja `GND` do circuito de baixa tensão, poderá criar um curto-circuito através do osciloscópio.

É especialmente perigoso entrar na parte da rede elétrica de 110-230 Vca, SSR, fonte de alimentação ou fontes de alta tensão com um osciloscópio normal.

Você não pode:

- desconecte o terra do osciloscópio para medição "flutuante";
- conecte o terra da sonda à fase ou outro ponto de tensão;
- medir a tensão da rede com uma sonda normal sem entender o circuito;
- suponha que os dois canais sejam completamente independentes: os aterramentos dos canais geralmente estão conectados entre si.

Para medições flutuantes, medições do lado alto e medições de alta tensão, você precisa de métodos adequados: sonda diferencial, dispositivo isolado ou outra abordagem segura.

## Como conectar uma sonda

Para circuitos de baixa tensão:

1. Conecte a ponta de prova ao osciloscópio.
2. Conecte o terra da sonda ao `GND` do dispositivo.
3. Conecte a ponta da sonda ao sinal.
4. Selecione a configuração correta da sonda: `10x` ou `10x`.
5. Certifique-se de que o osciloscópio esteja configurado para o mesmo fator.

Para a maioria dos sinais digitais, use `10x`: a ponta de prova carrega menos o circuito e geralmente mostra melhor o formato do sinal.

## PWM

PWM is a pulse signal.

O osciloscópio mostra:

- frequency;
- duty cycle;
- logic high level;
- logic low level;
- edges;
- jitter;
- noise.

Para um fã ou MOSFET isso ajuda a entender:

- se o pino emite algum sinal;
- se o nível de 3,3 V ou 5 V é suficiente;
- se a frequência corresponde à configuração;
- se o ciclo de trabalho muda sob comando;
- se o sinal não cede quando a carga está conectada.

## UART

O UART no osciloscópio parece uma sequência de pulsos.

O osciloscópio ajuda a ver:

- se há atividade no `TX`;
- se os níveis lógicos não são trocados;
- qual é o nível de inatividade;
- se há ruído forte;
- whether baud rate roughly matches.

Para decodificar texto, um analisador lógico ou adaptador USB-UART é mais conveniente. Mas um osciloscópio mostra rapidamente se o sinal está fisicamente ativo.

## Power supply sag

Um multímetro pode não detectar uma breve queda.

Por exemplo, quando um servo é iniciado, uma linha de 5V pode cair por alguns milissegundos. O multímetro mostra 5V quase normal, mas o driver já foi reiniciado.

An oscilloscope lets you see:

- quanta tensão cai;
- quanto tempo dura a flacidez;
- se há picos;
- whether a capacitor helps;
- se a situação muda com uma fonte de alimentação ou fios diferentes.

Isto é especialmente útil para ESP32, servos, ventiladores e DC-DC.

## Ruído e interferência

O ruído nas linhas de energia ou de sinal pode interromper os sensores e a comunicação.

An oscilloscope helps see:

- DC-DC ripple;
- motor spikes;
- barulho próximo ao aquecedor;
- button bounce;
- interferência em um fio longo.

Mas entenda os limites: uma conexão de aterramento deficiente da sonda pode adicionar ruído ao próprio display. Uma mola de aterramento de sonda curta ou um fio de aterramento curto geralmente fornecem uma imagem mais honesta do que um clipe longo.

## Multímetro com medição de frequência

Às vezes, um osciloscópio não é necessário para verificações iniciais.

Alguns multímetros podem medir a frequência do sinal. Nas especificações, isso pode ser chamado de `frequency`, `frequency counter` ou `frequency counter`.

Isso é útil se você precisar entender rapidamente:

- whether a PWM signal exists at all;
- se a frequência muda com o ajuste;
- se a saída do controlador funciona;
- se há atividade em uma linha digital simples.

Por exemplo, se um controlador emitir PWM para um ventilador ou módulo MOSFET, um multímetro de medição de frequência pode mostrar que o sinal existe e sua frequência corresponde aproximadamente ao valor esperado.

But a multimeter doesn't show signal shape. It won't show:

- logic high level;
- pulse width;
- PWM duty cycle;
- signal edges;
- brief dips;
- ruído e interferência;
- line distortion.

Portanto, um multímetro de medição de frequência é uma boa ferramenta para verificações rápidas, mas não é um substituto completo do osciloscópio.

## O que verificar antes de medir

Antes de conectar a probe:

1. O que é `GND` no circuito?
2. Este ponto está conectado ao terra de proteção da rede elétrica?
3. Não há tensão de rede?
4. A sonda está classificada para a tensão?
5. `10x` está selecionado se necessário?
6. A sonda e o canal estão configurados da mesma maneira?
7. Os aterramentos do canal não conectam diferentes pontos do circuito?
8. Você pode primeiro verificar o sinal no lado de baixa tensão?

Se você tiver dúvidas sobre 110-230V AC, não conecte o osciloscópio.

## Erros comuns

- clipe de aterramento conectado a um ponto de tensão, não `GND`;
- tentando “desconectar” o terra do osciloscópio da rede elétrica;
- medir a tensão da rede com uma sonda normal sem diferencial;
- esquecendo que os aterramentos do canal estão conectados;
- sonda definida como `1x`, osciloscópio definido como `1x`;
- usando sonda longa e vendo ruído extra;
- apenas olhando com um multímetro e perdendo uma breve queda;
- pensar que um problema UART é software quando não há sinal físico na linha.

## O essencial

- An oscilloscope shows signal shape over time.
- É útil para PWM, UART, queda de energia, ruído e falhas breves.
- Um aterramento normal do osciloscópio de bancada está conectado ao aterramento de proteção da rede elétrica.
- Você não pode conectar o aterramento da sonda a um ponto arbitrário do circuito.
- Para medições de rede e flutuantes, são necessários métodos especiais de segurança.
- Um multímetro de medição de frequência é útil, mas não um substituto do osciloscópio.

## Reference materials

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - basic practical introduction to oscilloscopes, signals and controls.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - grounding, setup, controls and basic oscilloscope use.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - warnings about probe ground, mains earth and danger of floating measurements with a normal oscilloscope.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - why disconnecting oscilloscope mains earth is dangerous and what safe alternatives exist.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight does not recommend bypassing grounding and suggests differential probes.
