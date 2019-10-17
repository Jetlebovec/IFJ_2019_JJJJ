/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Diviš Jan	    xdivis12
 *          Kopáček Jiří	xkopac06
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: stack.c
 */

//library for work with a string structure

#include <stdlib.h>
#include <string.h>
#include "custom_string.h"

void string_clear(string *s)
{
	s->length = 0;
	s->str[0] = '\0';
}

int string_init(string *s)
{
	if ((s->str = (char *) malloc(STRINGLEN)) == NULL)
	{
		return 1;
	}
	else
	{
		string_clear(s);
		s->size = STRINGLEN;
		return 0;
	}
	
}

void string_free(string *s)
{
	free(s);
}

int string_append_char(string *s, char c)
{
	if (s->length + 1 >= s->size)
	{
		if ((s->str = (char *) realloc(s->str, s->length + STRINGLEN)) == NULL)
		{
			return 1;
		}
	}

	string_clear(s);
	s->size = s->length + STRINGLEN;
	s->str[s->length++] = c;
	s->str[s->length] = '\0';
	return 0;
}

int string_concat(string *s1, string *s2)
{
	int new_size = s1->length + s2->length;
	if (new_size >= s1->size)
	{
		if ((s1->str = (char *) realloc(s1->str, new_size)) == NULL)
		{
			return 1;
		}
		s1->size = new_size;
	}

	s1->length += s2->length;
	strcat(s1->str, s2->str);
	return 0;
}




