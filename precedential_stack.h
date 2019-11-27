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

/**
 * @struct stack item represetation.
 */
typedef struct stack_item
{
	symbols symbol; // Symbol of stack item.
	int type;
/*****************************************************************************/
/*************************** Data_type data_type;*****************************/  /*Data type used for semantic analysis.*/
/*****************************************************************************/
	struct stack_item *next; // Pointer to next stack item.
} stack_item_t;

/**
 * @struct stack top representation.
 */
typedef struct stack_top
{
	stack_item_t *top; // Pointer to stack item on top of stack.
} stack_top_t;


/**
 * Function initializes stack.
 *
 * @param stack Pointer to stack.
 */
void init(stack_top_t* stack);

/**
 * Function pushes symbol to stack and sets its data type.
 *
 * @param stack Pointer to stack.
 * @param symbol Symbol to be pushed.
 * @param type Type to be set.
 */
void push(stack_top_t* stack, symbols symbol, int type);

/**
 * Function pops top from stack.
 *
 * @param stack Pointer to stack.
 * @return True if successfull.
 * @return False else not successfull.
 */
bool pop(stack_top_t* stack);

/**
 * Function pops stack N times.
 *
 * @param stack Pointer to stack.
 * @param n How many times stack will be popped.
 */
void pop_n_times(int n, stack_top_t* stack);

/**
 * Function returns top.
 *
 * @param stack Pointer to stack.
 * @return Returns pointer to top symbol.
 * @return Returns S_DOLLAR in else.
 */
int top(stack_top_t* stack);

/**
 * Function push/insert symbol after top term.
 *
 * @param stack Pointer to stack.
 * @param symbol Symbol to be push/insert.
 */
void insert_after_top_term(stack_top_t* stack, symbols symbol);

/**
 * Function returns top symbol.
 * @param stack Pointer to stack.
 * @return Pointer to symbol on the top.
 */
stack_item_t* symbol_stack_top(stack_top_t* stack);

/**
 * Function frees resources used for stack.
 *
 * @param stack Pointer to stack.
 */
void symbol_stack_free(stack_top_t* stack);
