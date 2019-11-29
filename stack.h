/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Kopáček Jiří    xkopac06
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

/**
 * @brief Initializes the stack
 * @param s stack
 * @return 0 if successful, 99 if null
 */
int stack_init (tStack* s);

/**
 * @brief Checks if the stack is empty
 * @param s stack
 * @return 1 if empty, 0 if not, 99 if null
 */
int stack_empty (tStack* s);

/**
 * @brief Checks if the stack is full
 * @param s stack
 * @return 1 if full, 0 if not, 99 if null
 */
int stack_full (tStack* s);

/**
 * @brief Rewrites x with the value at the top of the stack
 * @param s stack
 * @param x int to store the top in
 * @return 0 if successful, 1 if the stack is empty, 99 if null
 */
int stack_top (tStack* s, int* x);

/**
 * @brief Pops the stack
 * @param s stack
 * @return 0 if successful, 1 if the stack is empty, 99 if null
 */
int stack_pop (tStack* s);

/**
 * @brief Pushes x to the stack
 * @param s stack
 * @param x int to push
 * @return 0 if successful, 1 if the stack is full, 99 if null
 */
int stack_push (tStack* s, int x);


#endif // STACK_H_INCLUDED
