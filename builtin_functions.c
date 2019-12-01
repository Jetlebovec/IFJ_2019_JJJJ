/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Kopáček Jiří    xkopac06
 *
 *      File: builtin_functions.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "builtin_functions.h"

void add_inputs()
{
    printf("\
\n LABEL $inputs\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n READ LF@%%retval string\
\n POPFRAME\
\n RETURN\
");

}

void add_inputf()
{
    printf("\
\n LABEL $inputf\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n READ LF@%%retval float\
\n POPFRAME\
\n RETURN\
");

}

void add_inputi()
{
    printf("\
\n LABEL $inputi\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n READ LF@%%retval int\
\n POPFRAME\
\n RETURN\
");

}

void add_print()
{

}

void add_len()
{
    printf("\
\n LABEL $len\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n DEFVAR LF@param1\
\n MOVE LF@param1 LF@%%1\
\n DEFVAR LF@param1$type\
\n TYPE LF@param1$type LF@param1\
\n JUMPIFEQ $len$if$typestring$true LF@param1$type string@string\
\n EXIT int@4\
\n LABEL $len$if$typestring$true\
\n STRLEN LF@%%retval LF@param1\
\n POPFRAME\
\n RETURN\
");

}

void add_substr()
{

}

void add_ord()
{

}

void add_chr()
{
        printf("\
\n LABEL $chr\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n DEFVAR LF@param1\
\n MOVE LF@param1 LF@%%1\
\n DEFVAR LF@param1$type\
\n TYPE LF@param1$type LF@param1\
\n JUMPIFEQ $chr$if$typeint$true LF@param1$type string@int\
\n EXIT int@4\
\n LABEL $chr$if$typeint$true\
\n DEFVAR LF@cmpres1\
\n DEFVAR LF@cmpres2\
\n LT LF@cmpres1 LF@param1 int@0\
\n GT LF@cmpres2 LF@param1 int@255\
\n OR LF@cmpres1 LF@cmpres1 LF@cmpres2\
\n JUMPIFEQ $chr$ininterval LF@cmpres1 bool@false\
\n EXIT int@4\
\n LABEL $chr$ininterval\
\n INT2CHAR LF@%%retval LF@param1\
\n POPFRAME\
\n RETURN\
");

}





