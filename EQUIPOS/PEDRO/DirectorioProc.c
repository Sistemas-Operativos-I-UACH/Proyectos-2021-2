#include<stdio.h>
#include<dirent.h>
#include<ctype.h>
#include<string.h>

void abrirArchivo(char *nombreArchivo){

    char cadena[255];
    FILE *punteroArchivo = fopen(nombreArchivo, "r");

    if (punteroArchivo == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
    }
    
    while (feof(punteroArchivo) == 0 )
    {
        fgets(cadena, 255, punteroArchivo);
        puts(cadena);
    }
    
    fclose(punteroArchivo);
}


int main(){

    DIR *directorio;
    struct dirent *dt;
    
    directorio=opendir("/proc/");

    int esDirectorio=0;
    while((dt=readdir(directorio)) != NULL){
        for(int i=0; i < strlen(dt->d_name); i++){
            if(!isdigit(dt->d_name[i])){
                
                esDirectorio=1;
                break;
            }
            else{
                esDirectorio=0;
            }
        }
        
        if(esDirectorio==0){
            puts(dt->d_name);
            abrirArchivo(dt->d_name);
        }
    }
    
}