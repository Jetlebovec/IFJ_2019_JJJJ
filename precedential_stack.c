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


/*typedef struct stack_item
{
    int symbol;
    int type;
    struct stack_item *next;
}stack_item_t;

typedef struct stack_top
{
    stack_item_t *top;  // Pointer to stack item on top of stack.
}stack_top_t;
*/

void init(stack_top_t* stack)   // Function initializes stack.
{
    stack->top = NULL;
}

bool push(stack_top_t* stack, symbols symbol)  // Function pushes symbol to stack and sets its data type.
{
    stack_item_t *tmp = malloc(sizeof(stack_item_t));

    if (tmp == NULL)
    {
        return false;
    }

    tmp->symbol = symbol;
    tmp->next = stack->top;

    stack->top = tmp;
    return true;

}

bool pop(stack_top_t* stack)  // Function pops top symbol from stack.
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

    while (tmp != NULL)
    {
        if (tmp->symbol < S_STOP)
        {
            stack_item_t *new_item = malloc(sizeof(stack_item_t));

            if (new_item == NULL)
            {
                return false;
            }

            new_item->symbol = S_STOP;
            new_item->next = tmp;

            if (prev == NULL)
            {
                new_item->next = stack->top;
                stack->top = new_item;
            } else {
                new_item->next = prev->next;
                prev->next = new_item;
            }
            return true;
        }
        else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return true;
}

stack_item_t* find_terminal(stack_top_t* stack)
{
	for (stack_item_t* tmp = stack->top; tmp != NULL; tmp = tmp->next)
	{
		if (tmp->symbol < S_STOP)
			return tmp;
	}
	return NULL;
}



void stack_free(stack_top_t* stack)  // Function frees resources used for stack.
{
	while (pop(stack));
}
