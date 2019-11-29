/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Diviš Jan       xdivis12
 *          Pojsl Jakub	    xpojsl00
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

	case S_MINUS:
		return MINUS;

	case S_MUL:
		return MUL;

	case S_IDIV :
		return IDIV;

	case S_DIV:
		return DIV;

	case S_EQ:
		return EQ;

	case S_NEQ:
		return NEQ;

	case S_LSEQ:
		return LSEQ;

	case S_GTEQ:
		return GTEQ;

	case S_LS:
		return LS;

	case S_GT:
		return GT;

	case S_LBR:
		return LBR;

	case S_RBR:
		return RBR;

	case S_ID:
    case S_INT:
	case S_FLOAT:
	case S_STR:
    case S_NONE:
		return TERM;

	case S_ASSIGN:
		return ASSIGN;

	case S_DOLLAR:
		return DOLLAR;


	default:
		return DOLLAR;

	}
}



//get symbol from token used for analysis
symbols get_symbol(Token* token)
{
    switch (token->type)
	{
		case TOKEN_PLUS:
		return S_PLUS;

	case TOKEN_MINUS:
		return S_MINUS;

	case TOKEN_MULTI:
		return S_MUL;

	case TOKEN_INT_DIV :
		return S_IDIV;

	case TOKEN_FLOAT_DIV:
		return S_DIV;

	case TOKEN_EQUAL:
		return S_EQ;

	case TOKEN_NOT_EQUAL:
		return S_NEQ;

	case TOKEN_LESSER_EQUAL:
		return S_LSEQ;

	case TOKEN_GREATER_EQUAL:
		return S_GTEQ;

	case TOKEN_LESSER:
		return S_LS;

	case TOKEN_GREATER:
		return S_GT;

	case TOKEN_LBRACKET:
		return S_LBR;

	case TOKEN_RBRACKET:
		return S_RBR;

	case TOKEN_IDENTIFIER:
		return S_ID;

    case TOKEN_NUM:
		return S_INT;

	case TOKEN_NUM_DEC:
		return S_FLOAT;

    case TOKEN_NUM_EXP:
		return S_FLOAT;

	case TOKEN_STRING:
		return S_STR;

	case TOKEN_ASSIGN:
		return S_ASSIGN;


	default:
		return S_DOLLAR;

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
			if(push(&symbol_stack, S_NONTERM) == 1)
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
	if (symbol1->symbol == S_LBR && symbol2->symbol == S_NONTERM && symbol3->symbol == RBR)
	{
		err = SYNTAX_OK;
	}

	//E->E?E
	if (symbol1->symbol == S_NONTERM && symbol3->symbol == S_NONTERM)
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
	if(push(&symbol_stack, S_NONTERM) == 1)
	{
		return ERROR_INTERNAL;
	}
	return err;
}

//main function for expression handle
int expression(prog_data* data)
{
	int err = 0;

	//init stack
	init(&symbol_stack);

	//init of token for imputing in the end of list when all input tokens are parsed, until everything from stack is parsed
	//(weird solution but works)
	tString string;
	string_init(&string);
	string_append_char(&string,'X');
	Token token;
	init_token(&token, &err);
	token.attribute = &string;
	token.type = TOKEN_UNDEFINED;

	//input symbol readed from token
	symbols actual_symbol;
	//terminal symbol nearest to the stack top
	stack_item_t* top_terminal;

	//$ bottom of stack
	if (push(&symbol_stack, S_DOLLAR) == 1)
    {
        return ERROR_INTERNAL;
    }

	//star parsing expression untill list is empty
	while(!(IS_END)  || symbol_stack.top->next != NULL)
	{
		//get index of token type
		actual_symbol = get_symbol(&TOKEN);
		top_terminal = find_terminal(&symbol_stack);

		//if there is no terminal on stack
		if(top_terminal == NULL)
		{
			return SYNTAX_ERR;
		}

        tSymdata *pom;
        //if variable is not defined
        if (TOKEN.type == TOKEN_IDENTIFIER) {
            if ((symtable_search_variable(&data->local_table, TOKEN.attribute->str, &pom) != 0) &&
                (symtable_search_variable(&data->global_table, TOKEN.attribute->str, &pom) != 0)) {
                return SEM_UNDEF_ERR;
            }
        }

		//get rule from precedence table for two terminals
		switch (prec_table[get_symbol_index(top_terminal->symbol)][get_symbol_index(actual_symbol)])
		{

		//just push symbol on stack
		case '=':
				if(push(&symbol_stack,actual_symbol) == 1)
				{
					return ERROR_INTERNAL;
				}

				//move forward in list - get next symbol
				NEXT_TOKEN;
				break;


		//inserting stop symbol after first terminal on stack (changing priority), pushing input symbol
		case '<':
				if (insert_stop_symbol(&symbol_stack) == 1)
                {
                    return ERROR_INTERNAL;
                }
				if (push(&symbol_stack, actual_symbol) == 1)
                {
                    return ERROR_INTERNAL;
                }
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
