#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bornADT.h"

#define BLOQUE 400
#define MAX_LENGTH 200

void processProvinceData(FILE * province_data, bornADT b);
void processBornsData(FILE * borns_data, bornADT b);
void query1(char provinces[][MAX_LENGTH], int *bornsByProvince, const int dim);
void query2(int * year, int * male, int * female, const int dim);
void query3(char provinces[][MAX_LENGTH],int percentage[], const int dim);

int main(int argc, char **argv){

    if(argc != 3){ //me aseguro de recibir los archivos en la línea de comandos, el primer argumento siempre es el programa en si.
        printf("ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.\n");
        return 1;
    }

    bornADT born = new();
    FILE * f = fopen(argv[1], "r"); //abro el archivo de provincias que recibi como parametro con permisos de lectura

    if(f == NULL){
        printf("ERROR: File could not be opened\n");
        return 1;
    }

    processProvinceData(f, born);
    fclose(f); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo

    f = fopen(argv[2], "r"); //abro el archivo de nacimientos

    if(f==NULL){
        printf("ERROR: File could not be opened\n");
        return 1;
    }

    processBornsData(f, born);

    fclose(f); //cuando termino de leer todas las nacimientos y agregarlas, cierro el archivo

		processQueries(born);

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
    return;
}


//Query 1

void query1(char provinces[][MAX_LENGTH], int *bornsByProvince, const int dim){
    FILE *fp = fopen("query1.csv", "w");
    fprintf(fp, "Provincias;Nacimientos\n");
		int len;

    for(int i = 0; i < dim; i++){
				len=strlen(provinces[i]);
				if(len > 0)
					provinces[i][len-2]='\0';
        fprintf(fp, "%s;%d\n",provinces[i], bornsByProvince[i]);
    }
    fclose(fp);

    return;
}


//Query 2

void query2(int * year, int * male, int * female, const int dim){
  FILE *fp = fopen("query2.csv", "w");
  fprintf(fp, "Año;Varón;Mujer\n");

  for(int i=0; i < dim; i++){
     fprintf(fp, "%d;%d;%d \n", year[i],male[i], female[i]);
  }

  fclose(fp);

  return;
}

//Query 3
void query3(char provinces[][MAX_LENGTH],int percentage[], const int dim){
    FILE *fp;
    fp=fopen("query3.csv", "w");
    fprintf(fp, "Provincia;Porcentaje\n");
    for(int i=0; i<dim; i++){
        fprintf(fp, "%s;%d%%\n", provinces[i],percentage[i]);
    }
    fclose(fp);
    return;
}
