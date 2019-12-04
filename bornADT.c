#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bornADT.h"
#define MAX_LENGTH 4000

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
    size_t allBorns;
    provNode firstProvince;
    provNode currentProvince;
    dateNode firstDate;
    dateNode currentDate;
};
static int compareChar(char c1, char c2){
    return c1-c2;
}
static int compareInt(int c1, int c2){
    return c1-c2;
}

static void freeProvince(provNode b);
static void freeDate(dateNode b);
static nodeProv addProvince(char *province, int code, int dimProvince);



bornADT new(void){
    bornADT new= calloc(1, sizeof(struct bornCDT));
    return new;
}

void freeBorn(bornADT b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->firstProvince);
    freeDate(b->firstDate);
    free(b);
}

static void freeProvince(provNode b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->next);
    free(b->name);
    free(b);
}

static void freeDate(dateNode b){
    if (b==NULL) {
        return;
    }
    freeDate(b->next);
    free(b);
}

int isEmpty(const bornADT b){
    return b->allBorns == 0;
}

void toBeginDate(bornADT b){
    b->currentDate = b->firstDate;
}

void toBeginProvince(bornADT b){
    b->currentProvince = b->firstProvince;
}

int hasNextDate(bornADT b){
    return b->currentDate != NULL;
}

int hasNextProvince(bornADT b){
    return b->currentProvince != NULL;
}

void addProvinces(provNode born, char *province, int code, int dimProvince){
    provNode actual = born->firstProvince, previous = NULL;
    if(actual == NULL){
      nodeProv new = addProvince(province, code, dimProvince, actual);
      born->firstProvince = new;
      toBeginProvince(born);
    }
    else{
      while(actual != NULL && ((strcmp (actual->name, province)) < 0)){
        previous = actual;
        provNode aux = actual->next;
        actual = aux;
        born->currentProvince = actual;
      }
      if(actual == NULL){
        nodeProv new = addProvince(province, code, dimProvince, aux);
      }
      else{

      }
    }
}

static nodeProv addProvince(char *province, int code, int dimProvince, provNode nextNode){
  provNode new = malloc(sizeof(nodeProv));
  new->name = province;   //ACA TENDRIA QUE HACER UN STRCPY???? NECESITO DIMPROVINCE???
  new->code = code;
  new->next = nextNode;

  return new;
}

void addYears(bornADT born, int year, int gender, int provinceCode){
  dateNode aux = born->firstDate, previous = NULL;
  int c;
  if(aux == NULL){
    nodeDate new = addYear(year, gender);
    born->firstDate = new;
    toBeginDate(born);
    (born->allBorns)++;
  }
  else{
    while(aux != NULL){
            if((c = compareInt(aux->year, year)) == 0){
              if(gender == 1)
                aux->men+=1;

              if(gender == 2)
                aux->women+=1;

            }
            else if(c > 0){ //los ordeno por año: si viene aca es pq c>0    ESTO NO ENTENDI
              dateNode new = addYear(gender, year);
              previous->next = new;
              new->next = aux;
            }
            else{
              dateNode new = addYear(gender, year);
              new->next = aux->next;
              aux->next = new->next;
            }
            previous = aux;
            aux= aux->next;
    }

  }
}

static nodeDate addYear(int gender, int currentYear) { //FALTA QUE NEXT APUNTE AL SIGUIENTE
  dateNode new = malloc(sizeof(nodeDate));
  new->year = currentYear;

  if(gender == 1)
    new->men=1;

  if(gender == 2)
    new -> women = 1;

  return new;
}
