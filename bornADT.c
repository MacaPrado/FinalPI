#include <stdio.h>
#include <stdlib.h>
#include <math.h>	
#include <string.h>
#include "bornADT.h"

typedef struct nodeDate{        //Estructura con año y sexo del nacido
    dateNode next;       //ORDENARLO POR FECHAS
    size_t year;
    size_t men;
    size_t women;
} nodeDate;


typedef struct nodeProv{        //Nodo de provincia con cantidad de nacidos
    provNode next;            //ORDENARLO ALFABETICAMENTE
    char * name;
    size_t borns;
    size_t code;
} nodeProv;

//Lista con un puntero hacia el nodo de provincia
//y un puntero hacia un nodo de fechas
struct bornCDT{
    size_t AllBorns;
    provNode firstProvince;
    provNode currentProvince;
    dateNode firstDate;
    dateNode currentDate;
};
static int compare(char c1, char c2){
    return c1-c2;

static void freeProvince(provNode b);
static void freeDate(dateNode b);


bornADT new(void){
    bornADT new= calloc(1, sizeof(struct bornCDT));
    return new;
}

void 
freeBorn(bornADT b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->firstProvince);
    freeDate(b->firstDate);
    free(b);
}

static void
freeProvince(provNode b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->next);
    free(b->name);
    free(b);
}

static void
freeDate(dateNode b){
    if (b==NULL) {
        return;
    }
    freeDate(b->next);
    free(b);
}

int isEmpty(const bornADT b){
    return b->size == 0;
}

void toBegin(bornADT b){
    b->current = b->first;
}

int hasNext(bornADT b){
    return b->current != NULL;
}

void add(bornADT born, provNode Province){
    born->firstProvince= addProvince(born->firstProvince, Province);
    born->AllBorns++;
}

provNode addProvince(provNode b, char Province[MAX_LENGTH], int code){
    int c;

    if(b == NULL || b->code < code){
        provNode new= malloc(sizeof(struct nodeProv));
        new->code = code;
        new->name = malloc(sizeof(char));
        strcpy(new->name, province);
        new->next=
    }
}
 

