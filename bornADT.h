#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * provNode;
typedef struct nodeDate * dateNode;


bornADT new(void);

int isEmpty(const bornADT b);

void toBeginDate(bornADT b);

void toBeginProvince(bornADT b);

int hasNextDate(bornADT b);

int hasNextProvince(bornADT b);

void freeBorn(bornADT b);

void addProvinces(provNode born, char *province, int code, int dimProvince);

void addYears(bornADT born, int year, int gender, int provinceCode);

#endif
