---
title: "Inicialização de firmware em idryer-core: primeiro lançamento e vinculação ao portal"
description: "Criando um projeto PlatformIO na biblioteca idryer-core: platformio.ini, secrets.h, Config do dispositivo, primeiro flash ESP32 e vinculação ao portal iDryer."
---

# Início da firmware no núcleo

Nesta página, você cria um projeto de firmware, coloca o ESP32 no estado Online no portal e verifica que a parte de rede funciona. Sensores e lógica de aquecimento serão adicionados nos próximos passos.

A abordagem é construída na fachada `iDryer::Link`. Você descreve o dispositivo com uma estrutura `iDryer::Config`, chama `link.begin()` e `link.loop()` — o núcleo cuida de toda a conexão de rede sozinho.

## 1. Prepare as ferramentas

Você vai precisar:

- VS Code com extensão PlatformIO;
- Cabo USB;
- Rede Wi-Fi `2.4 GHz` (ESP32 não funciona com redes apenas `5 GHz`).

O que é firmware do controlador e como ele entra na placa — [Firmware do controlador](../02-controllers/11-flashing-controller.md).

## 2. Crie um projeto

No PlatformIO, um projeto é uma pasta com estrutura fixa. Crie uma pasta de projeto (por exemplo `my-cabinet`) e abra-a em VS Code. Dentro devem haver esses arquivos:

```text
my-cabinet/
├── platformio.ini        # configurações de build (preencheremos na etapa 4)
├── include/
│   └── secrets.h         # login e senha Wi-Fi (etapa 3)
├── lib/
│   └── idryer-core/      # biblioteca de núcleo (symlink ou cópia)
└── src/
    └── main.cpp          # código do dispositivo: Config + setup() + loop()
```

Todos os fragmentos de código abaixo vão para esses arquivos — cada etapa indica onde. Crie as pastas `include/`, `lib/` e `src/` manualmente, se não existirem.

Coloque a biblioteca `idryer-core` em `lib/` — PlatformIO encontra bibliotecas lá automaticamente. A forma mais fácil é fazer um symlink para a biblioteca baixada:

```bash
ln -s /caminho/para/idryer-core lib/idryer-core
```

Isso também é necessário para a geração de menu (capítulo 6) — o hook procura o gerador dentro de `lib/idryer-core/`.

## 3. Crie secrets.h

Copie o exemplo `secrets.h.example` da biblioteca para `include/secrets.h` do seu projeto e especifique os dados da sua rede:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Adicione `include/secrets.h` ao `.gitignore` para que a senha não vá para o repositório.

## 4. Configure platformio.ini

Preencha `platformio.ini` na raiz do projeto:

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

Substitua `board` pela sua placa (por exemplo, `esp32-s3-devkitc-1`). Você não precisa especificar `idryer-core` em `lib_deps` — ela está em `lib/` (etapa 2).

!!! note "Por que todas essas dependências"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` e `Improv-WiFi-Library` são necessários para a própria biblioteca `idryer-core` (MQTT, acesso WebSocket em LAN, Wi-Fi provisioning). Sem qualquer um deles a build cai com erro como `... .h: No such file`. Os sinalizadores `MQTT_BROKER` e `MQTT_PORT` também são obrigatórios — sem eles o núcleo não compila (`'MQTT_BROKER' was not declared`).

## 5. Descreva o dispositivo em Config

A seguir tudo acontece em um arquivo — `src/main.cpp`. Abra-o e escreva o código desta e das próximas etapas.

`iDryer::Config` é o passaporte do dispositivo. Os sinalizadores `has*` dizem ao portal o que o dispositivo tem e determinam quais campos de telemetria são publicados.

Para o gabinete aquecido no topo de `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Periféricos:
    .hasHeater         = true,    // aquecedor controlado
    .hasFan            = true,    // ventilador
    .hasAirTemp        = true,    // temperatura do ar (SHT31)
    .hasAirHumidity    = true,    // umidade do ar (SHT31)
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

!!! note "Sinalizadores has* — é um contrato com o portal"
    Um campo de telemetria cujo sinalizador correspondente é `false` não é publicado. Por exemplo, sem `hasAirHumidity = true`, a umidade não vai para a nuvem, mesmo que você escreva no código. Inclua apenas o que fisicamente existe no dispositivo.

Lista de componentes e sinalizadores — [Composição do sistema](02-bom.md).

## 6. Função main mínima

No mesmo arquivo após o bloco `Config`, adicione as funções `setup()` e `loop()`. Para o primeiro lançamento é suficiente iniciar o link e rodá-lo em `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Isto é suficiente para o dispositivo se conectar ao Wi-Fi e ir para o portal. Sensores serão adicionados na etapa [Sensores](05-sensors.md).

### Completo `src/main.cpp` após este capítulo

Pegue ambos os blocos acima em um arquivo — este é todo o `src/main.cpp` nesta etapa:

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

O capítulo anterior mostra **o que adicionar** e **o `src/main.cpp` completo após as mudanças**, para que você sempre veja o quadro geral, não fragmentos dispersos.

## 7. Flash

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

Se o dispositivo parou na linha `PIN: ...` — é normal. Vá para vinculação.

## 9. Vincule o dispositivo ao portal

1. Abra [portal.idryer.org](https://portal.idryer.org/).
2. Vá para a seção **Add device**.
3. Digite o PIN do Serial Monitor.

Após vinculação o dispositivo muda para o status `Online`. No log aparece:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Verificação de resultado

Nesta etapa o dispositivo deve estar Online no portal. Dados de sensores ainda não há — é esperado. Se o dispositivo não se conecta:

- verifique que a rede é `2.4 GHz` e a senha em `secrets.h` está correta;
- verifique alimentação ESP32 (quedas durante boot Wi-Fi são causa comum de reinicializações);
- veja [Erros de potência](../08-common-mistakes/02-power-mistakes.md) e [Erros de controlador](../08-common-mistakes/04-controller-mistakes.md).

## O que vem a seguir

A parte de rede funciona. Vá para [Sensores](05-sensors.md): vamos conectar SHT31 e termistor e ver seus dados no portal.
