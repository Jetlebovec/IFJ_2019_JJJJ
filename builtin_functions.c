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

void generate_main_body()
{
    printf("\n.IFJcode19");
    printf("\nDEFVAR GF@exp_result");
    printf("\nJUMP $$main");
    add_inputs();
    add_inputf();
    add_inputi();
    add_print();
    add_len();
    add_substr();
    add_ord();
    add_chr();
    printf("\nLABEL $$main");
}

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
    printf("\
\n LABEL $print\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n DEFVAR LF@par1type\
\n TYPE LF@par1type LF@%%1\
\n JUMPIFNEQ $print$isnotnone LF@par1type string@nil\
\n MOVE LF@%%1 string@None\
\n LABEL $print$isnotnone\
\n WRITE LF@%%1\
\n POPFRAME\
\n RETURN\
");

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
    printf("\
\n LABEL $substr\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n DEFVAR LF@param1\
\n MOVE LF@param1 LF@%%1\
\n DEFVAR LF@param2\
\n MOVE LF@param2 LF@%%2\
\n DEFVAR LF@param2$type\
\n TYPE LF@param2$type LF@param2\
\n DEFVAR LF@param3\
\n MOVE LF@param3 LF@%%3\
\n DEFVAR LF@param3$type\
\n TYPE LF@param3$type LF@param3\
\n JUMPIFEQ $substr$if$type2int$true LF@param2$type string@int\
\n EXIT int@4\
\n LABEL $substr$if$type2int$true\
\n JUMPIFEQ $substr$if$type3int$true LF@param3$type string@int\
\n EXIT int@4\
\n LABEL $substr$if$type3int$true\
\n DEFVAR LF@length\
\n DEFVAR LF@tmp\
\n CREATEFRAME\
\n DEFVAR TF@%%1\
\n MOVE TF@%%1 LF@%%1\
\n CALL $len\
\n MOVE LF@length TF@%%retval\
\n CLEARS\
\n PUSHS LF@param2\
\n PUSHS int@0\
\n LTS\
\n PUSHS LF@param2\
\n PUSHS LF@length\
\n GTS\
\n PUSHS LF@param3\
\n PUSHS int@0\
\n LTS\
\n ORS\
\n ORS\
\n POPS LF@tmp\
\n CLEARS\
\n JUMPIFEQ $substr$return LF@tmp bool@true\
\n MOVE LF@%%retval string@\
\n DEFVAR LF@maxn\
\n ADD LF@maxn LF@param2 LF@param3\
\n PUSHS LF@maxn\
\n PUSHS LF@length\
\n GTS\
\n POPS LF@tmp\
\n CLEARS\
\n JUMPIFEQ $substr$inrange LF@tmp bool@false\
\n MOVE LF@maxn LF@length\
\n LABEL $substr$inrange\
\n PUSHS LF@param2\
\n PUSHS LF@maxn\
\n LTS\
\n POPS LF@tmp\
\n JUMPIFEQ $substr$return LF@tmp bool@false\
\n GETCHAR LF@tmp LF@param1 LF@param2\
\n CONCAT LF@%%retval LF@%%retval LF@tmp\
\n ADD LF@param2 LF@param2 int@1\
\n JUMP $substr$inrange\
\n LABEL $substr$return\
\n POPFRAME\
\n RETURN\
");
}

void add_ord()
{
    printf("\
\n LABEL $ord\
\n PUSHFRAME\
\n DEFVAR LF@%%retval\
\n MOVE LF@%%retval nil@nil\
\n DEFVAR LF@param1\
\n MOVE LF@param1 LF@%%1\
\n DEFVAR LF@param1$type\
\n TYPE LF@param1$type LF@param1\
\n DEFVAR LF@param2\
\n MOVE LF@param2 LF@%%2\
\n DEFVAR LF@param2$type\
\n TYPE LF@param2$type LF@param2\
\n JUMPIFEQ $ord$if$type1string$true LF@param1$type string@string\
\n EXIT int@4\
\n LABEL $ord$if$type1string$true\
\n JUMPIFEQ $ord$if$type2int$true LF@param2$type string@int\
\n EXIT int@4\
\n LABEL $ord$if$type2int$true\
\n DEFVAR LF@strlen\
\n STRLEN LF@strlen LF@param1\
\n SUB LF@strlen LF@strlen int@1\
\n DEFVAR LF@cmpres1\
\n DEFVAR LF@cmpres2\
\n LT LF@cmpres1 LF@param2 int@0\
\n GT LF@cmpres2 LF@param2 LF@strlen\
\n OR LF@cmpres1 LF@cmpres1 LF@cmpres2\
\n JUMPIFEQ $ord$notininterval LF@cmpres1 bool@true\
\n STRI2INT LF@%%retval LF@param1 LF@param2\
\n LABEL $ord$notininterval\
\n POPFRAME\
\n RETURN\
");
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





