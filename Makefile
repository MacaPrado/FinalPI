COMPILER=gcc
OUTPUT_FILE=FinalPI

all: ADT.o
	$(COMPILER) -Wall -pedantic -std=c99 -fsanitize=address -o $(OUTPUT_FILE) born.c ADT.o

ADT.o: bornADT.c
	$(COMPILER) -Wall -pedantic -std=c99 -fsanitize=address -c bornADT.c

clean:
	rm -r $(OUTPUT_FILE) *.o