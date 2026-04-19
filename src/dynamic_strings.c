#include <stddef.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "dynamic_strings.h"

// String pointers
String* string_new()
{
	String* str = (String*)malloc(sizeof(String));
	str->data = (char*)malloc(sizeof(char) * 120);
	str->buffer = 1024;
	str->length = 0;

	return str;
}

String* string_input()
{
	String* str = (String*)malloc(sizeof(String));
	str->data = NULL;
	str->buffer = 0;

	getline(&(str->data), &(str->buffer), stdin);

	str->data[strcspn(str->data, "\n")] = '\0';
	str->length = strlen(str->data);

	return str;
}

String* string_from(char* str_from)
{
	String* str = (String*)malloc(sizeof(String));
	size_t new_length = strlen(str_from);

	str->buffer = new_length + 1024;
	str->data = malloc(str->buffer);
	memcpy(str->data, str_from, new_length + 1);

	str->length = new_length;
	return str;
}

String* string_push(String* str, char* value)
{
	if (value == NULL)
	{
		return str;
	}

	size_t value_len = strlen(value);
	size_t new_size = str->length + value_len;

	if (new_size + 1 > str->buffer)
	{
		while (str->buffer < new_size + 1)
		{
			if (str->buffer < 1024)
			{
				str->buffer *= 2;
			}
			else
			{
				str->buffer += 1024;
			}

			char* tmp = realloc(str->data, str->buffer);
			if (tmp == NULL)
			{
				return str;
			}

			str->data = tmp;
		}
	}

	memcpy(str->data + str->length, value, value_len);
	str->length = new_size;
	str->data[str->length] = '\0';
	return str;
}

String*
string_insert(String* str, char* value, size_t index)
{
	if (value == NULL)
	{
		return str;
	}

	size_t value_len = strlen(value);
	size_t new_size = str->length + value_len;

	if (new_size + 1 > str->buffer)
	{
		while (str->buffer < new_size + 1)
		{
			if (str->buffer < 1024)
			{
				str->buffer *= 2;
			}
			else
			{
				str->buffer += 1024;
			}

			char* tmp = realloc(str->data, str->buffer);
			if (tmp == NULL)
			{
				return str;
			}

			str->data = tmp;
		}
	}

	memmove(
		str->data + index + value_len,
		str->data + index,
		str->length - index
	);
	memcpy(str->data + index, value, value_len);

	str->length = new_size;
	str->data[str->length] = '\0';
	return str;
}

String* string_remove_at(String* str, size_t index)
{
	if (index >= str->length)
		return str;

	memmove(
		str->data + index,
		str->data + index + 1,
		str->length - index
	);

	str->length--;
	return str;
}

String* string_clear(String* str)
{
	str->length = 0;
	str->buffer = 1024;
	str->data = "";
	return str;
}

// void
void string_print(String* str)
{
	printf("%s\n", str->data);
	return;
}

void string_print_informations(String* str)
{
	printf("----- String Information -----\n");
	printf("Data -> ");
	string_print(str);
	printf("Length -> %zu\n", str->length);
	printf("Buffer -> %zu\n", str->buffer);
	printf("Memory Address -> %p\n", str);
	return;
}

void string_free(String* str)
{
	free(str->data);
	str->length = 0;
	str->buffer = 0;
	free(str);
	return;
}

// char
char string_at(String* str, size_t index)
{
	return str->data[index];
}

char string_at_last(String* str)
{
	return string_at(str, str->length - 1);
}

// size_t
size_t string_find(String* str, char value)
{
	for (size_t i = 0; i < str->length; i++)
	{
		if (value == str->data[i])
		{
			return i;
		}
	}

	return -1;
}