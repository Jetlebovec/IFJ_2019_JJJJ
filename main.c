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


 int main (int argc, char* argv[])
 {
    if (argc != 2)
    {
        fprintf(stderr, "Invalid arguments\n");
    }

    printf("Hello World\n");

    return 0;
 }
