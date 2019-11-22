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
//#include "token_list.h"

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

//macro to check if token could be beginning of expression
#define IS_EXPR(token)                 \
token.type == TOKEN_STRING ||       \
token.type == TOKEN_NUM ||          \
token.type == TOKEN_NUM_DEC ||      \
token.type == TOKEN_NUM_EXP ||      \
token.type == TOKEN_LBRACKET


//checks if we want to use the statement rule
#define IS_STATEMENT_FUN (IF || WHILE || PASS || RETURN || IS_VALUE(data->token))
#define IS_STATEMENT (IF || WHILE || PASS || IS_VALUE(data->token))

//getting token and checking if lex err didnt occur
#define GET_TOKEN(data)                         \
err = get_token(&(data->token), data->file);    \
if (err != 0) { return err; }

//checking if we got the expected token
#define CHECK_TOKEN_TYPE(data, token_type)   \
if(data->token.type != token_type) {   \
    return SYNTAX_ERR; }

//checking if token is expected keyword
#define CHECK_KEYWORD(data, keyword)   \
if(string_compare_char(data->token.attribute, keyword)) {   \
    return SYNTAX_ERR; }


int init_global_table(prog_data* data)
{
    symtable_init(data->global_table);    
    data->token_loaded = false;


    //TODO first go through program
}



