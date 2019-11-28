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
 *      File: precedential_stack.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "precedential_stack.h"

void init(stack_top_t* stack)
{
    stack->top = NULL;
}

bool push(stack_top_t* stack, symbols symbol)
{
    /*
    stack_item_t *tmp = malloc(sizeof(stack_item_t));

    if (tmp == NULL)
    {
        return false;
    }

    tmp->symbol = symbol;
    tmp->next = stack->top;

    stack->top = tmp;
    return true;
*/
    stack_item_t *tmp = stack->top;

    stack->top = malloc(sizeof(stack_item_t));
    if (stack->top == NULL)
    {
        return false;
    }
    stack->top->symbol = symbol;
    stack->top->next = tmp;
    return true;
}

bool pop(stack_top_t* stack)
{
    if (stack->top != NULL)
    {
        stack_item_t *tmp = stack->top;
        stack->top = tmp->next;

        free(tmp);
        return true;
    }
    return false;
}

bool insert_stop_symbol(stack_top_t* stack)
{
    stack_item_t *tmp = stack->top;
    stack_item_t *prev = NULL;

    //Cycles through the stack
    while (tmp != NULL)
    {
        //If the correct placement is found
        if (tmp->symbol < S_STOP)
        {
            //inserts a new stop symbol
            stack_item_t *stop_symbol = malloc(sizeof(stack_item_t));
            if (stop_symbol == NULL)
            {
                return false;
            }

            //If the correct placement is at the top of the stack
            if (prev == NULL)
            {
                //corrects pointers
                stop_symbol->next = stack->top;
                stack->top = stop_symbol;
            } else {
                //otherwise corrects pointers on the previous symbol
                stop_symbol->next = prev->next;
                prev->next = stop_symbol;
            }
            stop_symbol->symbol = S_STOP;

            return true;
        }
        else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return false;
}

stack_item_t* find_terminal(stack_top_t* stack)
{
    stack_item_t *tmp = stack->top;

    //Cycles through the stack
    while (tmp != NULL)
    {
        //If the correct symbol is found, returns it
        if (tmp->symbol < S_STOP)
        {
            break;
        }
        tmp = tmp->next;
    }
    return tmp;

    /*
	for (stack_item_t* tmp = stack->top; tmp != NULL; tmp = tmp->next)
	{
		if (tmp->symbol < S_STOP)
			return tmp;
	}
	return NULL;
	*/
}

void stack_free(stack_top_t* stack)
{
    while (stack->top != NULL)
    {
        pop(stack);
    }
}
