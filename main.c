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


/*  TREE TEST
    tBSTNodePtr maintree;
    BST_init(&maintree);

    BST_insert(&maintree, "sdfsdf", 1, NULL);
    BST_print(&maintree, 0);
    printf("\n");

    BST_insert(&maintree, "dsfsdf", 1, NULL);
    BST_print(&maintree, 0);
    printf("\n");

    BST_insert(&maintree, "zet", 1, NULL);
    BST_print(&maintree, 0);
    printf("\n");

    BST_insert(&maintree, "khf", 1, NULL);
    BST_print(&maintree, 0);
    printf("\n");

    BST_insert(&maintree, "zet", 0, NULL);
    BST_print(&maintree, 0);
    printf("\n");

    tBSTNodePtr foundtest;
    printf("%d\n\n", BST_search(&maintree, "dsfsdf", &foundtest));

    BST_delete(&maintree, "dsfsdf");
    BST_print(&maintree, 0);
    printf("\n");

    printf("%d\n\n", BST_search(&maintree, "dsfsdf", &foundtest));

    BST_dispose(&maintree);
    BST_print(&maintree, 0);
    printf("\n");

    printf("Hello World\n");
    return 0;
*/
//  SYMTABLE TEST
/*
    tBSTNodePtr symtable;
    tSymdata *data;
    symtable_init(&symtable);
    symtable_create_function(&symtable, "555");
    symtable_create_function(&symtable, "222");
    BST_print(&symtable, 0);

    symtable_create_variable(&symtable, "777");
    BST_print(&symtable, 0);

    if (symtable_search_function(&symtable, "222", &data) == 0)
    {
        printf("Function 222 found\n");
    } else
    {
        printf("Function 222 not found\n");
    }
    if (data != NULL)
    {
        printf("NOT NULL OK\n");
    }

    if (symtable_search_variable(&symtable, "777", &data) == 0)
    {
        printf("Variable 777 found\n");
    } else
    {
        printf("Variable 777 not found\n");
    }
    if (data != NULL)
    {
        printf("NOT NULL OK\n");
    }

    symtable_create_variable(&symtable, "999");
    BST_print(&symtable, 0);

    symtable_delete_symbol(&symtable, "777");
    BST_print(&symtable, 0);

    symtable_delete_symbol(&symtable, "777");
    BST_print(&symtable, 0);

    if (symtable_search_variable(&symtable, "777", &data) == 0)
    {
        printf("Variable 777 found\n");
    } else
    {
        printf("Variable 777 not found\n");
    }
    if (data == NULL)
    {
        printf("NULL OK\n");
    }

    symtable_delete_symbol(&symtable, "555");
    BST_print(&symtable, 0);

    symtable_dispose(&symtable);
    BST_print(&symtable, 0);
    printf("Hello World\n");
    return 0;
*/
/* Symtable undefined test
    tBSTNodePtr symtable;
    tSymdata *data;
    symtable_init(&symtable);
    symtable_create_variable(&symtable, "555");
    symtable_create_function(&symtable, "222");
    BST_print(&symtable, 0);

    symtable_create_variable(&symtable, "777");
    BST_print(&symtable, 0);
    printf("Contains undefined: %d \n", symtable_contains_undefined(&symtable));

    tSymdata *symd = NULL;
    if (symtable_search_function(&symtable, "222", &symd) == 0)
    {
        printf("Function 222 found\n");
    }
    symd->defined = true;
    printf("Contains undefined: %d \n", symtable_contains_undefined(&symtable));

    symtable_create_function(&symtable, "111");
    BST_print(&symtable, 0);
    printf("Contains undefined: %d \n", symtable_contains_undefined(&symtable));

    if (symtable_search_function(&symtable, "111", &symd) == 0)
    {
        printf("Function 111 found\n");
    }
    symd->defined = true;
    printf("Contains undefined: %d \n", symtable_contains_undefined(&symtable));


    symtable_dispose(&symtable);
    BST_print(&symtable, 0);
    printf("Hello World\n");
    return 0;
*/
 }
