"""
Pre-build hook: автогенерация меню из src/menu/menu.yaml.

Что делает:
  Запускает lib/idryer-core/menu/menu_gen.py с src/menu/menu.yaml продукта,
  кладёт сгенерированные .h/.cpp туда же — в src/menu/. PlatformIO потом
  сам компилирует всё из src/.

Когда срабатывает:
  Перед каждым `pio run`. Mtime-check: если menu.yaml не новее src/menu/*.cpp —
  пропускает. Поэтому повторные сборки без правки yaml не тратят время.

Где что лежит:
  src/menu/menu.yaml                    ← source of truth (правит разработчик)
  src/menu/menu_*.{h,cpp}               ← autogen (НЕ редактировать)
  lib/idryer-core/src/menu_commands.h   ← runtime helper (header-only, общий для всех продуктов)
  lib/idryer-core/menu/menu_gen.py      ← общий генератор (часть core)
  lib/idryer-core/menu/menu.template.yaml  ← шаблон для нового продукта

Подключение в platformio.ini:
  [env:my-device]
  build_flags = -Isrc/menu
  extra_scripts =
    pre:extra_scripts/pre_gen_menu.py
    post:extra_scripts/copy_firmware.py

Ручное использование (без PIO):
  python3 lib/idryer-core/menu/menu_gen.py src/menu/menu.yaml --out src/menu --num-units 1

Принудительная регенерация:
  touch src/menu/menu.yaml && pio run
"""

import os
import sys
import subprocess
from pathlib import Path

Import("env")

PROJECT_DIR = Path(env["PROJECT_DIR"])
OUT_DIR     = PROJECT_DIR / "src" / "menu"
YAML_PATH   = OUT_DIR / "menu.yaml"
GEN_PATH      = PROJECT_DIR / "lib" / "idryer-core" / "menu" / "menu_gen.py"
TEMPLATE_PATH = PROJECT_DIR / "lib" / "idryer-core" / "menu" / "menu.template.yaml"

GREEN = "\033[92m"
YELLOW = "\033[93m"
RED = "\033[91m"
RESET = "\033[0m"


def _ensure_pyyaml() -> None:
    """Ставит pyyaml в PIO venv если его нет (один раз). Генератор требует yaml."""
    probe = subprocess.run(
        [sys.executable, "-c", "import yaml"],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    if probe.returncode == 0:
        return
    print(f"  {YELLOW}[menu_gen] installing pyyaml into PIO venv (one-time){RESET}")
    subprocess.check_call(
        [sys.executable, "-m", "pip", "install", "--quiet", "pyyaml"]
    )


def _needs_regen() -> bool:
    """True если menu.yaml новее autogen-маркера, или маркер отсутствует.

    Сравниваем с одним autogen-файлом (menu_state.cpp), а не с min(*) по всей
    папке — так стабильнее и не зависит от git-mtime посторонних файлов.
    """
    marker = OUT_DIR / "menu_state.cpp"
    if not marker.exists():
        return True
    return YAML_PATH.stat().st_mtime > marker.stat().st_mtime


def _run() -> None:
    if not YAML_PATH.exists():
        print(f"  {YELLOW}[menu_gen] src/menu/menu.yaml не найден — генерация пропущена{RESET}")
        if TEMPLATE_PATH.exists():
            print(f"  {YELLOW}[menu_gen] стартовый шаблон: {TEMPLATE_PATH.relative_to(PROJECT_DIR)}{RESET}")
            print(f"  {YELLOW}[menu_gen] cp {TEMPLATE_PATH.relative_to(PROJECT_DIR)} src/menu/menu.yaml{RESET}")
        return
    if not GEN_PATH.exists():
        print(f"  {RED}[menu_gen] generator not found: {GEN_PATH}{RESET}")
        print(f"  {RED}[menu_gen] check that lib/idryer-core points to a valid checkout{RESET}")
        return

    if not _needs_regen():
        print(f"  {GREEN}[menu_gen] up-to-date — generation skipped{RESET}")
        return

    _ensure_pyyaml()
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"  {GREEN}[menu_gen] regenerating from {YAML_PATH.name} → src/menu/{RESET}")
    subprocess.check_call([
        sys.executable, str(GEN_PATH),
        str(YAML_PATH),
        "--out", str(OUT_DIR),
        "--num-units", "1",
    ])


_run()
