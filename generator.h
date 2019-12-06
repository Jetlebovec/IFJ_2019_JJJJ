/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Kopáček Jiří    xkopac06
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: generator.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"



//function prototypes

// Generates the head and the built-in functions
void generate_main_body();

// Generates the appropriate built-in function
void add_inputs();
void add_inputf();
void add_inputi();
void add_print();
void add_len();
void add_substr();
void add_ord();
void add_chr();



void gen_defvar(char* var_name, bool in_function);
void gen_move_exp_res (char* dest, bool in_function);
void gen_tf_defvar(int param_id);

int gen_move_arg(int param_id, Token *token, bool local, bool id);
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

int gen_push_operand(Token token, int is_global);
void gen_operation(symbols symbol);

void gen_type_check_arithmetic();
void gen_type_check_arithmetic_plus();
void gen_type_check_relation();
void gen_zero_div_check();
void gen_int_div();
void gen_float_div();


/**
 * @brief Converts token to a string compatible with ifjcode variables, FREE THE CHAR* LATER
 * @param token Token with a value that can be converted
 * @return Pointer to a string if successful, NULL if error or token type is ID or non-value type
 */
char* token_to_ifjcode_val(Token *token);

