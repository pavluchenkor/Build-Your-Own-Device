# Multímetro

Um multímetro é a principal ferramenta de diagnóstico de primeira linha.

Você pode verificar com ele:

- se há energia presente;
- se a tensão está correta;
- onde está o positivo e negativo;
- se um fio está quebrado;
- se um fusível está intacto;
- se um termistor parece estar funcional;
- se há queda de tensão sob carga.

Mas é fácil cometer erros com um multímetro se confundir os modos. Os erros mais perigosos envolvem medir corrente e tensão de rede.

## Sondas e Portas

Um multímetro típico tem:

- `COM` - porta comum, onde você quase sempre insere a sonda preta;
- `V/Ohm/mA` ou semelhante - para tensão, resistência, continuidade e pequenas correntes;
- `10A` ou `A` - porta separada para corrente grande.

Antes de medir, sempre verifique:

- qual porta a sonda vermelha está inserida;
- qual modo está selecionado;
- exactamente o que você está prestes a medir.

Um erro muito comum: após medir corrente, você esquece de mover a sonda de `A` de volta para `V/Ohm`, depois tenta medir tensão. Isto pode causar curto-circuito.

## Medindo Tensão DC

DC é tensão directa (constante). Nos nossos dispositivos isto é geralmente:

- `3.3V`;
- `5V`;
- `12V`;
- `24V`.

Procedimento:

1. Sonda preta em `COM`.
2. Sonda vermelha na porta `V`.
3. Selecione modo de tensão DC: geralmente `V` com linha recta.
4. Sonda preta em negativo ou `GND`.
5. Sonda vermelha em positivo.
6. Leia o visor.

Se um sinal de menos aparece antes do número no visor, as sondas estão trocadas. Isto é útil: você pode determinar a polaridade desta forma.

![Multímetro digital com sondas](../../img/05-tools/02-digital-multimeter.jpg)

*Fonte: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Onde Medir Tensão

Não se limite apenas à saída da fonte de alimentação.

Verifique:

- nos terminais da fonte de alimentação;
- na entrada da placa;
- nos terminais da carga;
- num módulo DC-DC;
- no ventoinha;
- num servo;
- numa tira LED.

Se a fonte de alimentação mostra 24V mas a carga mostra notavelmente menos, procure por queda nos fios, terminais ou conectores.

Para diagnóstico de fonte de alimentação, é importante medir sob carga, não apenas em vazio.

## Medindo Tensão AC

AC é tensão alternada, como 110-230V da rede.

A tensão da rede é perigosa.

Se não compreender o que está a fazer, não meça partes de rede abertas com um multímetro. Melhor usar módulos seguros prontos para usar, terminais fechados e ajuda de especialista.

Se medir, você precisa:

- um multímetro com categoria de segurança **CAT II** ou **CAT III** — isto está escrito no corpo do dispositivo junto à tensão, por exemplo `CAT II 600V`. CAT I não é adequado para rede doméstica. CAT III e CAT IV fornecem margem extra para instalações mais complexas;
- sondas em funcionamento apropriado com categoria não inferior ao multímetro;
- mãos secas;
- montagem fechada e estável;
- compreensão de onde estão a fase e neutro;
- sem pontos de contacto acidental abertos.

Para a maioria das tarefas envolvendo eletrônica de baixa tensão, medições DC são suficientes.

## Verificação de Continuidade

Continuidade mostra se dois pontos estão electricamente conectados.

É útil para verificar:

- se um fio está intacto;
- se `GND` está conectado;
- se um cabo não está quebrado;
- se um botão funciona;
- se um fusível está intacto;
- se contactos vizinhos não estão em curto.

Procedimento:

1. Desligue a energia.
2. Coloque o multímetro em modo de continuidade: geralmente um ícone de som ou símbolo de díodo.
3. Toque as sondas uma à outra - deve haver um bip.
4. Toque os dois pontos que deseja verificar.
5. Se der bip, existe uma conexão condutora entre os pontos.

A verificação de continuidade é feita num circuito desenergizado.

