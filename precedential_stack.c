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

#include <stdbool.h>
#include "parser.h"

typedef struct stack_item
{
    int symbol;
    struct stack_item *next;
}stack_item_t;

typedef struct stack_top
{
    stack_item_t *top;
}stack_top_t;


void init(stack_top_t* stack)
{
    stack->top = NULL;
}

int push(int symbol, stack_top_t* stack)
{
    stack_item_t *tmp = malloc(sizeof(stack_item_t));

    if (tmp == NULL)
    {
        return 1;
    }
        
    tmp->symbol = symbol;
    tmp->next = stack->top;
    stack->top = tmp;
}

void pop(stack_top_t* stack) 
{
    if (stack->top != NULL) 
    {
        stack_item_t *tmp = stack->top;
        stack->top = tmp->next;
        free(tmp);
    }
}

void pop_n_times(int n, stack_top_t* stack) 
{
    for (int i = 0; i < n; i++) 
    {
        pop(stack);
    }
}


// okopírované.. moc teď nevím.. pokecáme o těch nontermech.. jsem teď v úzkých.. ráno kouknu na to video ještě si radši!
stack_item_t* stack_top_terminal(stack_top_t* stack)
{
	for (stack_item_t* tmp = stack->top; tmp != NULL; tmp = tmp->next)
	{
		if (tmp->symbol < S_STOP)
			return tmp;
	}

	return NULL;
}

bool push_stop_symbol(stack_top_t* stack, symbols symbol)
{
	stack_item_t* prev = NULL;
    stack_item_t* tmp = stack->top;

	while (tmp != NULL)
	{
		if (tmp->symbol < S_STOP)
		{
			stack_item_t* new_item = (stack_item_t*)malloc(sizeof(stack_item_t));

			if (new_item == NULL)
				return false;

			new_item->symbol = symbol;

			if (prev == NULL)
			{
				new_item->next = stack->top;
				stack->top = new_item;
			}
			else
			{
				new_item->next = prev->next;
				prev->next = new_item;
			}

			return true;
		}

		prev = tmp;
        tmp = tmp->next;
	}

	return false;
}