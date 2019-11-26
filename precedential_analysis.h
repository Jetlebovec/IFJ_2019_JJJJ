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
 *      File: precedential_analysis.h
 */

#include <stdio.h>
#include <stdlib.h>

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
	ASSIGN, //14
	TERM,	//15
    DOLLAR  //16

} Prec_table_symbol;

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