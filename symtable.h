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
 *      File: symtable.h
 */


#ifndef SYMTABLE_H_INCLUDED
#define SYMTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tBSTNode {
	char *key;
	int isVariable;
	void *data;
	struct tBSTNode *LPtr;
	struct tBSTNode *RPtr;
} *tBSTNodePtr;

/**
 * @brief Tree initialization
 * @param RootPtr Pointer to the root
*/
void BST_init(tBSTNodePtr *RootPtr);

/**
 * @brief Searches for the node based on the given key
 * @param RootPtr Pointer to the root
 * @param key Name of the searched node
 * @param foundNode Pointer to the pointer to save the result of the search
 * @return 0 if found, 1 if not found
*/
int BST_search(tBSTNodePtr *RootPtr, char *key, tBSTNodePtr *foundNode);

/**
 * @brief Inserts a new node (or rewrites and old one)
 * @param RootPtr Pointer to the root
 * @param key Name of the inserted node
 * @param isVar 0 if function, 1 if variable
 * @param content Pointer to the inserted structure
 * @return 0 if ok, 1 if error
*/
int BST_insert(tBSTNodePtr *RootPtr, char *key, int isVar, void *content);

/**
 * @brief Deletes the node based on the given key
 * @param RootPtr Pointer to the root
 * @param key Name of the deleted node
*/
void BST_delete (tBSTNodePtr *RootPtr, char *key);

/**
 * @brief Deletes the entire tree, recursive
 * @param RootPtr Pointer to the root
*/
void BST_dispose(tBSTNodePtr *RootPtr);

/**
 * @brief Testing function
 * @param RootPtr Pointer to the root
 * @param indent Indentation when printing (for testing pass 0)
*/
void BST_print(tBSTNodePtr *RootPtr, int indent);


#endif // SYMTABLE_H_INCLUDED
