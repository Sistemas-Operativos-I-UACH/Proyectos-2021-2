#include <stdio.h>
#include <stdlib.h>

int main (void){
	
	FILE *f = fopen ("file.txt","w");
	char buff [255];
	
	printf ("Ingresa el texto: ");
	fgets (buff,255,stdin);
	
	if (f == NULL){
		printf ("No se encontro el archivo. \n");
		return 1; 
	}
	
	fprintf (f,"%s",buff);
	
	fclose (f);
	
	return 0;
}
