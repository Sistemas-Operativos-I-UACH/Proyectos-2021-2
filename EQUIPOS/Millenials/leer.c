#include<stdio.h>

int main(){
    FILE *archivo = fopen("archivo.txt","r");
    char linea[200];

    if(archivo!=NULL){
        while(!feof(archivo)){
            if(fgets(linea,200,archivo)!=NULL){
                printf("%s",linea);
            }
        }
    }
    fclose(archivo);
}