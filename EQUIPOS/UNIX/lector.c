#include<stdio.h>
#include<stdlib.h>/*Control de procesos*/

/**/

int main()
{

    FILE *archivo; /*Objeto capaz de almacenar informacion*/
    char caracter;

    archivo = fopen("archivo.txt","r");
    if(archivo==NULL)
        printf("Error en la apartura del archivo\n");

    else
        printf("El contenido del archivo es: \n\n");
        while (feof(archivo)==0)/*feof: Comprueba el indicador final del archivo*/
        {
            caracter = fgetc(archivo); /*Obtiene un caracter a la vez*/
            printf("%c",caracter);
        }
        
    fclose(archivo);
    getch();

    return 0;

}

