---
title: "Arranque de firmware em idryer-core: primeira execução e vinculação ao portal"
description: "Criação de projecto PlatformIO na biblioteca idryer-core: platformio.ini, secrets.h, Config do dispositivo, primeiro firmware de ESP32 e vinculação ao portal iDryer."
---

# Arranque de firmware no núcleo

Nesta página você cria um projecto de firmware, leva o ESP32 ao estado Online no portal e verifica que a parte de rede funciona. Sensores e lógica de aquecimento adicionamos nos passos seguintes.

A abordagem é construída na fachada `iDryer::Link`. Você descreve o dispositivo com uma estrutura `iDryer::Config`, chama `link.begin()` e `link.loop()` - o núcleo faz toda a ligação de rede.

## 1. Prepare as ferramentas

Você vai precisar de:

- VS Code com extensão PlatformIO;
- cabo USB;
- rede Wi-Fi `2,4 GHz` (ESP32 não funciona com redes só `5 GHz`).

O que é firmware do controlador e como entra na placa - [Firmware do controlador](../02-controllers/11-flashing-controller.md).

## 2. Crie um projecto

Em PlatformIO um projecto é uma pasta com estrutura fixa. Crie uma pasta de projecto (por exemplo `my-cabinet`) e abra-a em VS Code. Dentro devem estar estes ficheiros:

```text
my-cabinet/
├── platformio.ini        # configurações de construção (preenchidas no passo 4)
├── include/
│   └── secrets.h         # SSID e senha Wi-Fi (passo 3)
├── lib/
│   └── idryer-core/      # biblioteca do núcleo (symlink ou cópia)
└── src/
    └── main.cpp          # código do dispositivo: Config + setup() + loop()
```

Todos os fragmentos de código abaixo vão para estes ficheiros - cada passo especifica qual. Crie as pastas `include/`, `lib/` e `src/` manualmente se não existirem.

Coloque a biblioteca `idryer-core` em `lib/` - PlatformIO encontra bibliotecas lá automaticamente. A maneira mais fácil é fazer um symlink para a biblioteca transferida:

```bash
ln -s /caminho/para/idryer-core lib/idryer-core
```

Isto também é necessário para gerar menu (capítulo 6) - o hook procura o gerador dentro de `lib/idryer-core/`.

## 3. Crie secrets.h

Copie o exemplo `secrets.h.example` da biblioteca para `include/secrets.h` do seu projecto e forneça os dados da sua rede:

```cpp
#define WIFI_SSID      "seu-ssid"
#define WIFI_PASSWORD  "sua-senha"
```

Adicione `include/secrets.h` ao `.gitignore` para que a senha não vá para o repositório.

## 4. Configure platformio.ini

Preencha `platformio.ini` na raiz do projecto:

```ini
[env:cabinet]
platform    = espressif32
framework   = arduino
board       = esp32-c3-devkitm-1

lib_deps =
    bblanchon/ArduinoJson @ ^6.21.0
    knolleary/PubSubClient
    densaugeo/base64 @ ^1.4.0
    links2004/WebSockets @ ^2.4.0
    https://github.com/jnthas/Improv-WiFi-Library.git

build_flags =
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1
```

Substitua `board` pela sua placa (por exemplo, `esp32-s3-devkitc-1`). Não precisa de especificar `idryer-core` em `lib_deps` - ela está em `lib/` (passo 2).

!!! note "Por que todas estas dependências"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` e `Improv-WiFi-Library` são necessários para a própria biblioteca `idryer-core` (MQTT, acesso WebSocket por LAN, Wi-Fi provisioning). Sem qualquer uma delas a construção cai com um erro como `... .h: No such file`. As flags `MQTT_BROKER` e `MQTT_PORT` também são obrigatórias - sem elas o núcleo não compila (`'MQTT_BROKER' was not declared`).

## 5. Descreva o dispositivo em Config

A seguir tudo acontece num ficheiro - `src/main.cpp`. Abra-o e escreva o código deste e dos passos seguintes.

`iDryer::Config` é o passaporte do dispositivo. As flags `has*` dizem ao portal o que o dispositivo tem e determinam quais campos de telemetria são publicados.

Para o armário aquecido no início de `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Periféricos:
    .hasHeater         = true,    // aquecedor controlado
    .hasFan            = true,    // ventoinha
    .hasAirTemp        = true,    // temperatura do ar (SHT31)
    .hasAirHumidity    = true,    // humidade do ar (SHT31)
    .hasHeaterTemp     = true,    // temperatura do aquecedor (termistor)
    // Períodos de autopublicação:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identificação no portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Flags has* - isto é um contrato com o portal"
    Um campo de telemetria cuja flag correspondente é `false` não é publicado. Por exemplo, sem `hasAirHumidity = true` a humidade não vai para a nuvem, mesmo que a escreva no código. Incluir apenas o que fisicamente existe no dispositivo.

A lista de componentes e flags - [Composição do sistema](02-bom.md).

## 6. Programa principal mínimo

No mesmo ficheiro após o bloco `Config` adicione as funções `setup()` e `loop()`. Para primeira execução é suficiente iniciar a ligação e executá-la em `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Isto é o suficiente para o dispositivo se ligar a Wi-Fi e ir online no portal. Sensores adicionamos no passo [Sensores](05-sensors.md).

### Completo `src/main.cpp` após este capítulo

Pegue nos dois blocos acima num ficheiro - este é todo o `src/main.cpp` neste passo:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    .hasHeater         = true,
    .hasFan            = true,
    .hasAirTemp        = true,
    .hasAirHumidity    = true,
    .hasHeaterTemp     = true,
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
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

O capítulo anterior mostra o que **adicionar** e o **completo `src/main.cpp` após as mudanças**, para que sempre veja a imagem inteira, não fragmentos dispersos.

## 7. Grave o firmware

```bash
pio run -e cabinet -t upload
```

## 8. Abra Serial Monitor

```bash
pio device monitor -b 115200
```

Sequência esperada no log:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Se o dispositivo parou na linha `PIN: ...` - isto é normal. Vá para vinculação.

## 9. Vincule o dispositivo ao portal

1. Abra [portal.idryer.org](https://portal.idryer.org/).
2. Vá para a secção **Add device**.
3. Introduza o PIN do Serial Monitor.

Após vinculação o dispositivo muda para estado `Online`. No log aparecerá:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Verificação de resultado

Neste passo o dispositivo deve estar Online no portal. Dados dos sensores ainda não existem - isto é esperado. Se o dispositivo não se conecta:

- verifique que a rede é `2,4 GHz` e a senha em `secrets.h` está correcta;
- verifique alimentação de ESP32 (quedas ao iniciar Wi-Fi - causa frequente de reinicializações);
- veja [Erros de potência](../08-common-mistakes/02-power-mistakes.md) e [Erros de controladores](../08-common-mistakes/04-controller-mistakes.md).

## O que vem a seguir

A parte de rede funciona. Vá para [Sensores](05-sensors.md): ligaremos SHT31 e termistor e veremos os dados no portal.
