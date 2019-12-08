TRABAJO FINAL PROGRAMACIÓN IMPERATIVA 	        

Integrantes:	Conca, Maria Victoria
		Limachi, Desiree
		Prado Torres, Macarena				        


1- Una vez posicionado en el directorio en el que se encuentran los archivos fuente y de encabezado entregados utilizar el siguiente comando para generar el ejecutable "TPEFinal":

   $> make


>> Ejecutar el programa:

1- Ejecutar el siguiente comando en consola:

   $> ./TPEFinal *file1* *file2*

Donde *file1* y *file2* representan el PATH de los archivos .csv de los cuales serán extraídos los datos.

Los archivos serán "provincias.csv", "nacimientos.csv" :
	
   $> ./TPEFinal provincias.csv nacimientos.csv


>> Errores:

1- "ERROR: Incorrect number of parameters. Files nacimientos.csv and provincias.csv are expected as parameters.": la cantidad de argumentos al momento de ejecutar el programa es incorrecta.

2- "ERROR: File could not be opened": algún PATH ingresado como argumento es incorrecto.

3- "ERROR: No space memory left": no se realizó el espacio en memoria.


Una vez ejecutado correctamente el programa se crearán 3 archivos .csv correspondientes a cada query:

Query1: Cantidad de nacimientos por provincia, ordenados de forma alfabética por provincias.
Query2: Cantidad de nacimientos por género durante cada año, ordenados de forma ascendente por año.
Query3:	Porcentaje de nacimientos por provincia, ordenados de forma descendente por porcentaje, el cual se encuentra truncado. 
    
