#include "editor.h"
#include "dynamic_strings.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE* file_open(char* path)
{
	FILE* fprt;
	fprt = fopen(path, "r");

	if (fprt == NULL)
	{
		fclose(fopen(path, "w+"));
		fprt = fopen(path, "r");
	}

	return fprt;
}

Editor* editor_set_data(Editor* editor)
{
	if (editor->file == NULL)
	{
		printf("File to open file %s\n", editor->filePath);
		exit(1);
	}

	fseek(editor->file, int_max(0, editor->jumps) * editor->buffer, SEEK_SET);
	char* tmp = malloc(editor->buffer);
	if (tmp == NULL)
	{
		return editor;
	}

	fread(tmp, 1, editor->buffer, editor->file);
	editor->string = string_from(tmp);

	return editor;
}

Editor* editor_new(char* path)
{
	Editor* editor = malloc(sizeof(Editor));
	editor->jumps = 0;
	editor->buffer = 1024;
	editor->string = NULL;
	editor->file = file_open(path);
	editor->filePath = path;
	editor->message = string_new();
	editor->position = 0;

	return editor_set_data(editor);
}

void editor_close(Editor* editor)
{
	string_free(editor->string);
	fclose(editor->file);
	free(editor);
	return;
}

Editor* editor_write(Editor* editor)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
	printf("Line %zu\n File Open : %s\n", editor->position, editor->filePath);
	printf("%s\n", editor->message->data);
	for (size_t i = 0; i < editor->string->length; i++)
	{
		if (editor->position == i)
		{
			write(STDOUT_FILENO, "\x1b[4m", 4);
		}
		write(STDOUT_FILENO, &(editor->string->data[i]), 1);
		if (editor->position == i)
		{
			write(STDOUT_FILENO, "\x1b[0m", 4);
		}
	}

	return editor;
}

Editor* editor_delete(Editor* editor)
{
	size_t len_buffer = editor->string->length;
	string_remove_at(editor->string, editor->position - 1);
	if (len_buffer != editor->string->length)
	{
		editor->position = int_min(
			int_max(0, (editor->position - 1)),
			(int_max(editor->string->length, 0))
		);
	}
	return editor;
}

Editor* editor_save(Editor* editor)
{
	FILE* file = fopen(editor->filePath, "w");
	if (file == NULL)
	{
		printf("Fail to open file %s\n", editor->filePath);
		return editor;
	}

	size_t written =
		fwrite(editor->string->data, 1, editor->string->length, file);

	if (written != editor->string->length)
	{
		printf("Fail to write file %s\n", editor->filePath);
		fclose(file);
		return editor;
	}
	editor->message = string_from("File Saved");

	fclose(file);

	return editor;
}

Editor* editor_move(Editor* editor, enum SIDES side)
{
	editor->position = int_min(
		int_max(0, (editor->position + side)),
		(int_max(editor->string->length, 0))
	);
	return editor;
}

Editor* editor_read(Editor* editor)
{
	char c, c_buffer[2];
	int running = 1;

	while (running)
	{
		ssize_t nread = read(STDIN_FILENO, &c, 1);
		if (nread <= 0)
		{
			continue;
		}

		if (c == KEY_ESC)
		{
			char seq[2];

			if (read(STDIN_FILENO, &seq[0], 1) == 0)
			{
				continue;
			}
			if (read(STDIN_FILENO, &seq[1], 1) == 0)
			{
				continue;
			}

			if (seq[0] == '[')
			{
				switch (seq[1])
				{
				case 'A':
					editor_move(editor, UP);
					break;
				case 'B':
					editor_move(editor, DOWN);
					break;
				case 'C':
					editor_move(editor, RIGHT);
					break;
				case 'D':
					editor_move(editor, LEFT);
					break;
				}
			}
		}
		else
		{
			switch (c)
			{
			case KEY_BACKSPACE:
				editor_delete(editor);
				break;

			case SHORTCUT_SAVE:
				editor_save(editor);
				break;

			case SHORTCUT_EXIT:
				running = 0;
				editor->message = string_from("Exit File");
				break;

			default:
				string_clear(editor->message);
				c_buffer[0] = c;
				c_buffer[1] = '\0';
				// string_push(editor->string, c_buffer);
				string_insert(editor->string, c_buffer, editor->position);
				editor->position++;
				break;
			}
		}

		editor_write(editor);
	}

	return editor;
}

struct termios* terminal_init(void)
{
	struct termios* oldt = malloc(sizeof(struct termios));
	struct termios newt;
	tcgetattr(STDIN_FILENO, oldt);
	newt = *oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_iflag &= ~(IXON);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	return oldt;
}
