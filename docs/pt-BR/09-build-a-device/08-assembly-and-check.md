---
title: "Montagem do gabinete aquecido e verificacao antes do lancamento"
description: "Montagem final do gabinete caseiro em ESP32: instalacao no gabinete, primeiro aquecimento, calibracao de temperatura e lista de verificacao de seguranca antes do funcionamento permanente."
---

# Montagem e verificacao

Nesta pagina voce monta o dispositivo no gabinete, faz o primeiro aquecimento controlado e verifica que o gabinete funciona com seguranca. Faca as verificacoes em ordem e nao deixe o dispositivo sem supervisao no primeiro lancamento.

## Ordem de montagem

1. Fixe o ESP32 e a parte de potencia no gabinete de forma que as zonas de sinal fraco e de potencia estejam separadas.
2. Coloque o sensor SHT31 no gabinete longe do fluxo direto do aquecedor — senao ele mostrara a temperatura do jato, nao do ar no volume.
3. Fixe o termistor em contato termico com o aquecedor.
4. Verifique que os fios nao tocam o aquecedor e nao caem no ventilador.
5. Na versao B (`220V`) certifique-se que os fios de rede sao fixos nos terminais, a isolacao esta intacta, o gabinete e aterrado.

Requisitos para o gabinete e colocacao dos nos — [Projeto de gabinete](../07-3d-printing/05-enclosure-design.md).

!!! warning "Pecas plasticas perto do aquecimento"
    PLA amolece na temperatura que facilmente se encontra perto do aquecedor. Pecas perto do calor imprima em material termoresistente. Veja [Materiais termoresistentes](../07-3d-printing/04-heat-resistant-materials.md) e [Por que PLA e uma escolha arriscada](../07-3d-printing/06-why-pla-is-risky.md).

## Verificacao antes de energizar

Teste com multimetro antes do primeiro lancamento:

- sem curtos entre alimentacao e terra;
- alimentacao de sensores `3.3V`, nao `5V`;
- terra comum do controlador e bloco de potencia;
- termistor e resistor divisor montados corretamente;
- na versao B — aterramento do gabinete e fusivel em lugar.

Como usar multimetro — [Multimetro](../05-tools/02-multimeter.md).

## Primeiro lancamento

1. Forne energia apenas ao controlador e sensores (nao conecte a carga ainda, se possivel).
2. Certifique-se que o dispositivo esta Online no portal e mostra temperatura e umidade.
3. Conecte o aquecedor e ventilador.
4. Inicie o modo de manutencao de calor no portal e observe.

!!! danger "Nao deixe o primeiro aquecimento sem supervisao"
    No primeiro lancamento, supervise o dispositivo. Certifique-se que o aquecedor desliga ao atingir a meta e pela protecao do termistor, nao aquece continuamente.

O que observar nos primeiros minutos:

- temperatura do ar sobe e estabiliza perto da meta;
- temperatura do aquecedor nao excede o limite definido;
- o aquecimento desliga ao atingir a meta e liga novamente apos esfriar na quantidade de histerese;
- o ventilador funciona e nao pega os fios;
- o controlador nao se reinicializa quando a carga liga.

## Calibracao

Apos o primeiro aquecimento, compare as leituras com um termometro separado no gabinete:

- se a temperatura do ar no gabinete difere da meta — verifique a colocacao do SHT31 (nao deve estar no jato ou na parede);
- se a temperatura do aquecedor parece improvavel — verifique o tipo de termistor e valor de resistor do divisor;
- se necessario, corrija a temperatura-alvo e histerese no [menu](06-menu.md).

## Se algo nao funciona

| Sintoma | Onde procurar |
|---------|---------------|
| Controlador se reinicializa na carga | [Erros de potencia](../08-common-mistakes/02-power-mistakes.md) |
| Sensor mostra bobagem | [Erros de fiacao](../08-common-mistakes/03-wiring-mistakes.md), [Verificacao de termistor](../06-practical-guides/02-checking-thermistor.md) |
| Dispositivo nao conecta ao Wi-Fi | [Erros de controlador](../08-common-mistakes/04-controller-mistakes.md) |
| Aquecedor/SSR aquece muito | [Erros de aquecedor e SSR](../08-common-mistakes/05-heater-ssr-mistakes.md) |

Sequencia geral de diagnostico — [Lista de verificacao de diagnostico](../08-common-mistakes/06-diagnostic-checklist.md).

## Lista de verificacao antes de funcionamento permanente

- [ ] Dispositivo mantem temperatura-alvo e nao aquece continuamente.
- [ ] Protecao do aquecedor por termistor funciona.
- [ ] Fios nao tocam o aquecedor e ventilador.
- [ ] Pecas plasticas perto do calor sao termoresistentes.
- [ ] Na versao B: gabinete e aterrado, fusivel instalado, isolacao intacta.
- [ ] Dados no portal correspondem a temperatura real no gabinete.

## Resultado

Voce montou um gabinete aquecido de armazenamento de filamento em ESP32 e `idryer-core`: o dispositivo le o clima e temperatura do aquecedor, mantem temperatura especificada, protege o aquecedor de superaquecimento e e controlado do portal. E uma base completa sobre a qual voce pode construir seus proprios modulos de ecossistema.

Componentes posteriores — iluminacao, balanca, RFID — o nucleo tambem suporta; eles podem ser adicionados pelo mesmo esquema: sensor ou periferia → telemetria ou comando → exibicao no portal.
