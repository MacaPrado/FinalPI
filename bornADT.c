#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//ES NECESARIA???
#include <string.h>	
#include "bornADT.h"

typedef struct Fecha{		//Estructura con año y sexo del nacido
    size_t year;
    char * sexo;
    size_t code;
}Fecha;


typedef struct nodeProv{        //Nodo de provincia con cantidad de nacidos
    struct nodeProv *next;
    char * provincia;
    size_t nacidos;
    size_t cod;
} nodeProv;

//Lista con un puntero hacia el nodo de privincia
//y un puntero hacia una estructura con los datos del sexo y año, no se si realizar otro nodo para esto
//esta parte me recuerda al ejerccio de calendario y quiza por eso lo estoy tomando asi, si vemos una mejor forma lo podemos cambiar, 
//la forma de comparar quiza sea distinto, no recuerdo bien
struct nacidosCDT{              
    size_t Total;
    struct nodeProv * first;
    struct nodeProv * current;
    Fecha * nacimiento;
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
