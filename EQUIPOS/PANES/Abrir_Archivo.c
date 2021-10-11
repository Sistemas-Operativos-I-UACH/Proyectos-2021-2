#include <stdio.h>
#include <string.h>

int main(){

	FILE *manejador_archivo = NULL;
	char caracter[255];
	
	manejador_archivo = fopen ("/home/pan/Desktop/file.txt","r");	

	if (manejador_archivo == NULL){
		printf ("No fue posible abrir el archivo.");
		return -1;
	}
	
	while (feof(manejador_archivo) == 0){
		fgets(caracter,255,manejador_archivo);
		printf ("%s",caracter);
	}
	
	fclose (manejador_archivo);
	
	return 0;
}
