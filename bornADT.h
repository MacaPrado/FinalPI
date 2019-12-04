#ifndef BORNADT_H_
#define BORNADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * provNode;
typedef struct nodeDate * dateNode;


bornADT new(void);

int isEmpty(const bornADT b);

void toBegin(bornADT b);

int hasNext(bornADT b);

void freeBorn(bornADT b);

void addProvinces(bornADT born, provNode Province);

void addYears(bornADT born, int year, int sex);

#endif
