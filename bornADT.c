#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bornADT.h"

#define MAX_LENGTH  100
#define DIM 200

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
    pDate firstDate;
};


/* Descripción: libera todas las provincias de la lista
 * Parametros de entrada: puntero al nodo provincia
*/
static void freeProvince(pProv b);

/* Descripción: libera todos los años de la lista
 * Parametros de entrada: puntero al nodo Date
*/
static void freeDate(pDate  b);

/* Descripción:  crea un nuevo nodo Provincia
 * Parametros de entrada:  vector de la provincia, codigo de la provincia
 * Parametros de salida: flag del error
 * Retorna: el puntero al nuevo nodo si es que se pudo crear
*/
static pProv addProvince(char *province, int code, int *error);

/* Descripción:   crea un nuevo nodo Date
 * Parametros de entrada:    genero, año
 * Parametros de salida: flag del error
 * Retorna: el puntero al nuevo nodo si es que se pudo crear
*/
static pDate addYear(int gender, int year, int *error);


bornADT new(void){
    bornADT new = calloc(1, sizeof(struct bornCDT));
    return new;
}

int isEmpty(const bornADT b){
    return b->allBorns == 0;
}

void freeBorn(bornADT b){
    freeProvince(b->firstProvince);
    freeDate(b->firstDate);
    free(b);
}

static void freeProvince(pProv b){
    if(b == NULL) {
        return;
    }
    free(b->province);
    freeProvince(b->next);
    free(b);
}
static void freeDate (pDate  b){
    if(b == NULL) {
        return;
    }
    freeDate(b->next);
    free(b);
}

void addBorn(bornADT born, int provinceCode){
    pProv aux = born->firstProvince;

    while(aux != NULL && aux->code != provinceCode){
      aux = aux->next;
    }
    if(aux == NULL)
      return;

    aux->borns += 1;
}

void addProvinces(bornADT born, char *province, int code, int *toReturnError){
    pProv aux = born->firstProvince, previous = NULL;
    int error = 0;
    while(aux != NULL){

        if((strcmp (province, aux->province)) < 0){
          pProv new = addProvince(province, code, &error);
          if(error){
            *toReturnError = 1;
            return ;
          }
          born->sizeProvinces += 1;
          if(previous == NULL)
                born->firstProvince = new;
          else
                previous->next = new;

	              new->next = aux;
          return;
        }
        previous = aux;
        aux = aux->next;
    }

    if(aux == NULL){
      pProv new = addProvince(province, code, &error);
      if(error){
        *toReturnError = 1;
        return ;
      }
      born->sizeProvinces += 1;

        if(previous == NULL)
          born->firstProvince = new;
        else
          previous->next = new;

        new->next = NULL;
    }
    return;
}

static pProv addProvince(char *province, int code, int *error){
    pProv new = malloc(sizeof(nodeProv));
    if(new == NULL){
      *error = 1;
      return NULL;
    }

    new->province = malloc(sizeof(char)*DIM);
    if(new->province == NULL){
      free(new);
      *error = 1;
      return NULL;
    }

    strcpy(new->province, province);
    new->code = code;
    new->borns = 0;

  return new;
}

void addYears(bornADT born, int year, int gender, int *toReturnError){
    pDate aux = born->firstDate, previous = NULL;
    int error = 0;
    while(aux != NULL){
          if(year == aux->year){
            if(gender == 1)
              aux->male += 1;

            if(gender == 2)
              aux->female += 1;

            born->allBorns += 1;
            return ;
          }
          else if(year < aux->year){
            pDate new = addYear(gender, year, &error);
            if(error){
              *toReturnError = 1;
              return ;
            }
            born->sizeDates += 1;
            if(previous == NULL)
                born->firstDate = new;
            else
                previous->next = new;
            new->next = aux;
            born->allBorns += 1;
            return ;
          }
          previous = aux;
          aux= aux->next;
    }

    if(aux == NULL){
      pDate new = addYear(gender, year, &error);
      born->sizeDates += 1;
      if(previous == NULL)
        born->firstDate = new;
      else
        previous->next = new;

      born->allBorns += 1;
      new->next = NULL;
      }
    return ;
}

static pDate addYear(int gender, int year, int *error) {
    pDate new = malloc(sizeof(nodeDate));
    if(new == NULL){
      *error = 1;
      return NULL;
    }
    new->year = year;
    if(gender == 1){
      new->male = 1;
      new->female = 0;
    }

    if(gender == 2){
      new->female = 1;
      new->male = 0;
    }
    return new;
}

int calculatePercentage(bornADT born, pProv node){
  	int percentage = (int)(((node->borns)*100)/(born->allBorns));
    return percentage;
}

int orderByPercentage(bornADT born, int ** percentage, char *** provinces, int *error){
    pProv aux = born->firstProvince;
    int dimProv = born->sizeProvinces;
    int dim = 0, auxPercentage = -1;
    char *auxProvince = NULL;
    int *percentages = malloc(dimProv*sizeof(int));
    if(percentages == NULL){
      *error = 1;
      return 0;
    }
    char **provs;
    provs= (char**)malloc(dimProv*sizeof(char*));
    if(provs == NULL){
      *error = 1;
      return 0;
    }

    while (aux != NULL) {
      percentages[dim] = calculatePercentage(born, aux);
      provs[dim] = aux->province;
      dim++;
      aux = aux->next;
    }

    for(int i=1; i<dimProv; i++){
      for(int j=0; j<i-1; j++){
        if(percentages[i] > percentages[j]){
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

int listProvinces(bornADT born,  char ***provinces, int **bornsByProvince, int *error){

    pProv aux = born->firstProvince;
    int dimProv = born->sizeProvinces;
    int dim = 0;
    char **provs;
    provs = (char**)malloc(dimProv*sizeof(char*));
    if(provs == NULL){
      *error = 1;
      return 0;
    }
    int *borns = malloc(dimProv*sizeof(int));
    if(borns == NULL){
      *error = 1;
      return 0;
    }

    while(aux != NULL){
      provs[dim] = aux->province;
      borns[dim] = aux->borns;
      dim++;
      aux = aux->next;
    }

    *provinces = provs;
    *bornsByProvince = borns;

    return dimProv;
}

int listYears(bornADT born, int **years, int **males, int **females, int *error){

    pDate aux = born->firstDate;
    int dimDates = born->sizeDates;
    int dim = 0;
    int *arrYear = malloc(dimDates*sizeof(int));
    if(arrYear == NULL){
      *error = 1;
      return 0;
    }
    int *arrMales = malloc(dimDates*sizeof(int));
    if(arrMales == NULL){
      *error = 1;
      return 0;
    }
    int *arrFemales = malloc(dimDates*sizeof(int));
    if(arrFemales == NULL){
      *error = 1;
      return 0;
    }

    while(aux != NULL){
      arrYear[dim] = aux->year;
      arrMales[dim] = aux->male;
      arrFemales[dim] = aux->female;
      dim++;
      aux = aux->next;
     }

    *years = arrYear;
    *males = arrMales;
    *females = arrFemales;

    return dim;
}
