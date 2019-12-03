/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Kopáček Jiří    xkopac06
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: parser.h
 */


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "symtable.h"
#include "token_list.h"
#include "precedential_analysis.h"
#include "precedential_stack.h"
#include "generator.h"

#define LEX_OK			            0
#define SYNTAX_OK 					0
#define LEX_ERR         			1   //lexical analysis error
#define SYNTAX_ERR					2   //syntactic analysis error
#define SEM_UNDEF_ERR       		3   //undefined variable or function
#define SEM_TYPE_ERR    			4   //types in expression incompatible
#define SEM_PARAM_ERR    			5   //param count doesnt match in function call
#define SEM_ERR_OTHER               6   //other semantic errors
#define SEM_ZERO_ERR                9   //dividing by zero error
#define ERROR_INTERNAL             99   //internal compiler error

typedef struct {
    tBSTNodePtr global_table;        // Global symbol table
    tBSTNodePtr local_table;        // Local symbol table

    FILE *file; //soubor, ze kterého čte scanner

    Token token; //

    bool token_loaded;  //overeni, zda nacitat novy token

    bool in_function;

    tDLList expression_list; //list of tokens that form expression

    tSymdata *current_fun_data;

} prog_data;

//enum of symbol indexes for prec. table
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
	TERM,	//14
	ASSIGN, //15
    DOLLAR  //16

} Prec_table_symbol;

/**
 * @brief Main parser function
 * @return Returns error code
 */
int analyse();

int expression(prog_data* data);

#endif // PARSER_H_INCLUDED
