#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // Libreria encargada de las entidades en un directorio
#include <string.h>
#include <sys/stat.h>

int is_directory(const char*);
void procesoArchivo(char *archivo);

int main(){

    /* En *pDirent habrá información sobre el archivo que se está "sacando" a cada momento */
    struct dirent *pDirent;
    /* Con un puntero a DIR abriremos el directorio */    
    DIR *pDir;
    char dirname[200];

    /* Empezaremos a leer en el directorio actual */
    pDir = opendir ("/proc/");

    /* Verificamos que no haya error */
    if(pDir == NULL){
        printf("No se puede abrir el directorio /proc");
        return 1;
    }

    /* Una vez nos aseguramos de que no hay error */
    /* Leemos uno a uno todos los archivos del directorio*/
    while((pDirent = readdir(pDir)) != NULL){
        printf("Leyendo %s\n", pDirent->d_name);
        if(is_directory(pDirent->d_name)){
            strcpy(dirname, "/proc/");
            strcat(dirname, pDirent->d_name);
            strcat(dirname, "/cmdline");
            printf("Leyendo %s\n", dirname);
            procesoArchivo(pDirent->d_name);
            
        }
    }

    closedir (pDir);

    return 0;
}

int is_directory(const char* target){
    struct stat statbuf;
    stat(target, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

void procesoArchivo(char *archivo){
  FILE *fich;
  long ftam;

  fich=fopen(archivo, "r");
  if (fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      printf ("%30s (%ld bytes)\n", archivo, ftam);
    }
  else
    /* Si ha pasado algo, sólo decimos el nombre */
    printf ("%30s (No info.)\n", archivo);
}