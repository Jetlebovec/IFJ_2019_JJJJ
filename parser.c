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



int program(prog_data* data) {

    get_token(data->token, data->file);


    //<program> -> <def_function> <program>
    if (string_compare(data->token.attribute, "def")) {

        if(!def_function(data)) {
            return 1;
        }
        return program(data);
    }

    //<program> -> <statement> <program>
    if (string_compare(data->token.attribute, "if")
        || string_compare(data->token.attribute, "while")
        || string_compare(data->token.attribute, "pass")
        || data->token.type == TOKEN_IDENTIFIER
        )
    {
        if (!statement(data)) {
            return 1;
        }
        return program(data);
    }

    //<program> -> EOF
    if (data->token.type == TOKEN_EOF) {
        return 0;
    }
    else {
        return 1;
    }

}


int statement(prog_data* data)
{


}


int def_function(prog_data* data)
{


}

int statement_fun(prog_data* data)
{


}

int idwhat(prog_data* data)
{


}

int term(prog_data* data)
{
    get_token(data->token, data->file);

    //<term> -> value <term_n>
    //<term> -> id <term_n>
    //<term> -> None <term_n>
    if (data->token.type == TOKEN_STRING ||
        data->token.type == TOKEN_NUM ||
        data->token.type == TOKEN_NUM_DEC ||
        data->token.type == TOKEN_NUM_EXP ||
        data->token.type == TOKEN_IDENTIFIER ||
        string_compare(data->token.attribute, "None")
            )
    {
        term_n(data);
    }

    //<term> -> Ɛ
    return 0; //syntax ok

}

int term_n(prog_data* data)
{


}

int param(prog_data* data)
{


}
int param_n(prog_data* data)
{


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


    //****************************************************************TEST START

    // TESTING WITH FILE
    FILE *file;
    file = fopen("test.txt", "r");
    // TESTING WITH FILE

    // Get new token from the scanner
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

    // TESTING WITH FILE
    fclose(file);
    // TESTING WITH FILE


    //*****************************************************************TEST END

    // Free token
    string_free(newToken.attribute);
    free(newToken.attribute);

    return err_code;
}

