#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bornADT.h"

#define BLOQUE 400
#define MAX_LENGTH 100


void processProvinceData(FILE * province_data, bornADT b);
void processBornsData(FILE * borns_data, bornADT b);

void query1(bornADT born);
void query2(bornADT born);
void query3(bornADT born);

int main(int argc, char **argv){

    if(argc != 3){
        printf("ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.\n");
        return 1;
    }

    bornADT born = new();
    FILE * fp = fopen(argv[1], "r");
    FILE * fn = fopen(argv[2], "r");
    if(fn == NULL || fp == NULL){
        printf("ERROR: File could not be opened\n");
        return 1;
    }
    printf("\n----------------------TRABAJO FINAL PI----------------------\n");
    printf("--------Conca, Maria | Limachi, Desiree | Prado, Macarena-------\n");

    processProvinceData(fp, born);
    processBornsData(fn, born);

    fclose(fp);
    fclose(fn);

    query1(born);
    query2(born);
    query3(born);

    freeBorn(born);
    return 0;
}

void processProvinceData(FILE * province_data, bornADT b){
    char buf[BLOQUE];
    int cont=0, toReturnError = 0;
    int numCampo, code;
    char *province=malloc(sizeof(char)*MAX_LENGTH);
    if(province == NULL){
      printf("\n");
      return;
    }

    while(fgets(buf, BLOQUE, province_data)){
        numCampo=0;
        cont++;

        if(cont==1)
            continue;
        char * campo = strtok(buf, ",");
        while(campo){

            if(numCampo == 0){
                sscanf(campo, "%d", &code);
            }
            if(numCampo == 1){
      		    strcpy(province, campo);
            }

            campo = strtok(NULL, ",");
            numCampo++;
        }
        addProvinces(b, province, code, &toReturnError);
        if(toReturnError){
          printf("No space memory left\n");
          return;
        }
    }
    free(province);
    return;
}

void processBornsData(FILE * borns_data, bornADT b){
    char buf[BLOQUE];
    int cont=0, toReturnError = 0;
    int numCampo;
    int year, gender, provinceCode;

    while(fgets(buf, BLOQUE, borns_data)){
        numCampo=0;
        cont++;

        if(cont==1)
            continue;
        char * campo = strtok(buf, ",");

        while(campo){

            if(numCampo == 0){
                sscanf(campo, "%d", &year);
            }
            if(numCampo == 1){
                sscanf(campo, "%d", &provinceCode);
            }
	          if(numCampo == 3){
                sscanf(campo, "%d", &gender);
            }

            campo = strtok(NULL, ",");
            numCampo++;
        }
        addBorn(b, provinceCode);
        addYears(b, year, gender, &toReturnError);
        if(toReturnError){
          printf("No space memory left\n");
          return;
        }
    }
    return;
}

void query1(bornADT born){
    FILE *fp=fopen("query1.csv", "w");
    fprintf(fp, "Provincias;Nacimientos\n");

    int len, error= 0;
    char **provinces;
    int *bornsByProvince;

    int dim= listProvinces(born, &provinces, &bornsByProvince, &error);

    if(error){
      printf("No space memory left\n");
      return ;
    }

    for(int i = 0; i < dim; i++){
	     len=strlen(provinces[i]);
	     if(len > 0)
		        provinces[i][len-2]='\0';
       fprintf(fp, "%s;%d\n",provinces[i], bornsByProvince[i]);
    }

    free(provinces);
    free(bornsByProvince);
    fclose(fp);

    return;
}

void query2(bornADT born){
    FILE *fp=fopen("query2.csv", "w");
    fprintf(fp, "Año;Varón;Mujer\n");
    int error = 0;
	  int *year, *male, *female;

	  int dim= listYears(born, &year, &male, &female, &error);

    if(error){
      printf("No space memory left\n");
      return ;
    }
    for(int i=0; i<dim; i++){
         fprintf(fp, "%d;%d;%d\n", year[i], male[i], female[i]);
    }

	  free(year);
	  free(female);
	  free(male);

    fclose(fp);
    return;
}

void query3(bornADT born){
    FILE *fp=fopen("query3.csv", "w");
    fprintf(fp, "Provincia;Porcentaje\n");
    int len, error = 0;
    int *percentage;
    char **provinces;

    int dim= orderByPercentage(born, &percentage, &provinces, &error);
    if(error){
      printf("No space memory left\n");
      return ;
    }

    for(int i = 0; i < dim; i++){
      len=strlen(provinces[i]);
      if(len > 0)
          provinces[i][len]='\0';
      fprintf(fp, "%s;%d\n", provinces[i], percentage[i]);
    }

    free(provinces);
    free(percentage);

    fclose(fp);
    return;
}
