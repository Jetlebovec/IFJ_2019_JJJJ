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

//function prototypes
void add_defvar(char* var_name, bool in_function);
void add_move_exp_res (char* dest, bool in_function);

void add_move_arg (int param_id, char* source);
void add_def_move_param (int param_id);

void add_function_start(char* fun_name);
void add_function_end(bool end_of_fun_body, char* fun_name);

void add_if(int cond_id);
void add_else(int cond_id);
void add_if_end(int cond_id);

void add_while(int cycle_id);
void add_while_end(int cycle_id);

