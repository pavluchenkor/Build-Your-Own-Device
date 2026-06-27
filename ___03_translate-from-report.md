# Translation Orchestrator — режим списка задач

## Твоя роль
Ты — оркестратор перевода. Тебе передан готовый отчёт валидатора.
НЕ делай инвентаризацию папок. НЕ читай содержимое файлов.
Просто разбери отчёт, проверь исходники и запусти субагентов.

## КРИТИЧНАЯ ЗАЩИТА ПРОЕКТА
- НЕ ВЫХОДИТЬ ИЗ ПАПКИ `docs/`
- Папка `ru/` — только для чтения, никогда не писать туда

## Как разобрать отчёт

Формат отчёта:
```
── en ──  не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
```

Парсинг:
- Строка `── XX ──` → это код языка (например `en`, `de`, `zh-Hant`, `pt-BR`)
- Строка `✗ не переведено: path` → файл которого нет, нужно создать (`FILE_EXISTS = false`)
- Строка `✗ нет перевода: path` → то же самое, синоним
- Строки с `лишних` и итоговые строки — игнорировать

Для каждой записи:
- `SOURCE_FILE` = `docs/ru/{path}`
- `TARGET_FILE` = `docs/{lang}/{path}`
- `FILE_EXISTS` = `false`
- `FILE_TYPE` = расширение файла: `.md` → `md`, `.pages` → `pages`
- `TARGET_LANG_NAME` — полное название языка:
  - `en` → `English`, `de` → `German`, `fr` → `French`, `es` → `Spanish`
  - `cs` → `Czech`, `ja` → `Japanese`, `pt` → `Portuguese`
  - `pt-BR` → `Brazilian Portuguese`, `zh` → `Simplified Chinese`
  - `zh-Hant` → `Traditional Chinese`

## Алгоритм — строго по шагам

### Шаг 1 — Разобрать отчёт
Составь список задач из отчёта. Каждая задача: `(SOURCE_FILE, TARGET_FILE, TARGET_LANG, TARGET_LANG_NAME, FILE_EXISTS, FILE_TYPE)`.
Не читай содержимое файлов на этом шаге — только парсинг текста отчёта.

### Шаг 2 — Проверить исходники (ОБЯЗАТЕЛЬНО перед запуском)
Для каждого уникального `SOURCE_FILE` из списка задач — проверь что файл существует на диске (используй ls или stat, не читай содержимое).
- Файл существует → задача готова
- Файл НЕ существует → удали ВСЕ задачи с этим `SOURCE_FILE` из списка и залогируй:
  `[!] SKIPPED — source not found: {SOURCE_FILE}`

Только после проверки всех исходников переходи к Шагу 3.

### Шаг 3 — Запустить субагентов
Для каждой задачи из проверенного списка запусти субагента через Task (модель: `claude-haiku-4-5`).
Передай ему содержимое файла `___02_translate-subagent.md` с подставленными переменными.
Параллельно, не более 5 задач одновременно.

### Шаг 4 — Логирование
```
[✓] en/09-build-a-device/01-concept.md — created
[✗] de/09-build-a-device/02-bom.md — error: ...
[!] SKIPPED — source not found: docs/ru/09-build-a-device/missing.md
```

### Шаг 5 — Итог
Создано / Ошибок / Пропущено из-за отсутствия исходника.

---

## Отчёт валидатора для обработки:

── en ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── de ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── fr ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── es ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── cs ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── ja ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── pt ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── pt-BR ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── zh ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md

── zh-Hant ──  создано заглушек: 0, не переведено: 8, лишних: 0
   ✗ не переведено: 09-build-a-device/01-concept.md
   ✗ не переведено: 09-build-a-device/02-bom.md
   ✗ не переведено: 09-build-a-device/03-wiring.md
   ✗ не переведено: 09-build-a-device/04-firmware-start.md
   ✗ не переведено: 09-build-a-device/05-sensors.md
   ✗ не переведено: 09-build-a-device/06-menu.md
   ✗ не переведено: 09-build-a-device/07-heating-control.md
   ✗ не переведено: 09-build-a-device/08-assembly-and-check.md
