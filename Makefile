COMPILER=gcc
OUTPUT_FILE= TPFinal

all: compile
	rm -r *.o *.h.gch

compile: ADT.o 
	$(COMPILER) -pedantic -std=c99 -Wall -fsanitize=address -o $(OUTPUT_FILE) main.c ADT.o

ADT.o: bornADT.c 
	$(COMPILER) -c bornADT.c

clean:
	rm -r $(OUTPUT_FILE) *.o
	
	
//no se que es clean por eso lo deje, ahi modifique lo de all y el adt porque no hay que repetir lo mismo de arriba
//otro tema, nos quedaria modificar el nombre del main y definir como llamarlo porque exigen entendimiento de nombres 
//a los archivos, o algo asi
