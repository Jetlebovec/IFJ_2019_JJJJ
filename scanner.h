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
 *      File: scanner.h
 */


#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "custom_string.h"

// Enum of all the possible states
typedef enum
{
    // Start
    stSTART,

    // IDs
    stID_KEYWORD,

    // Number
    stNUM,
    stNUM_POINT,
    stNUM_DEC,
    stNUM_E,
    stNUM_SIGN,
    stNUM_EXP,

    // String
    stSTRING_UNFINISHED,
    stSTRING_EXCAPE,
    stSTRING_ESCAPE_HEX,
    stSTRING_EXCAPE_HEX_HALF,
    //stSTRING,

    // Doc string
    stDOC_STRING_A,
    stDOC_STRING_B,
    stDOC_STRING_UNFINISHED,
    stDOC_STRING_UNFINISHED_A,
    stDOC_STRING_UNFINISHED_B,
    stDOC_STRING,

    // Comment
    stCOMMENT,

    // Indentation
    stINDENTATION_COUNT,

    // Special characters
    //stCOLON,
    //stCOMMA
    //stLBRACKET,
    //stRBRACKET,

    // Operators
    //stPLUS,
    //stMINUS,
    //stMULTI,
    stINT_DIV,
    //stFLOAT_DIV,

    // Comparators
    stGREATER,
    //stGREATER_EQUAL,
    stLESSER,
    //stLESSER_EQUAL,
    stASSIGN,
    //stEQUAL,
    stEXCL,
    //stNOT_EQUAL,

} tState;


// Enum of all the possible token types
typedef enum
{
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,

    TOKEN_NUM,
    TOKEN_NUM_DEC,
    TOKEN_NUM_EXP,

    TOKEN_STRING,

    TOKEN_DOC_STRING,

    //TOKEN_COMMENT,

    TOKEN_INDENT,
    TOKEN_DEDENT,

    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTI,
    TOKEN_INT_DIV,
    TOKEN_FLOAT_DIV,

    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESSER,
    TOKEN_LESSER_EQUAL,
    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,

    TOKEN_EOL,
    TOKEN_EOF,
    TOKEN_UNDEFINED
} tokenType;

// Struct of type Token
typedef struct
{
    tokenType type;
    tString *attribute;
} Token;

// Reads the next token, returns error code
int get_token(Token *token);



#endif // SCANNER_H_INCLUDED
