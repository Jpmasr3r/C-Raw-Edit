#ifndef EDITOR_H
#define EDITOR_H
#include <termios.h>
#include "dynamic_strings.h"
#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct Editor
{
	FILE* file;
	char* filePath;
	String* string;
	String* message;
	size_t jumps;
	size_t position;
	size_t buffer;
} Editor;

enum EDITOR_KEYS
{
	KEY_ENTER = '\r',
	KEY_BACKSPACE = 127,
	KEY_ESC = 27,
};

enum SIDES
{
	LEFT = -1,
	RIGHT = 1,
	UP = 1,
	DOWN = -1,
};

enum EDITOR_SHOTCUTS
{
	SHORTCUT_SAVE = CTRL_KEY('s'),
	SHORTCUT_SELECT_ALL = CTRL_KEY('a'),
	SHORTCUT_EXIT = CTRL_KEY('q'),
};

FILE* file_open(char* path);

Editor* editor_set_data(Editor* editor);
Editor* editor_write(Editor* editor);
Editor* editor_read(Editor* editor);
Editor* editor_new(char* path);
Editor* editor_move(Editor* editor, enum SIDES side);

void editor_close(Editor* editor);

struct termios* terminal_init();

#endif