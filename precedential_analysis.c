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
#include "parser.h"
#include "precedential_analysis.h"

#define TABLE_SIZE 16


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

//enum of symbol indexes in prec. table
typedef enum
{
    LS,     //1
    GT,     //2
    LSEQ,   //3
    GTEQ,   //4
    EQ,     //5
    NEQ,    //6
    PLUS,   //7
    MINUS,  //8
    MUL,    //9
    DIV,    //10
    IDIV,   //11
    LBR,    //12
    RBR,    //13
    TERM,   //14
    EQ,     //15
    DOLLAR,  //16

} Prec_table_index;

//get symbol index in prec. table
Prec_table_index get_symbol_index(Token* token)
{
    switch (token->type)
	{
	case TOKEN_PLUS:
		return PLUS;
	case TOKEN_MINUS:
		return MINUS;
	case TOKEN_MULTI:
		return MUL;
	case TOKEN_INT_DIV :
		return IDIV;
	case TOKEN_FLOAT_DIV:
		return DIV;
	case TOKEN_ASSIGN:
		return EQ;
	case TOKEN_NOT_EQUAL:
		return NEQ;
	case TOKEN_LESSER_EQUAL:
		return LSEQ;
	case TOKEN_GREATER_EQUAL:
		return GTEQ;
	case TOKEN_LESSER:
		return LS;
	case TOKEN_GREATER:
		return GT;
	case TOKEN_LBRACKET:
		return LBR;
	case TOKEN_RBRACKET:
		return RBR;
	case TOKEN_IDENTIFIER:
    case TOKEN_NUM:
	case TOKEN_NUM_DEC:
    case TOKEN_NUM_EXP:
	case TOKEN_STRING:
		return TERM;
	
	default:
		return DOLLAR;
	}
}

//get first token from list and delete it
Token load_token(prog_data* data)
{    
    Token token = data->expression_list.First->token;
    DLDeleteFirst(&(data->expression_list));     
    return token;   
}

//main function for expression handle
int expression(prog_data* data)
{
    //TODO stack 
    //start with first token)

    Token token = load_token(data);
}
