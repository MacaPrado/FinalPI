#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//ES NECESARIA???
#include <string.h>
#include "bornsADT.h"

#define MAX_LENGTH 20
#define BLOQUE2 350

typedef struct nodeDate{		//Estructura con año y sexo del nacido
    dateNode next;       //ORDENARLO POR FECHAS
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

// static int compare(char c1, char c2){
//     return c1-c2;
// }

static void freeProvince(provNode b);
static void freeDate(dateNode b);

bornADT new(void){
    return calloc(1, sizeof(struct bornCDT));
}

void 
freeBorn(bornADT b){
    if (b==NULL) {
        return;
    }
    freeProvince(b->firstProvince);
    freeFechas(b->firstDate);
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
// int isEmpty(const bornADT b){
//     return b->size == 0;
// }
//
// void toBegin(bornADT b){
//     b->current = b->first;
// }
//
// int hasNext(bornADT b){
//     return b->current != NULL;
// }

// void
// processProvinceData(FILE * province_data, bornADT born){
//     char fmt[]="%d,%[^,]";
//     int code;
//     char province[MAX_LENGTH];
//     while(fgetc(province_data)!='\n');
//     while (fscanf(province_data, fmt, &code, province) == 2){
//         //addProvince(borns, province, code);
//         printf("hola\n");
//     }
//     fclose(province_data);
// }


// void
// processBornsData(FILE * borns_data, bornADT born){
//     char fmt[]="%d/%d/%d,%d,%[^,],%[^,],%[^,], %d";
//     int year, provinceCode, parto, sex, cuenta;//QUE MIERDA ES CUENTA
//     char rango[MAX_LENGTH];
//     char study[MAX_LENGTH];
//     char peso[MAX_LENGTH];
//
//     while(fgetc(borns_data)!='\n');
//     while (fscanf(borns_data, fmt, &year, &provinceCode, &parto, &sex, rango, study, peso, cuenta) == 8) {
//         addDate(born, year, sex);
//     }
//     fclose(borns_data);
// }



void processProvinceData(FILE * f, bornADT b){
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
        printf("%d\n", cont );
        //addYears(b, year, sex, persons);
    }
}



void add(bornADT born, provNode Province){
    born->firstProvince= addProvince(born->firstProvince, Province);
    born->AllBorns++;
}

provNode addProvince(provNode b, char Province[MAX_LENGTH], int code){
    int c;

    if(b == NULL || b->code < code){
        provNode new= malloc(sizeof(struct nodeProv));
        new->code = code;
        new->name = malloc(sizeof(char));
        strcpy(new->name, province);
        new->next=
    }
}
