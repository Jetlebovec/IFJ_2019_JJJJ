/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Sasín Jonáš     xsasin05
 *
 *      File: generator.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void gen_tf_defvar(int param_id) {
    printf("\nDEFVAR TF@%%%d", param_id);
}

void gen_defvar(char* var_name, bool in_function)
{
    if(in_function) {
        printf("\nDEFVAR LF@%s", var_name);
    }
    else {
        printf("\nDEFVAR GF@%s", var_name);
    }
}

void gen_move_exp_res (char* dest, bool in_function)
{
    printf("\nPOPS GF@exp_result");

    if(in_function) {
        printf("\nMOVE LF@%s GF@exp_result", dest);
    }
    else {
        printf("\nMOVE GF@%s GF@exp_result", dest);
    }
}

int gen_move_arg(int param_id, char* attribute, char* type, bool local, bool id)
{
    char* source;

    if (id) {

        if (local) {
            source = "LF@";
            strcat(source, attribute);
        }
        else {
            source = "GF@";
            strcat(source, attribute);
        }

    }
    else {

        if (strcmp(type, "nil")) {
            source = "nil@nil";
            gen_move_arg_print(param_id, source);
        }
        else if (strcmp(type, "int")) {
            printf("\nMOVE TF@%%%d int@%s", param_id, attribute);
        }
        else if (strcmp(type, "float")) {
            printf("\nMOVE TF@%%%d float@%a", param_id, strtod(attribute, NULL));
        }
        else {
            //convert the string to the retarded format
            // TODO strToIFJcode(&attribute);

            if (attribute == NULL) {
                return 99;
            }
            printf("\nMOVE TF@%%%d string@%s", param_id, attribute);
        }

        return 0;
    }

    gen_move_arg_print(param_id, source);
    return 0;
}

void gen_move_arg_print(int param_id, char* source)
{
    printf("\nMOVE TF@%%%d %s", param_id, source);
}

void gen_def_move_param (char* param_name, int param_id)
{
    printf("\nDEFVAR LF@%s", param_name);
    printf("\nMOVE LF@%s LF@%%%d", param_name, param_id);
}

void gen_function_start(char* fun_name)
{
    printf("\nJUMP $jump_fun_%s", fun_name);
    printf("\nLABEL $%s", fun_name);
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@%%retval");
    printf("\nMOVE LF@%%retval nil@nil");
}

void gen_function_end(bool end_of_fun_body, char* fun_name)
{
    //exiting fun via return - get the return value
    if (!end_of_fun_body) {
        printf("\nPOPS LF@%%retval");
    }

    printf("\nPOPFRAME");
    printf("\nRETURN");

    //exiting fun body without return - label the end of function
    if (end_of_fun_body) {
        printf("\nLABEL $jump_fun_%s", fun_name);
    }
}

void gen_call_fun(char* fun_name) {
    printf("CALL $%s", fun_name);
    printf("MOVE GF@exp_result TF@%%retval");
}

void gen_if(int cond_id)
{
    printf("\nPOPS GF@exp_result");
    printf("\nJUMPIFEQ $else_label_%d GF@exp_result int@0", cond_id);
    printf("\nJUMPIFEQ $else_label_%d GF@exp_result bool@false", cond_id);
}

void gen_else(int cond_id)
{
    printf("\nJUMP $if_end_%d", cond_id);
    printf("\nLABEL $else_label_%d", cond_id);
}

void gen_if_end(int cond_id)
{
    printf("\nLABEL $if_end_%d", cond_id);
}

void gen_while(int cycle_id)
{
    printf("\nLABEL $while_%d", cycle_id);
    printf("\nPOPS GF@exp_result");
    printf("\nJUMPIFEQ $while_end_%d GF@exp_result int@0", cycle_id);
    printf("\nJUMPIFEQ $while_end_%d GF@exp_result bool@false", cycle_id);
}

void gen_while_end(int cycle_id)
{
    printf("\nJUMP $while_%d", cycle_id);
    printf("\nLABEL $while_end_%d", cycle_id);
}

