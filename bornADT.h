#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * pProv;
typedef struct nodeDate * pDate;

/* Descripción: 	inicializa la lista.
*/
bornADT new(void);

/* Descripción:   consulta si esta vacia la lista
 * Parametros de entrada:    estructura del TAD
 * Retorna: 1 si esta vacio, 0 sino
*/
int isEmpty(const bornADT b);


/* Descripción: 	libera la lista
 * Parametros de entrada: 		estructura del TAD
*/
void freeBorn(bornADT b);

/* Descripción: agrega las provincias y sus respectivos codigos del archivo csv a la lista
 * Parametros de entrada:  estructura del TAD, puntero al nombre de la provincia, codigo de la provincia
 * Parametros de salida:   flag de error
*/
void addProvinces(bornADT born, char *province, int code, int *toReturnError);

/* Descripción: agrega el año y aumenta la cantidad a cada genero del archivo csv a la lista
 * Parametros de entrada: estructura del TAD, año, genero
 * Parametros de salida:   flag de error
*/
void addYears(bornADT born, int year, int gender, int *toReturnError);

/* Descripción: agrega la cantidad de nacimientos por provincia a la lista de provincias
 * Parametros de entrada: estructura del TAD, codigo de la provincia
*/
void addBorn(bornADT born, int provinceCode);

/* Descripción: calcula el porcentaje de nacimientos por provincia
 * Parametros de entrada: estructura del TAD, puntero al nodo de provincia
 * Retorna: el porcentaje truncado a int
*/
int calculatePercentage(bornADT born, pProv node);

/* Descripción: ordena en forma descendiente por porcentaje la lista de provincias
 * Parametros de entrada: estructura del TAD
 * Parametros de salida: vector de porcentajes ordenados en forma descendiente, vector de las provincias, flag del error
 * Retorna: dimension de los vectores (es la misma para ambos)
*/
int orderByPercentage(bornADT born, int ** percentage, char *** provinces, int *error);

/* Descripción:   genera un vector con las provincias en orden ascendiente, y genera un vector con la cantidad de nacimientos
 * Parametros de entrada: estructura del TAD
 * Parametros de salida:  un vector de las provincias, y otro con la cantidad e nacimientos,  flag de error
 * Retorna: dimension de los vectores (es la misma para ambos)
*/
int listProvinces(bornADT born, char ***provinces, int **bornsByProvince, int *error);

/* Descripción: genera tres vectores: uno con los años que aparecen en el csv, y dos vectores en los cuales se guardan la cantidad de nacidos de cada genero
 * Parametros de entrada: estructura del TAD
 * Parametros de salida:  un vector de los años, y otros dos con la cantidad e nacimientos por genero masculino y femenino,  flag de error
 * Retorna: dimension de los vectores (es la misma para los tres)
*/
int listYears(bornADT born, int **years, int **males, int **females, int *error);

#endif
