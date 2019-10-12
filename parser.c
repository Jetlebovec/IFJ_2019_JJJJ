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
#include "scanner.h"
#include "parser.h"

int analyse()
{
    Token newToken;
    if (getToken(&newToken) != 0)
    {
        return 1;
    }

    printf("Token type %s, token attribute %s \n", newToken.type, newToken.attribute);
    return 0;
}

