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
 *      File: parser.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

//function prototypes
int program(prog_data* data);
int statement(prog_data* data);
int def_function(prog_data* data);
int term(prog_data* data);
int term_n(prog_data* data);
int param(prog_data* data);
int param_n(prog_data* data);
int statement_fun(prog_data* data);
int return_value(prog_data* data);
int idwhat(prog_data* data);
int assign(prog_data* data);

//checking keywords
#define DEF string_compare_char(data->token.attribute, "def")
#define ELSE string_compare_char(data->token.attribute, "else")
#define IF string_compare_char(data->token.attribute, "if")
#define NONE string_compare_char(data->token.attribute, "None")
#define PASS string_compare_char(data->token.attribute, "pass")
#define RETURN string_compare_char(data->token.attribute, "return")
#define WHILE string_compare_char(data->token.attribute, "while")

//macro to check if the token is value
#define IS_VALUE(token)                 \
token.type == TOKEN_STRING ||       \
token.type == TOKEN_NUM ||          \
token.type == TOKEN_NUM_DEC ||      \
token.type == TOKEN_NUM_EXP ||      \
token.type == TOKEN_IDENTIFIER

//checks if we want to use the statement rule
#define IS_STATEMENT_FUN (IF || WHILE || PASS || RETURN || IS_VALUE(data->token))
#define IS_STATEMENT (IF || WHILE || PASS || IS_VALUE(data->token))

//getting token and checking if lex err didnt occur
#define GET_TOKEN(data)                             \
if(get_token(data->token, data->file) != LEX_OK) {  \
    return LEX_ERR; }

//checking if we got the expected token
#define CHECK_TOKEN_TYPE(data, token_type)   \
if(data->token.type != token_type) {   \
    return SYNTAX_ERR; }



// <program> rule
int program(prog_data* data) {

    GET_TOKEN(data)


    //<program> -> <def_function> <program>
    if (DEF) {

        //error number stored
        int err = def_function(data);

        if(err != 0) {
            return err;
        }

        return program(data);
    }

    //<program> -> <statement> <program>
    if (IS_STATEMENT)
    {

        int err = statement(data);

        if (err != 0) {
            return err;
        }

        return program(data);
    }

    //<program> -> EOF
    if (data->token.type == TOKEN_EOF) {
        return SYNTAX_OK;
    }
    else {
        return SYNTAX_ERR;
    }

}


int statement(prog_data* data)
{


}

int statement_fun(prog_data* data)
{


}

//<def_function> rule
int def_function(prog_data* data)
{
    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_IDENTIFIER)

        //todo sem control


    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_LBRACKET)

    int err = param(data);

    if (err != 0) {
        return err;
    }

    CHECK_TOKEN_TYPE(data, TOKEN_RBRACKET)

    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_COLON)

    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_EOL)

    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

    GET_TOKEN(data)

    if (IS_STATEMENT_FUN)
    {

        int err = statement_fun(data);

        if (err != 0) {
            return err;
        }
    }
    else {
        return SYNTAX_ERR;
    }

    CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

}

//<idwhat> rule
int idwhat(prog_data* data)
{
    GET_TOKEN(data)

    //<idwhat> -> = <assign>
    if (data->token.type == TOKEN_ASSIGN) {
        return assign(data);
    }
    //<idwhat> -> ( <term> )
    else if (data->token.type == TOKEN_LBRACKET) {
        return term(data);
    }
    else {
        return SYNTAX_ERR;
    }

}

// <term> rule
int term(prog_data* data)
{
    GET_TOKEN(data)

    //<term> -> value <term_n>
    //<term> -> id <term_n>
    //<term> -> None <term_n>
    if (IS_VALUE(data->token) || NONE)
    {
        //TODO sem control

        return term_n(data);
    }

    //<term> -> Ɛ
    return SYNTAX_OK;

}

// <term_n> rule
int term_n(prog_data* data)
{
    GET_TOKEN(data)

    //<term_n> -> , <term>
    if(data->token.type == TOKEN_COMMA) {
        return term(data);
    }

    //<term_n> -> Ɛ
    return SYNTAX_OK;

}

// <param> rule
int param(prog_data* data)
{
    GET_TOKEN(data)

    //<param> -> id
    if(data->token.type == TOKEN_IDENTIFIER) {
        //TODO sem control

        return param_n(data);
    }

    //<param> -> Ɛ
    return SYNTAX_OK;

}

// <param_n> rule
int param_n(prog_data* data)
{
    GET_TOKEN(data)

    //<param_n> -> , <param>
    if(data->token.type == TOKEN_COMMA) {
        param(data);
    }

    //<param_n> -> Ɛ
    return SYNTAX_OK;

}


int assign(prog_data* data)
{


}


int return_value(prog_data* data)
{


}

int analyse()
{
    int err_code = 0;
    // Initialize token
    Token newToken;
    newToken.type = TOKEN_UNDEFINED;
    newToken.attribute = (tString*) malloc(sizeof(tString));
    if (newToken.attribute == NULL)
    {
        return 99;
    }
    string_init(newToken.attribute);
    // Initialize indentation stack of the scanner
    stack_init(&indent_stack);
    stack_push(&indent_stack, 0);




    // TESTING WITH FILE
    FILE *file;
    file = fopen("test.txt", "r");
    // TESTING WITH FILE

    //****************************************************************TEST START

    // Test prints the first 150 tokens from test.txt
    for (int i = 0; i < 150; i++)
    {
        if ((err_code = get_token(&newToken, file)) != 0)
        {
            break;
        } else
        {
            printf("Token %d:\n", i);
            printf("Token type: %d\n", newToken.type);
            printf("Token attribute: ");
            string_print(newToken.attribute);
            printf("\n");
            if (newToken.type == TOKEN_EOF)
            {
                break;
            }
        }
    }

    //*****************************************************************TEST END

    // TESTING WITH FILE
    fclose(file);
    // TESTING WITH FILE


    // Free token
    string_free(newToken.attribute);
    free(newToken.attribute);

    return err_code;
}

