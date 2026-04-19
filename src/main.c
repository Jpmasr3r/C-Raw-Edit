#include <stdlib.h>
#include <unistd.h>
#include "editor.h"

int main(int argc, char* argv[])
{
	Editor* editor;
	if (argc >= 2)
	{
		editor = editor_new(argv[1]);
	}
	else
	{
		editor = editor_new("default.txt");
	}

	editor_write(editor);

	struct termios* oldt = terminal_init();

	editor_read(editor);
	tcsetattr(STDIN_FILENO, TCSANOW, oldt);

	// free
	editor_close(editor);
	free(oldt);
	return 0;
}
