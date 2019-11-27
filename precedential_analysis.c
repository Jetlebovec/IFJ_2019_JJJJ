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
 *      File: precedential_analysis.c
 */


#include <stdio.h>
#include <stdlib.h>
#include "precedential_analysis.h"

#define TABLE_SIZE 16

int reduce(prog_data* data);
Prec_table_symbol get_symbol_index(symbols symbol);
symbols get_symbol(Token* token);
int symbol_count();
int reduce(prog_data* data);

//precedence table
char prec_table[TABLE_SIZE][TABLE_SIZE] = { /*
      1    2    3    4    5    6    7    8    9    10   11   12   13   14   15  16
	  <    >    <=   >=   ==   !=   +    -    *    /    //   (    )    t    =    $    */
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // <
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // >
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // <=
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // >=
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // ==
	{'>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // !=
	{'>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '>', '<', ' ', '>'}, // +
	{'>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '>', '<', ' ', '>'}, // -
	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', ' ', '>'}, // *
	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', ' ', '>'}, // /
	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', ' ', '>'}, // //
	{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', ' ', ' '}, // (
	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', ' ', '>'}, // )
	{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', '=', '>'}, // t (term - id,int,str,float,None)
	{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '<', ' ', '>'}, // =
	{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', ' ', '<', ' ', ' '}, // $
};


//get symbol index in prec. table
Prec_table_symbol get_symbol_index(symbols symbol)
{
    switch (symbol)
	{
		case S_PLUS:
		return PLUS;
		break;
	case S_MINUS:
		return MINUS;
		break;
	case S_MUL:
		return MUL;
		break;
	case S_IDIV :
		return IDIV;
		break;
	case S_DIV:
		return DIV;
		break;
	case S_EQ:
		return EQ;
		break;
	case S_NEQ:
		return NEQ;
		break;
	case S_LSEQ:
		return LSEQ;
		break;
	case S_GTEQ:
		return GTEQ;
		break;
	case S_LS:
		return LS;
		break;
	case S_GT:
		return GT;
		break;
	case S_LBR:
		return LBR;
		break;
	case S_RBR:
		return RBR;
		break;
	case S_ID:
    case S_INT:
	case S_FLOAT:
	case S_STR:
    case S_NONE:
		return TERM;
		break;
	case S_ASSIGN:
		return ASSIGN;
		break;
	case S_DOLLAR:
		return DOLLAR;
		break;

	default:
		return DOLLAR;
		break;
	}
}



//get symbol from token used for analysis
symbols get_symbol(Token* token)
{
    switch (token->type)
	{
		case TOKEN_PLUS:
		return S_PLUS;
		break;
	case TOKEN_MINUS:
		return S_MINUS;
		break;
	case TOKEN_MULTI:
		return S_MUL;
		break;
	case TOKEN_INT_DIV :
		return S_IDIV;
		break;
	case TOKEN_FLOAT_DIV:
		return S_DIV;
		break;
	case TOKEN_EQUAL:
		return S_EQ;
		break;
	case TOKEN_NOT_EQUAL:
		return S_NEQ;
		break;
	case TOKEN_LESSER_EQUAL:
		return S_LSEQ;
		break;
	case TOKEN_GREATER_EQUAL:
		return S_GTEQ;
		break;
	case TOKEN_LESSER:
		return S_LS;
		break;
	case TOKEN_GREATER:
		return S_GT;
		break;
	case TOKEN_LBRACKET:
		return S_LBR;
		break;
	case TOKEN_RBRACKET:
		return S_RBR;
		break;
	case TOKEN_IDENTIFIER:
		return S_ID;
		break;
    case TOKEN_NUM:
		return S_INT;
		break;
	case TOKEN_NUM_DEC:
		return S_FLOAT;
		break;
    case TOKEN_NUM_EXP:
		return S_FLOAT;
		break;
	case TOKEN_STRING:
		return S_STR;
		break;
	case TOKEN_ASSIGN:
		return S_ASSIGN;
		break;

	default:
		return S_DOLLAR;
		break;
	}
}

stack_top_t symbol_stack;

//access to current token
#define TOKEN data->expression_list.First->token
//get next token
#define NEXT_TOKEN DLDeleteFirst(&(data->expression_list))
//end of exp
#define IS_END data->expression_list.First == NULL


//count symbols on stack before stop symbol
int symbol_count()
{
	stack_item_t* tmp = symbol_stack.top;
	int count = 0;

//counting symbols before stop symbol
	while (tmp != NULL)
	{
		if(tmp->symbol == S_STOP)
		{
			break;
		}
		else
		{
			count++;
		}
		tmp = tmp->next;
	}
	return count;
}

// Function pops stack n times.
void pop_n(int n, stack_top_t* stack) 
{
    for (int i = 0; i < n; i++)
    {
        pop(stack);
    }
}

//reduce 1 or 3 terms to nonterm based on rules and do all required actions
int reduce(prog_data* data)
{
	int err = 0;
	int count = 0; //number of symbols loaded from stack before stop symbol (<)

	stack_item_t* symbol1 = NULL;
	stack_item_t* symbol2 = NULL; //symbols loaded from stack
	stack_item_t* symbol3 = NULL;

//count symbols on stack before stop symbol, it could be 1 or 3 (i or E?E)
	count = symbol_count();

//if there was 1 symbol, it should be id/value and it could be replaced by nonterm
//in final code it means operand were pushed on stack
	if(count == 1)
	{
		//E->i rule
		symbol1 = symbol_stack.top;

		if(symbol1->symbol == S_ID || symbol1->symbol == S_INT || symbol1->symbol == S_FLOAT || symbol1->symbol == S_STR)
		{
			//pop first symbol and stop symbol and replace it by nonterm symbol
			pop_n(2, &symbol_stack);
			if(push(&symbol_stack, S_NONTERM) == false)
			{
				return ERROR_INTERNAL;
			}
			return SYNTAX_OK;
		}
		else
		{
			return SYNTAX_ERR;
		}

	}

//if there are three symbols, it will be some kind of operations between two nonterms E?E or E->(E)
//aka operation between two operands we already have on stack in real code

	else if (count == 3)
	{
		symbol3 = symbol_stack.top;
		symbol2 = symbol_stack.top->next;
		symbol1 = symbol2->next;
	}
	else
	{
		return SYNTAX_ERR;
	}

	//E->(E)
	if (count == 3 && symbol1->symbol == S_LBR &&symbol2->symbol == S_NONTERM && symbol3->symbol == RBR)
	{
		err = SYNTAX_OK;
	}

	//E->E?E
	if (count == 3 && symbol1->symbol == S_NONTERM &&symbol3->symbol == S_NONTERM)
	{
//switch according to operation between two operands, instructions for type control and for 
//coresponding stack operation will be generated 
		switch (symbol2->symbol)
		{
		//E->E<E
		case S_LS:
				//sem control
				//code gen
			break;
		//E->E>E
		case S_GT:
				//sem control
				//code gen
			break;
		//E->E<=E
		case S_LSEQ:
				//sem control
				//code gen
			break;
		//E->E>=E
		case S_GTEQ:
				//sem control
				//code gen
			break;
		//E->E==E
		case S_EQ:
				//sem control
				//code gen
			break;
		//E->E!=E
		case S_NEQ:
				//sem control
				//code gen
			break;
		//E->E+E
		case S_PLUS:
				//sem control
				//code gen
			break;
		//E->E-E
		case S_MINUS:
				//sem control
				//code gen
			break;
		//E->E*E
		case S_MUL:
				//sem control
				//code gen
			break;
		//E->E/E
		case S_DIV:
				//sem control
				//code gen
			break;
		//E->E//E
		case S_IDIV:
				//sem control
				//code gen
			break;
		//any of allowed operations -> syntax err
		default:
				return SYNTAX_ERR;
			break;
		}

	}

//pop 3 symbols and the stop symbol and replace it by nonterm symbol - operation with two operands
//was done

	pop_n(4, &symbol_stack);
	if(push(&symbol_stack, S_NONTERM) == false)
	{
		return ERROR_INTERNAL;
	}
	return err;
}

//main function for expression handle
int expression(prog_data* data)
{

	int err;
	
	//init stack
	init(&symbol_stack);

	//token for imputing in the end of list when all input tokens are parsed, until everything from stack is parsed 
	//(weird solution but works)
	Token token;	
	init_token(&token, &err);
	token.attribute = NULL;
	token.type = TOKEN_UNDEFINED;

	//input symbol readed from token
	symbols actual_symbol;
	//terminal symbol nearest to the stack top
	stack_item_t* top_terminal;

	//$ bottom of stack
	push(&symbol_stack, S_DOLLAR);

	//star parsing expression untill list is empty
	while(!(IS_END  || symbol_stack.top->next != NULL))
	{
		//get index of token type
		actual_symbol = get_symbol(&TOKEN);
		top_terminal = find_terminal(&symbol_stack);

		//if there is no terminal on stack
		if(top_terminal == NULL)
		{
			return SYNTAX_ERR;
		}

		//TODO sem control when token is identifier

		//get rule from precedence table for two terminals
		switch (prec_table[get_symbol_index(top_terminal->symbol)][get_symbol_index(actual_symbol)])
		{

		//just push symbol on stack
		case '=':
				if(push(&symbol_stack,actual_symbol) == false)
				{
					return ERROR_INTERNAL;
				}
								
				//move forward in list - get next symbol
				NEXT_TOKEN;
				break;


		//inserting stop symbol after first terminal on stack (changing priority), pushing input symbol
		case '<':
				insert_stop_symbol(&symbol_stack);
				push(&symbol_stack, actual_symbol);
				
				//if it is value/id generate push instruction (operand on stack)

				//move forward in list - get next symbol
				NEXT_TOKEN;
			
				break;

		//symbol(s) on stack can be handled and reduced to nonterminal according to reducing rules (when <y is on top) 
		case '>':

				err = reduce(data);
				if (err != 0)
				{
					return err;
				}

				break;

		//empty space in precedence table -> end of parsing if stack is empty and input list is empty or syntax err
		case ' ':
				if (actual_symbol == S_DOLLAR && top_terminal->symbol == S_DOLLAR )
				{
					return err;
				}
				else
				{
					return SYNTAX_ERR;
				}
				
				break;

		}
		//when list is empty but stack not, we have to first handle all remaining symbols on stack till it is empty
		//we keep adding new token in list with unkown type which will be seen as $ - ending symbol
		if(data->expression_list.First == NULL && symbol_stack.top->next != NULL)
		{
			DLInsertLast(&data->expression_list, &token, &err);
		}
		
	}

    return err;

}
