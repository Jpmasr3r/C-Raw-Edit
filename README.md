# C-Raw-Edit

🖥️ A minimal low-level C text editor for the terminal.

---

## ⚙️ Features

- Terminal-based text editing
- Cursor movement with arrow keys
- Character insertion at cursor position
- Backspace support
- File loading and saving
- Raw terminal mode (no canonical input, no echo)
- Escape sequence parsing for special keys

---

## 🧪 Concepts explored

This project is built from scratch to explore:

- Low-level memory management (`malloc`, `realloc`, `memmove`)
- Unix system calls (`read`, `write`, `fopen`, `fwrite`)
- Terminal control with `termios`
- Manual string manipulation
- Escape sequence parsing (arrow keys, ESC handling)

---

## ⌨️ Controls

- `← → ↑ ↓` → move cursor
- `BACKSPACE` → delete character
- `CTRL+S` → save file
- `CTRL+Q` → exit editor

---

## 🏗️ Build

```bash
cmake
```

or manually:

```bash
gcc -o c_raw_edit *.c -O2
```

🚀 Run

```bash
./c_raw_edit file.txt
```

If the file does not exist, it will be created automatically.

---

## 🧠 How it works

Input is read in raw mode using termios
Each key is processed manually via read()
Arrow keys are decoded from escape sequences (\x1b[A, etc.)
Text is stored in a dynamic string structure
Insert/delete operations are handled with memmove for efficiency
Screen is redrawn after every input cycle

---

## ⚠️ Notes

This project is experimental and not production-ready
No undo/redo system yet
No syntax highlighting
No scrolling system implemented yet

---

## 📜 License

This project uses the **GPLv2** license.
