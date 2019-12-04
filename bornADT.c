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
static provNode addProvince(provNode b, char Province[MAX_LENGTH], int code);
static nodeDate addYear(int sex, int currentYear);


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
    return b->AllBorns == 0;
}

void toBegin(bornADT b){
    b->current = b->first;
}

int hasNext(bornADT b){
    return b->current != NULL;
}

void addProvinces(bornADT born, provNode Province){
    born->firstProvince= addProvince(born->firstProvince, Province); //ERROR: ADDPROVINCE RECIBE 3 PARAMETROS
    born->AllBorns++;
}

static provNode addProvince(provNode b, char Province[MAX_LENGTH], int code){
    int c;

    if(b == NULL || b->code < code){    //ERROR: QUEREMOS ORDENAR ALFABETICAMENTE, NO POR CODIGO
        provNode new= malloc(sizeof(struct nodeProv));
        new->code = code;
        new->name = malloc(sizeof(char)); //SIZE OF CHAR LE DARIA UN SOLO BYTE, NECESITAMOS QUE SEA DEL TAMANO DE NAME (EJ: CHAR * MAX_LENGHT O ALGO ASI Y DESPUES UN REALLOC)
        strcpy(new->name, province); //ACA NO IRIA PROVINCE CON P MAYUSCULA?
        new->next= //FALTA ESTO
    }
}

void addYears(bornADT born, int year, int sex){     //NUNCA LE SUMAMOS UNO A BORNS EN PROVINCE
  dateNode aux = born->firstDate, previous = NULL;
  int c;
  if(aux == NULL){
    nodeDate new = addYear(year, sex);
    born->firstDate = new;
    (born->size)++;   //BORN NO TIENE SIZE, SERIA ALLBORNS?
  }
  else{
    while(aux != NULL){
            if((c = compareInt(aux->year, year)) == 0){   //NO EXISTE COMPARE INT
              if(sex == 1)
                aux->men+=1;

              if(sex == 2)
                aux->women+=1;

            }
            else if(c > 0){ //los ordeno por año: si viene aca es pq c>0    ESTO NO ENTENDI
              dateNode new = addYear(sex, year);
              previous->next = new;
              new->next = aux;
            }
            else{
              dateNode new = addYear(sex, year);
              new->next = aux->next;
              aux->next = new->next;
            }
            previous = aux;
            aux= aux->next;
    }

  }
}

static nodeDate addYear(int sex, int currentYear) {
  dateNode new = malloc(sizeof(nodeDate));
  new->year = currentYear;

  if(sex == 1)
    new->men=1;

  if(sex == 2)
    new -> women = 1;

  return new;
}
