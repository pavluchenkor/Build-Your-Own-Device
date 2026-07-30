---
title: "Filtro inteligente: composição do sistema (BOM)"
description: "Lista de componentes do filtro de ar: ESP32-C3, sensor VOC SGP40, ventilador 120 mm, filtros HEPA e de carvão, chave MOSFET, alimentação."
---

# Composição do sistema

Lista completa de componentes. Os preços são orientativos; tudo pode ser adquirido em qualquer marketplace.

## Eletrónica

| Componente | Exemplo | Preço | Finalidade |
|---|---|---|---|
| Placa ESP32-C3 | ESP32-C3 Super Mini ou semelhante | ~$3 | cérebro do dispositivo, Wi-Fi |
| Sensor VOC | SGP40 (módulo, I2C) | ~$4 | índice de qualidade do ar |
| Ventilador 120 mm, 12 V | qualquer ventilador de caixa, preferencialmente com rolamento hidráulico | ~$5 | circulação de ar através do filtro |
| Chave MOSFET | módulo AO3400/IRLZ44N ou módulo de chave MOSFET pronto | ~$1 | activação do ventilador a partir de GPIO 3.3V |
| Fonte de alimentação 12 V / 1 A | qualquer de boa qualidade | ~$4 | alimentação do ventilador |
| Módulo buck 12→5 V | mini-360 (buck) | ~$1 | alimentação de ESP32 a partir da mesma fonte |

Para a escolha de placas — [Controladores](../02-controllers/01-what-is-controller.md), para alimentação e módulos buck — [Eletrónica Básica](../01-electronics-basics/01-voltage-current-resistance.md).

## Parte filtrante

| Componente | Exemplo | Finalidade |
|---|---|---|
| Filtro HEPA | cartucho redondo de purificador de ar automóvel/doméstico | retém partículas |
| Carvão activado | grânulos em cassete ou manta de carvão | absorve VOC e odores |
| Caixa | impressa (você projeta o STL para seu filtro) ou qualquer caixa adequada | mantém tudo junto |

!!! note "Ordem das camadas"
    O ar deve passar: entrada → HEPA → carvão → ventilador → saída. O ventilador pode estar em modo de sopro após os filtros — assim o ar sujo não é aspirado através das fendas da caixa contornando o filtro, mas em geral isso não é crítico; trabalhamos com o número de trocas de ar por unidade de tempo, quanto maior o CFM do ventilador menor este tempo.

## Porque SGP40

- I2C, alimentação 3.3 V — liga-se ao ESP32 com dois fios de sinal;
- fornece **índice VOC** 0..500 (100 — «ar normal», mais alto — mais sujo), não requer calibração;
- existe uma biblioteca Adafruit pronta.

Alternativas:

- **ENS160** — índice VOC + estimativa de eCO2, também I2C. Boa opção «dois em um»;
- **MH-Z19B/C** — verdadeiro sensor NDIR de CO2 (ppm), UART, ~$20. Excessivo para um filtro.

## Ferramentas

Ferro de solda, flux, solda, multímetro, tubo termorretráctil. Detalhes — [Ferramentas](../05-tools/01-multimeter.md).
