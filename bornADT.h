#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * pProv;
typedef struct nodeDate * pDate;

/* Descripción: 	inicializa la lista.
 * Parametros: 		ninguno.
*/
bornADT new(void);

/* Descripción:   consulta si esta vacia la estrcutura
 * Parametros:
*/
int isEmpty(const bornADT b);

/* Funcion:
 * Descripción: 	inicializa la lista.
 * Parametros: 		ninguno.
*/
void freeBorn(bornADT b);

/* Descripción:
 * Parametros:
*/
void addProvinces(bornADT born, char *province, int code);

/* Descripción:
 * Parametros:
*/
void addYears(bornADT born, int year, int gender);

/* Descripción:
 * Parametros:
*/
void addBorn(bornADT born, int provinceCode);

/* Descripción:
 * Parametros:
*/
int calculatePercentage(bornADT born, pProv node);

/* Descripción:
 * Parametros:
*/
int orderByPercentage(bornADT born, int ** percentage, char *** provinces, int *error);

/* Descripción:
 * Parametros:
*/
int listProvinces(bornADT born, char ***provinces, int **bornsByProvince, int *error);

/* Descripción:
 * Parametros:
*/
int listYears(bornADT born, int **years, int **males, int **females, int *error);

#endif
