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
 *      File: scanner.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "stack.h"

// Reserved keywords that must not be used as a variable name
const char* keywords[7] =
{
    "def", "else", "if", "none", "pass", "return", "while"
};


int get_token(Token *token)
{
    // TESTING TESTING TESTING TESTING TESTING TODO REWRITE FOR STDIN
    FILE *file;
    file = fopen("test.txt", "r");
    // /TESTING

    // Initialize all required variables
    char c;
    tState state;
    token->type = TOKEN_UNDEFINED;
    string_clear(token->attribute);

    //  TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN
    while (file)
    {
        c = getc(file);
        if (c == EOF)
        {
            printf("\nFile end\n");
            break;
        } else
        {
            printf("%c", c);
        }
    }

    // TESTING TESTING TESTING TESTING TESTING
    fclose(file);
    // /TESTING
    return 0;
}
