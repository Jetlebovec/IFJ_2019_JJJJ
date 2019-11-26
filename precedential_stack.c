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
#include "precedential_analysis.h"
#include "precedential_analysis.c"

typedef struct stack_item
{
    int symbol;
    int type;
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

void push(int symbol, int type, stack_top_t* stack)
{
    stack_item_t *tmp = malloc(sizeof(stack_item_t));

    if (tmp == NULL)
    {
        return;
    }

    if(tmp != NULL)
    {
        tmp->symbol = symbol;
        tmp->type = type;
        tmp->next = stack->top;

        stack->top = tmp;
    }
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

int top(stack_top_t* stack)
{
    if (stack->top != NULL)
        return stack.top->symbol;
    else
        return DOLLAR;
}
// okopírované.. moc teď nevím.. pokecáme o těch nontermech.. jsem teď v úzkých.. ráno kouknu na to video ještě si radši!
/*Symbol_stack_item* symbol_stack_top_terminal(Symbol_stack* stack)
{
	for (Symbol_stack_item* tmp = stack->top; tmp != NULL; tmp = tmp->next)
	{
		if (tmp->symbol < STOP)
			return tmp;
	}

	return NULL;
}*/
// STOP symbol used when reducing!

stack_item_t* symbol_stack_top(stack_top_t* stack)
{
	return stack->top;
}


void symbol_stack_free(stack_top_t* stack)
{
	while (symbol_stack_pop(stack));
}