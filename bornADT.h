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

void addProvinces(pProv born, char *province, int code, int dimProvince);

void addYears(bornADT born, int year, int sex, int provinceCode);



#endif
