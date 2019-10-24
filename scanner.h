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
#include "stack.h"

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
    stSTRING_ESCAPE,
    stSTRING_ESCAPE_HEX,
    stSTRING_ESCAPE_HEX_HALF,
    //stSTRING,

    // Doc string
    stDOC_STRING_A,
    stDOC_STRING_B,
    stDOC_STRING_UNFINISHED,
    stDOC_STRING_UNFINISHED_A,
    stDOC_STRING_UNFINISHED_B,
    //stDOC_STRING,

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
    TOKEN_IDENTIFIER, //0
    TOKEN_KEYWORD,

    TOKEN_NUM, //2
    TOKEN_NUM_DEC,
    TOKEN_NUM_EXP,

    TOKEN_STRING, //5

    TOKEN_DOC_STRING, //6

    //TOKEN_COMMENT,

    TOKEN_INDENT, //7
    TOKEN_DEDENT, //8

    TOKEN_COLON, //9
    TOKEN_COMMA,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_PLUS, //13
    TOKEN_MINUS,
    TOKEN_MULTI,
    TOKEN_INT_DIV,
    TOKEN_FLOAT_DIV,

    TOKEN_GREATER, //18
    TOKEN_GREATER_EQUAL,
    TOKEN_LESSER, //20
    TOKEN_LESSER_EQUAL,
    TOKEN_ASSIGN, //22
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL, //24

    TOKEN_EOL, // 25
    TOKEN_EOF, //26
    TOKEN_UNDEFINED
} tokenType;

// Struct of type Token
typedef struct
{
    tokenType type;
    tString *attribute;
} Token;

tStack indent_stack;
// 1 if the stack is being emptied
int state_dedenting;
// stores the searched indentation value
int searched_value;
// 1 if eof has been reached and the stack is being emptied
int eof_reached;

// Returns 1 if the character is a letter, 0 otherwise
int isCharAlpha(char c);

// Returns 1 if the character is a digit, 0 otherwise
int isCharDigit(char c);

// Returns 1 if the character is a keyword, 0 otherwise
int isStringKeyword(tString *s);

// Finishes all operations before returning the token
int finalize(Token *token);

// Dedents the stack and tries to find the searched value on the stack
int dedent_stack(Token *token);

// Empties the stack after reading EOF
int empty_stack(Token *token);

// Reads the next token, returns error code(0, 1, 99)
int get_token(Token *token, FILE *file);



#endif // SCANNER_H_INCLUDED
