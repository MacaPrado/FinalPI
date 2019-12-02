#ifndef BORNADT_H_
#define BORNADT_H_
typedef struct transporteCDT * transporteADT;		//ESTO ES PARA TENER UNA IDEA, NO VA, HAY QUE EDITARLO TODO PARA NUESTRO TP
typedef struct nodeLinea * pLinea;
typedef struct nodeEstacion * pEstacion;

typedef struct estacion{
	char linea;
	char* nombre;
	int id;
	long int diurnos;
	long int nocturnos;
}Testacion;

typedef struct dia{
	long int diurnos;
	long int nocturnos;
}tDia;								//HASTA ACA HAY QUE EDITAR

//COMPARE NO SE PONIA ACA, NO?
bornADT new(void);
int isEmpty(const bornADT b);
void toBegin(bornADT b);
int hasNext(bornADT b);
void add(ACA FALTA PARAMETRO, ACA FALTA PARAMETRO);

#endif
