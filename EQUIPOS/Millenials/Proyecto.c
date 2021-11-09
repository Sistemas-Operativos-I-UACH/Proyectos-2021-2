#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procStat();
void cpuInfo();
void memInfo();
void procMisc();

int main(){

    cpuInfo();
    memInfo();
    procMisc();
    procStat();

    return 0;
}

void cpuInfo(){

    FILE *archivo; 
    char caracter;

    archivo = fopen("/proc/cpuinfo","r");
    if(archivo==NULL)
        printf("Error en la apartura del archivo\n");
    else
        printf("La informacion del CPU es: \n\n");
        while (feof(archivo)==0)
        {
            caracter = fgetc(archivo); 
            printf("%c",caracter);
        }
    
    fclose(archivo);
         
}

void memInfo(){

    FILE *archivo; 
    char caracter;

    archivo = fopen("/proc/meminfo","r");
    if(archivo==NULL)
        printf("Error en la apartura del archivo\n");
    else
        printf("La informacion de la memoria del sistema es: \n\n");
        while (feof(archivo)==0)
        {
            caracter = fgetc(archivo); 
            printf("%c",caracter);
        }
        
    fclose(archivo);

}

void procMisc(){

    FILE *archivo;
    char caracter;

    archivo = fopen("/proc/misc","r");
    if(archivo==NULL)
        printf("Error en la apartura del archivo\n");
    else
        printf("\nLa informacion de la memoria del sistema es: \n\n");
        while (feof(archivo)==0)
        {
            caracter = fgetc(archivo); 
            printf("%c",caracter);
        }
        
    fclose(archivo);

}

void procStat(){

    FILE *archivo; 
    char caracter;

    archivo = fopen("/proc/stat","r");
    if(archivo==NULL)
        printf("Error en la apartura del archivo\n");
    else
        printf("La informacion del stat es: \n\n");
        while (feof(archivo)==0)
        {
            caracter = fgetc(archivo);
            printf("%c",caracter);
        }
    
    fclose(archivo);

}