#ifndef BORNADT_H_
#define BORNADT_H_
#define MAX_LENGTH 200

typedef struct bornCDT * bornADT;
typedef struct nodeProv * pProv;
typedef struct nodeDate * pDate;


bornADT new(void);

int isEmpty(const bornADT b);

// void toBeginDate(bornADT b);
//
// int hasNextDate(bornADT b);
//
// void toBeginProvince(bornADT b);
//
// int hasNextProvince(bornADT b);

void freeBorn(bornADT b);

void addProvinces(bornADT born, char *province, int code);

void addYears(bornADT born, int year, int gender);

void imprimirDate(bornADT born);

void imprimirProvince(bornADT born);

void addBorn(bornADT born, int provinceCode);

void processQueries(bornADT born);

int calculatePercentage(bornADT born, pProv node);

void orderByPercentage(char provinces[][MAX_LENGTH],int percentage[], const int dim);

void query1(char provinces[][MAX_LENGTH], int *bornsByProvince, const int dim);

void query2(int * year, int * male, int * female, const int dim);

void query3(char provinces[][MAX_LENGTH],int percentage[], const int dim);

#endif
