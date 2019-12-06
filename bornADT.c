#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bornADT.h"

#define MAX_LENGTH  200
#define DIM 100

typedef struct nodeDate{
    pDate next;
    int year;
    int male;
    int female;
}nodeDate;


typedef struct nodeProv{
    pProv next;
    char * province;
    int borns;
    int code;
}nodeProv;

struct bornCDT{
    int allBorns;
    int sizeDates;
    int sizeProvinces;
    pProv firstProvince;
    pProv currentProvince;      //SI NO LOS USAMOS, BORRARLOS
    pDate firstDate;
    pDate currentDate;          //SI NO LOS USAMOS, BORRARLOS
};

static int compareInt(int c1, int c2){
    return c1-c2;
}

static void freeProvince(pProv b);
static void freeDate(pDate  b);
static pProv addProvince(char *province, int code);
static pDate addYear(int gender, int currentYear);


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

void addBorn(bornADT born, int provinceCode){
  pProv aux = born->firstProvince;

  while ( aux != NULL && aux->code != provinceCode){
    aux = aux->next;
  }
  if(aux == NULL){
    return;
  }

  aux->borns += 1;
}


void addProvinces(bornADT born, char *province, int code){
    pProv aux = born->firstProvince, previous = NULL;

    while(aux != NULL){

        if((strcmp (province, aux->province)) < 0){
          pProv new = addProvince(province, code);
          born->sizeProvinces += 1;
          if(previous == NULL)
                born->firstProvince = new;
          else
                previous->next = new;

	              new->next = aux;
          return ;
        }
        previous = aux;
        aux = aux->next;

    }

    if(aux == NULL){
      pProv new = addProvince(province, code);
      born->sizeProvinces += 1;
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
  new->province = malloc(sizeof(char)*DIM);
  strcpy(new->province, province);
  new->code = code;
  new->borns = 0;

  return new;
}


void addYears(bornADT born, int year, int gender){
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
            else if(c < 0){
              pDate new = addYear(gender, year);
              born->sizeDates += 1;
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
    born->sizeDates += 1;
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

int calculatePercentage(bornADT born, pProv node){
	int percentage = (int)(((node->borns)*100)/(born->allBorns));
  return percentage;
}

int orderByPercentage(bornADT born, int ** percentage, char *** provinces){
    pProv aux = born->firstProvince;
    int dimProv= born->sizeProvinces;
    int dim = 0, auxPercentage = -1;
    char *auxProvince =NULL;
    int *percentages = malloc(dimProv*sizeof(int));
    char **provs;
    provs= (char**)malloc(dimProv*sizeof(char*));

    while (aux != NULL) {
      percentages[dim] = calculatePercentage(born, aux);
      provs[dim] = aux->province;
      dim++;
      aux = aux->next;
    }

    for(int i=1; i<dimProv; i++){
      for(int j=0; j<i-1;j++){
        if(percentages[i]>percentages[j]){
          auxPercentage = percentages[i];
          percentages[i] = percentages [j];
          percentages[j] = auxPercentage;

          auxProvince = provs[i];
          provs[i] = provs[j];
          provs[j] = auxProvince;
        }
      }
    }

	*percentage = percentages;
  *provinces = provs;
	return dim;
}


int listProvinces(bornADT born,  char ***provinces, int **bornsByProvince){

  pProv aux = born->firstProvince;
  int dimProv = born->sizeProvinces;
  int dim = 0;
  char **provs;
  provs= (char**)malloc(dimProv*sizeof(char*));
  int *borns = malloc(dimProv*sizeof(int));

  while(aux != NULL){
    provs[dim] = aux->province;
    borns[dim] = aux->borns;
    dim++;
    aux=aux->next;
  }

  *provinces = provs;
  *bornsByProvince = borns;

  return dimProv;
}

int listYears(bornADT born, int **years, int **males, int **females){

  pDate aux = born->firstDate;
  int dimDates = born->sizeDates;
  int dim = 0;
  int *arrYear = malloc(dimDates*sizeof(int));
  int *arrMales = malloc(dimDates*sizeof(int));
  int *arrFemales = malloc(dimDates*sizeof(int));

  while(aux != NULL){
    arrYear[dim] = aux->year;
    arrMales[dim] = aux->male;
    arrFemales[dim] = aux->female;
    dim++;
    aux=aux->next;
   }

  *years = arrYear;
  *males = arrMales;
  *females = arrFemales;

  return dim;
}

//HABRIA QUE ELIMINARLA ANTES DE ENTREGAR EL TP
void imprimirDate(bornADT born){
  pDate aux = born->firstDate;
  while(aux != NULL){
    printf("year: %d; male: %d; female:%d\n", aux->year, aux->male, aux->female);
    aux = aux->next;
  }
  printf("total: %d\nsize: %d\n", born->allBorns, born->sizeDates);
  return;
}
//HABRIA QUE ELIMINARLA ANTES DE ENTREGAR EL TP
void imprimirProvince(bornADT born){
  pProv aux = born->firstProvince;
  while(aux != NULL){
    printf("provincia: %s; code: %d, borns: %d, porcentaje: %d\n", aux->province, aux->code, aux->borns, calculatePercentage(born, aux));
    aux = aux->next;
  }
  printf("size: %d\n", born->sizeProvinces);
  return;
}
