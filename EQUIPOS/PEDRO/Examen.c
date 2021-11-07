#include<stdio.h>
#include<dirent.h>
#include<ctype.h> 
#include<string.h>
void abrirNombre(char *nombreArchivo){
    FILE *punteroArchivo = fopen(nombreArchivo, "r");
    char proc[255];
    if (punteroArchivo == NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
    }
    else{
        fgets(proc,255,punteroArchivo);  
        printf("Nombre: %s",proc);
        fclose(punteroArchivo);
    }
}
void abrirMemoria(char *nombreArchivo){
    FILE *punteroArchivo = fopen(nombreArchivo, "r");
    char proc[255];
    long int no,si;
    if (punteroArchivo == NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
    }
    else{
        fgets(proc,255,punteroArchivo);
        sscanf(proc,"%ld %ld",&no,&si);
        printf("Memoria: %ld kB\n",si*4);
        fclose(punteroArchivo);
    }
}
void abrirPriority(char *nombreArchivo){
    FILE *punteroArchivo = fopen(nombreArchivo, "r");
    char proc[255],no[255];
    int si;
    if (punteroArchivo == NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
    }
    else{
        fgets(proc,255,punteroArchivo);
        sscanf(proc,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d",no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,&si);
        printf("Prioridad: %d\n",si);
        fclose(punteroArchivo);
    }
}
void kernelOno(char *nombreArchivo){
    FILE *punteroArchivo = fopen(nombreArchivo, "r");
    char proc;
    if (punteroArchivo==NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
    }
    else{
        if(fscanf(punteroArchivo,"%c",&proc)==EOF){ 
            printf("Proceso de Kernel\n"); 
        }else{
            printf("Proceso de Usuario\n"); 
        }
        fclose(punteroArchivo); 
    }    
}
void MemTotal(char *nombreArchivo){
    FILE *punteroArchivo = fopen(nombreArchivo, "r");
    char proc[255];
    if (punteroArchivo == NULL){
        printf("ERROR: No se pudo abrir el archivo\n");
    }
    else{
        fgets(proc,255,punteroArchivo);  
        printf("%s\n",proc);
        fclose(punteroArchivo);
    }
}
int main(){
    DIR *directorio = opendir("/proc/");
    struct dirent *dt;
    char rutaArchivo[255];
    if(directorio == NULL){
        printf("Error al abrir /proc/\n");
    }else{
        while((dt = readdir(directorio)) != NULL){
        int esDirectorio=0;  
        for(int i=0; i < strlen(dt->d_name); i++){  
            if(!isdigit(dt->d_name[i])){
                esDirectorio=1;
                break;
            }
        }
        if(esDirectorio==0){ 
            printf("ID: %s\n", dt->d_name);

            strcpy(rutaArchivo, "/proc/");
            strcat(rutaArchivo, dt->d_name);
            strcat(rutaArchivo, "/comm");
            abrirNombre(rutaArchivo); 

            strcpy(rutaArchivo, "/proc/");
            strcat(rutaArchivo, dt->d_name);
            strcat(rutaArchivo, "/statm");
            abrirMemoria(rutaArchivo); 

            strcpy(rutaArchivo, "/proc/");
            strcat(rutaArchivo, dt->d_name);
            strcat(rutaArchivo, "/stat");
            abrirPriority(rutaArchivo); 

            strcpy(rutaArchivo, "/proc/");
            strcat(rutaArchivo, dt->d_name);
            strcat(rutaArchivo, "/cmdline");
            kernelOno(rutaArchivo); 
            printf("--------------------------------------------------------\n");
        }
        }
    }
    MemTotal("/proc/meminfo"); 
    closedir(directorio);
    return 0;
}