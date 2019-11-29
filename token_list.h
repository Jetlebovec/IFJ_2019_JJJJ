/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: token_list.h
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef struct tDLElem {
        Token token;
        struct tDLElem *rptr;
} *tDLElemPtr;

typedef struct {
    tDLElemPtr First;
    tDLElemPtr Last;
} tDLList;

void DLInitList (tDLList *);
void DLDisposeList (tDLList *);
void DLInsertLast(tDLList *, Token *token, int *err_code);
void DLDeleteFirst (tDLList *);

void init_token(Token *token, int *error_code);
