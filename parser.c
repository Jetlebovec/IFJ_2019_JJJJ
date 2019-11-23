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

//macro to check if token could be beginning of expression
#define IS_EXPR(token)                 \
token.type == TOKEN_STRING ||       \
token.type == TOKEN_NUM ||          \
token.type == TOKEN_NUM_DEC ||      \
token.type == TOKEN_NUM_EXP ||      \
token.type == TOKEN_LBRACKET

//macro to check if token is operator
#define IS_OP(token)                 \
token.type == TOKEN_PLUS ||          \
token.type == TOKEN_MINUS ||         \
token.type == TOKEN_MULTI ||        \
token.type == TOKEN_INT_DIV ||      \
token.type == TOKEN_FLOAT_DIV ||    \
token.type == TOKEN_GREATER ||      \
token.type == TOKEN_GREATER_EQUAL || \
token.type == TOKEN_LESSER  ||      \
token.type == TOKEN_LESSER_EQUAL || \
token.type == TOKEN_EQUAL ||        \
token.type == TOKEN_NOT_EQUAL


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
    CHECK_TOKEN_TYPE(data, TOKEN_EOF)

    return SYNTAX_OK;

}


int statement(prog_data* data)
{   
    int err = 0;

//<statement> -> <expression> EOL <statement>
//rozdelil jsem rozpoznavani expressionu, kdyz zacina id bude to resit az pravidlo id what
//tady bude pripad kdy zacina random hodnotou (cislo, retezec..)

// <statement> -> <expression> EOL <statement>
    if(IS_EXPR(data->token))
    {
        //EXPRESSION
        //we add the whole expression until eol is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_EOL)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)
        GET_TOKEN(data)
        return statement(data);
    }

// <statement> -> id <idwhat> EOL <statement>
    if(data->token.type == TOKEN_IDENTIFIER)
    {

        err = idwhat(data);

        if(err != 0) {
            return err;
        }

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        return statement(data);
    }

//<statement> -> if <expression> : EOL INDENT <statement> DEDENT else : EOL INDENT <statement> DEDENT
    if(IF) 
    {
        //EXPRESSION
        //we add the whole expression until colon is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_COLON)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        //recursive calling of statement rule
        err = statement(data);

        if(err != 0) {
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

        //recursive statement call
        err = statement(data);

        if(err != 0) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement(data);
    }

    //<statement> -> while <expression> : EOL INDENT <statement> DEDENT <statement>
    if(WHILE) 
    {
        //EXPRESSION
        //we add the whole expression until colon is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_COLON)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        //recursive statement
        err = statement(data);

        if(err != 0) {
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
        //EXPRESSION
        //we add the whole expression until eol is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_EOL)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)
        GET_TOKEN(data)
        return statement_fun(data);
    }

// <statement_fun> -> id <idwhat> EOL <statement_fun>
    if(data->token.type == TOKEN_IDENTIFIER)
    {

        err = idwhat(data);

        if(err != 0) {
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
        //EXPRESSION
        //we add the whole expression until colon is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_COLON)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        err = statement_fun(data);

        if(err != 0) {
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

        err = statement_fun(data);

        if(err != 0) {
            return err;
        }

        CHECK_TOKEN_TYPE(data, TOKEN_DEDENT)

        GET_TOKEN(data)
        return statement_fun(data);
    }

    //<statement_fun> -> while <expression> : EOL INDENT <statement_fun> DEDENT <statement_fun>
    if(WHILE) 
    {
        //EXPRESSION
        //we add the whole expression until colon is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_COLON)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

        CHECK_TOKEN_TYPE(data, TOKEN_COLON)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_EOL)

        GET_TOKEN(data)

        CHECK_TOKEN_TYPE(data, TOKEN_INDENT)

        GET_TOKEN(data)

        err = statement_fun(data);

        if(err != 0) {
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
        GET_TOKEN(data)

        err = return_value(data);

        if(err != 0) {
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

    //ulozeni predchoziho tokenu - identifikator promenne, dulezite asf
    Token temp;
    init_token(&temp, &err);
    if (err != 0) {
        return err;
    }
    temp.type = data->token.type;
    if(string_copy(&temp.attribute, &data->token.attribute) != 0) {
        return ERROR_INTERNAL;
    }
    //token ulozen jako temp

    GET_TOKEN(data)

    //muze prijit operator a bude se vyhodnocovat jako vyraz
    if(IS_OP(data->token))
    {
        //EXPRESSION
        //we add the whole expression until eol is found into List
        tDLList expr;
        DLInitList(&expr);

        //WE NEED TO STORE THE PREVIOUS TOKEN FIRST
        DLInsertLast(&expr, &temp, &err);
        if (err != 0) {
            return err;
        }
        string_free(temp.attribute);
        free(temp.attribute);

        //storing rest of the expression
        while(data->token.type != TOKEN_EOL)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);
    }

    //<idwhat> -> = <assign>
    if (data->token.type == TOKEN_ASSIGN) {

        string_free(temp.attribute);
        free(temp.attribute);

        return assign(data);
    }

    //<idwhat> -> ( <term> )
    else if (data->token.type == TOKEN_LBRACKET) {
        string_free(temp.attribute);
        free(temp.attribute);

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
        string_free(temp.attribute);
        free(temp.attribute);

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
int assign(prog_data* data) {

    //error number stored
    int err = 0;

    GET_TOKEN(data)

    //temporary data pointer to symtable
    tSymdata **tmp;

    //after '=' (assign token) we expect string, number, id, or l-bracket - expression
    if (!(IS_VALUE(data->token) || data->token.type == TOKEN_LBRACKET)) {
        return SYNTAX_ERR;
    }

    //<assign> -> <expression>
    if (data->token.type != TOKEN_IDENTIFIER) {

        //EXPRESSION
        //we add the whole expression until eol is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_EOL)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);

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
    //TODO expression

    /*
    //we aint in a function
    if (data->local_table == NULL) {
        if (symtable_search_variable(data->global_table, data->token.attribute.str, *tmp)) {

            return SYNTAX_OK;

        } else {
            return SEM_UNDEF_ERR;
        }
    }
    //we in function
    if (data->local_table != NULL) {
        if (symtable_search_variable(data->local_table, data->token.attribute.str, *tmp)) {

            return SYNTAX_OK;

        } else {
            return SEM_UNDEF_ERR;
        }
    }*/

}

//<return_value> rule
int return_value(prog_data* data)
{
    int err = 0;

    //<return_value> -> <expression>
    if (IS_VALUE(data->token)) {
        //EXPRESSION
        //we add the whole expression until eol is found into List
        tDLList expr;
        DLInitList(&expr);

        while(data->token.type != TOKEN_EOL)
        {
            DLInsertLast(&expr, &data->token, &err);
            if (err != 0) {
                return err;
            }
            GET_TOKEN(data)
        }

        data->expression_list = expr;
        err = expression(data);   //precedential analysis
        if (err != 0) {
            return err;
        }
        DLDisposeList(&expr);
    }
    //<return_value> -> Ɛ
    else {
        return SYNTAX_OK;
    }
}

void init_token(Token *token, int *error_code){

        token.type = TOKEN_UNDEFINED;
        token.attribute = (tString*) malloc(sizeof(tString));
        if (token.attribute == NULL)
        {
            error_code = ERROR_INTERNAL;
        }
        if (string_init(token.attribute) != 0) {
            error_code = ERROR_INTERNAL;
        }
}

int analyse()
{
    int err_code = 0;

    // Initialize token
    Token newToken;

    init_token(&newToken, &err_code);
    if (err_code != 0)
        return err_code;

    // Initialize indentation stack of the scanner
    stack_init(&indent_stack);
    stack_push(&indent_stack, 0);

    //initialize the global symtable
    tBSTNodePtr *global_table;
    symtable_init(global_table);

    //create the structure to store parser data
    prog_data Data;

    //initialize the structure to store parser data
    Data.token = newToken;
    Data.local_table = NULL;
    Data.global_table = global_table;
    Data.file = stdin;
    Data.token_loaded = 0;

    //STARTING FOR REAL
    //starting the recursive descent
    err_code = program(&Data);


    symtable_dispose(global_table);


    /*

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

     */


    // Free token
    string_free(newToken.attribute);
    free(newToken.attribute);

    return err_code;
}

