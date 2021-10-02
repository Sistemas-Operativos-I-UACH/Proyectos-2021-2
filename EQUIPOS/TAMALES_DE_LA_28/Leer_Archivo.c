#include <stdio.h>

int main()
{
    FILE *file;
    char lectura[300];
    file = fopen("myarchivo.txt","r");
    if (file==NULL)
    {
       printf ("Crea el archivo primero"); 
       return 1;
    }  

    while(!feof(file))
    {        
        fgets(lectura,300,file);
    }
    printf("Archvio leido\n%s",lectura);

    fclose(file);
    return 0;
}