#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bornADT.h"


int main(int argc, char **argv){

	if(argc != 3){ //me aseguro de recibir los archivos en la línea de comandos, el primer argumento siempre es el programa en si. 
		printf("ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.\n"); //FUNCIONA CON FSANITIZE
		return 1;
	}

	FILE * f = fopen(argv[1], "r"); //abro el archivo de nacimientos que recibi como parametro con permisos de lectura

	if(f == NULL){
		printf("ERROR: File could not be opened\n"); //FUNCIONA CON FSANITIZE
		return 1;
	}

	fclose(f); //cuando termino de leer todas las estaciones y agregarlas, cierro el archivo

	f = fopen(argv[2], "r"); //abro el archivo de provincias 	//ES NECESARIO REPETIR EL CODIGO PORQUE SOLO PUEDO ABRIR UNO POR VEZ

	if(f==NULL){
		printf("ERROR: File could not be opened\n"); //FUNCIONA CON FSANITIZE
		return 1;
	}

	fclose(f); //cuando termino de leer todas las provincias y agregarlas, cierro el archivo

	return 0;
}

//NO ESTOY SEGURA DE QUE EL ARMADO DE LOS QUERYS SE HAGA ACA, ¿¿ POR QUE LO HABIAMOS HECHO ASI EN LA ENTREGA ANTERIOR ??


//______________________________________IDEA DE query1       NO LO PROBE CON FSANITIZE, ES UNA IDEA

void query1(char *provinces[],long int bornByProvince[], const int dim){ //DONDE DIM ES EL NUMERO DE PROVINCIAS QUE DEBERIAMOS IR SUMANDO EN CADA ADD
    FILE *fp;
    fp=fopen("query1.csv", "w");				//ASI SE CREA EL ARCHIVO
    fprintf(fp, "Provincia;Nacimientos\n");							//SI YA LOS ORDENAMOS ALFABETICAMENTE, ESE CODIGO PUEDE SER REUTILIZADO EN EL QUERY3 (QUE PIDE ORDEN POR PORCENTAJE Y ALFABETICO)
    for(int i=0; i<dim; i++){
        fprintf(fp, "%s;%ld\n", provinces[i],bornByProvince[i]);
    }
    fclose(fp);
    return;
}

//______________________________________IDEA DE query2       NO LO PROBE CON FSANITIZE, ES UNA IDEA

void query2(int *year, int *male, int *female, const int years){ 
    FILE *fp;
    fp=fopen("query2.csv", "w");				
    fprintf(fp, "Año;Varón;Mujer\n");	
    for(int i=0; i<years; i++){
        fprintf(fp, "%d;%ld;%ld\n", year[i],male[i],female[i]);
    }
    fclose(fp);
    return;
}

//______________________________________IDEA DE Query3       NO LO PROBE CON FSANITIZE, ES UNA IDEA

void query3(char *provinces[],int percentage[], const int dim){		//TENDRIAMOS QUE PONERLE CONST A ESTOS VECTORES EN CADA QUERY?
    FILE *fp;
    fp=fopen("query3.csv", "w"); 
    fprintf(fp, "Provincia;Porcentaje\n");
    for(int i=0; i<dim; i++){
        fprintf(fp, "%s;%ld%%\n", provinces[i],percentage[i]);
    }
    fclose(fp);
    return;
}
