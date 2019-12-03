#ifndef BORNSADT_H_
#define BORNSADT_H_

typedef struct bornCDT * bornADT;
typedef struct nodeProv * provNode;
typedef struct nodeDate * dateNode;


bornADT new(void);
int isEmpty(const bornADT b);
void toBegin(bornADT b);
int hasNext(bornADT b);
//void add(ACA FALTA PARAMETRO, ACA FALTA PARAMETRO);
void processProvinceData(FILE * f, bornADT born);

#endif
