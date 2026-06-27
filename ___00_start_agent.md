# Запуск агента перевода

## Подготовка (один раз)
```bash
# Перейти в корень проекта (где лежит папка docs/)
cd /путь/к/проекту
```

---

## Вариант 1 — Полный проход (все файлы)
Агент сам обходит docs/ru/ и сравнивает со всеми языками.
Используй когда добавил много новых файлов или запускаешь впервые.

```bash
# Обычный запуск
claude --model claude-sonnet-4-5 -p "$(cat ___01_translate-prompt.md)"

# С подробными логами (видно что агент делает)
claude --model claude-sonnet-4-5 --verbose -p "$(cat ___01_translate-prompt.md)"
```

⚠️ Может съесть много токенов на больших проектах.

---

## Вариант 2 — По отчёту валидатора (рекомендуется)
Сначала запускаешь валидатор — он показывает только то чего не хватает.
Агент получает готовый список и не тратит токены на инвентаризацию.
Используй для точечного перевода конкретных недостающих файлов.

```bash
# Шаг 1 — получить отчёт и сохранить в файл
python3 /Users/ruslanpavlucenko/Projects/docs-idryer-org/validate-i18n.py \
  './docs' --base ru > translation_tasks.txt

# Посмотреть что нужно сделать
cat translation_tasks.txt

# Шаг 2 — запустить агент с отчётом
claude --model claude-sonnet-4-5 -p "$(cat ___03_translate-from-report.md)"

$(cat translation_tasks.txt)"
```

---

## Вариант 3 — Одной командой (pipe)
То же что Вариант 2 но без промежуточного файла.

```bash
claude --model claude-sonnet-4-5 --verbose -p "$(cat ___03_translate-from-report.md)"

$(python3 /Users/ruslanpavlucenko/Projects/docs-idryer-org/validate-i18n.py './docs' --base ru)"
```

---

## После запуска — проверить результат

```bash
# Запустить валидатор снова — должно быть 0 непереведённых
python3 /Users/ruslanpavlucenko/Projects/docs-idryer-org/validate-i18n.py \
  './docs' --base ru
```

---

## Файлы системы
```
___01_translate-prompt.md      — оркестратор (полный проход)
___02_translate-subagent.md    — субагент Haiku (правила перевода)
___03_translate-from-report.md — оркестратор (по отчёту валидатора)
```

---

## Если что-то пошло не так

```bash
# Добавить --verbose чтобы видеть все шаги агента
claude --model claude-sonnet-4-5 --verbose -p "$(cat ___03_translate-from-report.md)

$(cat translation_tasks.txt)"

# Проверить что папка доверенная (если агент молчит)
# Открыть ~/.claude.json и убедиться что hasTrustDialogAccepted: true
# для текущего проекта
```