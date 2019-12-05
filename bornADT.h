#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * pProv;
typedef struct nodeDate * pDate;


bornADT new(void);

int isEmpty(const bornADT b);

void toBeginDate(bornADT b);
int hasNextDate(bornADT b);

void toBeginProvince(bornADT b);
int hasNextProvince(bornADT b);

void freeBorn(bornADT b);

void addProvinces(bornADT born, char *province, int code);

void addYears(bornADT born, int year, int gender);

void imprimirDate(bornADT born);

void imprimirProvince(bornADT born);

void addBorn(bornADT born, int provinceCode);

int calculatePercentage(bornADT born, pProv node);
#endif
