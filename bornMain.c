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

    if(argc != 3){  //Se asegura de recibir la cantidad de archivos correcta
        printf("ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.\n");
        return 1;
    }

    bornADT born = new();
    FILE * fp = fopen(argv[1], "r");  //Abre el archivo que correspondería a provincias.csv, con permiso de lectura
    FILE * fn = fopen(argv[2], "r");  //Abre el archivo que correspondería a nacimientos.csv, con permiso de lectura
    if(fn == NULL || fp == NULL){
        printf("ERROR: File could not be opened\n");
        return 1;
    }
    printf("\n----------------------------TRABAJO FINAL PI----------------------------\n");
    printf("--------Conca, Maria | Limachi, Desiree | Prado Torres, Macarena--------\n");
    printf("------------------------------------------------------------------------\n\n");

    processProvinceData(fp, born);  //Obtiene los datos necesarios del archivo provincias.csv y los analiza en el TAD
    processBornsData(fn, born);  //Obtiene los datos necesarios del archivo provincias.csv y los analiza en el TAD

    fclose(fp); //Cierra los archivos
    fclose(fn);

    query1(born); //Llama a las funciones Query
    query2(born);
    query3(born);

    freeBorn(born); //Libera el espacio almacenado
    return 0;
}

void processProvinceData(FILE * province_data, bornADT b){
    char str[BLOQUE];
    int count=0, toReturnError = 0;
    int field, code;
    char *province=malloc(sizeof(char)*MAX_LENGTH);
    if(province == NULL){
      printf("\n");
      return;
    }

    while(fgets(str, BLOQUE, province_data)){
        field=0;
        count++;

        if(count==1) //Saltea el título de las columnas
            continue;
        char * token = strtok(str, ",");  //Empieza a recorrer la primer línea de provincias.csv
        while(token){

            if(field == 0){
                sscanf(token, "%d", &code); //Guarda el código de la provincia
            }
            if(field == 1){
      		    strcpy(province, token);  //Guarda el nombre de la provincia
            }

            token = strtok(NULL, ",");  //Avanza a la siguiente línea
            field++;
        }
        addProvinces(b, province, code, &toReturnError);  //Envía el código y el nombre de la provincia para agregarlos a la lista en el TAD
        if(toReturnError){
          printf("ERROR: No space memory left\n");
          return;
        }
    }
    free(province); //Libera el espacio almacenado
    return;
}

void processBornsData(FILE * borns_data, bornADT b){
    char str[BLOQUE];
    int count=0, toReturnError = 0;
    int field;
    int year, gender, provinceCode;

    while(fgets(str, BLOQUE, borns_data)){
        field=0;
        count++;

        if(count==1)  //Saltea el título de las columnas
            continue;
        char * token = strtok(str, ",");  //Empieza a recorrer la primer línea de nacimientos.csv

        while(token){

            if(field == 0){
                sscanf(token, "%d", &year); //Guarda el año de nacimiento
            }
            if(field == 1){
                sscanf(token, "%d", &provinceCode); //Guarda el código de la provincia del nacido
            }
	          if(field == 3){
                sscanf(token, "%d", &gender); //Guarda el género del nacido
            }

            token = strtok(NULL, ",");  //Avanza a la siguiente línea
            field++;
        }
        addBorn(b, provinceCode);  //Envía el código de la provincia para agregar un nacido a la provincia en la lista en el TAD
        addYears(b, year, gender, &toReturnError);  //Envía el año y género del nacido para agregarlos a la lista en el TAD
        if(toReturnError){
          printf("ERROR: No space memory left\n");
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
      printf("ERROR: No space memory left\n");
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
      printf("ERROR: No space memory left\n");
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
      printf("ERROR: No space memory left\n");
      return ;
    }

    for(int i = 0; i < dim; i++){
      len=strlen(provinces[i]);
      if(len > 0)
          provinces[i][len]='\0';
      fprintf(fp, "%s;%d%%\n", provinces[i], percentage[i]);
    }

    free(provinces);
    free(percentage);

    fclose(fp);
    return;
}
