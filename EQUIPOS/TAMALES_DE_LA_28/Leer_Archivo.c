#include <stdio.h>

int main()
{
    FILE *file;
    char lectura[50]; 
    file = fopen("myarchivo.txt","r");
    if (file==NULL)
    {
       printf ("Crea el archivo primero"); 
       return 1;
    }  

    while(!feof(file))
    { 
        fflush(stdin);       
        fgets(lectura,50,file);
        printf("%s",lectura);    
    }
    fclose(file);
    return 0;
}