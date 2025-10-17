# Far Cry 4 Language Restriction Remover

Fixes the hardcoded interface language in the Russian version of Far Cry 4, allowing you to freely choose your preferred language through a simple INI file.

---

## Overview

The Russian release of Far Cry 4 forces the interface language on every launch, ignoring user settings.  
This mod removes that restriction and lets you set the desired language manually.

It works by intercepting the game's language initialization and reading the value from `lang_fix.ini`.

---

## Installation

1. Download the latest release from the [Releases](../../releases) page.  
   You will get a ZIP archive containing:

   ```
   version.dll
   lang_fix.ini
   ```

2. Extract both files into bin folder inside your Far Cry 4 installation folder (the one containing `FC64.dll`).

3. Open `lang_fix.ini` and edit the `Lang` value to your desired language code.

4. Launch the game. The interface will now appear in the language you selected.

---
