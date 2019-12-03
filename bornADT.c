#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//ES NECESARIA???
#include <string.h>
#include "bornADT.h"

typedef struct nodeDate{		//Estructura con año y sexo del nacido
    struct dateNode next;       //ORDENARLO POR FECHAS
    size_t year;
    size_t men;
    size_t women;
}Fecha;


typedef struct nodeProv{        //Nodo de provincia con cantidad de nacidos
    provNode next;            //ORDENARLO ALFABETICAMENTE
    char * province;
    size_t borns;
    size_t code;
} nodeProv;

//Lista con un puntero hacia el nodo de provincia
//y un puntero hacia un nodo de fechas
struct bornCDT{
    size_t totalBorns;
    provNode firstProvince;
    provNode currentProvince;
    dateNode firstDate;
    dateNode currentDate;
};

static int compare(char c1, char c2){
    return c1-c2;
}

bornADT new(void){
    return calloc(1, sizeof(struct bornCDT));
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

void add(, ){


}

