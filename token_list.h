#include<stdio.h>
#include<stdlib.h>
#include "scanner.h"
 
typedef struct tDLElem {                 /* prvek lss */
        Token token;                                         /* data */
        struct tDLElem *rptr;        /* ukazatel na následující prvek seznamu */
} *tDLElemPtr;

typedef struct {                                  /* dvousměrně vázaný seznam */
    tDLElemPtr First;                      /* ukazatel na první prvek seznamu */
    tDLElemPtr Act;                     /* ukazatel na aktuální prvek seznamu */
    tDLElemPtr Last;
} tDLList;

/* prototypy jednotlivých funkcí */
void DLInitList (tDLList *);
void DLDisposeList (tDLList *);
void DLInsertLast(tDLList *, Token *token);
void DLFirst (tDLList *);
void DLLast (tDLList *);
void DLCopy (tDLList *, Token *token);
int DLActive (tDLList *);
