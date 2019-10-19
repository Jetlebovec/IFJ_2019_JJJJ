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
 *      File: parser.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int analyse()
{
    // Initialize token
    Token newToken;
    newToken.type = TOKEN_UNDEFINED;
    newToken.attribute = (tString*) malloc(sizeof(tString));
    if (newToken.attribute == NULL)
    {
        return 99;
    }
    string_init(newToken.attribute);

    // TESTING WITH FILE
    FILE *file;
    file = fopen("test.txt", "r");
    // TESTING WITH FILE


    // Get new token from the scanner
    if (get_token(&newToken, file) != 0)
    {
        return 1;
    }

    // TESTING
    printf("Token attribute: ");
    string_print(newToken.attribute);
    printf("Token type: %d\n", newToken.type);
    // /TESTING

    // Free token
    string_free(newToken.attribute);
    free(newToken.attribute);

    // TESTING WITH FILE
    fclose(file);
    // TESTING WITH FILE

    return 0;
}

