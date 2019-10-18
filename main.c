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
 *      File: main.c
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "parser.h"

 #include "custom_string.h"

 int main (int argc, char* argv[])
 {
    if (argc > 1)
    {
        fprintf(stderr, "Invalid arguments\n");
        return 99;
    }

    //TODO Initialize stuff we dont have yet

    // Complete analysis
    int errorCode = analyse();

    if (errorCode == 0)
    {
        //TODO Stuff that happens when no error occured

    }

    //TODO Clean all the stuff we dont have yet

    printf("Hello World\n");

    return errorCode;
 }
