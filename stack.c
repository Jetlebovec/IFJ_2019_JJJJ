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

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stackInit (tStack* s) {
    // The stack is empty when initialized, so the value of top is -1
    if (s == NULL)
    {
        return 99;
    } else
    {
        s->top = -1;
        return 0;
    }
}

int stackEmpty (tStack* s) {
    // When the stack is empty, top should have the value -1
    if (s == NULL)
    {
        return 99;
    }
    return s->top == -1;
}

int stackFull (tStack* s) {
    // When the stack is full, top should be equal to the stack size - 1
    if (s == NULL)
    {
        return 99;
    }
    return s->top == (MAX_STACK_SIZE - 1);
}

int stackTop (tStack* s, int *x) {
    // Returns the int on the s.top index
    if (s == NULL)
    {
        return 99;
    }
    if (stackEmpty(s))
    {
        return 1;
    } else
    {
        *x = s->arr[s->top];
        return 0;
    }
}


int stackPop (tStack* s) {
    // Decrements the value of top making the previous character the new top
    if (s == NULL)
    {
        return 99;
    }
    if (stackEmpty(s))
    {
        return 1;
    } else
    {
        s->top--;
        return 0;
    }
}


int stackPush (tStack* s, int x) {
    // Increments the value of top and places the new char on the new top index
    if (s == NULL)
    {
        return 99;
    }
    if (stackFull(s))
    {
        return 1;
    } else
    {
        s->top++;
        s->arr[s->top] = x;
        return 0;
    }
}

/* Konec c202.c */



