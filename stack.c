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


int stack_init (tStack* s) {
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

int stack_empty (tStack* s) {
    // When the stack is empty, top should have the value -1
    if (s == NULL)
    {
        return 99;
    }
    return s->top == -1;
}

int stack_full (tStack* s) {
    // When the stack is full, top should be equal to the stack size - 1
    if (s == NULL)
    {
        return 99;
    }
    return s->top == (MAX_STACK_SIZE - 1);
}

int stack_top (tStack* s, int *x) {
    // Returns the int on the s.top index
    if (s == NULL)
    {
        return 99;
    }
    if (stack_empty(s))
    {
        return 1;
    } else
    {
        *x = s->arr[s->top];
        return 0;
    }
}


int stack_pop (tStack* s) {
    // Decrements the value of top making the previous character the new top
    if (s == NULL)
    {
        return 99;
    }
    if (stack_empty(s))
    {
        return 1;
    } else
    {
        s->top--;
        return 0;
    }
}


int stack_push (tStack* s, int x) {
    // Increments the value of top and places the new char on the new top index
    if (s == NULL)
    {
        return 99;
    }
    if (stack_full(s))
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



