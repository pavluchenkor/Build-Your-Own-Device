---
title: "Filtro inteligente: início da firmware e ligação ao portal"
description: "Estrutura da firmware do filtro em idryer-core: Config para tipo de dispositivo não-standard, primeira execução, ligação à conta por PIN."
---

# Início da firmware

A estrutura do projeto repete inteiramente [o capítulo do exemplo com o armário](../09-build-a-device/04-firmware-start.md): PlatformIO, `secrets.h`, `idryer-core` em `lib/`, mesmo `platformio.ini` (substitua apenas o nome do ambiente para `filter`). Aqui — apenas o que é diferente.

## Config: dispositivo de tipo não-standard

O filtro não tem nem aquecedor nem sensor de clima do dicionário do ecossistema. Das capacidades do dicionário tem apenas ventilador. Em `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // dispositivo não-standard
    .unitsCount        = 1,
    // Periféricos: do dicionário do ecossistema temos apenas ventilador.
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

!!! note "DeviceType::Unknown — isto é normal"
    O tipo `Unknown` significa «o portal não conhece este produto». Anteriormente era um problema: o portal não tinha cartão para tipo desconhecido. Agora é o caminho padrão: a interface do dispositivo será completamente descrita pelo manifesto de cartão ([capítulo 6](06-card.md)), e o portal construirá o cartão a partir dele. O tipo é necessário apenas para produtos «próprios» do iDryer que têm cartões comerciais.

A flag `hasFan = true` nos dá gratuitamente: campo `fanStatus` na telemetria, célula «Ventilador» no cartão e entidade no manifesto — tudo do dicionário do ecossistema.

## Sensor VOC não existe em Config — e não deveria existir

Note: em `Config` não há flag «hasVoc». O dicionário `has*` descreve periféricos conhecidos pelo ecossistema. O seu sensor próprio adiciona-o não através do dicionário, mas por dois outros mecanismos: acrescenta os seus dados à telemetria no seu próprio campo e declara-o no manifesto de cartão — são os próximos dois capítulos. Nisto reside a essência da abordagem: o dicionário não precisa de ser expandido para cada novo dispositivo.

## Primeira execução e ligação

O procedimento não difere do exemplo com o armário:

1. Carregue o código na placa, abra o Serial Monitor.
2. O dispositivo levantará Wi-Fi (dados de `secrets.h`), registar-se-á e imprimirá o PIN:
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. No [portal](https://portal.idryer.org/) — «Adicionar dispositivo» → insira o PIN.
4. Após a ligação no log aparecerá `Device claimed!`, o dispositivo mudará para `Online`.

Análise detalhada de ligação, erros de Wi-Fi e religação — [capítulo do exemplo com o armário](../09-build-a-device/04-firmware-start.md).

No portal o dispositivo é já visível, mas o cartão está quase vazio — ainda não há dados. Vamos ligar o sensor.
