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
 *      File: stack.h
 */


#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 30

typedef struct {
	int arr[MAX_STACK_SIZE];
	int top;
} tStack;

// Initializes the stack, returns 0 if successful, otherwise returns error code
int stackInit (tStack* s);

// Returns 0 if empty, 99 if null pointer, otherwise not empty
int stackEmpty (tStack* s);

// Returns 0 if full, 99 if null pointer, otherwise not full
int stackFull (tStack* s);

// Stores the top of the stack to the passed reference
// Returns 99 if null pointer, 0 if successful, 1 if stack was empty
int stackTop (tStack* s, int* x);

// Pops the top of the stack
// Returns 99 if null pointer, 0 if successful, 1 if stack was empty
int stackPop (tStack* s);

// Pushes x to the top of the stack
// Returns 99 if null pointer, 0 if successful, 1 if stack was full
int stackPush (tStack* s, int x);


#endif // STACK_H_INCLUDED
