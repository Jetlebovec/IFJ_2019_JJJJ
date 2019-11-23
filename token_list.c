
/* 
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**/

#include "token_list.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

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
tDLElemPtr akt = L->First;
tDLElemPtr next = L->First->rptr;

while (next != NULL)
{
	free(akt);
	akt = next;
	next = next->rptr;
}
free(akt);
L->Act = NULL;
L->First = NULL;
L->Last = NULL;
}

void DLInsertFirst (tDLList *L, Token token) {
/*
** Vloží nový prvek na začátek seznamu L.
**/
tDLElemPtr vkladany;
if ((vkladany = (tDLElemPtr) malloc(sizeof(struct tDLElem))) == NULL)
    DLError();

//pokud je seznam prazndy, vlozi se novy prvek na 1. misto a je zároveň i poslední
if (L->First == NULL)
{
    L->First = vkladany;
    L->Last = vkladany;
    vkladany->lptr=NULL;
    vkladany->rptr=NULL;
    vkladany->token = token;
}
else
{
//1. prvek se stava 2., ukazuje na nove vlozeny, nove vlozeny ukazuje na druhy
    L->First->lptr = vkladany;
    vkladany->rptr = L->First;
    L->First = vkladany;
    vkladany->lptr = NULL;
    vkladany->token = token;
}

    

}

void DLInsertLast(tDLList *L, Token token) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
**/ 	
tDLElemPtr vkladany;
if ((vkladany = (tDLElemPtr) malloc(sizeof(struct tDLElem))) == NULL)
    DLError();

//pokud je seznam prazndy, vlozi se novy prvek na 1. misto a je zároveň i poslední
if (L->First == NULL)
{
    L->First = vkladany;
    L->Last = vkladany;
    vkladany->lptr=NULL;
    vkladany->rptr=NULL;
    vkladany->token=token;
}
else
{
//posledni prvek se stava predposlednim, ukazuje na nove vlozeny, nove vlozeny ukazuje na predposledni
    L->Last->rptr = vkladany;
    vkladany->lptr = L->Last;
    L->Last = vkladany;
    vkladany->rptr = NULL;
    vkladany->token = token;
}






}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
**/

L->Act = L->First;
	
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
**/
	
	L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, Token *token) {
/*
** Prostřednictvím parametru token vrátí hodnotu prvního prvku seznamu L.
**/

	
	if(L->First != NULL)
    {
        *token = L->First->token;
    }
    else
    {
        DLError();
    }
    
}

void DLCopyLast (tDLList *L, Token *token) {
/*
** Prostřednictvím parametru token vrátí hodnotu posledního prvku seznamu L.
**/
if(L->First != NULL)
    {
        *token = L->Last->token;
    }
    else
    {
        DLError();
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
if(L->First == NULL)
    return;
//zruseni pripadne aktivity prvku
if(L->First == L->Act)
    L->Act = NULL;
//uvolneni prvniho prvku z pameti
free(L->First);
//druhy prvek se stava prvnim
druhy->lptr = NULL;
L->First = druhy;

}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
//ulozeni ukazatele na predposledni prvek
tDLElemPtr predposledni = L->Last->lptr;	
//overeni prazdnosti seznamu
if(L->First == NULL)
    return;
//zruseni pripadne aktivity prvku
if(L->Last == L->Act)
    L->Act = NULL;
//uvolneni posledniho prvku z pameti
free(L->Last);
//predposledni prvek se stava poslednim
predposledni->rptr = NULL;
L->Last = predposledni;
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
//prirazeni aktualniho prvku do promenne
tDLElemPtr aktualni = L->Act;
//overeni aktivity a pozice prvku
if(L->Act==NULL || L->Act == L->Last)
    return;

tDLElemPtr odstranovany = aktualni->rptr;
//aktualni prvek ukazuje na prvek za odstranovanym 
//a prvek za odstranovanym ukazuje na aktualni pokud neni posledni 
if(odstranovany->rptr!=NULL)
{
    aktualni->rptr = odstranovany->rptr;
    odstranovany->rptr->lptr = aktualni;
}
else
{
    aktualni->rptr = NULL;
    L->Last = aktualni;
}
//uvolneni pameti odstranovaneho prvku
free(odstranovany);
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	
//prirazeni aktualniho prvku do promenne
tDLElemPtr aktualni = L->Act;
//overeni aktivity a pozice prvku
if(L->Act==NULL || L->Act == L->First)
    return;

tDLElemPtr odstranovany = aktualni->lptr;
//aktualni prvek ukazuje na prvek pred odstranovanym 
//a prvek pred odstranovanym ukazuje na aktualni pokud neni prvni 
if(odstranovany->lptr!=NULL)
{
    aktualni->lptr = odstranovany->lptr;
    odstranovany->lptr->rptr = aktualni;
}
else
{
    aktualni->lptr = NULL;
    L->First = aktualni;
}
//uvolneni pameti odstranovaneho prvku
free(odstranovany);
}

void DLPostInsert (tDLList *L, Token token) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
**/
tDLElemPtr vkladany;
tDLElemPtr aktualni = L->Act;
//alokace pamtei pro novy prvek
if ((vkladany = malloc(sizeof(struct tDLElem))) == NULL)
    DLError();
vkladany->token = token;

if (aktualni == NULL)
    return;
//pokud aktualni neni posledni, aktualni ukazuje na nove vlozeny stejne jako prvek za nove vlozenym
if(aktualni->rptr != NULL)
{
    aktualni->rptr->lptr = vkladany;
    vkladany->rptr = aktualni->rptr;
    aktualni->rptr = vkladany;
    vkladany->lptr = aktualni;
}
else
{
    aktualni->rptr = vkladany;
    vkladany->lptr = aktualni;
    vkladany->rptr = NULL;
    L->Last = vkladany;
}
}

void DLPreInsert (tDLList *L, Token token) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
**/
tDLElemPtr vkladany;
tDLElemPtr aktualni = L->Act;
//alokace pamtei pro novy prvek
if ((vkladany = malloc(sizeof(struct tDLElem))) == NULL)
    DLError();
vkladany->token = token;

if (aktualni == NULL)
    return;
//pokud aktualni neni prvni, aktualni ukazuje na nove vlozeny stejne jako prvek za nove vlozenym
if(aktualni->lptr != NULL)
{
    aktualni->lptr->rptr = vkladany;
    vkladany->lptr = aktualni->lptr;
    aktualni->lptr = vkladany;
    vkladany->rptr = aktualni;
}
else
{
    aktualni->lptr = vkladany;
    vkladany->rptr = aktualni;
    vkladany->lptr = NULL;
    L->First = vkladany;
}
}

void DLCopy (tDLList *L, Token *token) {
/*
** Prostřednictvím parametru token vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
if(L->Act == NULL)
    DLError();
else
*token = L->Act->token;

}

void DLActualize (tDLList *L, Token token) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
if(L->Act == NULL)
    return;
L->Act->token = token;
	
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
**/
if(L->Act == NULL)
    return;
L->Act = L->Act->rptr;
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
**/
if(L->Act == NULL)
    return;
L->Act = L->Act->lptr;
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
**/
return (L->Act != NULL);
}
