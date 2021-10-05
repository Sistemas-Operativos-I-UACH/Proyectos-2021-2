#include <stdio.h>
//Escribe texto en un archivo
int main()
{
    FILE *file;
    char buffer[255]; 
    file = fopen("myarchivo.txt","w");
    if (file==NULL)
    {
       printf ("Crea el archivo primero"); 
       return 1;
    }
    printf("Ingrese el texto: \n");
    fgets(buffer,255,stdin);
    fprintf(file,"%s",buffer);
    fclose(file);
    return 0;
}