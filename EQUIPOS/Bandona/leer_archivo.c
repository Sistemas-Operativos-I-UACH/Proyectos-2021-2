#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	FILE *f = fopen("leer_en_archivo.txt" , "w");
	char texto[255];
	
	printf("Ingresa el texto: \n");
	scanf("%[^\n]",texto);
	
	if(f==NULL)
	{
		printf("Error al abrir el archivo\n");
		exit(1);
	}
	
	fprintf(f, "%s",texto);
	fclose(f);
	exit(0);
}
