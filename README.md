# C-Raw-Edit

A minimal terminal-based text editor written entirely from scratch in C, exploring low-level system programming concepts.

## Features

- Terminal-based text editing with raw mode input
- Cursor movement (arrow keys)
- Character insertion and deletion (backspace)
- File loading and saving
- Escape sequence parsing for terminal keys
- Status messages display

## Keybindings

| Key             | Action                         |
| --------------- | ------------------------------ |
| `←` `→` `↑` `↓` | Move cursor                    |
| `Backspace`     | Delete character before cursor |
| `Ctrl+S`        | Save file                      |
| `Ctrl+Q`        | Exit editor                    |

## Building

```bash
cmake -B build
cmake --build build
```

Or manually:

```bash
gcc -o c_raw_edit src/*.c libs/dynamic-Strings/src/*.c -O2 -Iinclude -Ilibs/dynamic-Strings/include
```

## Running

```bash
./c_raw_edit 
```

If the file does not exist, it will be created automatically. Defaults to `default.txt` if no argument provided.

## Architecture

### Core Components

| File               | Purpose                                     |
| ------------------ | ------------------------------------------- |
| `src/main.c`       | Entry point, terminal initialization        |
| `src/editor.c`     | Editor operations (read, write, save, move) |
| `src/utils.c`      | Utility functions                           |
| `include/editor.h` | Editor struct and public API                |
| `include/utils.h`  | Utility declarations                        |

### Editor Flow

1. `main()` opens or creates file via `editor_new()`
2. Initial screen rendered via `editor_write()`
3. Terminal set to raw mode via `terminal_init()`
4. Input loop in `editor_read()` processes:
   - Escape sequences for arrow keys
   - Character input for typing
   - Shortcuts (Ctrl+S, Ctrl+Q)
5. On exit, terminal restored and resources freed

### Dependencies

- **dynamic-Strings**  - Custom C string library with automatic buffer management. Implement with **FetchContent_Declare**

## Concepts Explored

This project demonstrates:

- Raw terminal I/O with `termios`
- Manual memory management (`malloc`, `realloc`, `memmove`)
- Unix system calls (`read`, `write`, `fopen`, `fwrite`)
- Escape sequence parsing for special keys
- Manual string operations

## Limitations

- No undo/redo
- No syntax highlighting
- No scrolling support
- Single-line buffer mode (loads 1024 bytes)
- Experimental - not production-ready

## Project Structure

```
raw-Editor/
├── CMakeLists.txt           # Build configuration
├── include/
│   ├── editor.h            # Editor public API
│   └── utils.h             # Utility declarations
├── src/
│   ├── main.c              # Entry point
│   ├── editor.c            # Editor implementation
│   └── utils.c             # Utility functions
└── build/                 # Build output
```

## License

GNU General Public License v2.0