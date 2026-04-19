#ifndef DYNAMIC_STRINGS_H
#define DYNAMIC_STRINGS_H
#include <stdio.h>

typedef struct String
{
	char* data;
	size_t length;
	size_t buffer;
} String;

// String pointer
String* string_new();
String* string_input();
String* string_from(char* str_from);
String* string_push(String* str, char* value);
String* string_remove_at(String* str, size_t index);
String* string_clear(String* str);
String*
string_insert(String* str, char* value, size_t index);
// void
void string_print(String* str);
void string_print_informations(String* str);
void string_free(String* str);

// char
char string_at(String* str, size_t index);
char string_at_last(String* str);

// size_t
size_t string_find(String* str, char value);

#endif