## Resistência

A resistência é medida em ohms.

Para as nossas tarefas isto é necessário para:

- verificar um termistor;
- verificar fio quebrado;
- verificar um fusível;
- determinar se existe curto-circuito;
- verificar um resistor.

Importante: a resistência é apenas medida num circuito desenergizado.

Se medir resistência numa placa energizada, pode obter leituras incorretas ou danificar o multímetro.

## Testando um Termistor

Para um NTC típico `100K` à temperatura ambiente, espere dezenas ou cerca de `100 kOhm`.

Se o multímetro mostrar:

- `OL` ou infinito - provável circuito aberto;
- quase `0 Ohm` - provável curto-circuito;
- valor flutuando muito quando move o fio - mau contacto;
- resistência diminuindo quando aquecida pelos seus dedos - parece um NTC vivo.

Os valores exactos dependem do tipo de termistor e da temperatura.

## Medindo Corrente

Medir corrente é mais perigoso do que medir tensão.

A tensão é medida em paralelo: as sondas tocam dois pontos.

A corrente é medida em série: você deve quebrar o circuito e conectar o multímetro na linha para que a corrente flua através do dispositivo.

Erro - colocar o multímetro em modo de corrente e tocar as sondas no mais e menos da fonte de alimentação. Isto é quase um curto-circuito através do multímetro.

Para um iniciante é melhor:

- primeiro calcular corrente a partir de potência;
- usar medidores de watts/medidor de potência USB/medidor de potência DC prontos;
- medir corrente apenas se compreender como conectar o multímetro em série;
- começar com o intervalo correto e porta correta.

## Verificando um Fusível

Verifique o fusível num circuito desenergizado.

Métodos:

- continuidade;
- medição de resistência.

Um fusível bom geralmente mostra continuidade e tem resistência muito baixa.

Um fusível queimado geralmente não mostra continuidade.

Se um fusível queimou, você não pode apenas instalar um de classificação superior. Primeiro encontre a causa.

## Como Não Queimar o Multímetro

Regras mínimas:

- verifique o modo antes de medir;
- verifique a porta da sonda vermelha antes de medir;
- não meça resistência num circuito energizado;
- não meça corrente como tensão;
- não vá para 110-230V AC sem compreender segurança;
- comece com um intervalo superior se o multímetro não for autovariável;
- usar sondas em funcionamento;
- não toque as dicas metálicas com seus dedos.

## Cenários Práticos

Verifique uma fonte de alimentação 24V:

1. Modo de tensão DC.
2. Sonda preta em negativo.
3. Sonda vermelha em positivo.
4. Deve ler cerca de 24V.

Verifique um ventoinha:

1. Meça tensão no conector do ventoinha.
2. Verifique polaridade.
3. Verifique tensão durante arranque.

Verifique fio quebrado:

1. Desligue a energia.
2. Modo de continuidade.
3. Sondas em ambas as extremidades do fio.
4. Sem bip - possível circuito aberto.

Verifique curto entre `+` e `GND`:

1. Desligue a energia.
2. Verifique continuidade entre `+` e `GND`.
3. Se der bip onde não deveria, procure um curto.

## Os Essenciais

- Para tensão DC use o modo `V` com linha reta.
- Resistência e continuidade são apenas feitas em circuitos desenergizados.
- Corrente é medida em série, não em paralelo.
- Após medir a corrente, mova a sonda de `V/Ohm` de volta para a porta normal `V/Ohm`.
- Tensão de rede é perigosa; não meça partes abertas 110-230V sem compreender segurança.
- Um multímetro sob carga frequentemente revela problemas invisíveis quando inativo.

## Materiais de Referência

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - guia prático para tensão, corrente, resistência, continuidade e portas de multímetro.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - medição segura de resistência.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - medir tensão AC e ordem de conexão de sonda.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - verificação de continuidade e busca de circuito aberto.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - por que portas de entrada de corrente precisam de fusíveis apropriados com tensão e classificação de interrupção corretas.
