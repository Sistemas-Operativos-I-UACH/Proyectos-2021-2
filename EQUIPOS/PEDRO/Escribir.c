#include<stdio.h>
int main(){
    char cadena[255];
    FILE *punteroArchivo = fopen("archivo.txt", "a");
    if (punteroArchivo == NULL){
        printf("ERROR: Archivo inexistente\n");
        return 1;
    }
    printf("Ingrese el texto: ");
    fgets(cadena,255,stdin);
    fprintf(punteroArchivo,"%s\n",cadena);
    fclose(punteroArchivo);
    return 0;
}
