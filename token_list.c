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
 *      File: token_list.c
 */

#include "token_list.h"

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
**/

//list je prazny tudiz vsechny ukazatele jsou nastaveny na NULL
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci.
**/

    //pomocny ukazatel
    tDLElemPtr pom = L->First;

    //mazani prvniho prvku dokud neni seznam prazdny
    while (L->First != NULL) {
        //posunuti na dalsi prvek
        L->First = L->First->rptr;
        //uvolneni prvniho prvku
        string_free(pom->token.attribute);
        free(pom->token.attribute);
        free(pom);
        //ulozeni prvniho prvku
        pom = L->First;
    }

    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void DLInsertLast(tDLList *L, Token *token_in, int *err_code) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
**/

    tDLElemPtr vkladany;
    if ((vkladany = (tDLElemPtr) malloc(sizeof(struct tDLElem))) == NULL)
        *err_code = 99;

    //inicializujeme token
    init_token(&vkladany->token, err_code);
    //zkopirujeme tokenu typ a atribut
    vkladany->token.type = token_in->type;
    if(string_copy(vkladany->token.attribute, token_in->attribute) != 0) {
        *err_code = 99;
    }

//pokud je seznam prazndy, vlozi se novy prvek na 1. misto a je zároveň i poslední
    if (L->First == NULL) {
        L->First = vkladany;
        L->Last = vkladany;
        vkladany->rptr = NULL;
    }
    else {
        L->Last->rptr = vkladany;
        L->Last = vkladany;
        vkladany->rptr = NULL;
    }
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

//ulozeni ukazatele na druhy prvek
    tDLElemPtr druhy = L->First->rptr;
//overeni prazdnosti seznamu
    if (L->First == NULL)
        return;
//zruseni pripadne aktivity prvku
    if (L->First == L->Act)
        L->Act = NULL;
//uvolneni prvniho prvku z pameti
    string_free(L->First->token.attribute);
    free(L->First->token.attribute);
    free(L->First);
//druhy prvek se stava prvnim
    L->First = druhy;
}

//function to initialize new token
void init_token(Token *token, int *error_code){

        token->type = TOKEN_UNDEFINED;
        token->attribute = (tString*) malloc(sizeof(tString));
        if (token->attribute == NULL)
        {
            *error_code = 99;
        }
        if (string_init(token->attribute) != 0) {
            *error_code = 99;
        }
}
