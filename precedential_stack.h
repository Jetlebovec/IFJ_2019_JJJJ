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
 *      File: precedential_stack.h
 */

#include <stdbool.h>

//enum of symbols for stack and analysis
typedef enum
{
    S_LS,     	//1
    S_GT,     	//2
    S_LSEQ,   	//3
    S_GTEQ,   	//4
    S_EQ,     	//5
    S_NEQ,    	//6
    S_PLUS,   	//7
    S_MINUS,  	//8
    S_MUL,    	//9
    S_DIV,    	//10
    S_IDIV,   	//11
    S_LBR,    	//12
    S_RBR,    	//13
	S_ASSIGN, 	//14
	S_ID,		//15
	S_INT,		//16
	S_STR,		//17
	S_FLOAT,	//18
	S_NONE,		//19
    S_DOLLAR,  	//20
	S_STOP,		//21
	S_NONTERM	//22
} symbols;

// More like list item
typedef struct stack_item
{
	symbols symbol; // Symbol enum
	struct stack_item *next;
} stack_item_t;

// Top of the stack, basically pointer to the end of dynamic list
typedef struct stack_top
{
	stack_item_t *top;
} stack_top_t;

// Stack init
void init(stack_top_t* stack);

// Stack push
bool push(stack_top_t* stack, symbols symbol);

// Stack pop
bool pop(stack_top_t* stack);

// Inserts new stop symbol in the stack
bool insert_stop_symbol(stack_top_t* stack);

// Returns first terminal from the stack
stack_item_t* find_terminal(stack_top_t* stack);

// Frees the stack
void stack_free(stack_top_t* stack);