void gen_push_operand(Token token, int is_global)
{
    if(token.type == TOKEN_IDENTIFIER)
    {
        if(is_global == 1)
        {
            printf("\nPUSHS GF@%s", token.attribute->str);
        }
        else
        {
             printf("\nPUSHS LF@%s", token.attribute->str);
        }
    }
    else
    {
        double number;
        switch (token.type)
        {
        case TOKEN_NUM:
            printf("\nPUSHS int@%s", token.attribute->str);
            break;

        case TOKEN_NUM_DEC:
            number = strtod(token.attribute->str,NULL);
            printf("\nPUSHS float@%a", number);
            break;

        case TOKEN_NUM_EXP:
            number = strtod(token.attribute->str,NULL);
            printf("\nPUSHS float@%a", number);
            break;

        case TOKEN_STRING:
            //TODO
            break;

        default:
            break;
        }
    }



}

void gen_operation(symbols symbol)
{
    //switch according to operation
    switch (symbol)
    {
    case S_LS:
        printf("LTS\n");
        break;

    case S_GT:
        printf("GTS\n");
        break;

    case S_LSEQ:
    //TODO DEF global var %%operand_1,2 in the beginning

        printf("\nPOPS GF@%%operand_1");
		printf("\nPOPS GF@%%operand_2");
		printf("\nPUSHS GF@%%operand_2");
		printf("\nPUSHS GF@%%operand_1");
		printf("\nLTS");
		printf("\nPUSHS GF@%%operand_2");
		printf("\nPUSHS GF@%%operand_1");
		printf("\nEQS");
		printf("\nORS");
		break;

    case S_GTEQ:
        printf("\nPOPS GF@%%operand_1");
		printf("\nPOPS GF@%%operand_2");
		printf("\nPUSHS GF@%%operand_2");
		printf("\nPUSHS GF@%%operan1");
		printf("\nGTS");
		printf("\nPUSHS GF@%%operan2");
		printf("\nPUSHS GF@%%operan1");
		printf("\nEQS");
		printf("\nORS");
		break;

    case S_EQ:
        printf("\nEQS");
        break;

    case S_NEQ:
        printf("\nEQS");
        printf("\nNOTS");
        break;

    case S_PLUS:
        printf("\nADDS");
        break;

    case S_MINUS:
        printf("\nSUBS");
        break;

    case S_MUL:
        printf("\nMULS");
        break;

    case S_DIV:
        printf("\nDIVS");
        break;

    case S_IDIV:
        printf("\nIDIVS");
        break;

    default:
        break;
    }

}

char* token_to_ifjcode_val(Token *token)
{
    // Allocates the new string
    char *new_var = malloc((32 + token->attribute->length) * sizeof(char));
    if (new_var == NULL)
    {
        return NULL;
    }
    // Variables for string copying
    int i = 0;
    int pos = 7;
    int length = 32 + token->attribute->length;
    char c;
    // Changes the value based on the token type
    switch(token->type)
    {
        case TOKEN_NUM:
            sprintf(new_var, "int@%d", strtol(token->attribute->str, NULL, 10));
            break;
        case TOKEN_NUM_DEC:
        case TOKEN_NUM_EXP:
            sprintf(new_var, "float@%a", strtod(token->attribute->str, NULL));
            break;
        case TOKEN_KEYWORD:
            if (strcmp(token->attribute->str, "None") == 0)
            {
                sprintf(new_var, "nil@nil");
            } else
            {
                free(new_var);
                return NULL;
            }
            break;
        case TOKEN_STRING:
            sprintf(new_var, "string@");
            // Copies the string
            while (token->attribute->str[i] != 0)
            {
                c = token->attribute->str[i];
                // If the string is getting too long, reallocates
                if (pos > length - 8)
                {
                    length += 64;
                    new_var = realloc(new_var, length * sizeof(char));
                    if (new_var == NULL)
                    {
                        return NULL;
                    }
                }
                // If one of the characters requires an escape sequence
                if (c <= 32 || c == 35 || c == 92)
                {
                    char tmp[4];
                    sprintf(tmp, "\\%03d", c);
                    new_var[pos] = tmp[0];
                    new_var[pos + 1] = tmp[1];
                    new_var[pos + 2] = tmp[2];
                    new_var[pos + 3] = tmp[3];
                    pos += 4;
                } else
                {
                    new_var[pos] = c;
                    pos++;
                }
                i++;
            }
            new_var[pos] = '\0';
            break;
        default:
            free(new_var);
            return NULL;
    }
    return new_var;
}

