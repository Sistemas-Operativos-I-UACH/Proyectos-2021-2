#include <stdio.h>
#include <string.h>
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
    fgets(buffer,255,stdin); //Es segura pero lee el salto de linea...
    //gets(buffer); Lee sin salto de linea pero es peligrosa - buffer overflow..

    //buffer[strlen(buffer) - 1] = '\0'; //Elimina salto de linea - necesita libreria string.h
    strtok(buffer, "\n"); //Elimina salto de linea - marca un warning




    fprintf(file,"%s",buffer);
    fclose(file);
    return 0;
}