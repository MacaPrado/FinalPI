#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//ES NECESARIA???
#include <string.h>
#include "bornADT.h"

typedef struct nodeFecha{		//Estructura con año y sexo del nacido
    struct nodeFecha *next;       //ORDENARLO POR FECHAS
    size_t year;
    size_t varon;
    size_t mujer;
}Fecha;


typedef struct nodeProv{        //Nodo de provincia con cantidad de nacidos
    struct nodeProv *next;            //ORDENARLO ALFABETICAMENTE
    char * provincia;
    size_t nacidos;
    size_t cod;
} nodeProv;

//Lista con un puntero hacia el nodo de provincia
//y un puntero hacia un nodo de fechas
struct bornCDT{
    size_t totalNacidos;
    struct nodeProv * first;
    struct nodeProv * current;
    struct nodeFecha * first;
    struct nodeFecha * current;
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

