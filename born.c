#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bornADT.h"

#define BLOQUE 400
#define MAX_LENGTH 5000

void processProvinceData(FILE * province_data, bornADT b);
void processBornsData(FILE * borns_data, bornADT b);

void query1(bornADT born);
void query2(bornADT born);
void query3(bornADT born);

int main(int argc, char **argv){

    if(argc != 3){ //me aseguro de recibir los archivos en la línea de comandos, el primer argumento siempre es el programa en si.
        printf("ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.\n"); //FUNCIONA CON FSANITIZE
        return 1;
    }

    bornADT born = new();//FUNCIONA CON FSANITIZE
    FILE * fp = fopen(argv[1], "r"); //abro el archivo de nacimientos que recibi como parametro con permisos de lectura
    FILE * fn = fopen(argv[2], "r");
    if(fn == NULL || fp == NULL){
        printf("ERROR: File could not be opened\n"); //FUNCIONA CON FSANITIZE
        exit(1);
    }

    processProvinceData(fp, born);
    processBornsData(fn, born);

    fclose(fp); //cuando termino de leer todas las estaciones y agregarlas, cierro el archivo
    fclose(fn); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo

    query1(born);
    query2(born);
    query3(born);

    freeBorn(born);

    return 0; 
}

void processProvinceData(FILE * province_data, bornADT b){
    char buf[BLOQUE]; //defino un vector de chars para poder usar en fgets
    int cont=0;
    int numCampo;
    int code;
    char *province=malloc(sizeof(char)*MAX_LENGTH);

    while(fgets(buf, BLOQUE, province_data)){
        numCampo=0;
        cont++;

        if(cont==1)
            continue; //me salteo el header
        char * campo = strtok(buf, ","); //empiezo a recorrer la linea del CSV
        while(campo){

            if(numCampo == 0){  //recibo el dato de la columna CODIGO
                sscanf(campo, "%d", &code);
            }

            if(numCampo == 1){ //recibo el dato de la columna VALOR
      		    strcpy(province, campo);//estoy copiando el nombre de la provincia
            }

            campo = strtok(NULL, ","); //avanzo de campo
            numCampo++;
        }
        addProvinces(b, province, code);
    }
    free(province);
    return;
}

void processBornsData(FILE * borns_data, bornADT b){
  char buf[BLOQUE]; //defino un vector de chars para poder usar en fgets
    int cont=0;
    int numCampo;
    int year, gender, provinceCode;

    while(fgets(buf, BLOQUE, borns_data)){
        numCampo=0;
        cont++;

        if(cont==1)
            continue; //me salteo el header
        char * campo = strtok(buf, ","); //empiezo a recorrer la linea del CSV
        while(campo){

            if(numCampo == 0){		//recibo el dato de la columna AN
                sscanf(campo, "%d", &year);
            }

            if(numCampo == 1){ //recibo el dato de la columna PROVRES
                sscanf(campo, "%d", &provinceCode);
            }

	    if(numCampo == 3){ //recibo el dato de la columna SEXO
                sscanf(campo, "%d", &gender);
            }

            campo = strtok(NULL, ","); //avanzo de campo
            numCampo++;
        }
        addBorn(b, provinceCode);
        addYears(b, year, gender);

    }
    //imprimirProvince(b);

   // imprimirDate(b);
}


//______________________________________IDEA DE query1     

void query1(bornADT born){
    FILE *fp;
    fp=fopen("query1.csv", "w");             //ASI SE CREA EL ARCHIVO
    fprintf(fp, "Provincias;Nacimientos\n");    //SI YA LOS ORDENAMOS ALFABETICAMENTE, ESE CODIGO PUEDE SER REUTILIZADO EN EL QUERY3 (QUE PIDE ORDEN POR PORCENTAJE Y ALFABETICO)

    int len;
    char **provinces;
    int *bornsByProvince;

    int dim= listProvinces(born, &provinces, &bornsByProvince);

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

// QUERY 2
void query2(bornADT born){
     FILE *fp;
     fp=fopen("query2.csv", "w");
     fprintf(fp, "Año;Varón;Mujer\n");

	int *year, *male, *female;

	int dim= listYears(born, &year, &male, &female);

     for(int i=0; i<dim; i++){
         fprintf(fp, "%d;%d;%d\n", year[i], male[i], female[i]);
     }

	free(year);
	free(female);
	free(male);

     fclose(fp);
     return; 
}

// //______________________________________QUERY 3

void query3(bornADT born){      
    FILE *fp;
    fp=fopen("query3.csv", "w");
    fprintf(fp, "Provincia;Porcentaje\n");
    int len, *percentage; 
    char **provinces;

    int dim= orderByPercentage(born, &percentage, &provinces);

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



















