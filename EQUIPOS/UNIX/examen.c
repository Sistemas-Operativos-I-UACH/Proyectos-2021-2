#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // Libreria encargada de las entidades en un directorio
#include <string.h>
#include <sys/stat.h>

void menu(); //Menu donde el usuario elige que informacion desea obtener

int is_directory(const char*); //Funcion para verificar si es un directorio

void procesoArchivo(char *archivo); //Dice el tamaño del archivo

int main(){

    menu(); //Llamada a funcion menu

    return 0;
}

int is_directory(const char* target){//Comprobamos si es un directorio
    struct stat statbuf;
    stat(target, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

void menu(){

    int opcion; //Variable que almacena el valor de la opcion que el usuario ingresa

    /* En *pDirent habrá información sobre el archivo que se está "sacando" a cada momento */
    struct dirent *pDirent;
    /* Con un puntero a DIR abriremos el directorio */    
    DIR *pDir;
    char dirname[200];

 do{

        printf("\n  Menu de opciones");
        printf("\n1. Procesos activos del sistema");
        printf("\n2. Procesos de kernel");
        printf("\n3. Procesos de usuario");
        printf("\n4. Memoria con la que cuenta el sistema");
        printf("\n5. Salir");
        printf("\nIndique la opcion: ");
        scanf("%d",&opcion);

        switch(opcion){

            case 1:

                /* Empezaremos a leer en el directorio actual */
                pDir = opendir ("/proc/self/");

                /* Verificamos que no haya error */
                if(pDir == NULL){
                    printf("No se puede abrir el directorio /proc/self/");
                }

                /* Una vez nos aseguramos de que no hay error */
                /* Leemos uno a uno todos los archivos del directorio*/
                while((pDirent = readdir(pDir)) != NULL){
                    printf("Leyendo %s\n", pDirent->d_name);

                    if(is_directory(pDirent->d_name)){
                        strcpy(dirname, "/proc/self/");
                        strcat(dirname, pDirent->d_name);
                        printf("Leyendo %s\n", dirname);
                        procesoArchivo(pDirent->d_name);            
                    }
                }

                closedir (pDir);

            break;

            case 2:

                /* Empezaremos a leer en el directorio actual */
                pDir = opendir ("/proc/sys/kernel/");

                /* Verificamos que no haya error */
                if(pDir == NULL){
                    printf("No se puede abrir el directorio /proc/sys/kernel/");
                }

                /* Una vez nos aseguramos de que no hay error */
                /* Leemos uno a uno todos los archivos del directorio*/
                while((pDirent = readdir(pDir)) != NULL){
                    printf("Leyendo %s\n", pDirent->d_name);

                    if(is_directory(pDirent->d_name)){
                        strcpy(dirname, "/proc/sys/kernel/");         
                        /*/proc/sys/kernel
                    
                        */
                        strcat(dirname, pDirent->d_name);
                        printf("Leyendo %s\n", dirname);   
                        procesoArchivo(pDirent->d_name);         
                    }
                }

                closedir (pDir);

            break;

            case 3:

                /* Empezaremos a leer en el directorio actual */
                pDir = opendir ("/proc/sys/user/");

                /* Verificamos que no haya error */
                if(pDir == NULL){
                    printf("No se puede abrir el directorio /proc/sys/user/");
                }

                /* Una vez nos aseguramos de que no hay error */
                /* Leemos uno a uno todos los archivos del directorio*/
                while((pDirent = readdir(pDir)) != NULL){
                    printf("Leyendo %s\n", pDirent->d_name);

                    if(is_directory(pDirent->d_name)){
                        strcpy(dirname, "/proc/sys/user/");
                        strcat(dirname, pDirent->d_name);
                        printf("Leyendo %s\n", dirname); 
                        procesoArchivo(pDirent->d_name);           
                    }
                }

                closedir (pDir);
            
            break;

            case 4:

                //Prototipo de comando cat

                FILE *archivo; /*Objeto capaz de almacenar informacion*/
                char caracter;

                archivo = fopen("/proc/meminfo","r");
                if(archivo==NULL)
                    printf("Error en la apartura del archivo\n");
                else
                    printf("La informacion de la memoria del sistema es: \n\n");
                    while (feof(archivo)==0)/*feof: Comprueba el indicador final del archivo*/
                    {
                        caracter = fgetc(archivo); /*Obtiene un caracter a la vez*/
                        printf("%c",caracter);
                    }
        
                fclose(archivo);
         
            break;

            default:
            break;
        }

    }while(opcion!=5);
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
