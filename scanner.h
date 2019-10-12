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
 *      File: scanner.h
 */


#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef enum
{
    TOKEN_INT,
    TOKEN_CHAR = 0,
} tokenType;

// Struct of type Token
typedef struct
{
    tokenType type;
    char *attribute;
} Token;

// Reads the next token, returns error code
int getToken(Token *token);



#endif // SCANNER_H_INCLUDED
