# Erros Comuns

Esta seção não está aqui para o criticar.

Está aqui para ajudá-lo a identificar rapidamente erros comuns num dispositivo DIY: fonte de alimentação a desfalecer, fio solto, sensor mostrando lixo, controlador reiniciando, aquecedor comportando-se estranhamente.

O formato da seção é directo:

- sintoma;
- causa provável;
- o que verificar;
- o que não fazer;
- como corrigir com segurança.

## A Regra Principal de Diagnóstico

Se o dispositivo se comporta estranhamente, não altere imediatamente o firmware, ressoldou tudo ou aumente a potência.

Primeiro, verifique o básico:

1. fonte de alimentação;
2. polaridade;
3. `GND` comum;
4. terminais e conectores;
5. sensores;
6. interruptores de alimentação;
7. firmware e configuração.

A maioria dos problemas em dispositivos simples acaba por não ser "eletrônica complexa", mas fonte de alimentação, orientações ou conexões incorretas.

## Quando Parar

Desligue a alimentação imediatamente se:

- cheiro de queimado aparece;
- fio está a aquecer;
- terminal está a aquecer;
- conector está a escurecer;
- gabinete se tornou quente num lugar inesperado;
- aquecedor não desliga;
- disjuntor ou fusível salta;
- sensor de temperatura mostra lixo;
- dispositivo funciona apenas quando move o fio.

Não "ligue uma mais vez para olhar". Se algo está a aquecer, cheirar ou centelhar, procure a causa primeiro sem alimentação.

## Principais Grupos de Erros

Nesta seção, os erros são divididos em grupos:

- `02-power-mistakes.md` - fonte de alimentação fraca, tensão incorreta, desfalecimento, fios finos, sem margem.
- `03-wiring-mistakes.md` - polaridade invertida, terminais fracos, sem terra comum, conectores defeituosos.
- `04-controller-mistakes.md` - placa inadequada, lógica 3.3V/5V, GPIO em vez de saída de alimentação, firmware incorreto.
- `05-heater-ssr-mistakes.md` - aquecedores, SSR, MOSFET, 110-230V AC, sensor de temperatura, dissipadores de calor e protecção.
- `06-diagnostic-checklist.md` - ordem de verificação geral quando o dispositivo não funciona.

## Porque a Fonte de Alimentação é Verificada Primeiro

A fonte de alimentação afeta quase tudo.

Se a fonte de alimentação for fraca ou os fios forem finos, os sintomas podem parecer um problema de firmware:

- controlador reinicia;
- Wi-Fi cai;
- display cintila;
- servomotor se move aos solavancos;
- ventoinha não arranca;
- sensores mostram valores aleatórios;
- aquecedor aquece mal.

Até que a fonte de alimentação seja verificada com um multímetro sob carga, é difícil diagnosticar com confiança tudo o resto.

## Porque a Fiação é Mais Importante do que Parece

Uma conexão pobre pode funcionar "quase normalmente".

Isto é exactamente o que é perigoso:

- hoje funciona;
- quando vibrado desconecta;
- quando aquecido, o contacto piora;
- terminal gradualmente escurece;
- fio começa a aquecer;
- sensor aparece e desaparece.

Se o dispositivo muda de comportamento quando move o fio, isto não é um erro de software. Este é um problema de conexão.

## Porque a Protecção Não Deve Ser Desactivada

Fuga térmica, `MINTEMP`, `MAXTEMP`, `aquecedor não aquecendo` e erros similares não existem para aborrecê-lo.

Estes são sinais de que o controlador já não confia na leitura de temperatura ou vê comportamento de aquecimento perigoso.

Má ideia:

- desactivar protecção térmica;
- expandir limites de temperatura sem compreender a razão;
- substituir o fusível por um maior;
- curto-circuitar o termóstato diretamente;
- curto-circuitar a protecção "para teste".

Ideia correta: procure a razão para a protecção disparar.

## Como Ler Esta Seção

Se o dispositivo não funciona totalmente, comece com a lista de verificação de diagnóstico.

Se o sintoma for claro, vá para o artigo relevante:

- reinicializações, cintilação, calor fraco - fonte de alimentação;
- funciona quando move o fio - fiação;
- placa não detectada ou pinos não respondendo - controlador;
- aquecedor não desliga ou SSR está a aquecer - aquecedor e SSR;
- tudo pouco claro - lista de verificação geral.

## Pontos-chave

- A maioria dos erros começa com alimentação, fiação e ligações incorretas.
- Se algo está a aquecer, cheirar ou escurecer, desligue a alimentação.
- O diagnóstico procede do simples para o complexo.
- A protecção de firmware e a protecção de hardware não devem ser desactivadas por conveniência.
- A rede AC 110-230V não pode ser diagnosticada "na bancada" sem compreender a segurança elétrica.

## References

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - basic approach to checking connections, power supply, heating, and hardware problems.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - voltage, current, and selecting power for an electronic project.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - practical analysis of temperature sensor, heater, fan, power supply, and wiring during thermal runaway.
- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - official heater verification and temperature sensor checking by expected temperature rise and accumulated error.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - example of the need for common `GND` when measuring/controlling external load.
