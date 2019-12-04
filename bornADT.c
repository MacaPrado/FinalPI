#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bornADT.h"

#define MAX_LENGHT  200

typedef struct nodeDate{
    pDate next;
    size_t year;
    size_t men;
    size_t women;
} nodeDate;


typedef struct nodeProv{
    pProv next;
    char * name;
    size_t borns;
    size_t code;
} nodeProv;

struct bornCDT{
    size_t allBorns;
    pProv firstProvince;
    pProv currentProvince;
    pDate firstDate;
    pDate currentDate;
};
static int compareChar(char c1, char c2){
    return c1-c2;
}
static int compareInt(int c1, int c2){
    return c1-c2;
}

static void freeProvince(pProv b);
static void freeDate(pDate  b);
static nodeProv addProvince(char *province, int code, int dimProvince, pProv nextNode);
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
    free(b->name);
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


// void addProvinces(pProv born, char *province, int code, int dimProvince){
//     pProv actual = born->firstProvince, previous = NULL;
//     if(actual == NULL){
//       pProv new = addProvince(province, code, dimProvince, actual);
//       born->firstProvince = new;
//       toBeginProvince(born);
//     }
//     else{
//       while(actual != NULL && ((strcmp (actual->name, province)) < 0)){
//         previous = actual;
//         pProv aux = actual->next;
//         actual = aux;
//         born->currentProvince = actual;
//       }
//       if(actual == NULL){
//         pProv new = addProvince(province, code, dimProvince, aux);
//       }
//       else{
//
//       }
//     }
// }
//
//
// static nodeProv addProvince(char *province, int code, int dimProvince, pProv nextNode){
//   pProv new = malloc(sizeof(nodeProv));
//   new->name = province;   //ACA TENDRIA QUE HACER UN STRCPY???? NECESITO DIMPROVINCE???
//   new->code = code;
//   new->next = nextNode;
//
//   return new;
// }


void addYears(bornADT born, int year, int gender, int provinceCode){
  pDate aux = born->firstDate, previous = NULL;
  int c;
  if(aux == NULL){
    pDate new = addYear(year, gender);
    born->firstDate = new;
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
              pDate new = addYear(gender, year);
              previous->next = new;
              new->next = aux;
            }
            else{
              pDate new = addYear(gender, year);
              new->next = aux->next;
              aux->next = new->next;
            }
            previous = aux;
            aux= aux->next;
    }

  }
}

static  pDate  addYear(int gender, int currentYear) {
  pDate new = malloc(sizeof(nodeDate));
  new->year = currentYear;

  if(gender == 1)
    new->men=1;

  if(gender == 2)
    new -> women = 1;

  return new;
}