// <program> rule
int program(prog_data* data) {

    //error number stored
    int err = 0;

    //if there is no loaded token, get one
    if(data->token_loaded != true) {
        GET_TOKEN(data)
        data->token_loaded = true;
    }

    //<program> -> <def_function> <program>
    if (DEF) {

        err = def_function(data);

        if(err != 0) {
            return err;
        }

        return program(data);
    }

    //<program> -> <statement> <program>
    if (IS_STATEMENT)
    {

        err = statement(data);

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
    int err = 0;

//<statement> -> <expression> EOL <statement>
//rozdelil jsem rozpoznavani expressionu, kdyz zacina id bude to resit az pravidlo id what
//tady bude pripad kdy zacina random hodnotou (cislo, retezec..)

    if(IS_EXPR(data->token))
    {
        //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)
        GET_TOKEN(data)
        return statement(data);
    }

// <statement> -> id <idwhat> EOL <statement>
    if(data->token.type == TOKEN_IDENTIFIER)
    {
            
        if((err = idwhat(data) != 0)) {
        return err;
        }

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data,TOKEN_EOL)

        GET_TOKEN(data)

        return statement(data);
    }

//<statement> -> if <expression> : EOL INDENT <statement> DEDENT else : EOL INDENT <statement> DEDENT
    if(IF) 
    {        
        //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        //recursive calling of statement rule
        if((err = statement(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)

        CHECK_KEYWORD(data, "else")

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data,TOKEN_COLON)
         
        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        if((err = statement(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement(data);
    }

    //<statement> -> while <expression> : EOL INDENT <statement> DEDENT <statement>
    if(WHILE) 
    {
         //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        if((err = statement(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement(data);
    }

    //<statement> -> pass EOL <statement>
    if(PASS)
    {
        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        return statement(data);
    }

    //<statement> -> Ɛ
    return SYNTAX_OK;

}

int statement_fun(prog_data* data)
{
    int err = 0;

//<statement_fun> -> <expression> EOL <statement_fun>

    if(IS_EXPR(data->token))
    {
        //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)
        GET_TOKEN(data)
        return statement_fun(data);
    }

// <statement_fun> -> id <idwhat> EOL <statement_fun>
    if(data->token.type == TOKEN_IDENTIFIER)
    {
            
        if((err = idwhat(data) != 0)) {
        return err;
        }

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data,TOKEN_EOL)

        GET_TOKEN(data)

        return statement_fun(data);
    }

//<statement_fun> -> if <expression> : EOL INDENT <statement_fun> DEDENT else : EOL INDENT <statement_fun> DEDENT
    if(IF) 
    {        
        //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        //recursive calling of statement_fun rule
        if((err = statement_fun(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)

        CHECK_KEYWORD(data, "else")

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data,TOKEN_COLON)
         
        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        if((err = statement_fun(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement_fun(data);
    }

    //<statement_fun> -> while <expression> : EOL INDENT <statement_fun> DEDENT <statement_fun>
    if(WHILE) 
    {
         //TODO expression

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        if((err = statement_fun(data) != 0)) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement_fun(data);
    }

    //<statement_fun> -> pass EOL <statement_fun>
    if(PASS)
    {
        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)
        return statement_fun(data);
    }

//<statement_fun> -> return <return_value> EOL <statement_fun>
    if(RETURN)
    {   
        if((err = return_value(data)) != 0) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        return statement_fun(data);
    }

    //<statement_fun> -> Ɛ
    return SYNTAX_OK;
}

//<def_function> rule
int def_function(prog_data* data)
{
    //error number stored
    int err = 0;

    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_IDENTIFIER)

        //TODO sem control


    GET_TOKEN(data)

    CHECK_TOKEN_TYPE(data, TOKEN_LBRACKET)

    err = param(data);

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

        err = statement_fun(data);

        if (err != 0) {
            return err;
        }
    }
    else {
        return SYNTAX_ERR;
    }

    CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)
    data->token_loaded = false;
}

//<idwhat> rule
int idwhat(prog_data* data)
{
    //error number stored
    int err = 0;

    GET_TOKEN(data)

    //pozn.: muze prijit operator a bude se vyhodnocovat jako vyraz
    

    //<idwhat> -> = <assign>
    if (data->token.type == TOKEN_ASSIGN) {
        return assign(data);
    }

    //<idwhat> -> ( <term> )
    else if (data->token.type == TOKEN_LBRACKET) {
        term(data);
        if(data->token.type != TOKEN_RBRACKET) {
            return SYNTAX_ERR;
        }
        else {
            return SYNTAX_OK;
        }
    }

    //<idwhat> -> Ɛ (id muze byt samotne na radku pokud bylo definovano)
    else {

        //TODO sem control
        return SYNTAX_OK;
    }

    
    
}

// <term> rule
int term(prog_data* data)
{
    //error number stored
    int err = 0;

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
    //error number stored
    int err = 0;

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
    //error number stored
    int err = 0;

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
    //error number stored
    int err = 0;

    GET_TOKEN(data)

    //<param_n> -> , <param>
    if(data->token.type == TOKEN_COMMA) {
        param(data);
    }

    //<param_n> -> Ɛ
    return SYNTAX_OK;

}

//<assign> rule
//TODO : check everything and try to simplify with macros
int assign(prog_data* data)
{
    //error number stored
    int err = 0;

    GET_TOKEN(data)

    if (IS_VALUE(data->token)) {

        //temporary data pointer to symtable
        tSymdata **tmp;

        if (data->token.type != TOKEN_IDENTIFIER) {

            //TODO expression

            return SYNTAX_OK;
        }

        //<assign> -> id( <term> )
        //ID is a function
        if (symtable_search_function(data->global_table, data->token.attribute.str, *tmp)) {

            GET_TOKEN(data)

            CHECK_TOKEN_TYPE(data, TOKEN_LBRACKET)

            err = term(data);

            if (err != 0) {
                return err;
            }

            CHECK_TOKEN_TYPE(data, TOKEN_RBRACKET)

            return SYNTAX_OK;
        }

        //<assign> -> <expression>
        //we in aint in a function
        if (data->local_table == NULL) {
            if (symtable_search_variable(data->global_table, data->token.attribute.str, *tmp)) {

                //TODO expression
                return SYNTAX_OK;

            }
            else {
                return SEM_UNDEF_ERR;
            }
        }
        //we in function
        if (data->local_table != NULL){
            if (symtable_search_variable(data->local_table, data->token.attribute.str, *tmp)) {

                //TODO expression
                return SYNTAX_OK;

            }
            else {
                return SEM_UNDEF_ERR;
            }
        }

    }
    else {
        return SYNTAX_ERR;
    }

    //TODO

}

//<return_value> rule
int return_value(prog_data* data)
{
    //<return_value> -> <expression>
    if (IS_VALUE(data->token)) {
        //TODO expressions
    }
    //<return_value> -> Ɛ
    else {
        return SYNTAX_OK;
    }
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

