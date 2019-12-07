#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * pProv;
typedef struct nodeDate * pDate;

/* Descripción: inicializa la lista.
*/
bornADT new(void);

/* Descripción: libera la lista
 * Parámetros de entrada: estructura del TAD
*/
void freeBorn(bornADT b);

/* Descripción: agrega las provincias y sus respectivos códigos del archivo csv a la lista
 * Parámetros de entrada: estructura del TAD, puntero al nombre de la provincia, código de la provincia
 * Parámetros de salida: flag de error
*/
void addProvinces(bornADT born, char *province, int code, int *toReturnError);

/* Descripción: agrega el año y aumenta la cantidad a cada género del archivo csv a la lista
 * Parámetros de entrada: estructura del TAD, año, género
 * Parámetros de salida: flag de error
*/
void addYears(bornADT born, int year, int gender, int *toReturnError);

/* Descripción: agrega la cantidad de nacimientos por provincia a la lista de provincias
 * Parámetros de entrada: estructura del TAD, código de la provincia
*/
void addBorn(bornADT born, int provinceCode);

/* Descripción: calcula el porcentaje de nacimientos por provincia
 * Parámetros de entrada: estructura del TAD, puntero al nodo de provincia
 * Retorna: el porcentaje truncado a int
*/
int calculatePercentage(bornADT born, pProv node);

/* Descripción: ordena en forma descendiente por porcentaje la lista de provincias
 * Parámetros de entrada: estructura del TAD
 * Parámetros de salida: vector de porcentajes ordenados en forma descendiente, vector de las provincias, flag de error
 * Retorna: dimensión de los vectores (es la misma para ambos)
*/
int orderByPercentage(bornADT born, int ** percentage, char *** provinces, int *error);

/* Descripción: genera un vector con las provincias en orden ascendiente, y genera un vector con la cantidad de nacimientos
 * Parámetros de entrada: estructura del TAD
 * Parámetros de salida: un vector de las provincias, otro con la cantidad de nacimientos y el flag de error
 * Retorna: dimensión de los vectores (es la misma para ambos)
*/
int listProvinces(bornADT born, char ***provinces, int **bornsByProvince, int *error);

/* Descripción: genera tres vectores: uno con los años que aparecen en el csv y dos vectores en los cuales se guardan la cantidad de nacidos de cada género
 * Parámetros de entrada: estructura del TAD
 * Parámetros de salida: un vector de los años, otros dos con la cantidad de nacimientos por género masculino y femenino, y el flag de error
 * Retorna: dimensión de los vectores (es la misma para los tres)
*/
int listYears(bornADT born, int **years, int **males, int **females, int *error);

#endif
