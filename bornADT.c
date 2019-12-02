#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//ES NECESARIA???
#include <string.h>	
#include "bornADT.h"

typedef struct nodeEstacion{		//ESTO ES PARA TENER UNA IDEA, NO VA, HAY QUE EDITARLO TODO PARA NUESTRO TP
    Testacion estacion; 
    struct nodeEstacion* sig;   
}nodeEstacion;


typedef struct nodeLinea{
    struct nodeLinea * next;
    pEstacion firstEst; 
    char linea;
} nodeLinea;


struct transporteCDT{
    size_t size;
    pLinea first;
    pLinea current;
};								//HASTA ACA HAY QUE EDITAR

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
