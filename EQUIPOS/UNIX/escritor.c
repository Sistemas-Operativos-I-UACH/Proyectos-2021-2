#include<stdio.h>
#include<stdlib.h>

void lectura(FILE *);
void escritura(FILE *);

int main(){

    FILE *archivo;
    char caracter;

    //lectura(archivo);
    escritura(archivo);

    return 0;
}

void lectura(FILE *archivo){

    char caracter;

    archivo=fopen("archivo.txt", "r");

    if(archivo==NULL){
        printf("El archivo que desea abrir no existe\n");
    }else{

        printf("El contenido del archivo es:\n\n");

        while (feof(archivo)==0){

            caracter=fgetc(archivo);
            printf("%c", caracter);
        }
        
    }

    fclose(archivo);
}

void escritura(FILE *archivo){

    char caracter;

    archivo=fopen("archivo.txt", "a");

    if(archivo==NULL){

        printf("El archivo que desea abrir no existe\n");

    }else{

        printf("Escribe en el archivo lo siguiente:\n\n");
        while ( (caracter=getchar())!='\n' ){ //Escribimos la info hasta hacer un salto de linea
            printf("%c", fputc(caracter, archivo));

        }   
    }

    fclose(archivo);
}