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

void readData(FILE * f, bornADT b){
  char buf[BLOQUE2]; //defino un vector de chars para poder usar en fgets
    int cont=0;
    int numCampo;
    int year, sex;
    long int persons;

    while(fgets(buf, BLOQUE2, f)){
        numCampo=0;
        cont++;

        if(cont==1)
            continue; //me salteo el header
        char * campo = strtok(buf, ","); //empiezo a recorrer la linea del CSV
        while(campo){

            if(numCampo == 0){
                sscanf(campo, "%d", &year); 
            }

            if(numCampo == 3){ //uso el campo de "hasta" para corroborar si el pasajero es diurno o nocturno
                sscanf(campo, "%d", &sex); //guardo la hora, descarto los minutos
            }

            campo = strtok(NULL, ","); //avanzo de campo
            numCampo++;
        }
      
        //addYears(b, year, sex, persons);
    }
}

