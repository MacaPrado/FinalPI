COMPILER=gcc
OUTPUT_FILE=TPEFinal

all: bornADT.c
	$(COMPILER) -Wall -pedantic -std=c99 -fsanitize=address -o $(OUTPUT_FILE) bornMain.c bornADT.c

clean:
	rm -r $(OUTPUT_FILE) *.o
