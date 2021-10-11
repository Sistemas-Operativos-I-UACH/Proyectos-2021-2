#include<stdio.h>
int main()
{
	char *archivo = "archivo.txt";
	FILE *abrir = fopen(archivo,"r");
	
	if(abrir == NULL)
	{
		printf("No se puede abrir el archivo\n");
		return 1;
	}
	char ch;
	while((ch = fgetc(abrir)) != EOF)
	{
		putchar(ch);
	}
	fclose(abrir);
	return 0;
}
