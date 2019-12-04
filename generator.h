/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Sasín Jonáš     xsasin05
 *
 *      File: generator.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"


//function prototypes
void gen_defvar(char* var_name, bool in_function);
void gen_move_exp_res (char* dest, bool in_function);

void gen_move_arg(int param_id, char* attribute, bool local, bool id);
void gen_move_arg_print(int param_id, char* source);
void gen_def_move_param (char* param_name, int param_id);

void gen_function_start(char* fun_name);
void gen_function_end(bool end_of_fun_body, char* fun_name);
void gen_call_fun(char* fun_name);

void gen_if(int cond_id);
void gen_else(int cond_id);
void gen_if_end(int cond_id);

void gen_while(int cycle_id);
void gen_while_end(int cycle_id);

void gen_push_operand(Token token, int is_global);
void gen_operation(symbols symbol);