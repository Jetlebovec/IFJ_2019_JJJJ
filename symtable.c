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
 *      File: symtable.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"

void BST_init(tBSTNodePtr *RootPtr)
{
    if (RootPtr != NULL)
    {
        *RootPtr = NULL;
    }
}

int BST_search(tBSTNodePtr *RootPtr, char *key, tBSTNodePtr *foundNode)
{
    // Checks if the struct exists
    if (RootPtr == NULL)
    {
        *foundNode = NULL;
        return 1;
    } else
    {
        tBSTNodePtr currentNode = *RootPtr;
        while (currentNode != NULL)
        {
            if (strcmp(currentNode->key, key) == 0)
            {
                *foundNode = currentNode;
                return 0;
            } else
            {
                // If the node key is greater than the searched key, search the left sub-tree
                if (strcmp(currentNode->key, key) > 0)
                {
                    currentNode = currentNode->LPtr;
                } else
                {
                    // Otherwise search the right sub-tree
                    currentNode = currentNode->RPtr;
                }
            }
        }
        // Not found
        *foundNode = NULL;
        return 1;
    }
}

int BST_insert(tBSTNodePtr *RootPtr, char *key, int isVar, void *content)
{
    // The new node is the first one
    if (RootPtr == NULL)
    {
        return 0;
    }
    if (*RootPtr == NULL)
    {
        *RootPtr = (tBSTNodePtr) malloc(sizeof(struct tBSTNode));
        if (*RootPtr == NULL)
        {
            return 1;
        }
        (*RootPtr)->key = key;
        (*RootPtr)->isVariable = isVar;
        (*RootPtr)->data = content;
        (*RootPtr)->LPtr = NULL;
        (*RootPtr)->RPtr = NULL;
        return 0;
    }

    tBSTNodePtr current = *RootPtr;
    tBSTNodePtr previous = NULL;
    // Searches the tree for the correct placement of the new node
    while (current != NULL)
    {
        // If the node already exists, rewrites it
        if (strcmp(current->key, key) == 0)
        {
            free(current->data);
            free(current->key);
            current->data = content;
            current->key = key;
            current->isVariable = isVar;
            return 0;
        }
        previous = current;
        if (strcmp(current->key, key) > 0)
        {
            // If the key is lesser than the current node, continues to the left sub-tree
            current = current->LPtr;
        } else
        {
            // If the key is greater than the current node, continues to the right sub-tree
            current = current->RPtr;
        }
    }
    // Creates a new node and connects it to the previous one
    current = (tBSTNodePtr) malloc(sizeof(struct tBSTNode));
    if (current == NULL)
    {
        return 1;
    }
    current->key = key;
    current->isVariable = isVar;
    current->data = content;
    current->LPtr = NULL;
    current->RPtr = NULL;
    if (strcmp(key, previous->key) < 0)
    {
        // If the previous key is greater than the new one, the new node becomes the left child
        previous->LPtr = current;
    } else
    {
        // Otherwise becomes the right child
        previous->RPtr = current;
    }
    return 0;
}

// Replaces toBeReplaced with it's rightmost node and deletes the rightmost node
// Could be shorter but this way it's way more readable
void replace_by_rightmost(tBSTNodePtr toBeReplaced)
{
    tBSTNodePtr current = toBeReplaced->LPtr;
    // If the first node in the left subtree is the rightmost one, replaces the original node
    if (current->RPtr == NULL)
    {
        free(toBeReplaced->data);
        free(toBeReplaced->key);
        toBeReplaced->isVariable = current->isVariable;
        toBeReplaced->data = current->data;
        toBeReplaced->key = current->key;
        toBeReplaced->LPtr = current->LPtr;
        free(current);
    } else
    {
        tBSTNodePtr previous = current;
        // Repeats until current is the rightmost node
        while (current->RPtr != NULL)
        {
            previous = current;
            current = current->RPtr;
        }
        // Replaces the original node
        free(toBeReplaced->data);
        free(toBeReplaced->key);
        toBeReplaced->isVariable = current->isVariable;
        toBeReplaced->data = current->data;
        toBeReplaced->key = current->key;
        // Corrects the pointer of the second rightmost node
        previous->RPtr = current->LPtr;
        free(current);
    }
}

void BST_delete (tBSTNodePtr *RootPtr, char *key)
{
    if (RootPtr != NULL && *RootPtr != NULL)
    {
        tBSTNodePtr current = *RootPtr;
        tBSTNodePtr previous = NULL;
        int isLeftChild = 0;
        // Searches the tree for the deleted node
        while (current != NULL)
        {
            // If the node is found, deletes it
            if (strcmp(current->key, key) == 0)
            {
                if (current->LPtr == NULL && current->RPtr == NULL)
                {
                    // Leaf node
                    // Sets the correct pointer in the previous node
                    if (isLeftChild == 1)
                    {
                        previous->LPtr = NULL;
                    } else
                    {
                        previous->RPtr = NULL;
                    }
                    free(current->key);
                    free(current->data);
                    free(current);
                } else if (current->LPtr != NULL && current->RPtr == NULL)
                {
                    // Has only a left child
                    // Sets the correct pointer in the previous node
                    if (isLeftChild == 1)
                    {
                        previous->LPtr = current->LPtr;
                    } else
                    {
                        previous->RPtr = current->LPtr;
                    }
                    free(current->key);
                    free(current->data);
                    free(current);
                } else if (current->LPtr == NULL && current->RPtr != NULL)
                {
                    // Has only a right child
                    // Sets the correct pointer in the previous node
                    if (isLeftChild == 1)
                    {
                        previous->LPtr = current->RPtr;
                    } else
                    {
                        previous->RPtr = current->RPtr;
                    }
                    free(current->key);
                    free(current->data);
                    free(current);
                } else
                {
                    // Has both child nodes
                    replace_by_rightmost(current);
                }
                return;
            } // If found, deleting node
            // If not found, continues down the tree
            previous = current;
            if (strcmp(current->key, key) > 0)
            {
                // If the key is lesser than the current node, continues to the left sub-tree
                current = current->LPtr;
                isLeftChild = 1;
            } else
            {
                // If the key is greater than the current node, continues to the right sub-tree
                current = current->RPtr;
                isLeftChild = 0;
            }
        } // While not NULL
        // Not found, returns
    } // If null
    return;
}

void BST_dispose(tBSTNodePtr *RootPtr)
{
    if ((*RootPtr) != NULL)
    {
        // Recursively dispose of both sub-trees
        BST_dispose(&((*RootPtr)->LPtr));
        BST_dispose(&((*RootPtr)->RPtr));
        free((*RootPtr)->key);
        free((*RootPtr)->data);
        free((*RootPtr));
        *RootPtr = NULL;
    }
}

void BST_print(tBSTNodePtr *RootPtr, int indent)
{
    if ((*RootPtr) != NULL)
    {
        for (int i = 0; i < indent; i++)
        {
            printf("--");
        }
        printf("%d:%s\n", (*RootPtr)->isVariable, (*RootPtr)->key);
        BST_print(&((*RootPtr)->LPtr), indent + 1);
        BST_print(&((*RootPtr)->RPtr), indent + 1);
    }
}

