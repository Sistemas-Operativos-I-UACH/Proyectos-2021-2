#include<stdio.h>
#include<dirent.h>
#include<ctype.h>  // Funcion is_digit 
#include<string.h>
#include<unistd.h>  // Funcion read()
#include<fcntl.h>  // Funcion open() - opciones de control de archivos (O_RDONLY)



void abrirArchivo(const char *nombreArchivo){
    
    char cmdline[255];
    FILE *punteroArchivo = NULL;
    int fd = open(nombreArchivo, O_RDONLY);  // File descriptor (index) - abre el archivo y regresa un -1 en caso de error.
    
    if (fd == -1)
    {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
    }
    else{
        char ch1;
        printf("\nArchivo (%s) abierto: ", nombreArchivo);
        do{
            ch1 = read(fd, &cmdline, 255);  // Copiamos contenido del archivo en arreglo cmdline 
            printf("%s\n", cmdline);
        }while(ch1 > 0);  // Si variable ch1 es 0 entonces alcanzo el final
        close(fd);
        printf("--------------------------------------------------------\n");
    }
}


int main(){

    DIR *directorio;
    struct dirent *dt;
    char rutaArchivo[255];
    
    directorio = opendir("/proc/");  // Especificamos el directorio proc

    
    while((dt = readdir(directorio)) != NULL){
        int esDirectorio=0;  // Variable para diferenciar entre directorios(1) y archivos(0)
        for(int i=0; i < strlen(dt->d_name); i++){  // si nombre del directorio/archivo contiene caracteres no numericos es directorio.
            if(!isdigit(dt->d_name[i])){
                esDirectorio=1;
                break;
            }
        }
        
        if(esDirectorio==0){  // Si todos los caracteres fueron numericos entonces es archivo y construye la ruta del archivo
            strcpy(rutaArchivo, "/proc/");
            strcat(rutaArchivo, dt->d_name);
            strcat(rutaArchivo, "/cmdline");
            printf("Reading %s", rutaArchivo);
            abrirArchivo(rutaArchivo);  // Llama a la funcion para leer el archivo
        }
    }
    
}