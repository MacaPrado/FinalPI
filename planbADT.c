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
    pDate firstDate;
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

// void toBeginDate(bornADT b){
//     b->currentDate = b->firstDate;
// }
// int hasNextDate(bornADT b){
//     return b->currentDate != NULL;
// }
//
// void toBeginProvince(bornADT b){
//     b->currentProvince = b->firstProvince;
// }
// int hasNextProvince(bornADT b){
//     return b->currentProvince != NULL;
// }

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


void processQueries(bornADT born){
    //Query 1
    pProv auxP = born->firstProvince;
    int dimProvince = born->sizeProvinces;
    char provinces[dimProvince][MAX_LENGTH];
    int *borns = malloc(dimProvince * sizeof(int));
    int i = 0;

    while (auxP != NULL) {
      strcpy(provinces[i], auxP->province);
      borns[i] = auxP->borns;
      i++;
      auxP = auxP->next;
    }

    //Query 2
    pDate auxD = born->firstDate;
    int dimDates = born->sizeDates;
    int *years = malloc(dimDates * sizeof(int));
    int *males = malloc(dimDates * sizeof(int));
    int *females = malloc(dimDates * sizeof(int));
    int j = 0;

    while(auxD != NULL){
      years[j] = auxD->year;
      males[j] = auxD->male;
      females[j] = auxD->female;

      j++;
      auxD = auxD->next;
    }

    //Query 3
    auxP = born->firstProvince;
    int *percentage = malloc(dimProvince * sizeof(int));
    int k = 0;
    while (auxP != NULL) {
      percentage[k] = calculatePercentage(born, auxP);
      k++;
      auxP = auxP->next;
    }

    //Queries
    query1(provinces, borns, dimProvince);
    query2(years, males, females, dimDates);
    orderByPercentage(provinces, percentage, dimProvince);
    query3(provinces, percentage, dimProvince);

    //Frees
    free(borns);
    free(years);
    free(males);
    free(females);
    free(percentage);

}

int calculatePercentage(bornADT born, pProv node){
	int percentage = (int)(((node->borns)*100)/(born->allBorns));
  return percentage;
}

void orderByPercentage(char provinces[][MAX_LENGTH],int *percentage, const int dim){
    int auxPercentage = -1;
    char *auxProvince = malloc(MAX_LENGTH * sizeof(char));
    for(int i=1; i<dim; i++){
      for(int j=0; j<i-1;j++){
        if(percentage[i]>percentage[j]){
          auxPercentage = percentage[i];
          percentage[i] = percentage [j];
          percentage[j] = auxPercentage;
          strcpy(auxProvince, provinces[i]);
          strcpy(provinces[i], provinces[j]);
          strcpy(provinces[j], auxProvince);
        }
      }
    }
    free(auxProvince);
}


// void imprimirDate(bornADT born){            //HABRIA QUE ELIMINARLA ANTES DE ENTREGAR EL TP
//   pDate aux = born->firstDate;
//   while(aux != NULL){
//     printf("year: %d; male: %d; female:%d\n", aux->year, aux->male, aux->female);
//     aux = aux->next;
//   }
//   printf("total: %d\nsize: %d\n", born->allBorns, born->sizeDates);
//   return;
// }
//
// void imprimirProvince(bornADT born){            //HABRIA QUE ELIMINARLA ANTES DE ENTREGAR EL TP
//   pProv aux = born->firstProvince;
//   while(aux != NULL){
//     printf("provincia: %s; code: %d, borns: %d, porcentaje: \n", aux->province, aux->code, aux->borns/*, calculatePercentage(born, aux)*/);
//     aux = aux->next;
//   }
//   printf("size: %d\n", born->sizeProvinces);
//   return;
// }
