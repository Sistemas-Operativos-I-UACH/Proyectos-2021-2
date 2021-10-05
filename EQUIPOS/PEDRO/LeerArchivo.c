#include<stdio.h>

int main(){

    const char *nombreArchivo = "archivo.txt";
    char cadena[255];
    FILE *punteroArchivo = fopen("archivo.txt", "r");

    if (punteroArchivo == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
        return 1;
    }
    
    while (feof(punteroArchivo) == 0 )
    {
        fgets(cadena, 255, punteroArchivo);
        fflush(stdin);
        puts(cadena);
    }
    
    fclose(punteroArchivo);
    return 0;
}