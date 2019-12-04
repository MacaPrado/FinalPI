#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bornADT.h"

#define MAX_LENGHT  200

typedef struct nodeDate{
    pDate next;
    int year;
    int male;
    int female;

} nodeDate;


typedef struct nodeProv{
    pProv next;
    char * province;
    int borns;
    int code;
} nodeProv;

struct bornCDT{
    int allBorns;
    pProv firstProvince;
    pProv currentProvince;
    pDate firstDate;
    pDate currentDate;
};

static int compareInt(int c1, int c2){
    return c1-c2;
}

static void freeProvince(pProv b);
static void freeDate(pDate  b);
static pProv addProvince(char *province, int code);
static  pDate  addYear(int gender, int currentYear);


bornADT new(void){
    bornADT new= calloc(1, sizeof(struct bornCDT));
    return new;
}

int isEmpty(const bornADT b){
    return b->allBorns == 0;
}

void freeBorn(bornADT b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->firstProvince);
    freeDate(b->firstDate);
    free(b);
}
static void freeProvince(pProv b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->next);
    free(b->province);
    free(b);
}
static void freeDate (pDate  b){
    if (b==NULL) {
        return;
    }
    freeDate(b->next);
    free(b);
}



void toBeginDate(bornADT b){
    b->currentDate = b->firstDate;
}
int hasNextDate(bornADT b){
    return b->currentDate != NULL;
}

void toBeginProvince(bornADT b){
    b->currentProvince = b->firstProvince;
}
int hasNextProvince(bornADT b){
    return b->currentProvince != NULL;
}


void addProvinces(bornADT born, char *province, int code){
    pProv aux = born->firstProvince, previous = NULL;

    while(aux != NULL){

        if((strcmp (aux->province, province)) > 0){

          pProv new = addProvince(province, code);
          previous->next = new;
          new->next = aux;
          return ;
        }
        previous = aux;
        aux = aux->next;
    }

    if(aux == NULL){
      pProv new = addProvince(province, code);
      printf("Entre al if\n");
        if(previous == NULL)
          born->firstProvince = new;

        else{
          previous->next = new;
        }
        new->next = NULL;
    }
    return ;
}

static pProv addProvince(char *province, int code){
  pProv new = malloc(sizeof(nodeProv));
  strcpy(new->province, province);
  new->code = code;

  return new;
}


void addYears(bornADT born, int year, int gender, int provinceCode){        //FALTA SUMARLE UNO A LAS PROVINCIAS
  pDate aux = born->firstDate, previous = NULL;
  int c;
  while(aux!= NULL){
            if((c = compareInt(year, aux->year)) == 0){
              if(gender == 1)
                aux->male+=1;

              if(gender == 2)
                aux->female+=1;

              born->allBorns+=1;
              return ;
            }
            else if(c < 0){ //los ordeno por año: si viene aca es pq c>0
              pDate new = addYear(gender, year);
              if(previous == NULL){
                born->firstDate = new;
              }
              else
                previous->next = new;
              new->next = aux;
              born->allBorns+=1;
              return ;
            }
            previous = aux;
            aux= aux->next;
  }

  if(aux == NULL){
    pDate new = addYear(gender, year);
    if(previous == NULL){
      born->firstDate = new;
    }
    else{
      previous->next = new;
    }
    born->allBorns+=1;
    new->next = NULL;
  }
  return ;
}

static pDate addYear(int gender, int currentYear) {
  pDate new = malloc(sizeof(nodeDate));
  new->year = currentYear;
  if(gender == 1){
    new->male=1;
    new->female=0;
  }

  if(gender == 2){
    new->female=1;
    new->male=0;
  }
  return new;
}

void imprimirDate(bornADT born){
  pDate aux = born->firstDate;
  while(aux != NULL){
    printf("year: %d; male: %d; female:%d\n", aux->year, aux->male, aux->female);
    aux = aux->next;
  }
  printf("%d\n", born->allBorns);
  return;
}

void imprimirProvince(bornADT born){
  pProv aux = born->firstProvince;
  while(aux != NULL){
    printf("provincia: %s; code: %d\n", aux->province, aux->code);
    aux = aux->next;
  }
  return;
}
