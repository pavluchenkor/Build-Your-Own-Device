---
title: "Filtro inteligente: início do firmware e vinculação ao portal"
description: "Estrutura base do firmware do filtro em idryer-core: configuração de tipo de dispositivo não-padrão, primeiro lançamento, vinculação à conta por PIN."
---

# Início do firmware

A estrutura do projeto repete completamente o [capítulo do exemplo do gabinete](../09-build-a-device/04-firmware-start.md): PlatformIO, `secrets.h`, `idryer-core` em `lib/`, o mesmo `platformio.ini` (apenas mude o nome do ambiente para `filter`). Aqui — apenas o que é diferente.

## Config: dispositivo de tipo não-padrão

O filtro não tem nem aquecedor, nem sensor de clima do dicionário do ecossistema. Do vocabulário do ecossistema, ele só tem ventilador. Em `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // dispositivo não-padrão
    .unitsCount        = 1,
    // Periféricos: do vocabulário do ecossistema, temos apenas ventilador.
    .hasFan            = true,
    // Períodos de publicação automática:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identificação no portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Air Filter",
};

static iDryer::Link s_link(CFG);

void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

!!! note "DeviceType::Unknown — é normal"
    O tipo `Unknown` significa "o portal não conhece este produto". Antes era um problema: o portal não tinha um cartão para um tipo desconhecido. Agora é o caminho padrão: a interface do dispositivo será totalmente descrita pelo manifesto do cartão ([capítulo 6](06-card.md)), e o portal construirá o cartão a partir dele. O tipo é necessário apenas para os próprios produtos iDryer, que têm cartões de marca.

A flag `hasFan = true` nos dá gratuitamente: campo `fanStatus` na telemetria, célula "Ventilador" no cartão e entidade no manifesto — tudo do vocabulário do ecossistema.

## VOC-sensor não está na Config — e não deveria estar

Observe: não há flag "hasVoc" na `Config`. O dicionário `has*` descreve periféricos conhecidos do ecossistema. Seu sensor customizado é adicionado não através do dicionário, mas através de dois outros mecanismos: você adiciona suas leituras à telemetria em seu próprio campo e o declara no manifesto do cartão — estes são os dois próximos capítulos. Esta é a essência da abordagem: o dicionário não precisa ser expandido para cada novo dispositivo.

## Primeiro lançamento e vinculação

O procedimento é idêntico ao exemplo do gabinete:

1. Carregue a placa e abra o Serial Monitor.
2. O dispositivo ativa Wi-Fi (dados de `secrets.h`), se registra e imprime o PIN:
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. No [portal](https://portal.idryer.org/) — "Adicionar dispositivo" → insira o PIN.
4. Após a vinculação, o log mostrará `Device claimed!`, o dispositivo entrará em `Online`.

Discussão detalhada de vinculação, erros de Wi-Fi e revinculação — no [capítulo do exemplo do gabinete](../09-build-a-device/04-firmware-start.md).

O dispositivo já é visível no portal, mas o cartão está quase vazio — ainda não há dados. Vamos conectar o sensor.
